#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUFFER_SIZE 51200
#define LENGTH_OF_REQUEST 20
#define LENGTH_OF_FILENAME 512
#define PORT 3456
int main(int argc,char **argv)
{
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=htons(INADDR_ANY);
	int sock_listen=socket(AF_INET,SOCK_STREAM,0);
	if(bind(sock_listen,&server_addr,sizeof(server_addr)))
	{
		printf("There is error in binding the server_addr and sock_listen.\n");
		exit(1);
	}
	if(listen(sock_listen,LENGTH_OF_REQUEST)<0)
	{
		printf("There is a error in listening.\n");
		exit(1);
	}
	struct  sockaddr_in client_addr;
	while(1)
	{
		int lenofseraddr=sizeof(client_addr);
		int sock_client=accept(sock_listen,(struct sockaddr*)&client_addr,&lenofseraddr);
		if(sock_client<0)
		{
			printf("there is a error in accepting the clientdata.\n");
			break;
		}
		char buffer[BUFFER_SIZE];
		bzero(buffer,BUFFER_SIZE);
		if(recv(sock_client,buffer,BUFFER_SIZE,0)<0)
		{
			printf("There is a error in receiving the filename.\n");
			break;
		}
		char filename[LENGTH_OF_FILENAME];
		bzero(filename,LENGTH_OF_FILENAME);
		strncpy(filename,buffer,strlen(buffer)>LENGTH_OF_FILENAME?LENGTH_OF_FILENAME:strlen(buffer));

		FILE *fp=fopen(filename,"w");
		if(fp==NULL)
		{
			printf("open the file has a error!\n");
			break;
		}
		bzero(buffer,BUFFER_SIZE);
		int bytes=0;
		while(bytes=recv(sock_client,buffer,BUFFER_SIZE,0))
		{
			//printf("123\n");
			if(bytes<0)
			{
				printf("there is error in recerving the file data.\n");
				break;
			}
			printf("%d\n",bytes);
			int len_bytes=fwrite(buffer,sizeof(char),bytes,fp);
			if(len_bytes<bytes)
			{
				printf("there is a error in writing the file!\n");
				break;
			}
			bzero(buffer,BUFFER_SIZE);
		}

		fclose(fp);
		close(sock_client);
		break;


	}
	printf("receive the file finished!\n");
	close(sock_listen);

	return 0;
}