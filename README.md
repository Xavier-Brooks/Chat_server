Xavier Brooks 

started: 12/06/20

simple chat room server created to teach myself a bit of networking in C 

educational resources

	binarytides.com/socket-programming-c-linux -tutorial/

extra notes 

	8888 is the hardcoded port I used at the start of the project for all server side startups
	can change in source if you desired or modiify code as you see fit.

structure

	bin folder

		contains any compiled binaries
	includes
	
		includes header files for source files
	src 
		contains all source code

compile command 

	gcc -g -Wall -pedantic chat_se.c -o bin/chat -lpthread
	gcc -g -Wall -pedantic chat_cli.c -o ../bin/chat_cli 

usage for main branch 

	//server host
	run ./chat to start server in terminal
		...should print ip address and port for chatroom

	//clients
	run ./chat_cli in terminal with ip address first followed by port
		example: ./chat_cli 1.1.1.1 8888

plans 

	rid of telnet usage :)
	add message communication to the server 
	enable threading for multiple user connection
	more features tbd...
