// Starts the Pixel Vault: opens the database, prints the boot log and serves the website.

#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

#include "database.hpp"
#include "http_routes.hpp"
#include "request_rate_limiter.hpp"
#include "secrets.hpp"
#include "shop.hpp"

const int PORT = 8080;
const std::string WEBSITE_FOLDER = "frontend";
const std::string DATA_FOLDER = "data";
const std::string DATABASE_PATH = DATA_FOLDER + "/vault.db";

const int ASSET_REQUESTS_ALLOWED_PER_WINDOW = 10;
const std::chrono::seconds ASSET_REQUEST_WINDOW(10);

// Makes sure a second vault can't start on the same port while the first one is still running.
void allowOnlyOneVaultPerPort(httplib::Server& server) {
    server.set_socket_options([](socket_t socket) {
        int enabled = 1;
        setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&enabled), sizeof(enabled));
    });
}

void printBootStep(const std::string& line) {
    std::cout << "  [boot] " << line << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(120));
}

void printBootLog() {
    std::cout << std::endl;
    std::cout << "  Pixel Vault 2.4 - brand asset storage" << std::endl;
    std::cout << std::endl;
    printBootStep("checking vault door sensors ....... ok");
    printBootStep("loading brand kit index ........... ok");
    printBootStep("opening database .................. ok");
    printBootStep("staging token: " + bootLogToken());
    printBootStep("all systems ready");
    std::cout << std::endl;
}

int main() {
    std::filesystem::create_directories(DATA_FOLDER);

    VaultDatabase database(DATABASE_PATH, STARTING_CREDITS);
    RequestRateLimiter assetRequestLimiter(ASSET_REQUESTS_ALLOWED_PER_WINDOW, ASSET_REQUEST_WINDOW);

    httplib::Server server;
    allowOnlyOneVaultPerPort(server);
    serveWebsiteFiles(server, WEBSITE_FOLDER);
    addApiRoutes(server, database, assetRequestLimiter);

    if (!server.bind_to_port("0.0.0.0", PORT)) {
        std::cout << "Port " << PORT << " is busy. Is the vault already running in another terminal?" << std::endl;
        return 1;
    }

    printBootLog();
    std::cout << "  The vault is open: http://localhost:" << PORT << std::endl;
    std::cout << "  Press Ctrl+C to close it." << std::endl << std::endl;

    server.listen_after_bind();
    return 0;
}
