#include "UdpSocket.h"

/*
	����	�Ȃ�
	
	�R���X�g���N�^
	Udp�\�P�b�g���쐬���܂�
*/
CUdpSocket::CUdpSocket()
{
	Open(SOCK_DGRAM);
}

/*
	����	�҂��󂯃|�[�g�ԍ�
	
	�R���X�g���N�^
	Udp�\�P�b�g���쐬���w�肳�ꂽ�|�[�g�ԍ���Bind����
*/
CUdpSocket::CUdpSocket(int port)
{
	Open(SOCK_DGRAM);
	this->port = port;
	Bind(port);
}

/*
	����	���M����f�[�^�ւ̃|�C���^�@���M����o�C�g���@���M����
	�߂�l	���M�����o�C�g���B

	�o�b�t�@�Ɏw�肳�ꂽ�f�[�^��len�o�C�g���M����B
*/
int CUdpSocket::SendTo(char *buf, int len, CInetAddress to_host)
{
	sockaddr_in to;
	
	//�ʐM�����̐ݒ�
	to.sin_family = to_host.GetAddressType();
	memcpy((char *)&to.sin_addr, to_host.GetAddress(), to_host.GetLength());
	
	return sendto(sock, buf, len, 0, (sockaddr*)&to, sizeof(to));
}

/*
	����	���M����f�[�^�ւ̃|�C���^�@���M����o�C�g���@���M��A�h���X
	�߂�l	���M�����o�C�g���B

	�o�b�t�@�Ɏw�肳�ꂽ�f�[�^��len�o�C�g���M����B
*/
int CUdpSocket::SendTo(char *buf, int len, char *host_name)
{
	CInetAddress to_host(host_name);
	
	return SendTo(buf, len, to_host);
}

/*
	����	��M�o�b�t�@�@�ő��M�o�C�g���@��M����
	�߂�l	��M�����o�C�g���B

	�w�肳�ꂽ�o�b�t�@�ɍő�len�o�C�g�܂Ńf�[�^����M����B
	���̊֐��̓f�[�^����M����܂ŏ�����Ԃ��Ȃ��B
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

	//�\���̂̏������Ɛݒ�
	memset((void *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(this->port);

	//�w�肳�ꂽ�|�[�g��BIND�����݂�
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