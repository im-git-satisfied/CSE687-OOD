#include "Workflow.h"

// Workflow Constructor
Workflow::Workflow()
{
}

// Workflow constructor 
Workflow::Workflow(std::string in_dir, std::string map_dll, std::string reduce_dll, 
                    std::string temp_dir, std::string out_dir, bool DEBUG, int port) :
    in_dir(in_dir),
    map_dll_dir(map_dll),
    reduce_dll_dir(reduce_dll),
    temp_dir(temp_dir),
    out_dir(out_dir),
    DEBUG(DEBUG),
    LPORT(port)
{
    // instantiate primary classes
    fm = new FileManagement();

    for (int i = 0; i < 17; i++) {
        sorter.push_back(new SortMap(DEBUG));
    }

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
        if (temp_dir == DEFAULT_TEMP){
            fm->create_directory(temp_dir);
            std::cout << "INFO  >> Creating default temporary directory " << temp_dir << std::endl;
        }
        else {
            std::cout << "ERROR >> temp directory " << temp_dir << " is invalid" <<std::endl;
            exit(0);
        }
        
    }

    //verify output directory 
     if (fm->verify_directory(out_dir) == false){
        if (out_dir == DEFAULT_OUT){
            fm->create_directory(out_dir);
            std::cout << "INFO  >> Creating default out directory " << out_dir << std::endl;
        }
        else {
            std::cout << "ERROR >> out directory " << out_dir << " is invalid" << std::endl;
            exit(0);
        }
    }

    
}

void Workflow::load_dlls(void) {

    map_dll = LoadLibraryA(map_dll_dir.c_str());
    reduce_dll = LoadLibraryA(reduce_dll_dir.c_str());
    

    if (!map_dll) {
        std::cout << "Failed to load map library" << std::endl;
        exit(1);
    }
    else {
        MapFactory mapfactory = (MapFactory)GetProcAddress(map_dll, "CreateMap");
        int count = fm->list_files(in_dir).size();
        for (int i = 0; i < count; i++) {
            mapper.push_back(mapfactory());
        }
    }

    if (!reduce_dll) {
        std::cout << "Failed to load reduce library" << std::endl;
        exit(1);
    }
    else {
        ReduceFactory reducefactory = (ReduceFactory)GetProcAddress(reduce_dll, "CreateReduce");
        int count = fm->list_files(in_dir).size();
        for (int i = 0; i < count; i++) {
            reducer.push_back(reducefactory());
        }
    }
}

void Workflow::free_dlls(void) {
    for (int i = 0; i < 17; i++) {
        mapper[i]->Destroy();
    }

    for (int i = 0; i < 17; i++) {
        reducer[i]->Destroy();
    }
    //mapper->Destroy();
    //reducer->Destroy();

    FreeLibrary(map_dll);
    FreeLibrary(reduce_dll);
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

    std::vector<std::thread> threads;

    // iterate over file list and call map_file
    int j = 0;
    for(auto& file: file_list){
        if(DEBUG){
            std::cout << "DEUBG >> MAPPING FILE: " << curr_dir << file << std::endl;
        }
        std::cout << "MAPPING " << file << std::endl;

        threads.push_back(std::thread(&Workflow::map_file, this, mapper[j], file));
        j++;
        //Workflow::map_file(file);
    }

    for (int i = 0; i < file_list.size(); i++) {
        threads[i].join();
    }

    if(DEBUG){
        std::cout << "DEBUG >> FINISHED MAPPING FILES" << std::endl;
    }

}

// Map File
// calls FileManagement.readFile and Maps files. 
void Workflow::map_file(MapInterface* map, std::string file){
    bool read = true;
    std::string line = "" ;

    // read loop that continues to call FileManagment.readFile until EOF is found
    while(read) {
            line = fm->readFile(curr_dir, file);
            if(fm->EndOfFile(file) == true) {
                read = false;
            }

            // pass read lines to Mapper
            map->tokenMap(file, line);

            // if Map buffer export is full, pass the buffer to FileManagement.writeFile and clear the buffer
            if(map->checkIsFull()){
                if(fm->writeFile(map->getWordBuffer(), target_dir, file)) {
                    map->clearBuffer();
                }
                else{
                    std::cout << "Error writing to temporary file for " << file <<std::endl; 
                }
            }     
    }

    // grab the final items from the buffer after EOF is found
    fm->writeFile(map->getWordBuffer(), temp_dir, file);
    map->clearBuffer();
}

