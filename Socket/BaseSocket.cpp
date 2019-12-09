#include "BaseSocket.h"

//static�����o�̎��Ԃ̊m��
int CBaseSocket::WsaOpenCnt = 0;

void CBaseSocket::InitWsa(void)
{

	if(WsaOpenCnt == 0){
		WSAStartup(MAKEWORD(2, 0), &wsaData);
	}
	WsaOpenCnt++;
}

/*
	����	�Ȃ�
	
	�R���X�g���N�^�B
	�\�P�b�g�I�u�W�F�N�g�̏����������܂��B
*/
CBaseSocket::CBaseSocket()
{
	InitWsa();
	sock = NULL;
}

/*
	����	�\�P�b�g�^�C�v(SOCK_STREAM or SOCK_DGRAM)
	
	�R���X�g���N�^�B
	�w�肳�ꂽ�\�P�b�g�^�C�v�Ń\�P�b�g���쐬���܂��B
*/
CBaseSocket::CBaseSocket(int type)
{
	InitWsa();
	Open(type);
}

/*
	�f�X�g���N�^�B
	�\�P�b�g����Y��Ă���ꍇ�́A�\�P�b�g����܂��B
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
	����	�A�h���X�^�C�v(�ʏ��PF_INET)�A�\�P�b�g�^�C�v(SOCK_STREAM or SOCK_DGRAM)
	�߂�l	������-TRUE ���s��-FALSE

	�w�肳�ꂽ�\�P�b�g�^�C�v�Ń\�P�b�g���쐬���܂��B
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
	����	�Ȃ�
	�߂�l	������-TRUE ���s��-FALSE

	�쐬�ς݂̃\�P�b�g����܂�
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
	����	�Ȃ�
	�߂�l	�\�P�b�g���쐬�ς�-TRUE �\�P�b�g���쐬-FALSE
	
	���蓖�Ă��Ă���\�P�b�g�I�u�W�F�N�g���쐬�ς݂��ǂ����𔻕ʂ��܂��B
*/
BOOL CBaseSocket::IsOk()
{
	return sock==NULL ? FALSE : TRUE;
}

/*
	����	
	�߂�l	������ 0 , ���s�� 0 �ȊO
	
	�\�P�b�g�I�v�V������ݒ肵�܂��B
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
	����	
	�߂�l	������ 0 , ���s�� 0 �ȊO
	
	�\�P�b�g�I�v�V�������擾���܂��B
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
	����	�Ȃ�
	�߂�l	�ŏI�G���[
	
	�ŏI�G���[���擾���܂��B
*/
int CBaseSocket::GetLastError(void)
{
	return ::WSAGetLastError();
}

