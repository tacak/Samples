/*********************************************************************
�N���X�� : CInetAddress
�쐬��   : 2003/05/10
�X�V��   : 2004/07/13
�T�v     : �w�肳�ꂽ�z�X�g�̏����擾����
���ӓ_   : GetAddressString �ɕs�����
*********************************************************************/

#ifndef __LOADED_CInetAddress__
#define __LOADED_CInetAddress__

#include <winsock2.h>

class CInetAddress{
  private:
	void InitWsa(void);

  protected:
	HOSTENT *host;
	char AddressString[16];
	WSADATA wsaData;
	
  public:
	CInetAddress();
	CInetAddress(sockaddr_in host);
	~CInetAddress();
	CInetAddress(char *host_name);
	BOOL SetHost(sockaddr_in host);
	BOOL SetHost(char *host_name);
	short GetLength();
	short GetAddressType();
	const char *GetHostName();
	void GetHostName(char buf[]);
	const char *GetAddress();
	const char *GetAddressString();
	void GetAddressString(char buf[]);
	char const* const*GetAddressList();
	BOOL IsOk();
};

#endif