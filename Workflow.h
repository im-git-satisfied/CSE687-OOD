#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "Sort.h"
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Workflow.h"
#include <iterator>
#include <utility>
#include <typeinfo>



class Workflow 
{
    private:

        std::string in_dir;                     // user provided input dir
        std::string temp_dir;                   // user provided temp dir
        std::string out_dir;                    // user provided out dir

        std::string curr_dir;                   // current read directory 
        std::string target_dir;                 // current write directory 
        
        std::vector<std::string> file_list;     // file list of curr_dir

        SortMap *sorter;                        // sort class 
        Map *mapper;                            // map class
        FileManagement *fm ;                    // file management class
        Reduce *reducer;                        // reduce class 

        bool DEBUG = false;                     // Debug flag

        void finish(void);                      // final workflow tasks (write SUCCESS file)

        void map_files(void);                   // iterate over files for mapping 
        void map_file(std::string file);        // map individual files

        void reduce_files(void);                // iterate over files for reducing
        void reduce_file(std::string file);     // reduce individual files 
        
        void verify_dirs(void);                 // verify user input 

        void list_files(void);                  // list the files for a respective directory

        //void err_out(std::string);

        

    public:
        
        // constructors 
        explicit Workflow();
        explicit Workflow(std::string in_dir, std::string temp_dir, std::string out_dir, bool DEBUG);

        int start();                            // kick off Workflow class

};

#endif