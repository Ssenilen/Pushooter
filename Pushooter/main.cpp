#include "stdafx.h"
#include "SocketAddress.h"

int main()
{
	WSADATA wsaData;
	int nErrorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nErrorCode != 0)
	{
		std::cout << "���� �Ҵ� ����" << std::endl;
		return 0;
	}


	nErrorCode = WSACleanup();
}