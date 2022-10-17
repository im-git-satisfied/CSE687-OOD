#include "sort.h"


using namespace MapReduce;
using namespace std;


void SortMap::add (string key, int value) {
                cout << "adding\n";
                vector<int> container = {value};
                this->words.insert({key, container});
            }

void SortMap::update (std::string key, int value){
                std::cout << "updating\n"; 
                this->words[key].push_back(value);
            }

// used to sort key, value pairs
void SortMap::sort(std::string key,  int value) {
    if (this->words.count(key) == 0) {
            this->add(key, value);
        } else {
            this->update(key, value);
        }
    }

            // grab items from the list. 
map<string, vector<int>>::iterator SortMap::begin(void){
    return this->words.begin();
}

map<string, vector<int>>::iterator SortMap::end(void){
    return this->words.end();
}
            // check and see if the map is empty. 
bool SortMap::is_empty(void){
    return this->words.empty();
}

// print the map and it's values 
void SortMap::print(void) {
    for(auto& item: this->words){
        std::cout << item.first << "\n";
        for (auto& num: item.second) {
             std::cout << num << " ";
        }
        std:: cout << "\n";
    }
}

// just print the keys 
void SortMap::print_keys(void) {
    for(auto& item: this->words){
            std::cout << item.first << " ";
    }
    std:: cout << "\n";
}



