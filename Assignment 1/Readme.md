1. WAP to create a Client/Server model (chat server) using TCP socket programming in connection oriented Scenario.
Steps need to preform to create socket for the connection oriented client/server communication are:
Server Side:
 Include appropriate header files.
 Create a TCP Socket.
 Bind the address and port using bind() system call.
 Server executes listen() system call to indicate its willingness to receive connections.
 Accept the next completed connection from the client process by using an accept() system
call. At this point, connection is established between client and server, and they are ready to
transfer data.
 Receive a message from the Client using recv() system call.
 Send the result of the request made by the client using send() system call.
 Close the socket using close() system call
Client Side:
 Include appropriate header files
 Create a TCP Socket.
 Establish connection to the Server using connect() system call.
 Send and recieve messages using send() and recv() system call respectively.
 Close the socket using close() system call
Execution Steps:
 Save client and server program into two separate file with .c extension.
 Open two terminal and execute .c files by following commands
 gcc filename.c -o filename (compilation)
 ./filename (run)
