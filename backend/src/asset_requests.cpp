// Checks that a brand asset request is complete and only contains known fields.

#include "asset_requests.hpp"

#include <algorithm>

#include "asset_request_fields.hpp"

namespace {

bool isAllowedField(const std::string& fieldName) {
    const auto& allowed = ALLOWED_ASSET_REQUEST_FIELDS;
    return std::find(allowed.begin(), allowed.end(), fieldName) != allowed.end();
}

bool isFilledIn(const nlohmann::json& request, const std::string& fieldName) {
    if (!request.contains(fieldName) || !request[fieldName].is_string()) {
        return false;
    }
    return !request[fieldName].get<std::string>().empty();
}

}  // namespace

ValidationResult validateAssetRequest(const nlohmann::json& request) {
    if (!request.is_object()) {
        return {false, "The request must be a JSON object."};
    }

    for (const auto& field : request.items()) {
        if (!isAllowedField(field.key())) {
            return {false, "unknown field: " + field.key()};
        }
    }

    for (const std::string& fieldName : REQUIRED_ASSET_REQUEST_FIELDS) {
        if (!isFilledIn(request, fieldName)) {
            return {false, "missing field: " + fieldName};
        }
    }

    return {true, ""};
}
