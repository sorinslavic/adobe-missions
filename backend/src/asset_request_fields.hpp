// The fields that a brand asset request may contain.
// The form in frontend/index.html sends these fields to the vault.
#pragma once

#include <string>
#include <vector>

// Every field the vault accepts. Anything else is rejected.
inline const std::vector<std::string> ALLOWED_ASSET_REQUEST_FIELDS = {
    "name",
    "email",
    "asset_type",
    "reason",
};

// Fields that must be filled in.
inline const std::vector<std::string> REQUIRED_ASSET_REQUEST_FIELDS = {
    "name",
    "email",
    "asset_type",
    "reason",
};
