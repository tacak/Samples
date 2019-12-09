/*********************************************************************
クラス名 : CBaseSocket
作成日   : 2003/05/11
更新日   : 2004/07/13
概要     : SOCKET のラッパークラス
注意点   : ws2_32.lib のリンクが必要
*********************************************************************/

#ifndef __LOADED_CBaseSocket__
#define __LOADED_CBaseSocket__

#include <iostream.h>
#include <winsock2.h>

class CBaseSocket{
  private:
	void InitWsa(void);	

  protected:
	SOCKET sock;
	WSADATA wsaData;

  public:
	static int WsaOpenCnt;
	CBaseSocket();
	CBaseSocket(int type);
	~CBaseSocket();
	BOOL Open(int type);
	BOOL Open(int type, int protocol);
	BOOL Close();
	BOOL IsOk();
	int SetSockOpt(int level, int optname, const char *optval, int optlen);
	int SetSockOpt(int optname, const char *optval, int optlen);
	int GetSockOpt(int level, int optname, char *optval, int *optlen);
	int GetSockOpt(int optname, char *optval, int *optlen);
	int GetLastError(void);
	operator SOCKET() const {return sock;}
};

#endif