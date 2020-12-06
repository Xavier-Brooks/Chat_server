Xavier Brooks 
started: 12/06/20
simple chat room server created to teach myself a bit of networking in C 

educational resources
	binarytides.com/socket-programming-c-linux -tutorial/

structure
	bin folder
		contains any compiled binaries
	includes
		includes header files for source files
	src 
		contains all source code

compile command 
	gcc -g -Wall -pedantic chat_se.c -o bin/chat

usage for main branch 
	run ./chat
	in seperate terminal run
		telnet localhost 8888

	should print messages in telnet terminal

plans 
	rid of telnet usage :)
	add message communication to the server 
	enable threading for multiple user connection
	more tbd...
