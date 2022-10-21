#include "Workflow.h"

// Workflow Constructor
Workflow::Workflow()
{
}

Workflow::Workflow(std::string in_dir, std::string temp_dir, std::string out_dir) :
    in_dir(in_dir),
    temp_dir(temp_dir),
    out_dir(out_dir)
{
    mapper = new Map();
    fm = new FileManagement();
    reducer = new Reduce();
    sorter = new SortMap(); 

    if(DEBUG){
        std::cout << "DEBUG >> DIRECTORY LIST: " << in_dir << " " << temp_dir << " " << out_dir << " " << std::endl;
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

   file_list = fm->list_files(in_dir);
   if(DEBUG){
        std::cout << "DEBUG >> FILE LIST" << std::endl;
        for (auto& file: file_list) {
            std::cout << "\t " << file << "\n" << std::endl;
        }
    }
}


void Workflow::read_file(void){
    bool read;
    std::string line = "";
    for(auto& file: file_list){
        read = true;
        if(DEBUG) {
            std::cout << "DEBUG >>>>>>>>>>>>>>>" << std::endl;
            std::cout << "DEBUG >> READING FILE: " << file << std::endl;
            std::cout << "DEBUG <<<<<<<<<<<<<<<" << std::endl;
        }
        while(read) {
            line = fm->readFile(in_dir, file);
            if(fm->EndOfFile(file) == true) {
                read = false;
            }

            //if(DEBUG) {
            //    std::cout << "DEBUG >> " << line << std::endl;
            //}
            /*
            mapper->tokenMap(line);
            if(mapper->isFull()){
                if(fm->writeFile(mapper.wordBuffer){
                    mapper->clearBuffer;
                }
                else{
                    std::cout << "Error writing to temporary file for " << file; 
                }
            }
            */
        }
        //fm->writeFile(mapper.wordBuffer)
        //mapper->clearBuffer;
    }
    std::cout << "Finished reading input files" << std::endl; 
}

//void err_out(std::string);

int Workflow::start(void){

    Workflow::verify_dirs();
    Workflow::list_files();
    Workflow::read_file();
    return 1;
}