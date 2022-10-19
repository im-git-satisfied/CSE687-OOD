#ifndef EXECUTIVE_H
#define EXECUTIVE_H



class Executive 
{
    private:
    
        int count;
        std::string in_dir;
        std::string inter_dir;
        std::string out_dir;


        bool err;
        char **argv;

    public:
        
        explicit Executive();
        explicit Executive(int argc, char** argv);

        void verify_count(void);

        void print_help(void);

        void grab_dirs(void);

        void err_out(std::string);

        int start();
};

#endif