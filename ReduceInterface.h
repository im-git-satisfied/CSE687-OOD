#ifndef __REDUCEINTERFACE_H__
#define __REDUCEINTERFACE_H__

#ifdef REDUCEWIN32DLL_EXPORTS
#define Reduce_API __declspec(dllexport)
#else
#define Reduce_API __declspec(dllimport)
#endif // REDUCEWIN32DLL_EXPORTS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>
#include <algorithm>

class ReduceInterface
{
    public:
        virtual std::vector<std::pair<std::string,std::vector<int>>> reduce(std::string key, std::vector<int> values) = 0;
};
#endif