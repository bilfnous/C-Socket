#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {
	printf("\nStarting Socket Client.\n\n");

	char client_msg[256] = "Hello Server!";
	char server_msg[256];

	// Creat TCP socket
	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_descriptor == -1) {
		printf("Socket creation faild.\n\n");
		return (-1);
	}
	else
		printf("Socket created.\n\n");

	// Prepare the sockaddr_in struct
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = INADDR_ANY; // local address

	// Connect to server
	if (connect(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		printf("Failed to connect!!\n\n");
		return -1;
	}
	else
		printf("Connection established.\n\n");

	if (send(socket_descriptor, client_msg, sizeof(client_msg), 0) < 0) {
		printf("Sending message failed.\n\n");
	}

	if (recv(socket_descriptor, server_msg, sizeof(server_msg), 0) < 0) {
		printf("Recieving message failed.\n\n");
	}
	else
		printf("Server response: %s\n\n", server_msg);

	close(socket_descriptor);
	printf("Connection Terminated.\n\n");

	return 0;
}

