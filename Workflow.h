#ifndef WORKFLOW_H
#define WORKFLOW_H



class Workflow 
{
    private:

        std::string in_dir;
        std::string temp_dir;
        std::string out_dir;
        std::vector<std::string> file_list; 

    public:
        
        explicit Workflow();
        explicit Workflow(std::string in_dir, std::string temp_dir, std::string out_dir);

        void verify_dirs(void);

        void list_files(void);

        void read_file(void);

        void err_out(std::string);

        int start();
};

#endif