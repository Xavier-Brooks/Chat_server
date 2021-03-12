/*
*simple chat server program developed on linux machine
*goal: gain understanding of server creation and maintainence
*created by Xavier Brooks - 12/06/20
*learning material
*	binarytides.com/socket-programming-c-linuxtutorial
*/

#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

//includes folder
#include "../includes/ERRORS.h"

int main(int argc, char *argv[]){

	int sock, msg_status;
	unsigned short port;
	struct sockaddr_in server_s;
	char buf[100] = {0}, buffer[100] = {0};

	if(argc != 3){
		printf("program requires 2 arguments ip address then port to connect to\n");
		printf("example: ./chat_cli 198.1.1.1 8888\n");
		printf("try again\n");
		exit(ARG_ERR);
	}

	//create client side socket
	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("failed creating client socket\n");
		exit(SOCK_ERR);
	}

	//stores ip of the server proveded by user
	inet_pton(AF_INET, argv[1], &(server_s.sin_addr));

	//assigns port the user typed port number
	port = (unsigned short) atoi(argv[2]);
	server_s.sin_family = AF_INET;
	server_s.sin_port = htons(port);

	//connect to the server
	if( connect(sock, (struct sockaddr *)&server_s, sizeof(server_s)) < 0){
		printf("connection error try again\n");
		close(sock);
		exit(CONN_ERR);
	}

	while(1){

		memset(buf, '\0', sizeof(buf));
		memset(buffer, '\0', sizeof(buffer));

		printf("Enter message for server: ");
		fgets(buf, 100, stdin);
		if(strncmp(buf, "end", 3) == 0){
			break;
		}
		msg_status = send(sock, buf, 100, 0);

		if(msg_status == -1){
			printf("Error sending message\n");
			close(sock);
			exit(CONN_ERR);
		}

		if (recv(sock, buffer, 100, 0) == -1){
			close(sock);
			printf("recv failed\n");
			exit(CONN_ERR);
		}
		printf("Msg rom server is: %s\n", buf);

	}
	close(sock);
	return 0;
}

