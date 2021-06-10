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

int main() {

	int initialPort;
	int finishPort;
	int test;
	int port;
	int counter;
	char ip[20];

	printf("Initial port: ");
	scanf("%d", &initialPort);
	printf("Finish port: ");
	scanf("%d", &finishPort);
	printf("Ip: ");
	scanf("%s", &ip);

	int openPorts[finishPort];
	counter = 0;

	printf("\n\n[TESTING] searching for open ports\n\n");

	for (port = initialPort; port <= finishPort; port++) {
		test = testPort(ip, port);
		if (test == 0) {
			openPorts[counter] = port;
			counter++;
		}
	}

	counter = 0;
	printf("\n\n");

	while ((port = openPorts[counter])) {
		printf("[PORT] %d OPEN\n", port);
		counter++;
	}

	return 0;
}
