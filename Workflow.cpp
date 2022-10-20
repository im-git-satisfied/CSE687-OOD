#include "Workflow.h"

// Workflow Constructor
Workflow::Workflow()
{
}

Workflow::Workflow(std::string in_dir, std::string temp_dir, std::string out_dir) {
    in_dir = in_dir;
    temp_dir = temp_dir;
    out_dir = out_dir;
    mapper = new Map();
    fm = new FileManagement();
    reducer = new Reduce();
    sorter = new Sorter; 

    std::cout << " " << in_dir, temp_dir, out_dir;
}
void Workflow::verify_dirs(void){
    if (fm->verify_directory(in_dir) == false){
        std::cout << "in directory " << in_dir << " is invalid";
        exit(0);
    }
     if (fm->verify_directory(temp_dir) == false){
        std::cout << "temp directory " << temp_dir << " is invalid";
        exit(0);
    }
     if (fm->verify_directory(out_dir) == false){
        std::cout << "out directory " << out_dir << " is invalid";
        exit(0);
    }
    
}

void Workflow::list_files(void){
   file_list = fm->list_files(in_dir);
}

void Workflow::read_file(void){
    for(auto& file: file_list){
        std::string line = fm->readFile(in_dir, file);
        while(fm->EndOfFile() != false)
            mapper->tokenMap(line);
            
        
        
         std:: cout << "\n";
    }

void err_out(std::string);

int start();