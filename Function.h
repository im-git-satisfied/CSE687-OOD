#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>

class Function
{
    public:
        virtual void fileExport(std::string key, int value);
        virtual void clearBuffer();
        virtual std::vector<std::pair<std::string,std::vector<int>>> getBuffer();
};
#endif