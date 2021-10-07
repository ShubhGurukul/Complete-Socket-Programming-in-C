#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

int main()
{
    char server_message[256]="you have reached the server";
        int server_socket;
        server_socket=socket(AF_INET, SOCK_STREAM,0);
        
          
        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9001);
        server_address.sin_addr.s_addr=INADDR_ANY;

    // bind function
     if(bind(server_socket,(struct sockaddr *) &server_address, sizeof(server_address))<0)
     printf("bind failed");
    
    //listen function 
        if (listen(server_socket,5)<0)
        printf("listen failed");
       
        //accept function
        int client_socket= accept(server_socket, NULL, NULL);
        
        
        send(client_socket, server_message, sizeof(server_message),0);

        
    return 0;
}
