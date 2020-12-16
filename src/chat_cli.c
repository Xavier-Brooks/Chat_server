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

	int cli_des, read_size;
	unsigned short port;

	struct sockaddr_in server_s;

	char msg[1000], reply[1000];

	if(argc != 3){
		printf("program requires 2 arguments ip address then port to connect to\n");
		printf("example: ./chat_cli 198.1.1.1 8888\n");
		printf("try again\n");
		exit(ARG_ERR);
	}

	//stores ip of the server proveded by user
	inet_pton(AF_INET, argv[1], &(server_s.sin_addr));

	//assigns port the user typed port number
	port = (unsigned short) atoi(argv[2]);
	server_s.sin_family = AF_INET;
	server_s.sin_port = htons(port);

	//creates client side socket
	if( (cli_des = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("failed on creation of client socket\n");
		exit(SOCK_ERR);
	}

	//connect to the server
	if( connect(cli_des, (struct sockaddr *)&server_s, sizeof(server_s)) < 0){
		printf("connection error try again\n");
		exit(CONN_ERR);
	}

	while(1){

		read_size = recv(server_s, msg, 1000, 0);
		if((read_size == 0) || (read_size == -1)){
			printf("error receiving servers message\n");
		}

		printf("%s", msg);

		write();

	}

	close(cli_des);
	return 0;
}