// ITerate over files for reducing
void Workflow::reduce_files(void){
    curr_dir = temp_dir;                // set curr_dir to temp dir
    target_dir = out_dir;               // set target_dir to out_dir 
    Workflow::list_files();             // list files of curr dir 

    std::vector<std::thread> threads;


    // iterate over files and call Workflow.reduce_file
    int j = 0;
    for(auto& file: file_list){
        if(DEBUG){
            std::cout << "DEUBG >> REDUCING FILE: " << curr_dir << file << std::endl;
        }
        std::cout << "REDUCING " << file << std::endl;

        threads.push_back(std::thread(&Workflow::reduce_file, this, reducer[j], sorter[j], file));
        j++;
        //Workflow::reduce_file(file);
    }

    for (int i = 0; i < file_list.size(); i++) {
        threads[i].join();
    }

    if(DEBUG){
        std::cout << "DEBUG >> FINISHED REDUCING FILES" << std::endl;
    }
}

// Reduce File
// Calls FileManagement.readFile, SortMap.sort, and Reduce.reduce
void Workflow::reduce_file(ReduceInterface* reduce, SortMap* sort,std::string file){
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
        sort->sort(line);
    }

    // send sortMap elements to reducer, word by word 
    for (auto x = sort->begin(); x != sort->end(); x++){
        if(DEBUG) {
            std::cout << "DEBUG >> SEND SORTED KEY,VAL TO REDUCE.REDUCE" << std::endl;
        }
        fm->writeFile(reduce->reduce(x->first, x->second), target_dir, file);
    }

    // clear the SortMap after it's been written out 
    sort->clear();

}


// Finish Mapping, Sorting, and Reducing 
// write SUCCESS file to out dir
void Workflow::finish(void){
    if(DEBUG){
        std::cout << "writing SUCCESS to " << out_dir << std::endl;
    }
    fm->writeFileSuccess(out_dir, "SUCCESS");
}

void Workflow::get_fd(void){
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
}

void Workflow::set_sock(void){
    
    if (setsockopt(server_fd, SOL_SOCKET,
				 SO_REUSEADDR, (char *) & opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

}

void Workflow::bind_sock(void){
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(LPORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void Workflow::listen_func(void){
    // listen
    
    if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

    // accept
    if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

    while(true) {
	    valread = _read(new_socket, buffer, 1024);
	    if (buffer == "map\n"){
            std::cout << "mapping";
            // call map method
        }
        else {
            // call reduce method 
            std::cout << "reducing";
        }
	    //send(new_socket, hello.c_str(), hello.length(), 0);
	    //printf("Hello message sent\n");
    }
}

//network methods 
void Workflow::serve(void){
  
    Workflow::get_fd();

	// Forcefully attaching socket to the port 8080
	Workflow::set_sock();

    Workflow::bind_sock();
	
    while(listen_var){
        std::cout << "listening on port: " << LPORT <<  std::endl;
        Workflow::listen_func();
    }

    std::cout << "No longer listening" << std::endl;

	// closing the connected socket
	_close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SD_BOTH);
	//return 0;
}

// Workflow order of operations 
int Workflow::start(void){
  
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    // verify dirs should happen at the controller 
    // though, the workflow will have access to the files as well
    Workflow::verify_dirs();        // Verify Directories

    // The workflow will load the DLL's 
    //Commented out for testing on linux 
    Workflow::load_dlls();

    Workflow::serve(); 
    //This will get moved into a listen method() 
    //Workflow::map_files();          // Map_Files

    // This will get moved into a listen method() 
    //Workflow::reduce_files();       // Reduce Files

    
    // This will also get moved into a listen method()
    Workflow::finish();             // Finish

    //Workflow::free_dlls();          // Unload dlls

    return 1;
}
