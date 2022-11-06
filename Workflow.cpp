#include "Workflow.h"

// Workflow Constructor
Workflow::Workflow()
{
}

// Workflow constructor 
Workflow::Workflow(std::string in_dir, std::string temp_dir, std::string out_dir, bool DEBUG) :
    in_dir(in_dir),
    temp_dir(temp_dir),
    out_dir(out_dir),
    DEBUG(DEBUG)
{
    // instantiate primary classes
    mapper = new Map();
    fm = new FileManagement();
    reducer = new Reduce();
    sorter = new SortMap(DEBUG); 

    if(DEBUG){
        std::cout << "DEBUG >> WORKFLOW CLASS INITIALIZED" << std::endl;
    }

}

// Verify user provided directories 
// calls FileManagement.verify_directory method
void Workflow::verify_dirs(void){
    if(DEBUG){
        std::cout << "DEBUG >> verifying directories" << std::endl;
    }
    
    // verify input directory 
    if (fm->verify_directory(in_dir) == false){
        std::cout << "ERROR >> in directory " << in_dir << " is invalid" << std::endl;
        exit(0);
    }

    // verify temp directory 
     if (fm->verify_directory(temp_dir) == false){
        std::cout << "ERROR >> temp directory " << temp_dir << " is invalid" <<std::endl;
        exit(0);
    }

    //verify output directory 
     if (fm->verify_directory(out_dir) == false){
        std::cout << "ERROR >> out directory " << out_dir << " is invalid" << std::endl;
        exit(0);
    }

    
}

// List Files 
// calls FileManagement.list_files
void Workflow::list_files(void){

    // curr_dir is set to the current read directory 
   file_list = fm->list_files(curr_dir);
   if(DEBUG){
        std::cout << "DEBUG >> FILE LIST" << std::endl;
        for (auto& file: file_list) {
            std::cout << "\t " << file << "\n" << std::endl;
        }
    }
}


// Map Files 
// Iterates over files and calls Workflow.map_file
void Workflow::map_files(void){

    curr_dir = in_dir;              // set curr_dir to in directory 
    target_dir = temp_dir;          // set target_dir to temp directory 
    Workflow::list_files();         // grab the list of files from curr_dir 

    // iterate over file list and call map_file 
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

// Map File
// calls FileManagement.readFile and Maps files. 
void Workflow::map_file(std::string file){
    bool read = true;
    std::string line = "" ;

    // read loop that continues to call FileManagent.readFile until EOF is found
    while(read) {
            line = fm->readFile(curr_dir, file);
            if(fm->EndOfFile(file) == true) {
                read = false;
            }

            // pass read lines to Mapper
            mapper->tokenMap(file, line);

            // if Map buffer export is full, pass the buffer to FileManagement.writeFile and clear the buffer
            if(mapper->checkIsFull()){
                if(fm->writeFile(mapper->getWordBuffer(), target_dir, file)){
                    mapper->clearBuffer();
                }
                else{
                    std::cout << "Error writing to temporary file for " << file <<std::endl; 
                }
            }     
    }

    // grab the final items from the buffer after EOF is found
    fm->writeFile(mapper->getWordBuffer(), temp_dir, file);
    mapper->clearBuffer();
}

// ITerate over files for reducing
void Workflow::reduce_files(void){
    curr_dir = temp_dir;                // set curr_dir to temp dir
    target_dir = out_dir;               // set target_dir to out_dir 
    Workflow::list_files();             // list files of curr dir 

    // iterate over files and call Workflow.reduce_file
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

// Reduce File
// Calls FileManagement.readFile, SortMap.sort, and Reduce.reduce
void Workflow::reduce_file(std::string file){
    bool read = true;
    std::string line = "";
    
    // read loop that sends lines to SortMap.sort
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

    // send sortMap elements to reducer, word by word 
    for (auto x = sorter->begin(); x != sorter->end(); x++){
        if(DEBUG) {
            std::cout << "DEBUG >> SEND SORTED KEY,VAL TO REDUCE.REDUCE" << std::endl;
        }
        fm->writeFile(reducer->reduce(x->first, x->second), target_dir, file);
    }

    // clear the SortMap after it's been written out 
    sorter->clear();

    
}


// Finish Mapping, Sorting, and Reducing 
// write SUCCESS file to out dir
void Workflow::finish(void){
    if(DEBUG){
        std::cout << "writing SUCCESS to " << out_dir << std::endl;
    }
    fm->writeFileSuccess(out_dir, "SUCCESS");
}


// Workflow order of operations 
int Workflow::start(void){

    
    Workflow::verify_dirs();        // Verify Directories

    Workflow::map_files();          // Map_Files

    Workflow::reduce_files();       // Reduce Files

    Workflow::finish();             // Finish

    return 1;
}