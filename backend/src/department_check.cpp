// Checks whether the vault is ready to handle departments on asset requests.

#include "department_check.hpp"

#include <fstream>

#include "asset_requests.hpp"
#include "json.hpp"

using nlohmann::json;

bool vaultAcceptsDepartment() {
    json sampleRequest = {
        {"name", "Sample Intern"},
        {"email", "intern@example.com"},
        {"asset_type", "Logo pack"},
        {"reason", "Readiness check"},
        {"department", "Creative Cloud"},
    };
    return validateAssetRequest(sampleRequest).isValid;
}

bool testReportHasPassingDepartmentTest(const std::string& testReportPath) {
    std::ifstream reportFile(testReportPath);
    if (!reportFile) {
        return false;
    }

    json report = json::parse(reportFile, nullptr, false);
    if (!report.is_object() || !report.contains("tests")) {
        return false;
    }

    for (const json& test : report["tests"]) {
        std::string testName = test.value("name", "");
        bool passed = test.value("passed", false);
        if (passed && testName.find("department") != std::string::npos) {
            return true;
        }
    }
    return false;
}
