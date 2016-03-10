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
#include<pthread.h>

pthread_t th1;
void *broadcasting(void *arg)
{
	printf("Broadcast your IP...\n");
	pthread_t id=pthread_self();
	int sock;
        int p=1;
        struct sockaddr_in server,client;
        if((sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1)
        {
                perror("socket: ");
                exit(-1);
        }
        server.sin_family=AF_INET;
        server.sin_port=htons(9000);
        server.sin_addr.s_addr=htonl(INADDR_BROADCAST);
        bzero(&server.sin_zero, 8);
        unsigned int len=sizeof(struct sockaddr_in);
        if((setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&p,sizeof(p)))==-1)
        {
                perror("setsockopt: ");
                exit(-1);
        }
        int cl;
        int sent;
        char msg[1024];
        while(1)
        {
                fgets(msg,1024,stdin);
                msg[strlen(msg)]='\0';
                if((sent=sendto(sock,msg,strlen(msg),0,(struct  sockaddr*)&server,sizeof(server)))==-1)
                {
                        perror("sendto: ");
                        exit(-1);
                }
                printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(server.sin_addr));
        }
        close(sock);
}
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
	int cl=-1;
	int sent;
	int data_len;
	while(1)
	{
		pthread_create(&(th1), NULL, &broadcasting, NULL);
	//	printf("%s\n",inet_ntoa(client.sin_addr));
		if((cl=accept(sock,(struct sockaddr*)&client, &len))==-1)
		{
			perror("socket: ");
			exit(-1);
		}
		//printf("cl is :- %d\n",cl);
		printf("Client connected from port no. %d and IP %s \n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
		//printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr));
		int ret=0;
		if(cl!=-1)
		{
			pthread_cancel(th1);
		}
		data_len = 1;
		char input[1024]="Thanks For Connecting!";
		char data[1024]={0};
		while(data_len)
		{
//			printf("**\n");
			printf("Waiting For Client's message....\n");
			data_len=recv(cl, data, 1024 ,0);
			data[data_len-1]='\0';
			printf("Received message: %s\n",data);
			if(data_len)
			{
				printf("Send your Message.....\n");
				fgets(input,1024,stdin);
//				getchar();
				send(cl,input,strlen(input),0);
				//input[data_len-1]='\0';
				printf("Sent message is: %s\n",input);
			}
		}
		printf("Client Disconnected\n");
		close(cl);

	}
	sleep(5);
	close(sock);
}



