#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char* argv[]) {

	char server_msg[256] = "Hello!";

	// creat TCP socket
	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = INADDR_ANY; // local address

	bind(socket_descriptor, (struct sockaddr*) &server_addr, sizeof(server_addr));

	listen(socket_descriptor, 1);

	int client_socket = accept(socket_descriptor, NULL, NULL);

	send(socket_descriptor, server_msg, sizeof(server_msg), 0);

	close(socket_descriptor);

	return 0;
}