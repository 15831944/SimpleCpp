#pragma once

#include "ScpDefine.h"
#include "Types.h"
#include <map>
using namespace std;

namespace Scp{
class CRpcServiceCatalog;
class CRpcService;
class CMessage;
class SCP_API CServiceContainer
{
public:
	CServiceContainer(void);
	virtual ~CServiceContainer(void);

	virtual int		AppendService(CRpcService* pService);
	virtual int		RemoveService(CRpcService* pService);
	virtual	CRpcServiceCatalog*	GetServiceCatalog(string& strName);
	//
	//����id ��ѯ
	virtual CRpcService*	GetService(string& strName, int64 i64Id);
	//���ݶԶ�id��ѯ
	virtual CRpcService*	GetServiceByRemoteId(string& strName, int64 i64IdFrom);
protected:

	//ӳ�䵽���֣�����Ҫӳ�䵽 id 
	//map<string, CRpcService*>			m_mapName2Service;
	//ӳ�䵽 service������
	map<string, CRpcServiceCatalog*>	m_mapName2ServiceCatalog;
	
};
}

