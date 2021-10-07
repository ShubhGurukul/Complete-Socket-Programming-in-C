#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

int main()
{
        int client_socket;
        client_socket=socket(AF_INET, SOCK_STREAM,0);
        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9001);
        server_address.sin_addr.s_addr=INADDR_ANY;

    //connect function  
    int connection_status= connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        char server_resp[256];
   
        if(connection_status<0)
        {
                printf("error here");
        }
        
        recv(client_socket, &server_resp, sizeof(server_resp),0);

        printf("%s\n", server_resp);

        
    return 0;
    }
