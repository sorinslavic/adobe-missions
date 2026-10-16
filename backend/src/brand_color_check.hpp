// Checks whether a color matches the official Adobe Red.
#pragma once

#include <string>

// Adobe Red (#EB1000), written the way browsers report colors.
const std::string ADOBE_RED_AS_RGB = "rgb(235, 16, 0)";

// Accepts colors like "rgb(235, 16, 0)" or "#EB1000".
bool isAdobeRed(const std::string& cssColor);
