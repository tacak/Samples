/*********************************************************************
�N���X�� : CBaseSocket
�쐬��   : 2003/05/11
�X�V��   : 2004/07/13
�T�v     : SOCKET �̃��b�p�[�N���X
���ӓ_   : ws2_32.lib �̃����N���K�v
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