#define SERVER_PORT 2222
#define LENGTHOFREQUEST 20
#define FILENAMESIZE 512
#define BUFFERSIZE 1024
#include <netinet/in.h> //for sockaddr_in
#include <sys/types.h> //for socket
#include <sys/socket.h> //for socket
#include <string.h> //for bzero
#include <stdio.h>
#include <stdlib.h> //for exit
int main(int argc,char **argv)
{
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	//int on,ret;
	int sock_server=socket(AF_INET,SOCK_STREAM,0);
	//on = 1;
	//ret = setsockopt(sock_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.s_addr=htons(INADDR_ANY);

	if(sock_server<0)
	{
		printf("create the socket failed!\n");
		exit(1);
	}
	if(bind(sock_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		printf("bind the server_addr and sock_server has a error\n");
		exit(1);
	}
	if(listen(sock_server,LENGTHOFREQUEST))
	{
		printf("sever listen failed!\n");
		exit(1);
	}

	while(1)
	{
		struct sockaddr_in client_addr;
		int length=sizeof(client_addr);
		int sock_client=accept(sock_server,(struct sockaddr*)&client_addr,&length);
		
		
		if(sock_client < 0)
		{
			//printf("%d\n",12);
			printf("accept has a error!\n");
			break;
			
		}

		char buffer[BUFFERSIZE];
		bzero(buffer,BUFFERSIZE);
		int len=recv(sock_client,buffer,BUFFERSIZE,0);
		if(len<0)
		{
			printf(" sever accept data has a error!\n");
			exit(1);
		}
		char filename[FILENAMESIZE];
		bzero(filename,FILENAMESIZE);
		strncpy(filename,buffer,strlen(buffer)>FILENAMESIZE?FILENAMESIZE:strlen(buffer));
		FILE *fp=fopen(filename,"r");
		if(fp==NULL)
		{
			printf("open the file has a error!\n");
			break;
		}
		else
		{
			bzero(buffer,BUFFERSIZE);
			int file_len=0;
			while((file_len=fread(buffer,sizeof(char),BUFFERSIZE,fp))>0)
			{
				printf("send %d data to client\n",file_len);
				if(send(sock_client,buffer,file_len,0)<0)
				{
					printf("send data has a error!\n");
					break;
				}
				bzero(buffer,BUFFERSIZE);
			}

		}
		fclose(fp);
		close(sock_client);


	}

	printf("%d\n",12);
	close(sock_server);
	return 0;
}