#include "Socket.h"

/*=================================================================================*/
/*																				   */
/*                        CSocket�N���X�̃����o�֐�                                */
/*																				   */
/*=================================================================================*/
/*
	����	�Ȃ�
	
	�R���X�g���N�^�B
	�T�[�o�[�ɐڑ��\�ȃ\�P�b�g���쐬���܂�
*/
CSocket::CSocket()
{
	Open(SOCK_STREAM);
	ConnectionFlg = FALSE;
}

/*
	����	�z�X�g��orIP�A�h���X�@�|�[�g�ԍ�
	
	�R���X�g���N�^�B
	�w�肳�ꂽ�z�X�g�A�|�[�g�ԍ��ɐڑ��ς݂̃\�P�b�g���쐬���܂��B
*/
CSocket::CSocket(char *host_name, int port)
{
	Open(SOCK_STREAM);
	Connect(host_name, port);
}

/*
	����	�z�X�g��orIP�A�h���X�@�|�[�g�ԍ�
	
	�R���X�g���N�^�B
	�w�肳�ꂽCInetIddress�N���X�̏��ɏ]���Đڑ��ς݂̃\�P�b�g���쐬���܂��B
*/
CSocket::CSocket(CInetAddress address, int port)
{
	Open(SOCK_STREAM);
	Connect(address, port);
}

/*
	����	�ڑ����񂪓�����CInetAddress�N���X�@�|�[�g�ԍ�
	�߂�l	�ڑ�������-TRUE ���s��-FALSE

	�w�肳�ꂽCInetAddress�N���X�̏������ɐڑ�����
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
	����	�ڑ���z�X�g�� or IP�A�h���X�@�|�[�g�ԍ�
	�߂�l	�ڑ�������-TRUE ���s��-FALSE

	�w�肳�ꂽ�z�X�g�� or IP�A�h���X�֐ڑ�����
*/
BOOL CSocket::Connect(char *host_name, int port)
{
	CInetAddress address(host_name);
	
	return Connect(address, port);
}

/*
	����	���M����f�[�^�ւ̃|�C���^�@���M����o�C�g��
	�߂�l	���M�����o�C�g���B�R�l�N�V�������m�����Ă��Ȃ����ɂ�-1��Ԃ�

	�o�b�t�@�Ɏw�肳�ꂽ�f�[�^��len�o�C�g���M����B
*/
int CSocket::Send(char *buf, int len)
{
	if(ConnectionFlg == FALSE){
		return -1;
	}
	
	return send(sock, buf, len, 0);
}

/*
	����	��M�o�b�t�@�@�ő��M�o�C�g��
	�߂�l	��M�����o�C�g���B�R�l�N�V�������m�����Ă��Ȃ����ɂ�-1��Ԃ�

	�w�肳�ꂽ�o�b�t�@�ɍő�len�o�C�g�܂Ńf�[�^����M����B
	���̊֐��̓f�[�^����M����܂ŏ�����Ԃ��Ȃ��B
*/
int CSocket::Receive(char *buf, int max_len)
{
	if(ConnectionFlg == FALSE){
		return -1;
	}
	
	return recv(sock, buf, max_len, 0);
}

/*
	����	�Ȃ�
	�߂�l	�\�P�b�g�����ɃR�l�N�g�ς�-TRUE ���R�l�N�g-FALSE

	�\�P�b�g���R�l�N�g�ς݂����R�l�N�g���𒲂ׂ�B
*/
BOOL CSocket::IsConnect()
{
	return ConnectionFlg;
}

/*=================================================================================*/
/*																				   */
/*                      CServerSocket�N���X�̃����o�֐�                            */
/*																				   */
/*=================================================================================*/
/*
	����	�҂��󂯃|�[�g�ԍ�
	
	�R���X�g���N�^�B
	�w�肳�ꂽ�|�[�g�ő҂��󂯉\�ȃ\�P�b�g���쐬���܂��B
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

	//�\���̂̏������Ɛݒ�
	memset((void *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port = htons(this->port);

	//�w�肳�ꂽ�|�[�g��BIND�����݂�
	if(bind(sock, (struct sockaddr *)&me, sizeof(me)) == -1){
		return FALSE;
	}
	return TRUE;
}

/*
	����	�Ȃ�
	�߂�l	������-�ʐM�\��CSocket�I�u�W�F�N�g ���s��-NULL
	
	�I�u�W�F�N�g�쐬���Ɏw�肳�ꂽ�|�[�g�ő҂��󂯂��J�n����B
	���̊֐��͐ڑ��v��������܂Ő����Ԃ��܂���B
*/
BOOL CServerSocket::Accept(CSocket *s)
{	
	//�\�P�b�g�ɃL���[�T�C�Y��ݒ�
	if(listen(sock, SOMAXCONN) != 0){
		return FALSE;
	}

	//�҂���
	SOCKET new_sock;
	int len = sizeof(from);
	if((new_sock = accept(sock, (struct sockaddr *)&from, &len)) < 0){
		return FALSE;
	}

	s->sock = new_sock;
	s->ConnectionFlg = TRUE;

	return TRUE;
}
