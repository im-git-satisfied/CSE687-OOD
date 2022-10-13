#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

using namespace std;

class Map
{
    public:
        explicit Map();
        void tokenMap(string key, string value);
    
    private:
        string tokenize(string word);
        void fileExport();
        map<string,int> wordCount;
};