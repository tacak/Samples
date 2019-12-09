/*********************************************************************
�N���X�� : CSocket
           CServerSocket
�쐬��   : 2003/05/18
�X�V��   : 2004/07/13
�T�v     : TCP ���g�����ʐM��e�Ղɍs�����Ƃ��ł���
           �N���C�A���g�́ACSocket ���g���B
           �T�[�o�[�́ACServerSocket ���g���B
���ӓ_   : ws2_32.lib �̃����N���K�v
*********************************************************************/

#ifndef __LOADED_CSocket__
#define __LOADED_CSocket__

#include "BaseSocket.h"
#include "InetAddress.h"

#define SOCK_NO_ERROR		 0
#define SOCK_BIND_FAILD		-1
#define SOCK_LISTEN_FAILD	-2
#define SOCK_ACCEPT_FAILD	-3

class CSocket;

class CServerSocket : public CBaseSocket{
  protected:
	sockaddr_in me;
	sockaddr_in from;
	int port;

  public:
	CServerSocket();
	CServerSocket(int port);
	BOOL Accept(CSocket *s);
	BOOL Bind(int port);
	BOOL Bind(void);
};

class CSocket : public CBaseSocket{
  protected:
	sockaddr_in server;
	BOOL ConnectionFlg;
	friend CServerSocket::Accept(CSocket *s);

  public:
	CSocket();
	CSocket(char *host_name, int port);
	CSocket(CInetAddress address, int port);
	BOOL Connect(char *host_name, int port);
	BOOL Connect(CInetAddress address, int port);
	int Send(char *buf, int len);
	int Receive(char *buf, int max_len);
	BOOL IsConnect();
};

#endif