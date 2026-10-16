// Connects each URL of the vault to the code that handles it.

#include "http_routes.hpp"

#include <climits>
#include <mutex>

#include "asset_requests.hpp"
#include "brand_color_check.hpp"
#include "department_check.hpp"
#include "json.hpp"
#include "secrets.hpp"
#include "shop.hpp"

using nlohmann::json;

namespace {

const std::string TEST_REPORT_PATH = "data/test-report.json";

// The database and the wallet are used by one request at a time.
std::mutex oneRequestAtATime;

void sendJson(httplib::Response& response, int status, const json& body) {
    response.status = status;
    response.set_content(body.dump(), "application/json");
}

// Reads the request body as a JSON object. Returns false if it isn't one.
bool readJsonBody(const httplib::Request& request, json& body) {
    body = json::parse(request.body, nullptr, false);
    return body.is_object();
}

bool fitsInAnInt(long long number) {
    return number >= INT_MIN && number <= INT_MAX;
}

// GET /api/progress
void showProgress(VaultDatabase& database, httplib::Response& response) {
    sendJson(response, 200, {{"solved", database.solvedMissions()}, {"total", NUMBER_OF_MISSIONS}});
}

// POST /api/flags   {"mission": 3, "flag": "adbe{...}"}
void checkFlag(VaultDatabase& database, const httplib::Request& request, httplib::Response& response) {
    json body;
    if (!readJsonBody(request, body) || !body["mission"].is_number_integer() || !body["flag"].is_string()) {
        sendJson(response, 400, {{"error", "Send a mission number and a flag."}});
        return;
    }

    int missionNumber = body["mission"];
    std::string flag = body["flag"];

    if (isCorrectFlag(missionNumber, flag)) {
        database.markMissionSolved(missionNumber);
        sendJson(response, 200, {{"correct", true}});
    } else {
        sendJson(response, 200, {{"correct", false}});
    }
}

// POST /api/asset-requests   {"name": "...", "email": "...", "asset_type": "...", "reason": "..."}
void receiveAssetRequest(VaultDatabase& database, RequestRateLimiter& assetRequestLimiter,
                         const httplib::Request& request, httplib::Response& response) {
    if (!assetRequestLimiter.allowRequest()) {
        response.set_header("X-Adobe-Flag", tooManyRequestsToken());
        sendJson(response, 429, {{"error", "Too many requests."}});
        return;
    }

    json body = json::parse(request.body, nullptr, false);
    ValidationResult validation = validateAssetRequest(body);
    if (!validation.isValid) {
        sendJson(response, 400, {{"error", validation.errorMessage}});
        return;
    }

    database.saveAssetRequest(body.dump());
    sendJson(response, 201, {{"message", "Request received."}});
}

// POST /api/brand-check   {"color": "rgb(235, 16, 0)"}
void checkBrandColor(const httplib::Request& request, httplib::Response& response) {
    json body;
    if (!readJsonBody(request, body) || !body["color"].is_string()) {
        sendJson(response, 400, {{"error", "Send a color."}});
        return;
    }

    if (isAdobeRed(body["color"])) {
        sendJson(response, 200, {{"approved", true}, {"flag", brandApprovalToken()}});
    } else {
        sendJson(response, 200, {{"approved", false}, {"required", ADOBE_RED_AS_RGB}});
    }
}

// GET /api/department-check
void checkDepartmentReadiness(httplib::Response& response) {
    bool departmentAccepted = vaultAcceptsDepartment();
    bool departmentTestPassed = testReportHasPassingDepartmentTest(TEST_REPORT_PATH);

    json result = {{"departmentAccepted", departmentAccepted}, {"departmentTestPassed", departmentTestPassed}};
    if (departmentAccepted && departmentTestPassed) {
        result["flag"] = departmentApprovalToken();
    }
    sendJson(response, 200, result);
}

// GET /api/shop
void showShop(VaultDatabase& database, httplib::Response& response) {
    json items = json::array();
    for (const ShopItem& item : shopCatalog()) {
        items.push_back({{"id", item.id}, {"name", item.name}, {"kind", item.kind}, {"price", item.price}});
    }
    sendJson(response, 200, {{"credits", database.credits()}, {"items", items}});
}

// POST /api/shop/checkout   {"item": "icon-pack", "quantity": 2}
void checkoutShop(VaultDatabase& database, const httplib::Request& request, httplib::Response& response) {
    json body;
    if (!readJsonBody(request, body) || !body["item"].is_string() || !body["quantity"].is_number_integer()) {
        sendJson(response, 400, {{"error", "Send an item and a whole-number quantity."}});
        return;
    }

    const ShopItem* item = findShopItem(body["item"]);
    if (item == nullptr) {
        sendJson(response, 404, {{"error", "The shop doesn't sell that item."}});
        return;
    }

    long long requestedQuantity = body["quantity"];
    if (!fitsInAnInt(requestedQuantity)) {
        sendJson(response, 400, {{"error", "That quantity is not a valid number."}});
        return;
    }

    CheckoutResult result = checkout(database.credits(), *item, static_cast<int>(requestedQuantity));
    if (!result.succeeded) {
        sendJson(response, 400, {{"error", result.message}, {"credits", result.creditsAfterCheckout}});
        return;
    }

    database.setCredits(result.creditsAfterCheckout);
    json receipt = {{"message", result.message}, {"credits", result.creditsAfterCheckout}};
    if (item->id == VAULT_FLAG_ITEM_ID) {
        receipt["download"] = vaultFlagToken();
    }
    sendJson(response, 200, receipt);
}

}  // namespace

void serveWebsiteFiles(httplib::Server& server, const std::string& folder) {
    server.set_mount_point("/", folder);
    // Always send the newest version of each file, so edits show up after a refresh.
    server.set_file_request_handler([](const httplib::Request&, httplib::Response& response) {
        response.set_header("Cache-Control", "no-store");
    });
}

void addApiRoutes(httplib::Server& server, VaultDatabase& database, RequestRateLimiter& assetRequestLimiter) {
    server.Get("/api/progress", [&](const httplib::Request&, httplib::Response& response) {
        std::lock_guard<std::mutex> lock(oneRequestAtATime);
        showProgress(database, response);
    });

    server.Post("/api/flags", [&](const httplib::Request& request, httplib::Response& response) {
        std::lock_guard<std::mutex> lock(oneRequestAtATime);
        checkFlag(database, request, response);
    });

    server.Post("/api/asset-requests", [&](const httplib::Request& request, httplib::Response& response) {
        std::lock_guard<std::mutex> lock(oneRequestAtATime);
        receiveAssetRequest(database, assetRequestLimiter, request, response);
    });

    server.Post("/api/brand-check", [&](const httplib::Request& request, httplib::Response& response) {
        checkBrandColor(request, response);
    });

    server.Get("/api/department-check", [&](const httplib::Request&, httplib::Response& response) {
        checkDepartmentReadiness(response);
    });

    server.Get("/api/shop", [&](const httplib::Request&, httplib::Response& response) {
        std::lock_guard<std::mutex> lock(oneRequestAtATime);
        showShop(database, response);
    });

    server.Post("/api/shop/checkout", [&](const httplib::Request& request, httplib::Response& response) {
        std::lock_guard<std::mutex> lock(oneRequestAtATime);
        checkoutShop(database, request, response);
    });
}
