#include <stdio.h>
#include "BaseSocket.h"
#include "InetAddress.h"

void CInetAddress::InitWsa(void)
{
	if(CBaseSocket::WsaOpenCnt == 0){
		WSAStartup(MAKEWORD(2, 0), &wsaData);
	}
	CBaseSocket::WsaOpenCnt++;
}

CInetAddress::CInetAddress()
{
	InitWsa();
	host = NULL;
}

CInetAddress::CInetAddress(sockaddr_in host)
{
	InitWsa();
	SetHost(host);
}

CInetAddress::CInetAddress(char *host_name)
{
	InitWsa();
	CBaseSocket::WsaOpenCnt++;

	SetHost(host_name);
}

CInetAddress::~CInetAddress()
{
	CBaseSocket::WsaOpenCnt--;
	if(CBaseSocket::WsaOpenCnt == 0){
		WSACleanup();
	}
}

BOOL CInetAddress::SetPort(int port)
{
	
}

BOOL CInetAddress::SetHost(char *host_name, int port)
{
	SetHost(host_name);
	SetPort(port);
}

BOOL CInetAddress::SetHost(char *host_name)
{
	unsigned long addr;
	
	//ホスト名かIPアドレスかを判別する
	addr = inet_addr(host_name);
	
	if(addr == INADDR_NONE){
		host = gethostbyname(host_name);
	}
	else{
		host = gethostbyaddr((const char*)&addr, 4, AF_INET);
	}
	
	return host == NULL ? FALSE : TRUE;
}

BOOL CInetAddress::SetHost(sockaddr_in host)
{
	this->host = gethostbyaddr((char *)&host.sin_addr, 4, 2);
	
	return this->host == NULL ? FALSE : TRUE;
}

short CInetAddress::GetLength()
{
	return host == NULL ? -1 : host->h_length;
}

short CInetAddress::GetAddressType()
{
	return host == NULL ? -1 : host->h_addrtype;
}

const char *CInetAddress::GetAddress()
{
	return host == NULL ? NULL : host->h_addr;
}

const char *CInetAddress::GetHostName()
{
	return host == NULL ? NULL : host->h_name;
}

void CInetAddress::GetHostName(char buf[])
{
	if(host == NULL){
		return;
	}
	strcpy(buf, host->h_name);
}

const char *CInetAddress::GetAddressString()
{
	if(host == NULL){
		return NULL;
	}
	
	sprintf(AddressString, "%u.%u.%u.%u", (unsigned char)host->h_addr[0], (unsigned char)host->h_addr[1], (unsigned char)host->h_addr[2], (unsigned char)host->h_addr[3]);
	return AddressString;
}

void CInetAddress::GetAddressString(char buf[])
{
	if(host == NULL){
		return;
	}

	strcpy(buf, GetAddressString());
}

char const* const*CInetAddress::GetAddressList()
{
	return host == NULL ? NULL : host->h_addr_list;
}

BOOL CInetAddress::IsOk()
{
	return host==NULL ? FALSE : TRUE;
}