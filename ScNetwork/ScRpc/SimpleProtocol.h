#pragma once
#include "Protocol.h"

class CBuffer;
namespace SimpleCpp{
	class CSimpleMessage;

	class SCP_API CSimpleProtocol :
	public CProtocol
{
public:
	CSimpleProtocol(void);
	virtual ~CSimpleProtocol(void);
	//���: ��Ϣ�����������
	virtual int Package(CMessage* pMessage, char *pBuffer, int &nLen);
	//������������δ ��Ϣ
	virtual int Unpackage(char *pBuffer, int nLen, CMessage **pMessage);
	//
	
	virtual CProtocol*	CreateObject(){return new CSimpleProtocol();}
protected:
	CSimpleMessage*	m_pMessageTmp;
	CBuffer*		m_pRecvBuffer;
	int				m_nMessageSeq;
};

}
