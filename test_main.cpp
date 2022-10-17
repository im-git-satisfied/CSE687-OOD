#include <iterator>
#include <utility>
#include <typeinfo>
#include "sort.h"

using namespace std;
//using namespace MapReduce;

int main() {

    MapReduce::SortMap *sorter = new MapReduce::SortMap();
    vector<string> keys = { "the", "brown", "fox", "jumped", "over", "the", "big", "brown", "fox"};

    for (auto& key: keys) {
        for (auto x = 0; x < 25; x++) {
            sorter->sort(key, 1);
        }
    }
    
    // 
    auto word_iter = sorter->begin();
    for (word_iter; word_iter != sorter->end(); word_iter++){
        cout << "key = " << word_iter->first << "\n";
        for (auto x = word_iter->second.begin(); x != word_iter->second.end(); x++){
            cout << *x << "";
        }
        cout << "\n";
    }
}