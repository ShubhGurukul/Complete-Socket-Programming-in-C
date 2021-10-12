#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct in_addr        localInterface;
struct sockaddr_in    sockaddr;
int                   server_socket;
int                   datalen;
char                  databuf[10]="hello";

int main (int argc, char *argv[])
{

  server_socket = socket(AF_INET, SOCK_DGRAM, 0);

  /*
   * Initialize the group sockaddr structure with a
   * group address of 225.1.1.1 and port 5555.
   */
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = inet_addr("225.1.1.1");
  sockaddr.sin_port = htons(1200);

  /*
   * Disable loopback so you do not receive your own datagrams.
   */
  {
    char loopch=0;

    if (setsockopt(server_socket, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char *)&loopch, sizeof(loopch)) < 0) {
      perror("setting IP_MULTICAST_LOOP:");
      close(server_socket);
      exit(1);
    }
  }

  /*
   * Set local interface for outbound multicast datagrams.
   * The IP address specified must be associated with a local,
   * multicast-capable interface.
   */
  int add=localInterface.s_addr = INADDR_ANY;
  printf("%d",add);
  if (setsockopt(server_socket, IPPROTO_IP, IP_MULTICAST_IF,
                 (char *)&localInterface,
                 sizeof(localInterface)) < 0) {
    perror("setting local interface");
    exit(1);
  }
  else{printf("done");}

  /*
   * Send a message to the multicast group specified by the
   * sockaddr sockaddr structure.
   */
  datalen = 10;
 // databuf="mesage from server";
  if (sendto(server_socket, databuf, datalen, 0,
             (struct sockaddr*)&sockaddr,
             sizeof(sockaddr)) < 0)
  {
    perror("sending datagram message");
  }
  else
  {
    printf("sent");
  }
  return 0;
}


