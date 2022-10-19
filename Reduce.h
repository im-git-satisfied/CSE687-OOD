#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <array>

class Reduce
{
    public:
        explicit Reduce();
        void reduce(std::string key, std::vector<int> values);
    
    private:
        void exportReduce(std::string key, int value);
};
