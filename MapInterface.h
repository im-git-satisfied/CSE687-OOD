#ifndef __MAPINTERFACE_H__
#define __MAPINTERFACE_H__

#ifdef MAPWIN32DLL_EXPORTS
#define Map_API __declspec(dllexport)
#else
#define Map_API __declspec(dllimport)
#endif // MAPWIN32DLL_EXPORTS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>
#include <algorithm>

class MapInterface
{
    public:
        virtual void tokenMap(std::string key, std::string value){}
        virtual std::vector<std::pair<std::string,std::vector<int>>> getWordBuffer() = 0;
        virtual bool checkIsFull() = 0;
        virtual void clearBuffer(){}
};
#endif