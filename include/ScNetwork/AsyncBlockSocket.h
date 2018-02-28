#pragma once
#include "Socket.h"

#include "ScNetworkDefine.h"
//�첽����socket�� ָʹ�õ��� ����socket
//��������һ���첽�������� socket
//�����ṩ�ص�ʱ�䴦��ʽ����
//�ڲ��Զ�ʵ��һ���߳�
namespace SimpleCpp{
	class CThread;
	class CMutex;
	class CEvent;
	class CBuffer;
}

namespace SimpleCpp
{

class SCNETWORK_API CAsyncBlockSocket :
	public CSocket
{
public:
	CAsyncBlockSocket(void);
	virtual ~CAsyncBlockSocket(void);
	
	//virtual int Accept(CSocket *pConnectedsocket );
	virtual int Create(eSocketType nType);

	virtual int Recv(char *pBuf, int nLen);
	virtual	int Close();

	virtual	bool WaitForReadyRead(int nMilliSeconds=1000, int nBytes=0);
	//
protected:
	virtual int Attach(HSOCKET hSocket);

	virtual	int Run();
	static  int __stdcall ThreadProc(void *pData);
	CThread*	m_pThread;
	CMutex*	m_pMutexRecvBuffer;
	CBuffer*	m_pBuffer;
	CEvent*	m_pEventReadyRead;
	int					m_nReadyReadBytes;
};
}