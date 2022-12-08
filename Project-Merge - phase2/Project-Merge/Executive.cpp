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

    if (count < 5) {
        err = true;
        Executive::err_out(err_str);
    }
    
    in_dir = argv[1];
    map_dll = argv[2];
    reduce_dll = argv[3];
    LPORT = atoi(argv[4]);

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
            if( i < 5){
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
    if (DEFAULT_OUT) {
        std::cout << "INFO >> Using default directory 'OUT_DIR' " << std::endl;
    }

}

// print the help message 
void Executive::print_help(void){
    std::cout << "\tUSAGE >> " << argv[0] << " {in_dir} {map_dll} {reduce_dll} -t {temp_dir} -o {out_dir}\n" << std::endl;
    std::cout << "\t-h, -help, --h, --help: print help message" << std::endl; 
    std::cout << "\tin_dir: \t\tREQUIRED: directory path containing files to be map reduced" << std::endl; 
    std::cout << "\tmap DLL: \t\tREQUIRED: directory path to map DLL. " << std::endl;
    std::cout << "\treduce DLL: \t\tREQUIRED: directory path to reduce DLL. " << std::endl;
    std::cout << "\tlisten port: \t\tREQUIRED: listen port for server. " << std::endl;
    std::cout << "\ttemp_dir: \t\tDEFAULT - TEMP_DIR: directory path to location of mapped/intermediary files. " << std::endl; 
    std::cout << "\tout_dir: \t\tDEFAULT - OUT_DIR: directory path to location of reduced/final files. " << std::endl; 
    
}

// err_out if command the wrong number of arguments are passed 
void Executive::err_out(std::string err_msg) {
    std::cout << err_msg << std::endl;
    print_help();
    exit(-1);
}

int Executive::start() {

    parse_args();
    
    // create a Workflow class
    worker = new Workflow(in_dir, map_dll, reduce_dll, temp_dir, out_dir, DEBUG, LPORT);


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