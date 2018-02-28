
#include "stdafx.h"
#include "MessageHandler.h"
#include "Register.h"
#include "Response.h"
#include "Request.h"
#include "Message.h"
#include "Scp.h"

namespace SimpleCpp{

CMessageHandler::CMessageHandler(CScp *pScp)
: m_pScp(pScp)
{
	
}

CMessageHandler::~CMessageHandler()
{

}

int CMessageHandler::OnMessage( CSimpleMessage *pMessage )
{
	if (!m_pScp)
	{
		return -1;
	}
	debug("%s: type: %d\n", __FUNCTION__, pMessage->GetType());
	//�յ��Ļ�Ӧ��Ϣע����Ϣ��
	//�����Ƿ��з�����Ϣ��Ӧ����Ҫ�ȴ�ͬ���ظ�����Ϣ
	/* �Ѿ���ÿһ��session�ִ�����ˡ�
	CMessage *pSendMessage = NULL;
	pSendMessage = m_pScp->FindRequestMessage(pMessage->GetMessageId() );
	if (pSendMessage)
	{
		debug("%s: type: %d\n", __FUNCTION__, pMessage->GetType());
		pSendMessage->SetResponse((CResponse*)pMessage);
		pSendMessage->GetEvent()->Set();

		return 0;
	}*/
	//�յ���������Ϣ
	if (pMessage->GetType() == eMessageType_Register)
	{//��Ҫ��Ӧ��Ϣ
		OnRegister(dynamic_cast<CRegister*>(pMessage) );
	}
	else if (pMessage->GetType() == eMessageType_RegisterAck)
	{
		OnRegisterAck(dynamic_cast<CRegisterAck*>(pMessage) );
	}
	else if (pMessage->GetType() == eMessageType_Request)
	{
		OnRequest(dynamic_cast<CRequest*>(pMessage) );
	}
	else if (pMessage->GetType() == eMessageType_Response)
	{
		OnReponse(dynamic_cast<CResponse*>(pMessage) );
	}
	else{

	}


	return 0;
}

int CMessageHandler::OnRequest( CRequest* pRequest )
{
	debug("%s\n", __FUNCTION__);
	if (m_pScp)
	{
		CResponse *pResponse  = new CResponse(pRequest);

		pResponse->Build();

		m_pScp->Send(pResponse);

		delete pResponse;
		delete pRequest;
	}
	return 0;
}

int CMessageHandler::OnReponse( CResponse* pResponse )
{
	debug("%s\n", __FUNCTION__);
	delete pResponse;
	return 0;
}
//���ͻ�Ӧ��Ϣ
int CMessageHandler::OnRegister( CRegister* pRegister )
{
	debug("%s: \n", __FUNCTION__);
	//
	int nSessionId = (int)pRegister->GetSession();
	
	m_pScp->RegisterSession(nSessionId, pRegister->GetSession());
	//
	CRegisterAck *pRegisterAck = new CRegisterAck(pRegister);
	pRegisterAck->Build();

	m_pScp->Send(pRegisterAck);

	delete pRegisterAck;

	delete pRegister;

	return 0;
}

int CMessageHandler::OnRegisterAck( CRegisterAck* pRegisterAck )
{
	debug("%s: \n", __FUNCTION__);
	debug("%s: ret: %d\n", __FUNCTION__, pRegisterAck->GetAckCode());

	delete pRegisterAck;
	
	return 0;
}

int CMessageHandler::OnNewSession( CSession* pSession )
{

	return 0;
}

}