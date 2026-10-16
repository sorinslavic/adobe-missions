// Connects each URL of the vault to the code that handles it.
#pragma once

#include "database.hpp"
#include "httplib.h"
#include "request_rate_limiter.hpp"

// Serves the website files (HTML, CSS, JavaScript, images) from a folder.
void serveWebsiteFiles(httplib::Server& server, const std::string& folder);

// Adds every /api/... URL to the server.
void addApiRoutes(httplib::Server& server, VaultDatabase& database, RequestRateLimiter& assetRequestLimiter);
