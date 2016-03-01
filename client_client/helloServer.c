#include<stdio.h>
//#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>
//using namespace std;
int main(int argc , char **argv)
{
	int sock;
	struct sockaddr_in server,client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		perror("socket: ");
		exit(-1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero, 8);
	unsigned int len=sizeof(struct sockaddr_in);
	if((bind(sock,(struct sockaddr*)&server,len))==-1)
	{
		perror("bind");
		exit(-1);
	}
	if((listen(sock,10))==-1)
	{
		perror("listen");
		exit(-1);
	}
	int cl;
	int sent;
	int data_len;
	while(1)
	{
	//	printf("%s\n",inet_ntoa(client.sin_addr));
		if((cl=accept(sock,(struct sockaddr*)&client, &len))==-1)
		{
			perror("socket: ");
			exit(-1);
		}
	//	printf("%d\n",cl);
		printf("Client connected from port no. %d and IP %s \n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
		//printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr));
		data_len = 1;
		char input[1024]={0};
		char data[1024]={0};
		while(data_len)
		{
//			printf("**\n");
			printf("Waiting For Sender's message....\n");
			data_len=recv(cl, data, 1024 ,0);
			printf("Received message: %s\n",data);
			if(data_len)
			{
				printf("Send your Message.....\n");
				fgets(input,1024,stdin);
//				getchar();
				send(cl,input,strlen(input),0);
//				input[data_len]='\0';
				printf("Sent message is: %s\n",input);
			}
		}
		printf("Client Disconnected\n");
		close(cl);
	}
	close(sock);
}



