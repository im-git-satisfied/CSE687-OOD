#ifndef __BASEMAP_H__
#define __BASEMAP_H__

#ifdef MAPWIN32DLL_EXPORTS
#define MapReduce_API __declspec(dllexport)
#else
#define MapReduce_API __declspec(dllimport)
#endif // MAPWIN32DLL_EXPORTS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>
#include <algorithm>

class BaseMap
{
    public:
        virtual void fileExport(std::string key, int value){}
        virtual void clearBuffer(){}
        virtual std::vector<std::pair<std::string,std::vector<int>>> getBuffer() = 0;
};
#endif