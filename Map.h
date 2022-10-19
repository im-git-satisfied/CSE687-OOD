#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

class Map
{
    public:
        explicit Map();
        void tokenMap(std::string key, std::string value);
        void getTokenMap();
    
    private:
        std::string tokenize(std::string word);
        void fileExport(std::string key, int value);
        std::map<std::string,int> wordBuffer;
};