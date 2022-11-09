#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "Sort.h"
#include "FileManagement.h"
#include "MapInterface.h"
#include "ReduceInterface.h"
#include "Workflow.h"
#include "Windows.h"
#include <iterator>
#include <utility>
#include <typeinfo>

//Function* is the type to our interface class
typedef MapInterface* (__cdecl* MapFactory)();
typedef ReduceInterface* (__cdecl* ReduceFactory)();

class Workflow 
{
    private:

        std::string in_dir;                     // user provided input dir
        std::string temp_dir;                   // user provided temp dir
        std::string out_dir;                    // user provided out dir
        const std::string DEFAULT_TEMP = "TEMP_DIR";
        const std::string DEFAULT_OUT = "OUT_DIR";
        std::string map_dll_dir;
        std::string reduce_dll_dir;

        std::string curr_dir;                   // current read directory 
        std::string target_dir;                 // current write directory 
        
        std::vector<std::string> file_list;     // file list of curr_dir

        SortMap* sorter;                        // sort class 
        FileManagement* fm;                    // file management class
        MapInterface* mapper;
        ReduceInterface* reducer;

        bool DEBUG = false;                     // Debug flag

        void finish(void);                      // final workflow tasks (write SUCCESS file)

        void map_files(void);                   // iterate over files for mapping 
        void map_file(std::string file);        // map individual files

        void reduce_files(void);                // iterate over files for reducing
        void reduce_file(std::string file);     // reduce individual files 
        
        void verify_dirs(void);                 // verify user input 

        void load_dlls(void);                   //load DLLs
        void free_dlls(void);       

        void list_files(void);                  // list the files for a respective directory

        //void err_out(std::string);

        

    public:
        
        // constructors 
        explicit Workflow();
        explicit Workflow(std::string in_dir, std::string map_dll, std::string reduce_dll, std::string temp_dir, std::string out_dir, bool DEBUG);

        int start();                            // kick off Workflow class

};

#endif