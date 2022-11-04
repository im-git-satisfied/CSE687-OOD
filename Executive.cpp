#include "Executive.h"

Executive::Executive()
{
    
}

Executive::Executive(int argc, char *argv[], bool DEBUG) : count(argc), argv(argv), DEBUG(DEBUG) 
{
    if(DEBUG){
        std::cout << "DEBUG >> EXECUTIVE CLASS INITIALIZED" << std::endl;
    }
}

// Verify Count
// ensure that the number of command line arguments are valid. 
void Executive::verify_count(void){
    if(DEBUG){
        std::cout << "DEBUG >> NUMBER ARGS: " << count << std::endl;
    }
    if (count != 4) {
        err = true;
        Executive::err_out("ERROR >> Invalid number of arguments. See Help\n");
    }

}

// print the help message 
void Executive::print_help(void){
    std::cout << "USAGE >> ./MapReduce in_dir temp_dir out_dir\n\n" << std::endl;
}


// access the directories passed in from the command line 
void Executive::grab_dirs(void){
    in_dir = argv[1];
    temp_dir = argv[2];
    out_dir = argv[3];
}

// err_out if command the wrong number of arguments are passed 
void Executive::err_out(std::string err_msg) {
    std::cout << err_msg << std::endl;
    print_help();
    exit(-1);
}

int Executive::start() {

    verify_count();         //verify dirs, err out if it's the wrong number 
    grab_dirs();            // grab the directories, used to pass to Workflow

    // create a Workflow class
    worker = new Workflow(in_dir, temp_dir, out_dir, DEBUG);
    
    // Workflow.start() returns 1 on success 
    int err_code = worker->start();

    if(err_code == 1){
        std::cout << " >> Executed Successfully" << std::endl; 
        return 1;
    }
    else{
        std::cout << " >> Executed Unsuccessfully" << std::endl;
        return 0;
    }

}

//#define Test_Drive 
#ifdef Test_Drive 

int main(int argc, char *argv[]) {

    Executive *exec = new Executive(argc, argv);
    exec->DEBUG = true;
    exec->start();

}
#endif