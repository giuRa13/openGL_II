#include "config.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::vector<std::string> split(std::string line, std::string delimiter)
{
    std::vector<std::string> splitLine;

    size_t pos = 0;
    std::string token; //numbers (delimiter is spaces)
    while((pos = line.find(delimiter)) != std::string::npos)
    {
        token = line.substr(0, pos);
        splitLine.push_back(token);
        line.erase(0, pos + delimiter.size());
    }
    //last word in a sentence(may not have space)
    splitLine.push_back(line);

    return splitLine;
}