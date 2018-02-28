#pragma once
#include "Protocol.h"

class CBuffer;
namespace SimpleCpp{
	class CRpcMessage;

class SCP_API CRpcProtocol :
	public CProtocol
{
public:
	CRpcProtocol(void);
	virtual ~CRpcProtocol(void);

	//���: ��Ϣ�����������
	virtual int Package(CMessage* pMessage, char *pBuffer, int &nLen);
	//������������δ ��Ϣ
	virtual int Unpackage(char *pBuffer, int nLen, CMessage **pMessage);

	virtual	int DestroyResponse(CMessage* pMessage);
	virtual int DestroyMessage(CMessage* pMessage);
	//
	virtual CProtocol*	CreateObject(){return new CRpcProtocol();};
	//
protected:
	CRpcMessage*	m_pMessageTmp;
	CBuffer*		m_pBuffer;
};

}