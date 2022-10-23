#include "Executive.h"

Executive::Executive()
{
    
}

Executive::Executive(int argc, char *argv[], bool DEBUG) : count(argc), argv(argv), DEBUG(DEBUG) 
{
    if(DEBUG){
        std::cout << "DEBUG >> EXECUTIVE CLASS INITIALIZED" << std::endl;
    }
}

void Executive::verify_count(void){
    if(DEBUG){
        std::cout << "DEBUG >> NUMBER ARGS: " << count << std::endl;
    }
    if (count != 4) {
        err = true;
        Executive::err_out("ERROR >> Invalid number of arguments. See Help\n");
    }

}

void Executive::print_help(void){
    std::cout << "USAGE >> ./MapReduce in_dir temp_dir out_dir\n\n" << std::endl;
}

void Executive::grab_dirs(void){
    in_dir = argv[1];
    temp_dir = argv[2];
    out_dir = argv[3];
}

void Executive::err_out(std::string err_msg) {
    std::cout << err_msg << std::endl;
    print_help();
    exit(-1);
}

int Executive::start() {

    verify_count();
    grab_dirs();
    worker = new Workflow(in_dir, temp_dir, out_dir, DEBUG);
    
    int err_code = worker->start();

    if(err_code > 0){
        std::cout << "executed successfully" <<std::endl; 
    }


    /*
    SortMap *sorter = new SortMap();
    std::vector<std::string> keys = { "the", "brown", "fox", "jumped", "over", "the", "big", "brown", "fox"};

    /*
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

    return 1;
    */
   return 0;

}

//#define Test_Drive 
#ifdef Test_Drive 

int main(int argc, char *argv[]) {

    Executive *exec = new Executive(argc, argv);
    exec->DEBUG = true;
    exec->start();

}
#endif