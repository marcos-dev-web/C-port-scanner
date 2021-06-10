#include <stdio.h>
#include <sys/socket.h>		// socket(), connect()
#include <sys/types.h>		// AF_INET, SOCK_STREAM
#include <arpa/inet.h>		// htons(), inet_addr()
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>			// close()

int testPort(char* ip, int port) {
	int sock;
	int result;

	struct sockaddr_in alvo;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	alvo.sin_family = AF_INET;
	alvo.sin_port = htons(port);
	alvo.sin_addr.s_addr = inet_addr(ip);

	result = connect(sock, (struct sockaddr *)&alvo, sizeof(alvo));

	close(sock);

	return result;
}

int main(int argc, char* argv[]) {

	if (argc == 1) {
		printf("You need pass an IP\n\n");
		printf(" [EXAMPLE] scan-ip 192.168.11.1\n\n");
		return 0;
	}

	int test;
	int port;
	char *ip = argv[1];

	printf("\n\n[TESTING] searching for open ports\n\n");

	for (port = 1; port <= 65536; port++) {
		test = testPort(ip, port);

		if (test == 0) {
			printf("[PORT] \t%d \tOPEN\n", port);
		}
	}

	return 0;
}
