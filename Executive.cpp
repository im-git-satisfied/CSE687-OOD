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

// DEPRECATED: USE parse_args
// Verify Count
// ensure that the number of command line arguments are valid. 
/*
void Executive::verify_count(void){
    std::string err_str = "ERROR >> Invalid number of arguments. See Help\n";
    if(DEBUG){
        std::cout << "DEBUG >> NUMBER ARGS: " << count << std::endl;
    }
    if (count != 4) {
        err = true;
        Executive::err_out(err_str);
    }

}
*/

void Executive::parse_args(void){

    std::string err_str = "ERROR >> Invalid number of arguments. See Help\n";
    int i = 1;
    if(DEBUG){
        std::cout << "DEBUG >> NUMBER ARGS: " << count << std::endl;
    }

    if (count < 4) {
        err = true;
        Executive::err_out(err_str);
    }
    
    in_dir = argv[1];
    map_dll = argv[2];
    reduce_dll = argv[3];

    for(i; i < count ; i++){
        if(std::string(argv[i]) == "-h"){
            Executive::err_out("");
        }
        else if(std::string(argv[i]) == "-help"){
            Executive::err_out("");
        }
        else if(std::string(argv[i]) == "--h"){
            Executive::err_out("");
        }
        else if(std::string(argv[i]) == "--help"){
            Executive::err_out("");
        }
        else if(std::string(argv[i]) == "-t") {
            if( i < 4){
                Executive::err_out("Missing positional arguments");
            }
            i+=1;
            if (i <= count){
                temp_dir = argv[i];
                DEFAULT_TEMP = false;
            }
            else {
                Executive::err_out("-t requires an argument");
            }
        }
        else if(std::string(argv[i]) == "-o"){
            if( i < 4){
                Executive::err_out("Missing positional arguments");
            }
            i+=1;
            if (i <= count){
                out_dir = argv[i];
                DEFAULT_OUT = false;
            }
            else {
                Executive::err_out("-o requires an argument");
            }
        }

    }

    if (DEFAULT_TEMP){
        std::cout << "INFO >> Using default directory 'TEMP_DIR' " << std::endl;
    }
    if (DEFAULT_OUT){
        std::cout << "INFO >> Using default directory 'OUT_DIR' " << std::endl;
    }
    /*
    if(count == 2){
        in_dir = argv[1];
        temp_dir = DEFAULT_TEMP;
        out_dir = DEFAULT_OUT;
        std::cout << "INFO >> Using default directories 'TEMP_DIR' and 'OUT_DIR' for arguments temp_dir and out_dir" << std::endl;
        return;
    }

    if(count == 3){
        in_dir = argv[1];
        temp_dir = argv[2];
        out_dir = DEFAULT_OUT;
        std::cout << "INFO >> Using default directory 'OUT_DIR' for argument out_dir" << std::endl;
        return;
    }

    if(count == 4){
        in_dir = argv[1];
        temp_dir = argv[2];
        out_dir = argv[3];
        return;
    }
    */ 

}

// print the help message 
void Executive::print_help(void){
    std::cout << "\tUSAGE >> " << argv[0] << " {in_dir} {map_dll} {reduce_dll} -t {temp_dir} -o {out_dir}\n" << std::endl;
    std::cout << "\t-h, -help, --h, --help: print help message" << std::endl; 
    std::cout << "\tin_dir: \t\tREQUIRED: directory path containing files to be map reduced" << std::endl; 
    std::cout << "\tmap DLL: \t\tREQUIRED: directory path to map DLL. " << std::endl;
    std::cout << "\treduce DLL: \t\tREQUIRED: directory path to reduce DLL. " << std::endl;
    std::cout << "\ttemp_dir: \t\tDEFAULT - TEMP_DIR: directory path to location of mapped/intermediary files. " << std::endl; 
    std::cout << "\tout_dir: \t\tDEFAULT - OUT_DIR: directory path to location of reduced/final files. " << std::endl; 
    
}

// DEPRECATED: USE parse_args
// access the directories passed in from the command line 
/*
void Executive::grab_dirs(void){
    in_dir = argv[1];
    temp_dir = argv[2];
    out_dir = argv[3];
}
*/

// err_out if command the wrong number of arguments are passed 
void Executive::err_out(std::string err_msg) {
    std::cout << err_msg << std::endl;
    print_help();
    exit(-1);
}

int Executive::start() {

    parse_args();             // replaces verify_count and grab_dirs. 
    //verify_count();         //verify dirs, err out if it's the wrong number 
    //grab_dirs();            // grab the directories, used to pass to Workflow

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