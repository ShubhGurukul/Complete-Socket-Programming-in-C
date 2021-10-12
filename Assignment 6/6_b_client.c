#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include<netinet/in.h>
#include<netinet/ip.h>
#include<stdlib.h>

int main()

{
    system("clear");
    int clientfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(clientfd==-1)
    {
        perror("Socket creation failed\n");
        exit(0);
    }
    struct sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_port=htons(5000);
    server.sin_addr.s_addr=INADDR_ANY;
    int c=connect(clientfd,(struct sockaddr*)&server,sizeof(server));
    if(c==-1)
    {
        perror("Connection error\n");
        exit(0);
    }
    printf("Connected to Server\n");
    char snd[20],rcv[20];
    while(1)
    {
        printf("enter msg to pass to server: ");
        scanf("%s",snd);
        send(clientfd,snd,strlen(snd),0);
        if(strcmp(snd,"exit")==0)
        {
            break;
        }
        int r=recv(clientfd,rcv,sizeof(rcv),0);
        rcv[r]='\0';
        printf("Msg From client is: %s\n",rcv);
    }
}
