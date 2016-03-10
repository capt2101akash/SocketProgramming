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
//using namespace std;
pthread_t th1,th2;
void *broadcast(void *arg)
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

/*void *receiver(void *arg)
{
	printf("Waiting For the Server's broadcast for it's IP.....\n");
	pthread_t id=pthread_self();
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
        if(bind(client_socket,(struct sockaddr*)&server,sizeof(server))==-1)
        {
                perror("bind: ");
                exit(-1);
        }
        char input[1024];
        //char output[1024];
        int sent;
        int len=1;
        struct sockaddr_in client;
        socklen_t len1=sizeof(client);
        socklen_t srv_len=sizeof(server);
        client.sin_addr.s_addr=htons(atoi("10.0.1.25"));
//        printf("%s\n",inet_ntoa(client.sin_addr));
        while(1)
        {
                while(len)
                {

			while(PAUSE==1){}
                        len=recvfrom(client_socket,output,1024,0,(struct sockaddr*)&client,&len1);
                        output[len-1]='\0';
                }
                close(client_socket);
                exit(0);
        }
}*/

void accept_conn(struct in_addr cli,uint16_t cli1,int cfd)
{
	printf("Client connected from port no. %d and IP %s \n",ntohs(cli1),inet_ntoa(cli));
	//printf("Sent %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr));
	printf("cl-2 :- %d",cfd);
	int data_len = 1;
	char input[1024]={0};
	char data[1024]={0};
	while(data_len)
	{
//		printf("**\n");
		printf("Waiting For Sender's message....\n");
		data_len=recv(cfd, data, 1024 ,0);
		printf("Received message: %s\n",data);
		if(data_len)
		{
			printf("Send your Message.....\n");
			fgets(input,1024,stdin);
//			getchar();
			send(cfd,input,strlen(input),0);
//			input[data_len]='\0';
			printf("Sent message is: %s\n",input);
		}
	}
	printf("Client Disconnected\n");
	close(cfd);
}
int main(int argc , char **argv)
{
	int sock;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int data_len;
	int cl;
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
	int sent;
	int a[1000]={0};
	int i=0,j=0,l=0,o=0;
	uint16_t c[1000]={0};
	struct in_addr b[1000]={0}; 
//	int data_len;
	//pthread_create(&(th2), NULL, &receiver, NULL)
	int rc=0;
	while(1)
	{
	//	printf("%s\n",inet_ntoa(client.sin_addr));
		pthread_create(&(th1), NULL, &broadcast, NULL);
		cl=accept(sock,(struct sockaddr*)&client, &len);
		if(cl==-1)
		{
			perror("socket: ");
			exit(-1);
		}
		if(cl!=-1)
		{
			printf("cancelling the thread\n");
			rc=pthread_cancel(th1);
		}
		if(rc==0) printf("thread cancelled succesfully\n");
		printf("cl is :- %d\n",cl);
		a[i++]=cl;
		b[l++]=client.sin_addr;
		c[o++]=client.sin_port;
		int cho,k=0;
		if(i>=2)
		{
		printf("Which client you want to connect :- \n");
		for(k=0;k<i;k++)
		{
			printf("%d. %s\n",k+1,inet_ntoa(b[k]));
		}
		scanf("%d",&cho);
		accept_conn(b[cho-1],c[cho-1],a[cho-1]);
		}
		j++;
	//	printf("%d\n",cl);
	}
	sleep(5);
	close(sock);
}