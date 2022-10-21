#ifndef EXECUTIVE_H
#define EXECUTIVE_H
//#include "Sort.h"

//#include "FileManagement.h"
//#include "Map.h"
//#include "Reduce.h"
#include "Workflow.h"
#include <iterator>
#include <utility>
#include <typeinfo>


class Executive 
{
    private:
        
        int count;
        std::string in_dir;
        std::string temp_dir;
        std::string out_dir;
        Workflow *worker;


        bool err;
        char **argv;

    public:
        
        explicit Executive();
        explicit Executive(int argc, char** argv);

        bool DEBUG = false;

        void verify_count(void);

        void print_help(void);

        void grab_dirs(void);

        void err_out(std::string);

        int start();
};

#endif