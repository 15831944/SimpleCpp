#pragma once

#include <map>
#include <string>
#include "MessageProcessor.h"
#include "ScpDefine.h"
#include "Types.h"

using namespace std;

namespace SimpleCpp{
	class CThreadPool;
}

/*
*�ַ���Ϣ
*/
namespace SimpleCpp{

	class CRpcService;
	class CMessage;
	class CRpcMessage;
	class CRpcServiceCatalog;
class SCP_API CRpcDispatcher:public CMessageProcessor
{
public:
	CRpcDispatcher(void);
	virtual ~CRpcDispatcher(void);
	//
	//
	virtual int		AppendService(CRpcService* pService);
	virtual int		RemoveService(CRpcService* pService);
	virtual	CRpcServiceCatalog*	GetService(string strName);

	//
	virtual int		OnMessage(CMessage *pMessage);
	//
	virtual CMessageProcessor*	CreateObject();
	//
	virtual CRpcService*	GetService(string strName, int64 i64Id);
	
	//
	CRpcService* GetRootService() const;
	void SetRootService(CRpcService* val);

	virtual int OnNoMessageTimeout(int nTimes);
protected:
	void	CloneServices(CRpcDispatcher *pRpcDispatcher);
	virtual int		Dispatch(CRpcMessage *pMessage);
	//ӳ�䵽���֣�����Ҫӳ�䵽 id 
	//map<string, CRpcService*>			m_mapName2Service;
	//ӳ�䵽 service������
	map<string, CRpcServiceCatalog*>	m_mapName2ServiceCatalog;
	//�����񣬲���delete
	CRpcService*						m_pRootService;
	// ��Ϣ�����̳߳ء�Ŀǰ���� ��ʱ��Ϣ�Ϳ����ˡ�
	//SThread::CThreadPool*				m_pThreadPool;
};
class SCP_API CRpcServiceCatalog{
public:
	CRpcServiceCatalog();
	~CRpcServiceCatalog();

	int		AppendService(CRpcService* pService);
	int		RemoveService(CRpcService* pService);
	CRpcService*	GetService(int64 i64Id);
	CRpcService*	GetServiceByRemoteId(int64 i64Id);

	CRpcService*	GetDefaultService();
	//
	void	CloneService(CRpcServiceCatalog* pOther/*, CRpcService* pSkipService=NULL*/);
	//
	CRpcDispatcher*				m_pRpcDispatcher;
	//
	string						m_strName;
	map<int64, CRpcService*>    m_mapId2Service;
	map<int64, CRpcService*>	m_mapToId2Service;
};
}