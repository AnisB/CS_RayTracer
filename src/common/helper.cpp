#include "helper.h"
#include <iostream>

using namespace std;
std::string replaceAll(const std::string& parString, const std::string& parBase, const std::string& parReplace) 
{
	std::string result = parString;
    if(parBase.empty())
        return std::string("");
    size_t start_pos = 0;
    while((start_pos = result.find(parBase, start_pos)) != std::string::npos) 
    {
        result.replace(start_pos, parBase.length(), parReplace);
        start_pos += parReplace.length();
    }
    return result;
}
