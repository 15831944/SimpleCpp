#include "StdAfx.h"
#include "RpcDuplexService.h"
#include "RpcMessage.h"
#include "Session.h"
#include "Variant.h"
#include "RpcDispatcher.h"

namespace SimpleCpp{
CRpcDuplexService::CRpcDuplexService(void)
: CRpcService()
{
	m_strName = "CRpcDuplexService";
	//m_mapName2Function["Function"] = &CRpcService::Function;;
	RegisterFunction(string("Function"), (ServiceFunctionHandle)&CRpcDuplexService::OnFunction);
}

CRpcDuplexService::~CRpcDuplexService(void)
{
}
//eg.
int CRpcDuplexService::Function( int nCount, int& nCountRet )
{
	if (!m_pProcessor)
		return -1;
	if (!m_pSession)
	{
		m_pSession = m_pProcessor->GetSession();
		if (!m_pSession)
		{
			return -2;
		}
	}
	//
	//
	int nRet = 0;
	CRpcMessage rpcCall;
	
	rpcCall.SetService(m_strName);
	rpcCall.SetFunction(string("Function"));
	rpcCall.SetObjectIdFrom(m_i64ObjectId);
	rpcCall.SetObjectIdTo(m_i64ObjectIdTo);
	//���
	CFunctionParams *pParams = rpcCall.GetFunctionParams();
	CBuffer* pParamBuffer = pParams->GetBuffer();
	//int nReturn;
	pParamBuffer->Write(nRet);
	//
	pParamBuffer->Write(nCount);

	pParamBuffer->Write(nCountRet);

	//����
	//
	//
	//����
	CRpcMessage *pRpcRet(NULL);
 
	if (!m_pSession)
	{
		m_pSession = m_pProcessor->GetSession();
	}
	nRet = m_pSession->Send(&rpcCall,(CMessage**) &pRpcRet, 20*1000);
	if (nRet < 0)
	{
		debug("%s: false\n", __FUNCTION__);
		return -1;
	}
	else
	{
		int nRetValue;
		if (pRpcRet)
		{
			CBuffer *pParamBuffer =  pRpcRet->GetFunctionParams()->GetBuffer();
			//�����л�
			pParamBuffer->Read(nRetValue);
			pParamBuffer->Read(nCountRet);
			debug("%s: ok: ret [%d], out count ret[%d]\n", __FUNCTION__, nRetValue, nCountRet);
		}

		return nRetValue;
	}

	return nRet;
}
//ͨ�õ���Ϣ��Ӧ���� �ص� 
int CRpcDuplexService::OnFunction( CFunctionParams* pFunctionParam )
{
	//CRpcService::OnFunction();
	debug("%s: ++\n", __FUNCTION__);
	//ʹ��buffer ֱ�ӽ��з����л�
	CBuffer*	pBuffer = pFunctionParam->GetBuffer();

// 	for (int i=0; i<arrParms.size();
// 		i++)
// 	{
// 		CParam* pParam = arrParms.at(i);
// 		//ת������������
//		pParam->m_pVariant->value<int>();
// 		OnFunction( pParam->m_pVariant->value<int>()
// 					, pParam->m_pVariant->value<int>()
// 					);
//		
// 		//
// 	}
	//
	int nRet(0);
	pBuffer->Read(nRet);
	int nCount(0);
	pBuffer->Read(nCount);
	int nCountRet(0);
	pBuffer->Read(nCountRet);
	//
	OnFunction(nCount, nCountRet);
	
	//���������л� �� pBuffer;, ֻ�����л���Ҫout ��param
	pBuffer->Clear();
	//����ֵ
	pBuffer->Write(nRet);

	pBuffer->Write(nCountRet);
	//
		
	debug("%s: --\n", __FUNCTION__);
	return 0;
}
//ʵ�ʵ���Ϣ��Ӧ����
int CRpcDuplexService::OnFunction(int nCount, int& nRet)
{
	nRet = nCount + 1;

	return nCount;
}

int CRpcDuplexService::OnGetDevices(CFunctionParams* pParams)
{
	CBuffer *pBuffer = pParams->GetBuffer();
	string strName;
	pBuffer->Read(strName);

	vector<CDeviceInfo0*> arrDevices;
	pBuffer->Read(arrDevices);
	
	OnGetDevices(strName, arrDevices);
	//
	pBuffer->Free(arrDevices);
	//
	return 0;
}

int CRpcDuplexService::OnGetDevices(string& strName, vector<CDeviceInfo0*>& arrDevices)
{
	return 0;
}

int CRpcDuplexService::GetDevices(string& strName, vector<CDeviceInfo0*>& arrDevices)
{

	return 0;
}

}