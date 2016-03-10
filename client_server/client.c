#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<signal.h>
#include<poll.h>
pthread_t th1;
int PAUSE;
char output[1024];

void exitfunc(int sig)
{
    _exit(1);
}
void *receiver(void *arg)
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
        //stop=time(NULL);
        
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
        //signal(SIGALRM,exitfunc);
        //alarm(12);
    return 0;
}
int mainagain();
int main(int argc, char **argv)
{
	int server_socket,client_socket;
	struct sockaddr_in server,client;
	PAUSE = 0;
	output[0]='\0';
	clock_t start,stop;
        double elap;
    struct timeval timeout;      
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
	pthread_create(&(th1), NULL, &receiver, NULL);
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
      	perror("Socket: ");
       	exit(-1);
   	}
   	/*if (setsockopt (client_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
   	                sizeof(timeout)) < 0)
   	        error("setsockopt failed\n");*/
	while(1)
	{
		if(strlen(output)>0)
		{
			PAUSE = 1;
			break;
		}	
	}	
/*	if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Socket: ");
		exit(-1);
	}*/
    printf("Server's IP is : %s\n",output);
	int acc=0;
	char st_output[1000];
	strcpy(st_output, output);
	printf("You want to connect to %s\n (0 for no 1 for yes) :- ",output);
	scanf("%d",&acc);
	if(acc==1){
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	struct in_addr addr;
	int i=0;
	if((i=inet_aton(st_output,&server.sin_addr))==0)
	{
		
		printf("Invalid IP: \n");
		exit(-1);
	}
//	server.sin_addr.s_addr=(struct in_addr_t)addr;
//	printf("%d\n",server.sin_addr.s_addr);
	PAUSE = 0;
	bzero(&server.sin_zero,8);
	if(connect(client_socket,(struct sockaddr*)&server,sizeof(struct sockaddr_in))==-1)
	{
		perror("connect: ");
		exit(-1);
	}
	char input[1024]="Your Welcome";
	char output[1024];
	int sent;
	int len=0,j=0;
	long long int lo=0;
	//char test[120]="Connection Established!";
	//send(client_socket,test,strlen(test),0);
	while(1)
	{	
		//printf("j is :- %d\n",j);
		//if(j>=1)
		{
			printf("Send Your Message.....\n");
			fgets(input,1024,stdin);
	//		getchar();
			sent=send(client_socket,input,strlen(input),0);
			printf("Sent message is : %s",input);
			printf("Recieving Server's Message......\n");
			//start=clock();
			//elap=((double)(start));
			struct pollfd fd;
			int res;
			fd.fd = client_socket;
			fd.events = POLLIN;
			res = poll(&fd, 1, 10000); // 1000 ms timeout
			if (res == 0)
			{
    			break;
			}
			else if (res == -1)
			{
    			// error
    			perror("error:");
			}
			else
			{
    			// implies (fd.revents & POLLIN) != 0
    			len=recv(client_socket,output,1024,0); // we can read ...
			}
			//len=recv(client_socket,output,1024,0);
			output[len]='\0';
			printf("Recieved message is : %s\n",output);
		}
		/*else
		{
			printf("Waiting for Server's acknowledgement...\n");
			while(lo<4000000)
			{
				printf("%lld\n",lo);
				lo++;
				len=recv(client_socket,output,1024,0);
				if(len>=0)
				{
					printf("%d\n",len);
					j=1;
					break;
				}
			}
			if(len==0)
			break;
		}*/
		j++;
	}
	/*	close(client_socket);
		sleep(5);*/
	close(client_socket);
    sleep(5);
    pthread_cancel(th1);
	}
	if(acc==0){
		printf("Exiting Connection!!\n");
	}	
}
int mainagain(){
	main(0,NULL);
}
