#pragma once
#include "Protocol.h"


namespace SimpleCpp{
	class CSimpleMessage;
	class CBuffer;
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
