#ifndef HELPER_COMMON
#define HELPER_COMMON

#include <string>
#include <vector>
std::string replaceAll(const std::string& parString, const std::string& parBase, const std::string& parReplace);

std::vector<std::string> split(const std::string& parString, char parSeparator);

int convertToInt(const std::string& parToConvert);
#endif // HELPER_COMMON
