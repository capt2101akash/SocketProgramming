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
int main()
{	
	int sock;
	int p=1;
	struct sockaddr_in server,client;
	if((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
	{
		perror("socket: ");
		exit(-1);
	}
	//memset(&server,0,sizeof(struct sockaddr_in));
	server.sin_family=AF_INET;
	server.sin_port=htons(9000);
	server.sin_addr.s_addr=htonl(INADDR_BROADCAST);
//	printf("%d\n",ntohl(server.sin_addr.s_addr));
	bzero(&server.sin_zero, 8);
//	client.sin_family=AF_INET;
	//client.sin_port=htons(20000);
//	inet_aton("255.255.255.255",&client.sin_addr);
//	bzero(&client.sin_zero,8);
	unsigned int len=sizeof(struct sockaddr_in);
	if((setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&p,sizeof(p)))==-1)
	{
		perror("setsockopt: ");
		exit(-1);
	}
	/*if((bind(sock,(struct sockaddr*)&server,len))==-1)
	{
		perror("bind");
		exit(-1);
	}*/
/*	if((listen(sock,10))==-1)
	{
		perror("listen");
		exit(-1);
	}*/	
	int cl;
	int sent;
	char msg[1024];
/*	if((cl=accept(sock,(struct sockaddr*)&client, &len))==-1)
	{
		perror("socket: ");
		exit(-1);
	}*/
	while(1)
	{
		fgets(msg,1024,stdin);
		msg[strlen(msg)]='\0';
		if((sent=sendto(sock,msg,strlen(msg),0,(struct 	sockaddr*)&server,sizeof(server)))==-1)
		{
			perror("sendto: ");
			exit(-1);
		}
		printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(server.sin_addr));			
	}
	close(sock);
}