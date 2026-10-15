// Checks whether a color matches the official Adobe Red.

#include "brand_color_check.hpp"

#include <cctype>

namespace {

// "RGB(235, 16, 0)" becomes "rgb(235,16,0)" so different spellings compare equal.
std::string withoutSpacesInLowercase(const std::string& text) {
    std::string cleaned;
    for (char letter : text) {
        if (!std::isspace(static_cast<unsigned char>(letter))) {
            cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        }
    }
    return cleaned;
}

}  // namespace

bool isAdobeRed(const std::string& cssColor) {
    std::string color = withoutSpacesInLowercase(cssColor);
    return color == "rgb(235,16,0)" || color == "#eb1000";
}
