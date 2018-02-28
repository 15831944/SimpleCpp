
#include "stdafx.h"
#include "ScNetwork.h"
#include "SocketPumper.h"
#include "SelectPumper.h"
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")


#define debug(format, ...)	do{ \
	char szMsg[255];\
	memset(szMsg, 0, sizeof(szMsg));\
	sprintf(szMsg, format, __VA_ARGS__);\
	OutputDebugStringA(szMsg);  \
}while (0);


// ���ǵ���������һ��ʾ��
// SCNETWORK_API int nSimpleSocket=0;
// 
// // ���ǵ���������һ��ʾ����
// SCNETWORK_API int fnSimpleSocket(void)
// {
// 	return 42;
// }

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� SimpleSocket.h
// CSimpleSocket::CSimpleSocket()
// {
// 	return;
// }

SimpleCpp::CScNetwork::CScNetwork()
{
	Init();
	return;
}
SimpleCpp::CScNetwork::~CScNetwork()
{
	Free();
}

int SimpleCpp::CScNetwork::Init()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		//printf("Error at WSAStartup()\n");
	}

	if (!CSocketPumper::m_pDefaultPumper)
	{
		CSocketPumper::m_pDefaultPumper = new CSelectPumper();
		int nRet = CSocketPumper::m_pDefaultPumper->Open();
		if (nRet < 0)
		{
			debug("%s: error \n", nRet);
		}
	}
	return 0;
}

int SimpleCpp::CScNetwork::Free()
{
	if (CSocketPumper::m_pDefaultPumper)
	{
		delete CSocketPumper::m_pDefaultPumper;
		CSocketPumper::m_pDefaultPumper = NULL;
	}
	
	WSACleanup();

	return 0;
}
