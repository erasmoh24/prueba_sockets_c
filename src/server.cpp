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
    int client,server;
    bool exit = true;
    char buffer[BUFSIZE];

    struct sockaddr_in server_addr;

    socklen_t size;

    client = socket(AF_INET,SOCK_STREAM,0);

    if(client < 0) {
        printf("\nError establishing socket. \n");
        return -1;
    }

    printf("\n=> Socket server has been created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = PORT;

    if((bind(client,(struct sockaddr*)& server_addr,sizeof(server_addr))) < 0) {
        printf("=> Error binding connection, the socket has already been established. \n");
        return -1;
    }

    size = sizeof(server_addr);
    printf("=> Waiting clients. \n");

    listen(client,1);

    int clientCount = 1;
    server = accept(client,(struct sockaddr*)& server_addr,&size);

    if(server < 0) printf("=> Error on accepting. \n"); 

    while(server > 0) {
        strcpy(buffer,"=> Server connected. \n");
        send(server,buffer,BUFSIZE,0);
        printf("=> Connected with the client # %d ",clientCount);

        printf("Client: ");
        do {
            recv(server,buffer,BUFSIZE,0);
            printf("%c ",buffer);
            if(*buffer == '&') {
                *buffer = '*';
                exit = true;
            }
        }while(*buffer != '*');

        while(exit) {
            printf("\nServer: ");
            do {
                cin >> buffer;
                send(server,buffer,BUFSIZE,0);
                if(*buffer == '&') {
                    send(server,buffer,BUFSIZE,0);
                    *buffer = '*';
                    exit = false; 
                }

            }while(*buffer != '*');

            printf("Client: ");
            do {
                recv(server,buffer,BUFSIZE,0);
                printf("%c ",buffer);
                if(*buffer == '&') {
                    *buffer == '*';
                    exit = false;
                }
            }while(*buffer != '*');
        }

        printf("\n\n=> Connection finalized with IP %c",inet_ntoa(server_addr.sin_addr));
        close(server);
        printf("\nSee you later :) \n");
        exit = false;
        return 1;
    }

    close(client);
    return 0;
}