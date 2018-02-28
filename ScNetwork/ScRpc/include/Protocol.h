#pragma once
#include "ScpDefine.h"
/*
*Э�鴦���ࡣ
*/
//������Ϣ��
namespace Scp{


class CMessage;

class SCP_API CProtocol
{
public:
	CProtocol(void);
	virtual ~CProtocol(void);

	//���: ��Ϣ�����������
	virtual int Package(CMessage* pMessage, char *pBuffer, int &nLen);
	//������������δ ��Ϣ
	virtual int Unpackage(char *pBuffer, int nLen, CMessage **pMessage);
	//
	virtual int GetMessageSeq(){return m_nMessageSeq++;};

	virtual	int DestroyResponse(CMessage* pMessage);
	virtual int DestroyMessage(CMessage* pMessage);
	//�����ȡ����
	//virtual int Recv(CMessage **pMessage);;
	//���ͺ�����
	//virtual int Send(CMessage *pMessage);;
	//������Ϣ
	//virtual int OnRecvMessage(CMessage *pMessage);
	virtual CProtocol*	CreateObject(){return new CProtocol();};

protected:
	int		m_nMessageSeq;
};


}