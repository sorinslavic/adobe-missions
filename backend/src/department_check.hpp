// Checks whether the vault is ready to handle departments on asset requests.
#pragma once

#include <string>

// True when the most recent asset request (as JSON text) has a filled-in "department".
bool requestHasDepartment(const std::string& assetRequestAsJson);

// True when the test report lists a passing test with "department" in its name.
bool testReportHasPassingDepartmentTest(const std::string& testReportPath);
