#include "UdpSocket.h"

/*
	引数	なし
	
	コンストラクタ
	Udpソケットを作成します
*/
CUdpSocket::CUdpSocket()
{
	Open(SOCK_DGRAM);
}

/*
	引数	待ち受けポート番号
	
	コンストラクタ
	Udpソケットを作成し指定されたポート番号でBindする
*/
CUdpSocket::CUdpSocket(int port)
{
	Open(SOCK_DGRAM);
	this->port = port;
	Bind(port);
}

/*
	引数	送信するデータへのポインタ　送信するバイト数　送信先情報
	戻り値	送信したバイト数。

	バッファに指定されたデータをlenバイト送信する。
*/
int CUdpSocket::SendTo(char *buf, int len, CInetAddress to_host)
{
	sockaddr_in to;
	
	//通信相手先の設定
	to.sin_family = to_host.GetAddressType();
	memcpy((char *)&to.sin_addr, to_host.GetAddress(), to_host.GetLength());
	
	return sendto(sock, buf, len, 0, (sockaddr*)&to, sizeof(to));
}

/*
	引数	送信するデータへのポインタ　送信するバイト数　送信先アドレス
	戻り値	送信したバイト数。

	バッファに指定されたデータをlenバイト送信する。
*/
int CUdpSocket::SendTo(char *buf, int len, char *host_name)
{
	CInetAddress to_host(host_name);
	
	return SendTo(buf, len, to_host);
}

/*
	引数	受信バッファ　最大受信バイト数　受信先情報
	戻り値	受信したバイト数。

	指定されたバッファに最大lenバイトまでデータを受信する。
	この関数はデータを受信するまで処理を返さない。
*/
int CUdpSocket::ReceiveFrom(char *buf, int max_len, CInetAddress *from_host)
{
	int len, work;
	sockaddr_in from;
	work = sizeof(from);
	
	//bind(sock, (sockaddr*)&from, sizeof(from));
	len = recvfrom(sock, buf, max_len, 0, (sockaddr*)&from, &work);
	
	if(from_host != NULL){
		CInetAddress host(from);
		memcpy(from_host, &host, sizeof(host));
	}
	
	return len;
}

BOOL CUdpSocket::Bind(int port)
{
	sockaddr_in me;

	//構造体の初期化と設定
	memset((void *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(this->port);

	//指定されたポートでBINDを試みる
	if(bind(sock, (struct sockaddr *)&me, sizeof(me)) == -1){
		return false;
	}
	this->port = port;

	return TRUE;
}

int CUdpSocket::GetPort(void)
{
	return port;
}