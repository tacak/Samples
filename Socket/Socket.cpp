#include "Socket.h"

/*=================================================================================*/
/*																				   */
/*                        CSocketクラスのメンバ関数                                */
/*																				   */
/*=================================================================================*/
/*
	引数	なし
	
	コンストラクタ。
	サーバーに接続可能なソケットを作成します
*/
CSocket::CSocket()
{
	Open(SOCK_STREAM);
	ConnectionFlg = FALSE;
}

/*
	引数	ホスト名orIPアドレス　ポート番号
	
	コンストラクタ。
	指定されたホスト、ポート番号に接続済みのソケットを作成します。
*/
CSocket::CSocket(char *host_name, int port)
{
	Open(SOCK_STREAM);
	Connect(host_name, port);
}

/*
	引数	ホスト名orIPアドレス　ポート番号
	
	コンストラクタ。
	指定されたCInetIddressクラスの情報に従って接続済みのソケットを作成します。
*/
CSocket::CSocket(CInetAddress address, int port)
{
	Open(SOCK_STREAM);
	Connect(address, port);
}

/*
	引数	接続先情報が入ったCInetAddressクラス　ポート番号
	戻り値	接続成功時-TRUE 失敗時-FALSE

	指定されたCInetAddressクラスの情報を元に接続する
*/
BOOL CSocket::Connect(CInetAddress address, int port)
{
	server.sin_port = htons(port);
	//server.sin_family = AF_INET;
	server.sin_family = address.GetAddressType();
	memcpy((char *)&server.sin_addr, address.GetAddress(), address.GetLength());

	if(connect(sock, (sockaddr *)&server, sizeof(server)) == -1){
		return FALSE;
	}
	ConnectionFlg = TRUE;
	
	return TRUE;
}

/*
	引数	接続先ホスト名 or IPアドレス　ポート番号
	戻り値	接続成功時-TRUE 失敗時-FALSE

	指定されたホスト名 or IPアドレスへ接続する
*/
BOOL CSocket::Connect(char *host_name, int port)
{
	CInetAddress address(host_name);
	
	return Connect(address, port);
}

/*
	引数	送信するデータへのポインタ　送信するバイト数
	戻り値	送信したバイト数。コネクションが確立していない時には-1を返す

	バッファに指定されたデータをlenバイト送信する。
*/
int CSocket::Send(char *buf, int len)
{
	if(ConnectionFlg == FALSE){
		return -1;
	}
	
	return send(sock, buf, len, 0);
}

/*
	引数	受信バッファ　最大受信バイト数
	戻り値	受信したバイト数。コネクションが確立していない時には-1を返す

	指定されたバッファに最大lenバイトまでデータを受信する。
	この関数はデータを受信するまで処理を返さない。
*/
int CSocket::Receive(char *buf, int max_len)
{
	if(ConnectionFlg == FALSE){
		return -1;
	}
	
	return recv(sock, buf, max_len, 0);
}

/*
	引数	なし
	戻り値	ソケットが既にコネクト済み-TRUE 未コネクト-FALSE

	ソケットがコネクト済みか未コネクトかを調べる。
*/
BOOL CSocket::IsConnect()
{
	return ConnectionFlg;
}

/*=================================================================================*/
/*																				   */
/*                      CServerSocketクラスのメンバ関数                            */
/*																				   */
/*=================================================================================*/
/*
	引数	待ち受けポート番号
	
	コンストラクタ。
	指定されたポートで待ち受け可能なソケットを作成します。
*/
CServerSocket::CServerSocket(int port)
{
	Open(SOCK_STREAM);
	this->port = port;
	Bind(port);
}

CServerSocket::CServerSocket()
{
	Open(SOCK_STREAM);
}

BOOL CServerSocket::Bind(int port)
{
	if(port > 1024){
		this->port = port;
	}
	else{
		return FALSE;
	}

	//構造体の初期化と設定
	memset((void *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(this->port);

	//指定されたポートでBINDを試みる
	if(bind(sock, (struct sockaddr *)&me, sizeof(me)) == -1){
		return FALSE;
	}
	return TRUE;
}

/*
	引数	なし
	戻り値	成功時-通信可能なCSocketオブジェクト 失敗時-NULL
	
	オブジェクト作成時に指定されたポートで待ち受けを開始する。
	この関数は接続要求が来るまで制御を返しません。
*/
BOOL CServerSocket::Accept(CSocket *s)
{	
	//ソケットにキューサイズを設定
	if(listen(sock, SOMAXCONN) != 0){
		return FALSE;
	}

	//待ち受け
	SOCKET new_sock;
	int len = sizeof(from);
	if((new_sock = accept(sock, (struct sockaddr *)&from, &len)) < 0){
		return FALSE;
	}

	s->sock = new_sock;
	s->ConnectionFlg = TRUE;

	return TRUE;
}
