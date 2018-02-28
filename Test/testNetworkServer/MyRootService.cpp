#include "StdAfx.h"
#include "MyRootService.h"
#include "PlatformService.h"
#include "StreamService.h"
#include "ServiceContainer.h"

CMyRootService::CMyRootService(void)
{
	m_bAutoClone = true;
}

CMyRootService::~CMyRootService(void)
{
}

int CMyRootService::OnCreateService(string &strName, int64 i64IdFrom, OUT_P int64& i64IdTo, OUT_P string& strRemoteIp, OUT_P int &nRemotePort, string& strLocalIp, int& nLocalPort)
{
	debug("%s: %d ++: %s\n", __FUNCTION__, __LINE__, strName.c_str());
	//���Ȳ���form id�Ķ�Ӧ service �Ƿ���ڣ�
	
	//
	i64IdTo = 1000;
	
	int nRet = 0;
	CRpcService* pNewService(NULL);
	if (strName == "CModuleIFS")
	{
		pNewService = new CPlatformService();
		i64IdTo = (int64)pNewService;
		pNewService->SetObjectId(i64IdTo);
		pNewService->SetObjectIdTo(i64IdFrom);
		
	}
	else if (strName == "CStreamIfS")
	{
		pNewService = new CStreamService();
		i64IdTo = (int64)pNewService;
		pNewService->SetObjectId(i64IdTo);
		pNewService->SetObjectIdTo(i64IdFrom);
	}
	//
	//pNewService->SetNoMessageTimeout(3*1000);
	//��μ�� service �Ͽ���
	m_pChildServiceContainer->AppendService(pNewService);
	//
	if (nLocalPort <= 0)
	{//����ͨ��
		nRet = pNewService->Open(GetProcessor());
	}
	else
	{//����ͨ�� ��������
		strRemoteIp = "127.0.0.1";
		nRemotePort = nLocalPort + 1;

		nRet = pNewService->Open(strRemoteIp, nRemotePort);
	}

	return 0;
}

CRpcService* CMyRootService::CreateObject()
{
	CRpcService *pService(NULL);

	pService = new CMyRootService();
	pService->CopyFrom(this);

	return pService;
}

int CMyRootService::OnDestroyService(string& strServiceName, int64 i64IdFrom, int64 i64IdTo)
{
	debug("%s: %d ++: %s\n", __FUNCTION__, __LINE__, strServiceName.c_str());
	CRpcService::OnDestroyService(strServiceName, i64IdFrom, i64IdTo);

	return 0;
}
