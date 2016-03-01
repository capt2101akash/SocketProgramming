#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	int server_socket,client_socket;
	struct sockaddr_in server,client;
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Socket: ");
		exit(-1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&server.sin_zero,8);

	if(connect(client_socket,(struct sockaddr*)&server,sizeof(struct sockaddr_in))==-1)
	{
		perror("connect: ");
		exit(-1);
	}
	char input[1024];
	char output[1024];
	int sent;
	int len;
	while(1)
	{
		printf("Send Your Message.....\n");
		fgets(input,1024,stdin);
		sent=send(client_socket,input,strlen(input),0);
		printf("Sent message is : %s",input);
		printf("Recieving Server's Message......\n");
		len=recv(client_socket,output,1024,0);
		output[len]='\0';
		printf("Recieved message is : %s\n",output);
	}
	close(client_socket);
}
