/*********************************************************************
�N���X�� : CUdpSocket
�쐬��   : 2003/05/18
�X�V��   : 2004/07/13
�T�v     : UDP ���g�����ʐM��e�Ղɍs�����Ƃ��ł���
���ӓ_   : ws2_32.lib �̃����N���K�v
           ���݁A�������ł��萳�퓮�삵�Ȃ����߁A���̃N���X�͎g�p�s��
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