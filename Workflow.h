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
        std::vector<std::string> file_list; 
        SortMap *sorter;
        Map *mapper; 
        FileManagement *fm ;
        Reduce *reducer;

    public:
        bool DEBUG = false;
        explicit Workflow();
        explicit Workflow(std::string in_dir, std::string temp_dir, std::string out_dir);

        void verify_dirs(void);

        void list_files(void);

        void read_file(void);

        void err_out(std::string);

        int start();
};

#endif