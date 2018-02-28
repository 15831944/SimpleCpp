
#ifndef MessageHandler_H
#define MessageHandler_H

#include "ScpDefine.h"

namespace Scp{
class CScp;
class CSimpleMessage;
class CRequest;
class CResponse;
class CRegister;
class CRegisterAck;
class CSession;

class SCP_API CMessageHandler{
public:
	CMessageHandler(CScp *pScp=NULL);
	~CMessageHandler();
//	//
	virtual int OnNewSession(CSession* pSession);
	//���е���Ϣ���
	virtual int OnMessage(CSimpleMessage *pMessage);

	//ϸ�ֵ���Ϣ
	virtual int OnRequest(CRequest* pRequset);
	virtual int OnReponse(CResponse* pRequset);
	virtual int OnRegister(CRegister* pRegister);
	virtual int OnRegisterAck(CRegisterAck* pRegister);

	//
	void	SetScp(CScp *pScp){m_pScp = pScp;}
	//
protected:
	CScp *	m_pScp;
};

}
#endif