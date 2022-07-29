#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 1500 
#define BUFSIZE 1024

using namespace std;

int main() {
    int client;
    bool exit = true;
    char buffer[BUFSIZE];
    char* ip = "127.0.0.1";

    struct sockaddr_in server_addr;

    client = socket(AF_INET,SOCK_STREAM,0);

    if(client < 0) {
        printf("\n It has occurred an error with the connection of the socket \n");
        return -1;
    }

    printf("\n=> Socket client has been created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if(connect(client,(struct sockaddr *)& server_addr, sizeof(server_addr)) == 0) {
        printf("=> Connection to port number: %d \n",PORT);
    }

    printf("=> Waiting response from the server. \n");
    recv(client,buffer,BUFSIZE,0);
    printf("=> Connection confirmed. \n");

    printf("\n\n=> Enter & to end the connection \n");

    do {
        printf("Client: ");
        do {
            cin >> buffer;
            send(client,buffer,BUFSIZE,0);
            if(*buffer == '&') {
                send(client,buffer,BUFSIZE,0);
                *buffer = '*';
                exit = false;
            }
        }while(*buffer != 42);
        printf("Server: ");
        do {
            recv(client,buffer,BUFSIZE,0);
            cout << buffer << " ";
            if(*buffer == '&') {
               *buffer = '*'; 
               exit = false;
            }
        }while(*buffer != 42);
        cout << std::endl;
    }while(exit);

    printf("\n=> Connection finalized.\nSee you later:)\n");

    close(client);
    return 0;
}