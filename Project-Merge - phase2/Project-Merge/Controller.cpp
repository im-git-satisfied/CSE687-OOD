// Client side C/C++ program to demonstrate Socket
// programming
#include "Controller.hpp"
#define PORT 8000

// constructor
Controller::Controller()
{
    heartbeat = "heartbeat\n";
    map = "map;";
    reduce = "reduce;";
    start = "start;";
    stop = "stop;";
}

// set up socket with correction info and connect
int Controller::setUpSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    return 0;
}

// runs the controller for the map reduce
void Controller::runMapReduceController()
{
    char buffer[1024] = {0};
    // mapping part of the controller 
    send(sock, map, strlen(map), 0);

    int x = 0;
    while(x < 10)
    {
        x++;
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        if (x == 5)
        {
            send(sock, start, strlen(start), 0);
        }
        if (strstr(buffer,"EXITING"))
        {
            break;
        }        
        send(sock, heartbeat, strlen(heartbeat), 0);
    }

    valread = read(sock, buffer, 1024);
    send(sock, stop, strlen(stop), 0);
    printf("%s\n", buffer);

    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // reduce part of the controller
    send(sock, reduce, strlen(reduce), 0);

    x = 0;
    while(x < 10)
    {
        x++;
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        if (x == 5)
        {
            send(sock, start, strlen(start), 0);
        }
        if (strstr(buffer,"EXITING"))
        {
            break;
        }
        send(sock, heartbeat, strlen(heartbeat), 0);
    }
    valread = read(sock, buffer, 1024);
    send(sock, stop, strlen(stop), 0);
    printf("%s\n", buffer);
}

// ends the controller socket
void Controller::endControllerSocket()
{
    close(client_fd);
}

int main(int argc, char const* argv[])
{
    Controller client = Controller();

    client.setUpSocket();
    
    client.runMapReduceController();

    client.endControllerSocket();

    return 0;
}