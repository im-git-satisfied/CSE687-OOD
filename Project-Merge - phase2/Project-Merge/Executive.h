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
        bool DEFAULT_TEMP = true;
        bool DEFAULT_OUT = true;
        std::string in_dir;
        std::string temp_dir = "TEMP_DIR";
        std::string out_dir = "OUT_DIR";
        std::string map_dll;
        std::string reduce_dll; 
        int LPORT;
        Workflow *worker;
        bool DEBUG;


        bool err;
        char **argv;

    public:
        
        explicit Executive();
        explicit Executive(int argc, char** argv, bool DEBUG);

        void parse_args(void);

        //void verify_count(void);

        void print_help(void);

        //void grab_dirs(void);

        void err_out(std::string);

        int start();
};

#endif