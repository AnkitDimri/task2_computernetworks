	#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX 80
#define PORT 5002
#define SA struct sockaddr

struct msg {
	int num;
	int arr[100];
};
void func(int sockfd)
{
	struct msg buffer;
	int n;
	for (;;) {
		bzero(buffer.arr,sizeof(buffer.arr));
		printf("Enter the string : ");
		scanf("%d",&buffer.num);
		write(sockfd,&buffer, sizeof(buffer));
		bzero(buffer.arr,sizeof(buffer.arr));
		read(sockfd,&buffer, sizeof(buffer));
		printf("From server :\n");
		for(int i=0;i<buffer.num;i++)
			printf("%d\t",buffer.arr[i]);
		printf("\n");
		bzero(buffer.arr,sizeof(buffer.arr));
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	func(sockfd);
	close(sockfd);
}
