#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// chat between client and server.
void func(int sockfd, int index)
{
	char buff[MAX];
	int n;
	
	for (;;) {
	  bzero(buff, MAX);
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));

		if(index == 5)
		  printf("From Process P5: %s\t To Process P1: ", buff); 
		else
		  printf("From Process P%d: %s\t To Process P%d: ", index, buff, index+1); 
		
		break;
	}
}

int main()
{
	int sockfd, connfd, len;
	int index = 1;
	struct sockaddr_in servaddr, cli;

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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Socket bind failed...\n");
		exit(0);
	}
	else
	  printf("Socket successfully binded..\n");

	while(index != 0){	

	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// accept data packet
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Server acccept failed...\n");
		exit(0);
	}
	else
		printf("Server acccepted the client...\n");

	printf("Opening connection...\n");
	sleep(2);
	func(connfd, index);
	index ++;
	if(index == 6){
	  printf("Server closing...\n");
	  sleep(2);
	  index = 0;
	}
	}
	close(sockfd);
}
