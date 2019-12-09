/*********************************************************************
クラス名 : CSocket
           CServerSocket
作成日   : 2003/05/18
更新日   : 2004/07/13
概要     : TCP を使った通信を容易に行うことができる
           クライアントは、CSocket を使う。
           サーバーは、CServerSocket を使う。
注意点   : ws2_32.lib のリンクが必要
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