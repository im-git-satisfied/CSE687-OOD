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
        std::vector<std::pair<std::string,std::vector<int>>> reduce(std::string key, std::vector<int> values);
    
    private:
        std::vector<std::pair<std::string,std::vector<int>>> exportReduce(std::string key, int value);
};
