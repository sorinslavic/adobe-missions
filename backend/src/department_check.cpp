// Checks whether the vault is ready to handle departments on asset requests.

#include "department_check.hpp"

#include <fstream>

#include "json.hpp"

using nlohmann::json;

bool requestHasDepartment(const std::string& assetRequestAsJson) {
    json request = json::parse(assetRequestAsJson, nullptr, false);
    if (!request.is_object() || !request.contains("department")) {
        return false;
    }
    const json& department = request["department"];
    return department.is_string() && !department.get<std::string>().empty();
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
