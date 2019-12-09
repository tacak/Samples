#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in to, from;

	WSAStartup(MAKEWORD(2,0), &wsaData);

	memset(&to, 0, sizeof(to));

	to.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	to.sin_port = htons(80);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(!connect(sock, (sockaddr *)&to, sizeof(to))){
		printf("Error\n");
	}

	memset(&from, 0, sizeof(from));
	int len = sizeof(from);
	if(!getsockname(sock, (sockaddr *)&from, &len)){
		printf("Error\n");
	}

	unsigned long local_ip = ntohl(from.sin_addr.s_addr);
	unsigned short local_port = ntohs(from.sin_port);

	printf("%d,%d,%d,%d,%d\n",
		(int)(local_ip >> 24) & 0xff,
		(int)(local_ip >> 16) & 0xff,
		(int)(local_ip >> 8) & 0xff,
		(int)(local_ip) & 0xff,
		local_port);
	
	//printf("IpAddress: %s  Port: %d\n", inet_ntoa(*(struct in_addr *)&from.sin_addr.S_un.S_addr), ntohs(from.sin_port));

	closesocket(sock);

	WSACleanup();

	return 0;
}