#include "RawSocket.h"

/*=================================================================================*/
/*																				   */
/*                        CSocket�N���X�̃����o�֐�                                */
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