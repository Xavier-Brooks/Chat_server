/*
*simple chat server program developed on linux machine
*goal: gain understanding of server creation and maintainence
*created by Xavier Brooks - 12/06/20
*learning material
*	binarytides.com/socket-programming-c-linuxtutorial
*/

#include <pthread.h>
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

//void *connection_handler(void *cli_socket_desc);

int main(int argc, char *argv[]){

	int socket_des, cli, c, *new_client_socket;
	char buf[100], buf2[100];
	struct sockaddr_in server_s, client_s;

	int read_size = 0;

	//creates the socket we'll be using
	socket_des = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_des == -1){
		printf("failed to create socket -- exiting program\n");
		exit(SOCK_ERR);
	}

	//comverts the machines ip address to long format
	//may need to change to your computer's ip
	server_s.sin_addr.s_addr = INADDR_ANY;
	server_s.sin_family = AF_INET;
	server_s.sin_port = htons(8888);

	//binds a sock to ip address and port during server up-time
	if(bind(socket_des, (struct sockaddr *)&server_s, sizeof(server_s)) < 0){
		printf("binding failed -- exiting program\n");
		exit (BIND_ERR);
	}

	//listen for a client connection
	//backlog max of 4
	listen(socket_des, 4);
	printf("Waiting for somebody to connect...\n");

	c = sizeof(struct sockaddr_in);

	//keep server running until ...
	//	1. client disconnects or
	//	2. server program is closed
	while( (cli = accept(socket_des, (struct sockaddr*)&client_s, (socklen_t*)&c)) ){

		printf("Connection established...\n");

	        read_size = recv(cli,buf,100,0);
	        if( read_size == -1){
           	 	printf("Error in receiving");
           		break;
        	}

        	printf("Message got from client is : %s",buf);

		memset(buf, '\0', sizeof(buf));

        	fgets(buf,100,stdin);
        	if(strncmp(buf,"end",3)==0)
            		break;

        	read_size = send(socket_des,buf2,100,0);
        	if(read_size == -1){
           		printf("Error in sending");
            		break;
        	}

		memset(buf2, '\0', sizeof(buf2));

//		msg = "hello new user...\n";
//		write(cli, msg, strlen(msg));

//		pthread_t clients;
//		new_client_socket = malloc(1);
//		if(new_client_socket == NULL){
//			printf("failed to allocate socket id for new client\n");
//			return 1;
//		}

//		*new_client_socket = cli;
//		if(pthread_create(&clients, NULL, connection_handler, (void *) new_client_socket) < 0) {
//			printf("new client thread couldn't be created\n");
//			free(new_client_socket);
//			return 1;
//		}

//		pthread_join(clients, NULL);
	}

	if (cli < 0){
		printf("accept failed\n");
		exit(ACCEPT_ERR);
	}

	close(cli);
	close(socket_des);
	return 0;
}

//void *connection_handler(void *cli_socket_desc){
//	int cli_desc = *(int *)cli_socket_desc;
//	int read_size;
//	char clients_msg[100], server_msg[100];

//	while(1){

		//clears the buffer before each iteration so that characters from older messages don't
		//occur in new messages
//		memset(clients_msg, '\0', sizeof(clients_msg));
//		memset(server_msg, '\0', sizeof(server_msg));

		//recieve message from client
//		read_size = recv(cli_desc, clients_msg, 100, 0);
//		if(read_size == -1){
//			printf("error reading form client\n");
//		}

//		printf("Message from Client is: %s\n", clients_msg);
//		printf("Message for teh Client is: ");

//		fgets(server_msg, 100, stdin);
//		if( (strncmp(server_msg, "end", 3)) == 0){
//			break;
//		}

		//send the message back to client
//		read_size = send(cli_desc, server_msg, strlen(server_msg), 0);
//		if(read_size == -1){
//			printf("Error sending message\n");
//		}
//	}

//	if(read_size == 0){
//		printf("client disconnected\n");
//	}
//	else if(read_size == -1){
//		printf("recv error\n");
//	}
//
//	free(cli_socket_desc);
//}


