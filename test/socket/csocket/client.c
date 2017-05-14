#define SERVER_PORT 5555
#define LENGTHOFREQUEST 20
#define FILENAMESIZE 512
#define BUFFERSIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//#include <netdb.h>
#include <string.h> //for bzero
#include <sys/types.h> //for socket
#include <netinet/in.h>//for sockaddr_in
#include <sys/socket.h>//for socket
int main(int argc,char **argv)
{
   struct sockaddr_in client_addr;
   bzero(&client_addr,sizeof(client_addr));
   int sock_client=socket(AF_INET,SOCK_STREAM,0);
   client_addr.sin_family=AF_INET;
   client_addr.sin_port=htons(0);
   client_addr.sin_addr.s_addr=INADDR_ANY;
   
   if(sock_client < 0)
   {
      printf("sock_client is a error!\n");
      exit(1);
   }
   if(bind(sock_client,&client_addr,sizeof(struct sockaddr))<0)
   {
      printf("bind sock_lient and client_addr has a error\n");
      exit(1);
   }
   struct sockaddr_in server_addr;
   bzero(&server_addr,sizeof(server_addr));
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(SERVER_PORT);
    printf("%s\n","123");
   if(inet_pton(AF_INET,argv[1],&server_addr.sin_addr)==0)
   {
      printf("Server IP is a error!\n");
      exit(1);
   }
   
      if(connect(sock_client,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))<0)
      {
         printf("connet failed!\n");
         exit(1);
      }

      char filename[30];
      printf("Please input a filename:\n");
      scanf("%s",filename);
      char buffer[BUFFERSIZE];
      bzero(buffer,BUFFERSIZE);
      strncpy(buffer,filename,strlen(filename)>BUFFERSIZE?BUFFERSIZE:strlen(filename));
      int filename_len=send(sock_client,buffer,BUFFERSIZE,0);
     
      if(filename_len<0)
      {
         printf("send filename has a error!\n");
         exit(1);
      }
     
      FILE *fp=fopen(filename,"w");
      
      if(fp==NULL)
      {
         printf("open the file has a error!\n");
         exit(1);
      }

      bzero(buffer,BUFFERSIZE);
      int len=0;
      while(len=recv(sock_client,buffer,BUFFERSIZE,0))
      {
         if(len<0)
         {
            printf("Receive data failed from FTPserver\n");
            break;
         }
         int write_len=fwrite(buffer,sizeof(char),len,fp);
         if(write_len<len)
         {
            printf("write file has a error!\n");
            break;
         }

         bzero(buffer,BUFFERSIZE);
      }

      printf("Received file:%s form server%s\n",filename,argv[1]);
      fclose(fp);
      close(sock_client);
      return 0;



}