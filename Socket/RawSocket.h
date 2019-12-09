/*********************************************************************
クラス名 : CRawSocket
作成日   : 2009/03/14
更新日   : 2009/03/14
概要     : RAWSOCKET のラッパークラス
注意点   : ws2_32.lib のリンクが必要
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