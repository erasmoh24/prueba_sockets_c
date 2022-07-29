#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define PORT 8989 
#define BUFSIZE 1024

using namespace std;

int main() {
    int client,server;
    bool exit = false;
    char buffer[BUFSIZE];

    struct sockaddr_in server_addr;

    socklen_t size;

    client = socket(AF_INET,SOCK_STREAM,0);

    if(client < 0) {
        std::cout <<"\nError establishing socket. \n";
        return 1;
    }

    std::cout << "\n=> Socket server has been created. \n";

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if((bind(client,(struct sockaddr*)& server_addr,sizeof(server_addr))) < 0) {
        std::cout << "=> Error binding connection, the socket has already been established. \n";
        return 1;
    }

    size = sizeof(server_addr);
    std::cout << "=> Waiting clients. \n";

    listen(client,1);

    int clientCount = 1;
    server = accept(client,(struct sockaddr*)& server_addr,&size);

    if(server < 0) std::cout << "=> Error on accepting. \n"; 
    while(server > 0) {
        strcpy(buffer,"=> Server connected. \n");
        send(server,buffer,BUFSIZE,0);
        std::cout << "=> Connected with the client #  " << clientCount;

        std::cout << "\nClient: ";
        do {
            recv(server,buffer,BUFSIZE,0);
            std::cout << buffer << " ";
            if(*buffer == '&') {
                *buffer = '*';
                exit = true;
            }
        }while(*buffer != '*');

        do{
            std::cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server,buffer,BUFSIZE,0);
                if(*buffer == '&') {
                    send(server,buffer,BUFSIZE,0);
                    *buffer = '*';
                    exit = true; 
                }

            }while(*buffer != '*');

            std::cout << "Client: ";
            do {
                recv(server,buffer,BUFSIZE,0);
                std::cout << buffer << " ";
                if(*buffer == '&') {
                    *buffer == '*';
                    exit = true;
                }
            }while(*buffer != '*');
        }while(!exit);

        std::cout << "\n\n=> Connection finalized with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        std::cout << "\nSee you later :) \n";
        exit = true;
        return 1;
    }

    close(client);
    return 0;
}