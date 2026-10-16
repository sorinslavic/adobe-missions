// Checks whether the vault is ready to handle departments on asset requests.
#pragma once

#include <string>

// True when the vault accepts an asset request that includes a "department".
bool vaultAcceptsDepartment();

// True when the test report lists a passing test with "department" in its name.
bool testReportHasPassingDepartmentTest(const std::string& testReportPath);
