#include "Sort.h"


//using namespace MapReduce;
//using namespace std;

SortMap::SortMap()
{
    
}

SortMap::SortMap(bool DEBUG) : DEBUG(DEBUG)
{
    if(DEBUG){
        std::cout << "DEBUG >> SORTMAP CLASS INITIALIZED" << std::endl;
    }
}
void SortMap::clear(void){
    words.clear();
}
void SortMap::add (std::string key, int value) {
                if(DEBUG){
                    std::cout << "DEBUG >> ADDING TO SORT MAP " << std::endl; 
                }
                std::vector<int> container = {value};
                this->words.insert({key, container});
            }

void SortMap::update (std::string key, int value){
                if(DEBUG){
                    std::cout << "DEBUG >> UPDATING SORT MAP " << std::endl; 
                }
                
                this->words[key].push_back(value);
            }

// used to sort key, value pairs
void SortMap::sort(std::string line) {
    std::string buffer;
    std::string token;

    std::string key;
    int value = 0;
    
    std::stringstream ss(line);

    while (ss >> buffer)
    {
        token = tokenize(buffer);
        if(token == "1"){
            value = std::stoi(token);
        }
        else {
            key = token;
            
        }
    }

    if (key != "" ) {
        if (this->words.count(key) == 0) {
                this->add(key, value);
            } else {
                this->update(key, value);
            }
    }
}

            // grab items from the list. 
std::map<std::string, std::vector<int>>::iterator SortMap::begin(void){
    return this->words.begin();
}

std::map<std::string, std::vector<int>>::iterator SortMap::end(void){
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


// Code taken from Dami's Map Class 
std::string SortMap::tokenize(std::string token)
{
    // remove any punctuation in the token
    int len = token.size();
    for (int i = 0; i < len; i++)
    {
        if (ispunct((unsigned char)token[i]))
        {
            token.erase(i--,1);
            len = token.size();
        }
    }

    return token;
}

