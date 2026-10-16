// Checks that a brand asset request is complete and only contains known fields.
#pragma once

#include <string>

#include "json.hpp"

struct ValidationResult {
    bool isValid;
    std::string errorMessage;
};

ValidationResult validateAssetRequest(const nlohmann::json& request);
