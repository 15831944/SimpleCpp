#pragma once

#include "ScpDefine.h"
#include <string>
//
//����������
//
namespace SimpleCpp{
	class CSocket;
	class CSocketPumper;
}

using namespace SimpleCpp;
namespace SimpleCpp{
	class CTransport;

	using namespace std;
class SCP_API CTransportHandler{
public:
	CTransportHandler();
	~CTransportHandler();
	//�յ����ݵĻص�����
	virtual int OnRecv(CTransport* pTransport);
	virtual int OnDisconnect(CTransport* pTransport);
	virtual int OnTimer(CTransport* pTransport);
	//ͨ�������ݳ�ʱ
	virtual int OnNoDataTimeout(CTransport* pTransport, int nTimes);
protected:
	;
};

class SCP_API CTransport
{
public:
	CTransport(void);
	virtual ~CTransport(void);

	virtual int Open(string strRemoteIp, int nRemotePort,
					string strLocalIp="", int nLocalPort=0);
	//
	virtual int Open(CSocket*	pSocket);
	virtual int Close();
	//

	virtual int Send(char *pBuffer, int nLen);
	virtual int Recv(char *pBuffer, int nLen);

	virtual int OnRecv(int nError);
	//

	virtual void SetHandler(CTransportHandler* pHandler){m_pHandler = pHandler;};
	//
	virtual CTransport*	CreateObject(){return new CTransport();};
	
	virtual int OnNoDataTimeOut(int nErr, int nTimes);
	virtual int SetNoDataTimeout(int nTimeout);

	virtual void SetPumper(CSocketPumper *pPumper){m_pSocketPumper = pPumper;};
	CSocketPumper*	 GetPumper(){return m_pSocketPumper;}
protected:
	CTransportHandler*	m_pHandler;
	CSocketPumper *m_pSocketPumper;	//ly
};



}
