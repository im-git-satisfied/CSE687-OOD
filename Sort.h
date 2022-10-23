#ifndef SORT_H
#define SORT_H
#include <map>
#include <iostream>
#include <vector>
#include <sstream>


class SortMap
{
    private:
            
        // map to hold a key, value pair where the key is a string, and the value is a vector of occurrences. 
        std::map<std::string, std::vector<int>> words;

        // add a pair to the map
        void add (std::string key, int value);

        // update the number of occurrences to the key's value. 
        void update (std::string key, int value);

        std::string tokenize(std::string word);

        bool DEBUG;

    public:
        //SortMap();
        explicit SortMap();
        explicit SortMap(bool DEBUG);
        // used to sort key, value pairs

        void sort(std::string line);
    
        // grab items from the list. 
        std::map<std::string, std::vector<int>>::iterator begin(void);

        std::map<std::string, std::vector<int>>::iterator end(void);

        void clear();

        // check and see if the map is empty. 
        bool is_empty(void);

        // print the map and it's values 
        void print(void);

        // just print the keys 
        void print_keys(void);
};

#endif