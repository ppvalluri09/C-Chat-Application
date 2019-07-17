#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char* msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, const char* argv[])
{
  	if (argc<3)
	{
	 fprintf(stderr, "Too many few arguments to main()\n");
	 exit(1);
	}

	int sockfd, portno, n, i;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[255];

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd<0)
	{
	 error("Error Opening Socket");
	}

	server = gethostbyname(argv[1]);
	if (server==NULL)
	{
	 fprintf(stderr, "Error, no such host\n");
	 exit(0);
	}

	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server -> h_addr, (char*) &serv_addr.sin_addr.s_addr, server -> h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sock_addr *) &serv_addr, sizeof(serv_addr))<0)
	{
	 error("Connection error");
	}

	while(1)
	{
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
		{
		 error("Write Failed");
		}
		bzero(buffer, 255);

		n = read(sockfd, buffer, 255);
		if (n < 0)
		{
	 	 error("Read Failed");
		}

		printf("Server: %s", buffer);

		i = strncmp("Bye", buffer, 3);
		if (i==0)
		{
			printf("Program Terminated\n");
			exit(1);
		}
		}
		close(sockfd);
	return 0;
}
