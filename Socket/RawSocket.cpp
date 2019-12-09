#include "RawSocket.h"

/*=================================================================================*/
/*																				   */
/*                        CSocketÉNÉâÉXÇÃÉÅÉìÉoä÷êî                                */
/*																				   */
/*=================================================================================*/
CRawSocket::CRawSocket()
{
	Open(SOCK_RAW, IPPROTO_IP);
}

CRawSocket::CRawSocket(int protocol)
{
	Open(SOCK_RAW, protocol);
}

CRawSocket::~CRawSocket()
{
}