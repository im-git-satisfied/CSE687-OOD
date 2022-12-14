#include <arpa/inet.h>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class Controller
{
    public:
        explicit Controller();
        void runMapReduceController();
        int setUpSocket();
        void endControllerSocket();
    
    private:
        int sock;
        int valread;
        int client_fd;
        struct sockaddr_in serv_addr;
        char* heartbeat;
        char* map;
        char* reduce;
        char* start;
        char* stop;
};