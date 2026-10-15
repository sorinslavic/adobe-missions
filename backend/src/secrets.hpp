// Secrets that the vault hands out, and a way to check flags.
#pragma once

#include <string>

const int NUMBER_OF_MISSIONS = 8;

std::string bootLogToken();
std::string tooManyRequestsToken();
std::string brandApprovalToken();
std::string departmentApprovalToken();
std::string vaultFlagToken();

// True when `submittedFlag` is the correct flag for mission `missionNumber`.
bool isCorrectFlag(int missionNumber, const std::string& submittedFlag);
