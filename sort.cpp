
#include<iostream>
#include <map>
#include <iterator>
#include <vector>
#include <utility>
#include <typeinfo>

class Sort 
    {
        private:
            // map to hold a key, value pair where the key is a string, and the value is a vector of occurrences. 
            std::map<std::string, std::vector<int>> words;
    
            // add a pair to the map
            void add (std::string key, int value) {
                std::cout << "adding\n";
                std::vector<int> container = {value};
                this->words.insert({key, container});
            }

            // update the number of occurrences to the key's value. 
            void update (std::string key, int value){
                std::cout << "updating\n"; 
                this->words[key].push_back(value);
            }

        public:
            // used to sort key, value pairs
            void sort(std::string key,  int value) {
                if (this->words.count(key) == 0) {
                    this->add(key, value);
                } else {
                    this->update(key, value);
                }
            }

            // grab items from the list. 
            auto begin(void){
                return this->words.begin();
            }

            auto end(void){
                return this->words.end();
            }
            // check and see if the map is empty. 
            bool is_empty(void){
                return this->words.empty();
            }

            // print the map and it's values 
            void print(void) {
                for(auto& item: this->words){
                    std::cout << item.first << "\n";
                    for (auto& num: item.second) {
                        std::cout << num << " ";
                    }
                    std:: cout << "\n";
                }
            }

            // just print the keys 
            void print_keys(void) {
                for(auto& item: this->words){
                    std::cout << item.first << " ";
                }
                std:: cout << "\n";
            }

};

int main() {

    Sort *sorter = new Sort();
    std::vector<std::string> keys = { "the", "brown", "fox", "jumped", "over", "the", "big", "brown", "fox"};

    for (auto& key: keys) {
        for (auto x = 0; x < 25; x++) {
            sorter->sort(key, 1);
        }
    }
    
    // 
    auto word_iter = sorter->begin();
    for (word_iter; word_iter != sorter->end(); word_iter++){
        std::cout << "key = " << word_iter->first << "\n";
        for (auto x = word_iter->second.begin(); x != word_iter->second.end(); x++){
            std::cout << *x << "";
        }
        std::cout << "\n";
    }


 
    
    
    

}
