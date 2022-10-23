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

        std::string in_dir;
        std::string temp_dir;
        std::string out_dir;

        std::string curr_dir;
        std::string target_dir;
        

        std::vector<std::string> file_list; 

        SortMap *sorter;
        Map *mapper; 
        FileManagement *fm ;
        Reduce *reducer;

        bool DEBUG = false;

    public:
        
        explicit Workflow();
        explicit Workflow(std::string in_dir, std::string temp_dir, std::string out_dir, bool DEBUG);

        void map_files(void);
        void map_file(std::string file);

        void reduce_files(void);
        void reduce_file(std::string file);
        
        //void iter_files(void);

        void verify_dirs(void);

        void list_files(void);

        //void read_file(void);

        void err_out(std::string);

        int start();
};

#endif