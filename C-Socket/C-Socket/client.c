#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {
	
	// creat TCP socket
	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = INADDR_ANY; // local address

	if (connect(socket_descriptor, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
		printf("Failed to connect!!");
	}

	char server_response[256];
	recv(socket_descriptor, &server_response, sizeof(server_response), 0);

	printf("Server response: %s \n", server_response);

	close(socket_descriptor);

	return 0;
}

