#include <stdio.h>
#include "Socket.h"
#include "UdpSocket.h"

#pragma comment(lib, "ws2_32.lib")

void main(void)
{
	CUdpSocket u;
	CInetAddress host;
	char buf[256];

	u.Bind(5001);

	u.SendTo("abcde", 6, "127.0.0.1");
	u.ReceiveFrom(buf, 256, &host);
	
	printf("RecvData : %s\n", buf);
	printf("HostName : %s\n", host.GetAddressString());

	return;
}