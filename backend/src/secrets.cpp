// Secrets are stored scrambled, so they never appear as plain text in the code.
// Flags are checked by comparing fingerprints (SHA-256 hashes), never the flags themselves.

#include "secrets.hpp"

#include <vector>

#include "picosha2.h"

namespace {

const std::string SCRAMBLE_KEY = "brand-kit";

std::string unscramble(const std::vector<int>& scrambledBytes) {
    std::string text;
    for (size_t position = 0; position < scrambledBytes.size(); position++) {
        char keyLetter = SCRAMBLE_KEY[position % SCRAMBLE_KEY.size()];
        text += static_cast<char>(scrambledBytes[position] ^ keyLetter);
    }
    return text;
}

std::string fingerprintOf(const std::string& text) {
    return picosha2::hash256_hex_string(text);
}

// One fingerprint per mission, in mission order (0 to 7).
const std::vector<std::string> FLAG_FINGERPRINTS = {
    "5c74f547a086b6d421f6027f183147b3db16947271dcf9f8cb3f413d8a302a7f",
    "b77433eb7c1a953d09bb4d630bea43657a7753efb72f372d1d9ed9cc3f7edbe7",
    "b55e46e89b152bb637510b3b963eed6104c3cc737e13951d1df1913eed17f61d",
    "4f701e2b8bfcf75f9d09ec0660a3306e6ed73b53d8d05e11774dfed57625f34f",
    "00f925ee9226e367295017d2750ac5d881dbe67e1db2682168fb7de4b0fdbef5",
    "a51508bd317d818c8850a8bb75b74e9737b012a620e2656a5624585e22fbbf66",
    "369baa31e480c4561f41c44e3be97ec73ac750f95841e1660eeea9bbb089ac97",
    "64522fcecb8ecaf93ccf59c624a0ff9db77dce48e3e72711233dc51416e40a21",
};

}  // namespace

std::string bootLogToken() {
    return unscramble({3, 22, 3, 11, 31, 28, 7, 5, 1, 17, 6, 19, 90, 16, 29, 25, 20});
}

std::string tooManyRequestsToken() {
    return unscramble({3, 22, 3, 11, 31, 93, 25, 90, 25, 83, 65, 19, 93, 59, 93, 25, 89, 9});
}

std::string brandApprovalToken() {
    return unscramble({3, 22, 3, 11, 31, 75, 90, 27, 71, 4, 30, 24, 49, 9, 25, 12, 88, 23, 31});
}

std::string departmentApprovalToken() {
    return unscramble({3, 22, 3, 11, 31, 25, 13, 29, 71, 16, 45, 82, 8, 2, 30, 8, 29, 7, 31});
}

std::string vaultFlagToken() {
    return unscramble({3, 22, 3, 11, 31, 65, 90, 14, 28, 22, 0, 81, 94, 9, 80});
}

bool isCorrectFlag(int missionNumber, const std::string& submittedFlag) {
    bool missionExists = missionNumber >= 0 && missionNumber < NUMBER_OF_MISSIONS;
    if (!missionExists) {
        return false;
    }
    return fingerprintOf(submittedFlag) == FLAG_FINGERPRINTS[missionNumber];
}
