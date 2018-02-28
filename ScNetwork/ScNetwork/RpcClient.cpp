#include "StdAfx.h"
#include "RpcClient.h"
#include "RpcService.h"
#include "RpcMessage.h"
#include "RpcDispatcher.h"
#include "Session.h"

namespace SimpleCpp{
CRpcClient::CRpcClient(void)
//: m_pSession(NULL)
{
}

CRpcClient::~CRpcClient(void)
{
}

int CRpcClient::Function( int nSize )
{
// 	if (!m_pSession)
// 	{
// 		return -1;
// 	}
	//�Բ������
	CFunctionParams params;
	//
	CRpcMessage rpcMessage;
	rpcMessage.SetService(m_strService);
	rpcMessage.SetFunction(string(__FUNCTION__));
	//
	//rpcMessage.AppendI32(nSize);
	//
	CMessage *pResponse(NULL);
	m_pSession->Send(&rpcMessage, &pResponse, 2*1000);
	//
	if (pResponse)
	{//�յ���Ϣ��Ӧ
		CRpcMessage *pRpcResponse = dynamic_cast<CRpcMessage*>(pResponse);
		if (pRpcResponse)
		{
			//pRpcResponse->m_pParams->m_varReturn.m_nType;
			//��ȡ��������ֵ
		}
	}
	else
	{
		//δ�յ���Ӧ
	}
	//
	return 0;
}

int CRpcClient::Open(CSession *pSession)
{
	if (m_pSession)
		return -1;

	m_pSession = pSession;
	//
	//����Ҫsession�����ⲿ��������Ϊһ��session�����ж�� client����service
	//����Ҫ����
	//CRpcDispatcher *m_pDispatcher = new CRpcDispatcher();
	CRpcDispatcher *pDispatcher(NULL);
	CMessageProcessor *pProcessor = m_pSession->GetProcessor();
	pDispatcher = dynamic_cast<CRpcDispatcher*>(pProcessor);
	//
	pDispatcher->AppendService(this);;
	//

	//
	return 0;
}

}
