#include "sort.h"
#include <iterator>
#include <utility>
#include <typeinfo>


//using namespace std;
//using namespace MapReduce;
bool good_count(int argc){
    std::cout << "argc = " << argc;
    if (argc == 4 || argc == 2){
        return true;
    }
    return false;
}

void print_help(){
    std::cout << "Map Reduce:";
    std::cout << "Usage:";
    std::cout << "  help: ./mapreduce -h";
    std::cout << "  standard: ./mapreduce {in_dir} {intermediate_dir} {out_dir}";
}

int main(int argc, char *argv[]) {

    if (!good_count(argc)){
        std::cout << "ERR: invalud argument count";
        print_help();
        exit(0);
    }

    

    SortMap *sorter = new SortMap();
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