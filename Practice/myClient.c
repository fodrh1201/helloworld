#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 3000

int main()
{
	int ret = -1;
	int clientSock;
	struct sockaddr_in serverAddr;
	char str[100];

	if ((clientSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		goto leave;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	serverAddr.sin_port = htons(PORT);

	if ((ret = connect(clientSock, (struct sockaddr*)&serverAddr,
					sizeof(serverAddr))) == -1) {
		perror("connect");
		goto error;
	}

	while (strcmp(str, "exit") != 0) {
		scanf("%s", str);
		if ((ret = send(clientSock, str, sizeof(str), 0)) <= 0) {
			perror("send");
			ret = -1;
		} else
			printf("Wrote '%s' (%d Bytes)\n", str, ret);
	}
error:
	close(clientSock);
leave:
	return ret;
}

