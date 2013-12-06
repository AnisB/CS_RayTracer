// Implémentaton de helper.h
#include "helper.h"

#include <iostream>
#include <sstream>

using namespace std;


std::string replaceAll(const std::string& parString, const std::string& parBase, const std::string& parReplace) 
{
	std::string result = parString;
    // Si string nulle on renvoie la string nulle
    if(parBase.empty())
        return std::string("");
    // On remplace
    size_t start_pos = 0;
    while((start_pos = result.find(parBase, start_pos)) != std::string::npos) 
    {
        result.replace(start_pos, parBase.length(), parReplace);
        start_pos += parReplace.length();
    }
    return result;
}

std::vector<std::string> split(const std::string& parString, char parSeparator, std::vector<std::string> &outStringTable) 
{
    std::stringstream streamObj(parString);
    std::string item;
    while (std::getline(streamObj, item, parSeparator)) 
    {
        outStringTable.push_back(item);
    }
    return outStringTable;
}


std::vector<std::string> split(const std::string& parString, char parSeparator)
{
    std::vector<std::string> stringTable;
    split(parString, parSeparator, stringTable);
    return stringTable;
}


int convertToInt(const std::string& parToConvert)
{
	std::stringstream streamConverter;
	streamConverter<<parToConvert;
	int result;
	streamConverter>>result;
	return result;
}
