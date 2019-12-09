/*********************************************************************
クラス名 : CUdpSocket
作成日   : 2003/05/18
更新日   : 2004/07/13
概要     : UDP を使った通信を容易に行うことができる
注意点   : ws2_32.lib のリンクが必要
           現在、未完成であり正常動作しないため、このクラスは使用不可
*********************************************************************/

#ifndef __LOADED_CUdpSocket__
#define __LOADED_CUdpSocket__

#include "BaseSocket.h"
#include "InetAddress.h"

class CUdpSocket : public CBaseSocket{
  private:
	int port;

  public:
	CUdpSocket();
	CUdpSocket(int port);
	int SendTo(char *buf, int len, CInetAddress to_host);
	int SendTo(char *buf, int len, char *host_name);
	int ReceiveFrom(char *buf, int max_len, CInetAddress *from_host);
	BOOL Bind(int port);
	int GetPort(void);
};

#endif