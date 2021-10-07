#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<stdlib.h>

int main ( )

{

    system("clear");
    int serverfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(serverfd==-1)
    {   
        perror("Socket creation failed\n");
        exit(0);
    }

    struct sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_port=htons(5000);
    server.sin_addr.s_addr=INADDR_ANY;
    int b=bind(serverfd,(struct sockaddr*)&server,sizeof(server));
    if(b==-1)
    {
        perror("binding failure\n");
        exit(0);
    }
    listen(serverfd,5);
    int size=sizeof(struct sockaddr);
    while(1)
    {
        int clientfd=accept(serverfd,(struct sockaddr*)&client,&size);
        if(clientfd==-1)
        {
            perror("accept error\n");
            exit(0);
        }
        printf("Connection accepted\n");
        char snd[20],rcv[20];
        for(;;)
        {
            int r=recv(clientfd,rcv,sizeof(rcv),0);
            rcv[r]='\0';
            printf("Msg From client is: %s\n",rcv);
            if(strcmp(rcv,"exit")==0)
            {
                break;
            }
            printf("enter msg to pass to client: ");
            scanf("%s",snd);
            send(clientfd,snd,strlen(snd),0);
        }
    }
  return 0;
}
