#ifndef __BASEREDUCE_H__
#define __BASEREDUCE_H__

#ifdef REDUCEWIN32DLL_EXPORTS
#define MapReduce_API __declspec(dllexport)
#else
#define MapReduce_API __declspec(dllimport)
#endif // REDUCEWIN32DLL_EXPORTS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>
#include <algorithm>

class BaseReduce
{
    public:
        virtual void fileExport(std::string key, int value){}
        virtual void clearBuffer(){}
        virtual std::vector<std::pair<std::string,std::vector<int>>> getBuffer() = 0;
};
#endif