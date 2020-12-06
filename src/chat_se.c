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
#include "ERRORs.h"

int main(int argc, char *argv[]){

	int socket_des, cli, c;
	char *msg;
	struct sockaddr_in server_s, client_s;

	//creates the socket we'll be using
	socket_des = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_des == -1){
		printf("failed to create socket -- exiting program\n");
		return SOCK_ERR;
	}

	//comverts the machines ip address to long format
	//may need to change to your computer's ip
	server_s.sin_addr.s_addr = INADDR_ANY;
	server_s.sin_family = AF_INET;
	server_s.sin_port = htons(8888);

	//binds a sock to ip address and port during server up-time
	if(bind(socket_des, (struct sockaddr *)&server_s, sizeof(server_s)) < 0){
		printf("binding failed -- exiting program\n");
		return BIND_ERR;
	}

	//listen for a client connection
	//backlog max of 4
	listen(socket_des, 4);
	printf("Waiting for somebody to connect...\n");

	c = sizeof(struct sockaddr_in);

	//keep server running until ...
	//	1. telnet users close
	//	2. server program is closed
	while( (cli = accept(socket_des, (struct sockaddr*)&client_s, (socklen_t*)&c)) ){

		printf("connection established...\n");
		msg = "hello new user...\n";
		write(cli, msg, strlen(msg));
	}

	if (cli < 0){
		printf("accept failed\n");
		return(ACCEPT_ERR);
	}

	return 0;
}
