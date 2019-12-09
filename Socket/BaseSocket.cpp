#include "BaseSocket.h"

//staticメンバの実態の確保
int CBaseSocket::WsaOpenCnt = 0;

void CBaseSocket::InitWsa(void)
{

	if(WsaOpenCnt == 0){
		WSAStartup(MAKEWORD(2, 0), &wsaData);
	}
	WsaOpenCnt++;
}

/*
	引数	なし
	
	コンストラクタ。
	ソケットオブジェクトの初期化をします。
*/
CBaseSocket::CBaseSocket()
{
	InitWsa();
	sock = NULL;
}

/*
	引数	ソケットタイプ(SOCK_STREAM or SOCK_DGRAM)
	
	コンストラクタ。
	指定されたソケットタイプでソケットを作成します。
*/
CBaseSocket::CBaseSocket(int type)
{
	InitWsa();
	Open(type);
}

/*
	デストラクタ。
	ソケットを閉じ忘れている場合は、ソケットを閉じます。
*/
CBaseSocket::~CBaseSocket()
{
	Close();

	WsaOpenCnt--;
	if(WsaOpenCnt == 0){
		WSACleanup();
	}
}

/*
	引数	アドレスタイプ(通常はPF_INET)、ソケットタイプ(SOCK_STREAM or SOCK_DGRAM)
	戻り値	成功時-TRUE 失敗時-FALSE

	指定されたソケットタイプでソケットを作成します。
*/
BOOL CBaseSocket::Open(int type)
{
	sock = socket(AF_INET, type, 0);
	if( sock < 0){
		sock = NULL;
		return FALSE;
	}
	return TRUE;
}

BOOL CBaseSocket::Open(int type, int protocol)
{
	sock = socket(AF_INET, type, protocol);
	if( sock < 0){
		sock = NULL;
		return FALSE;
	}
	return TRUE;
}

/*
	引数	なし
	戻り値	成功時-TRUE 失敗時-FALSE

	作成済みのソケットを閉じます
*/
BOOL CBaseSocket::Close()
{
	if(sock == NULL){
		return FALSE;
	}
	closesocket(sock);
	sock = NULL;

	return TRUE;
}

/*
	引数	なし
	戻り値	ソケットが作成済み-TRUE ソケット未作成-FALSE
	
	割り当てられているソケットオブジェクトが作成済みかどうかを判別します。
*/
BOOL CBaseSocket::IsOk()
{
	return sock==NULL ? FALSE : TRUE;
}

/*
	引数	
	戻り値	成功時 0 , 失敗時 0 以外
	
	ソケットオプションを設定します。
*/
int CBaseSocket::SetSockOpt(int level, int optname, const char *optval, int optlen)
{
	return setsockopt(sock, level, optname, optval, optlen);
}

int CBaseSocket::SetSockOpt(int optname, const char *optval, int optlen)
{
	return setsockopt(sock, SOL_SOCKET, optname, optval, optlen);
}

/*
	引数	
	戻り値	成功時 0 , 失敗時 0 以外
	
	ソケットオプションを取得します。
*/
int CBaseSocket::GetSockOpt(int level, int optname, char *optval, int *optlen)
{
	return getsockopt(sock, level, optname, optval, optlen);
}

int CBaseSocket::GetSockOpt(int optname, char *optval, int *optlen)
{
	return getsockopt(sock, SOL_SOCKET, optname, optval, optlen);
}

/*
	引数	なし
	戻り値	最終エラー
	
	最終エラーを取得します。
*/
int CBaseSocket::GetLastError(void)
{
	return ::WSAGetLastError();
}

