#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd, int index)
{
	char buff[MAX];
	int n;
	for (;;) {
	  read(sockfd, buff, sizeof(buff));
	  printf("From Server : %s", buff);
	  if(index == 5){
	    printf("From Process P5: %s\t To Process P1: ", buff);
	    printf("Closing connection...\n");
	  }
	  else
	    printf("From Process P%d: %s\t To Process P%d: ", index, buff, index+1); 
	  bzero(buff, MAX);
	  n = 0;
	  break;
	}
}

int main()
{
	int sockfd, connfd;
	int index = 1;
	struct sockaddr_in servaddr, cli;
	while(index != 0){

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection with the server failed...\n");
		exit(0);
	}
	else
		printf("Connected to the server..\n");

	func(sockfd, index);
	if(index == 5){
	  exit(0);
	  
	}
	index++;
	close(sockfd);
	printf("Closing connection...\n");
	sleep(2);
	}
	
	close(sockfd);
}
