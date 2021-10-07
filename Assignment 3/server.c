#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<unistd.h>
#include <netdb.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void serverResponse(int sockfd)
{
    char buff[MAX];
    int n;
    while(1)
    {
        bzero(buff, MAX); // set buff with null values
        read(sockfd, buff, sizeof(buff));// Read the msg from client and copy it in buffer
        printf("From Client : %s\n",buff);
        if(strncmp("exit", buff,4) == 0)
        {
            printf("Server Exit..\n");
            break;
        }
        char *rev;
        rev = buff;
//      printf("%d, %s\n",strlen(rev),rev);
        int size = strlen(rev)-1;
        char strrev[size+1];
        for(int i=size; i>=0; i--)
        strrev[size-i] = rev[i];
        // send the reversed string to client
        write(sockfd, strrev, sizeof(strrev));
        bzero(buff, MAX);
        n = 0;
        printf("Reverse String send\n");
/*      printf("(server)For Exit type 'exit'\n");
        while ((buff[n++] = getchar()) != '\n');
//      write(sockfd, buff, sizeof(buff));
        if(strncmp("exit", buff,4) == 0)
        {
            printf("Server Exit..\n");
            break;
        }
*/      
        }




}

int main()
{
    //1. Making socket
    int sockfd, connfd, len;

    struct sockaddr_in servaddr, cli;

    // socket creation and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        printf("Socket creation is failed..\n");
        exit(0);
    }
    else 
        printf("Socket successfully created..\n");

    // 2. Assigning IP,PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    // 3. Binding newly created socket to given IP and verify

    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket Binding is failed..\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // 4. Listen new client request and verify
    if((listen(sockfd,5)) != 0)
    {
        printf("Listen failed..\n");
        exit(0);
    }
    else 
        printf("Server is listening ... \n");
    
    // 5. Accept the data packet from client and verify
    len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd <0)
    {
        printf("Server accept failed..\n");
    }
    else
        printf("Server accept the client..\n");

    // 6. 
    serverResponse(connfd);
    
    // 7. Close the socket
    // close(connfd);
    close(sockfd);

    return 0;
}
