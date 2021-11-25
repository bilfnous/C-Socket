#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {
	printf("\nStarting Socket Server.\n\n");

	char server_msg[256] = "Hello Client!";
	char client_msg[256];

	// Creat TCP socket
	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_descriptor == -1) {
		printf("Socket creation faild.\n\n");
		return (-1);
	}
	else
		printf("Socket created.\n\n");

	// Prepare the sockaddr_in struct
	struct sockaddr_in server_addr, client_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = INADDR_ANY; // local address

	// bind socket descriptor to socket struct
	if (bind(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Binding failed.\n\n");
		return (-1);
	}
	else
		printf("Binding complete.\n\n");

	// Listen for only 1 connection
	listen(socket_descriptor, 1);
	printf("Listening for a connection...\n\n");

	// Accept connection from a client
	int sock_len= sizeof(struct sockaddr_in);
	int client_socket = accept(socket_descriptor, (struct sockaddr*)&client_addr, (socklen_t*)&sock_len);
	if (client_socket < 0) {
		printf("Failed to accept connection.\n\n");
		return (-1);
	}
	else
		printf("Connection Accepted.\n\n");



	// Receive a message from client
	if (recv(client_socket, client_msg, sizeof(client_msg), 0) > 0) {
		printf("Client response: %s\n\n", client_msg);
	}
	else
		printf("Failed to recieve a message.\n\n");

	// Send a message to client
	send(client_socket, server_msg, sizeof(server_msg), 0);

	// Close socket
	close(socket_descriptor);
	close(client_socket);
	printf("connection Terminated.\n\n");

	return 0;
}