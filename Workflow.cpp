#include "Workflow.h"

// Workflow Constructor
Workflow::Workflow()
{
}

Workflow::Workflow(std::string in_dir, std::string temp_dir, std::string out_dir, bool DEBUG) :
    in_dir(in_dir),
    temp_dir(temp_dir),
    out_dir(out_dir),
    DEBUG(DEBUG)
{
    mapper = new Map();
    fm = new FileManagement();
    reducer = new Reduce();
    sorter = new SortMap(DEBUG); 

    if(DEBUG){
        std::cout << "DEBUG >> WORKFLOW CLASS INITIALIZED" << std::endl;
    }

}

void Workflow::verify_dirs(void){
    if(DEBUG){
        std::cout << "DEBUG >> verifying directories" << std::endl;
    }
    
    if (fm->verify_directory(in_dir) == false){
        std::cout << "ERROR >> in directory " << in_dir << " is invalid" << std::endl;
        exit(0);
    }
     if (fm->verify_directory(temp_dir) == false){
        std::cout << "ERROR >> temp directory " << temp_dir << " is invalid" <<std::endl;
        exit(0);
    }
     if (fm->verify_directory(out_dir) == false){
        std::cout << "ERROR >> out directory " << out_dir << " is invalid" << std::endl;
        exit(0);
    }

    
}

void Workflow::list_files(void){

   file_list = fm->list_files(curr_dir);
   if(DEBUG){
        std::cout << "DEBUG >> FILE LIST" << std::endl;
        for (auto& file: file_list) {
            std::cout << "\t " << file << "\n" << std::endl;
        }
    }
}

void Workflow::map_files(void){
    curr_dir = in_dir;
    target_dir = temp_dir;
    Workflow::list_files();

    for(auto& file: file_list){
        if(DEBUG){
            std::cout << "DEUBG >> MAPPING FILE: " << curr_dir << file << std::endl;
        }
        std::cout << "MAPPING " << file << std::endl;

        Workflow::map_file(file);
    }
    if(DEBUG){
        std::cout << "DEBUG >> FINISHED MAPPING FILES" << std::endl;
    }

}

void Workflow::map_file(std::string file){
    bool read = true;
    std::string line = "" ;
    while(read) {
            line = fm->readFile(curr_dir, file);
            if(fm->EndOfFile(file) == true) {
                read = false;
            }

            mapper->tokenMap(file, line);
            if(mapper->isFull){
                if(fm->writeFile(mapper->wordBuffer, target_dir, file)){
                    mapper->clearBuffer();
                }
                else{
                    std::cout << "Error writing to temporary file for " << file <<std::endl; 
                }
            }     
    }
    fm->writeFile(mapper->wordBuffer, temp_dir, file);
    mapper->clearBuffer();
}

void Workflow::reduce_files(void){
    curr_dir = temp_dir;
    target_dir = out_dir;
    Workflow::list_files();

    for(auto& file: file_list){
        if(DEBUG){
            std::cout << "DEUBG >> REDUCING FILE: " << curr_dir << file << std::endl;
        }
        std::cout << "REDUCING " << file << std::endl;
        Workflow::reduce_file(file);
    }
    if(DEBUG){
        std::cout << "DEBUG >> FINISHED REDUCING FILES" << std::endl;
    }
}

void Workflow::reduce_file(std::string file){
    bool read = true;
    std::string line = "";
    
    while(read) {
        line = fm->readFile(curr_dir, file);
        if(fm->EndOfFile(file) == true) {
            read = false;
        }
        if(DEBUG) {
            std::cout << "DEBUG >> SORTING LINE: " << line << std::endl;
        }
        sorter->sort(line);
    }

    for (auto x = sorter->begin(); x != sorter->end(); x++){
        if(DEBUG) {
            std::cout << "DEBUG >> SEND SORTED KEY,VAL TO REDUCE.REDUCE" << std::endl;
        }
        fm->writeFile(reducer->reduce(x->first, x->second), target_dir, file);
    }

    
}


int Workflow::start(void){

    Workflow::verify_dirs();

    Workflow::map_files();

    Workflow::reduce_files();

    return 1;
}