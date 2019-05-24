#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>    //socket() 
#include <netinet/in.h>   // inet_addr()
#include <arpa/inet.h>
#include <unistd.h>        // read()/ write
 
#include <errno.h>
extern int errno;
int main(int argc, char *argv[])
{
 
   int fd = socket(AF_INET, SOCK_DGRAM, 0);
   fprintf(stderr, "socket id = %d\n", fd);
 
   // 地址复用
   int on = 1;
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
 
 
   struct sockaddr_in servaddr;
   servaddr.sin_family = AF_INET;
   if(argc == 2)
      servaddr.sin_port =  htons(atoi(argv[1]));
   else
      servaddr.sin_port   = htons(4000);
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
   //servaddr.sin_addr.s_addr = htonl(127.0.0.1); // 0.0.0.0
   int ret = bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
   if(ret < 0)
   {
      fprintf(stderr, "error:%s\n", strerror(errno));
      close(fd);
      return -1;
   }
   struct sockaddr_in peer;  // 保存对方的地址信息
   socklen_t size;
   char buff[1024];
   int cnt;
   char ip[16];
   while(1)
   {
      bzero(&peer, sizeof(peer));
      size = sizeof(peer);
      //recv
      cnt = recvfrom(fd, buff, 1024, 0, (struct sockaddr *)&peer, &size);
      printf("ip:%s, port:%d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
      inet_ntop(AF_INET, &(peer.sin_addr), ip, 16);
      printf("ip:%s, port:%d\n", ip, ntohs(peer.sin_port));
      printf("recv: %s\n", buff);
      if(cnt <= 0)
         fprintf(stderr, "recv error or end\n");
      else
         sendto(fd, buff, cnt, 0, (struct sockaddr *)&peer, sizeof(peer));
   }
   close(fd);
   return 0;
}
