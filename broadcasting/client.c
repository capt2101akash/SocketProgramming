#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int server_socket,client_socket,p=1;
	struct sockaddr_in server;
	if((client_socket=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("Socket: ");
		exit(-1);
	}
	struct timeval time;
	time.tv_sec=2;
	time.tv_usec=0;
	server.sin_family=AF_INET;
	server.sin_port=htons(9000);
	server.sin_addr.s_addr=htonl(INADDR_BROADCAST);
	bzero(server.sin_zero,8);
//	printf("%d\n",ntohl(server.sin_addr.s_addr));
/*	if((connect(client_socket,(struct sockaddr*)&server,sizeof(struct sockaddr_in)))==-1)
	{
		perror("connect: ");
		exit(-1);
	}*/
	if(bind(client_socket,(struct sockaddr*)&server,sizeof(server))==-1)
	{
		perror("bind: ");
		exit(-1);
	}
	/*if((setsockopt(client_socket,SOL_SOCKET,SO_BROADCAST,&time,sizeof(time)))==-1)
	{
		perror("setsockopt: ");
		exit(-1);
	}*/
	char input[1024];
	char output[1024];
	int sent;
	int len=1;
	struct sockaddr_in client;
	socklen_t len1=sizeof(client);
	socklen_t srv_len=sizeof(server);
	client.sin_addr.s_addr=INADDR_ANY;
	printf("%s\n",inet_ntoa(client.sin_addr));
//	inet_aton("255.255.255.255",&client.sin_addr);
	/*fgets(input,1024,stdin);
	sent=send(client_socket,input,strlen(input),0);
	printf("Sent message is : %s",input);*/
	//scanf("You want to receive broadcast packet or not (1 for yes , 0 for no): %c\n",argv[1]);
	//int e=atoi(argv[1]);
	while(1)
	{
		while(len)
		{
			len=recvfrom(client_socket,output,1024,0,(struct sockaddr*)&client,&len1);
			output[len]='\0';
			//printf("%d\n",len);
			printf("Recieved message is : %s\n",output);
		}
		close(client_socket);
		exit(0);
	}
}
