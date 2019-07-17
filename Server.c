#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
   if (argc<2)
   {
    fprintf(stderr, "Port Number not provided, Program Terminated\n");
    exit(1);
   }
	int sockfd, newsockfd, portno, n;
	char buffer[256];

	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd<0)
	 {
	  error("Error creating Socket");
 	 }

	bzero((char*) &serv_addr, sizeof(serv_addr));
 	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)
	{
	 error("Connection Error");
	}

	listen(sockfd, 2);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if (newsockfd<0)
	{
	 error("Connection Failed");
	}

	while(1)
	{
	 bzero(buffer, 255);
	 n = read(newsockfd, buffer, 255);
	 if (n<0)
	 {
	  error("Error on Reading");
	 }

	printf("Client: %s", buffer);
	bzero(buffer, 255);
	scanf("\n");
	fgets(buffer, 255, stdin);

	n = write(newsockfd, buffer, strlen(buffer));
	if (n<0)
	{
	 error("Writing error");
	}
	int i = strncmp("Bye", buffer, 3);
	if (i==0)
	{
	 printf("Client Disconnected");
	 exit(1);
	}
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}
