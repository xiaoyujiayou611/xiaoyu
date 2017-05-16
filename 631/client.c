#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 51200
#define LENGTH_OF_REQUEST 20
#define LENGTH_OF_FILENAME 512
#define PORT 3456
int  main(int argc,char **argv)
{
	struct sockaddr_in client_addr,server_addr;
	int sock_server,sock_client;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(0);
	client_addr.sin_addr.s_addr=htons(INADDR_ANY);
	sock_client=socket(AF_INET,SOCK_STREAM,0);

	if(bind(sock_client,&client_addr,sizeof(struct sockaddr))<0)
	{
		printf("there is error in binging the sock_client and client_addr.\n");
		exit(1);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);

	if(inet_pton(AF_INET,argv[1],&server_addr.sin_addr)==0)
	{
		printf("server_addr is a error!");
		exit(1);
	}

	if(connect(sock_client,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))<0)
	{
		printf("there is a error in connecting server.\n");
		exit(1);
	}

	char filename[LENGTH_OF_FILENAME]="test.txt";
	char buffer[BUFFER_SIZE];
	bzero(buffer,BUFFER_SIZE);
	strncpy(buffer,filename,strlen(filename)>BUFFER_SIZE?BUFFER_SIZE:strlen(filename));
	send(sock_client,buffer,BUFFER_SIZE,0);
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("open the file has a error!\n");
		exit(1);
	}
	fseek(fp,0,SEEK_END);//将文件位置指针置于文件结尾
    int countbytes=ftell(fp);//得到当前位置与文件开始位置的字节偏移量。
    printf("%d\n",countbytes);
    fseek(fp,0,SEEK_SET);
	int bytes=0,sendedbytes=0;

	while((bytes=fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
	{
		//printf("123");
		clock_t start,end;
		double cost;
    	//struct tm *lt;
    	//time (&start);//获取Unix时间戳。
    	start=clock();   
		int sendbytes=0;
		//double starttime,endtime;
		//lt=localtime(&t);
		//starttime=lt->tm_sec;
		sendbytes=send(sock_client,buffer,BUFFER_SIZE,0);
		//lt=localtime(&t);
		//time(&end);
		end=clock();
		cost=end-start;
		printf("%.2lf\n",cost);
		//endtime=(lt->tm_sec<starttime?(lt->tm_sec+60):lt->tm_sec);
		if(sendbytes<bytes)
		{
			printf("There is a error in sending the data.\n");
			break;
		}
		//int costtime=endtime-starttime;
		sendedbytes+=sendbytes;
		double speed=sendbytes/(cost/1000);
		double process=(double)sendedbytes/countbytes*100;
		if(process>100)
			process=100;

		printf("------------------------------\n");
		printf("the current speed is:%.2lf\n",speed);
		printf("the process is:%.2lf%%\n",process);
		printf("------------------------------\n");
		bzero(buffer,BUFFER_SIZE);

	}
	printf("send file finished!\n");
	fclose(fp);
	close(sock_client);


	return 0;
}
