/*********************************************************************
�N���X�� : CRawSocket
�쐬��   : 2009/03/14
�X�V��   : 2009/03/14
�T�v     : RAWSOCKET �̃��b�p�[�N���X
���ӓ_   : ws2_32.lib �̃����N���K�v
*********************************************************************/

#ifndef __LOADED_CRawSocket__
#define __LOADED_CRawSocket__

#include "BaseSocket.h"
#include "InetAddress.h"

class CRawSocket :  public CBaseSocket{
  public:
	CRawSocket();
	CRawSocket(int protocol);
	~CRawSocket();
};

#endif