#pragma once

#include <string>
#include <vector>
#include <map>
#include "ScpDefine.h"
#include "Types.h"

#ifndef debug
#define debug
#endif

using namespace std;
namespace SimpleCpp{
	class CMutex;
	class CBuffer;
}

/*
*����
*/
namespace SimpleCpp{
	class CSession;
	class CVariant;
	class CMessageProcessor;
	class CServiceFactory;
	class CScp;
	//����
	typedef enum _eParamInOut{
		eParamInOut_In = 0,
		eParamInOut_Out,
		eParamInOut_InOut,
	}eParamInOut;
	//����
	class SCP_API CParam{
	public:
		CParam();
		~CParam();

		virtual int WriteTo(CBuffer* pBuffer);
		virtual int ReadFrom(CBuffer* pBuffer);

		void	CopyFrom(CParam* pOther);
		//����
		CVariant*	m_pVariant;
		//������־
		char			m_nInOut;
	};
	class SCP_API CFunctionParams{
	public:
		CFunctionParams();
		~CFunctionParams();
		//
		//
		void	Append(CVariant* pVar);
		void	Append(CParam* pParam);
		void	Clear();
		
		//vector<CVariant*>&	GetParam();;
		vector<CParam*>&	GetParam();

		void	SetReturn(CVariant* pVar);
		CVariant*	GetReturn();
		//
		void	CopyOutParam(CFunctionParams *pOther);
		CBuffer*	GetBuffer(){return m_pBuffer;}
	protected:
		//vector<CVariant*>	m_arrParams;
		//������ʹ���ˡ�
		vector<CParam*>		m_arrParams;
		CVariant*			m_pVarReturn;
		CBuffer*			m_pBuffer;
		//
	};
class CRpcService;
class CServiceContainer;
class CSimpleRpc;

	typedef int (CRpcService::*ServiceFunctionHandle)(CFunctionParams* );
	//ʹ���ڴ洫�ݲ��������ⲿ�������л�
	//typedef int (CRpcService::*ServiceFunctionHandle)(CBuffer* );
class SCP_API CRpcService
{
	friend class CRpcDispatcher;
public:
	CRpcService(void);
	virtual ~CRpcService(void);
	//
	//virtual	int		Open(CSession* pSession);
	virtual int		Open(CRpcDispatcher *pRpcProcessor);
	//��Ϊ�ͻ��˴򿪶���ͨ�����������κ� service
	virtual int		Open(string& strRemoteIp, int nRemotePort, string& strLocalIp, int &nLocalPort, bool bSendCreateMessage=true);
	//��Ϊ��������,�������Ӷ�·��ʱ��, RootService=true, ���service�����ÿ���Ựsocket �Զ�����һ���µĶ���
	//��������Ϊ����һ·socket �������ݵģ� ����Ϊfalse; �򲻻ᴴ���µĶ���
	virtual int		Open(string& strLocalIp, int &nLocalPort, bool bRootService=false);
	virtual int		Close();
	//
	virtual	int		CopyFrom(CRpcService* pOther);
	//ע�ắ��
	int				RegisterFunction(string &strName, ServiceFunctionHandle fun);
	bool			IsRegister(string &strName);
	//eg.���Ա�������õķ�����
	virtual int		Function(CFunctionParams * pParams);
	//
	string&			GetName(){return m_strName;}
	std::string GetServiceName() const { return m_strServiceName; }
	//void SetServiceName(std::string val) { m_strServiceName = val; }

	virtual	CRpcService*	CreateObject();
	//
	int64 GetObjectId() const { return m_i64ObjectId; }
	void  SetObjectId(int64 val) { m_i64ObjectId = val; }

	int64 GetObjectIdTo() const { return m_i64ObjectIdTo; }
	void  SetObjectIdTo(int64 val) { m_i64ObjectIdTo = val; }

	bool  IsAutoClone() const { return m_bAutoClone; }
	void  SetAutoClone(bool val) { m_bAutoClone = val; }

	CRpcDispatcher* GetProcessor() const { return m_pProcessor; }
	void SetProcessor(CRpcDispatcher* val) { m_pProcessor = val; }

	CServiceFactory* GetServiceFactory(){return  m_pServiceFactory;}
	//
	//virtual int		Connect();
	//virtual int		OnConnect(string& strServieName, int64 i64IdFrom, int64 i64IdTo);
	//virtual int		OnConnect(CFunctionParams * pParams);
	//
	//virtual int		CreateObject(string &strName, CRpcService*&pService, string& strRemoteIp, int &nRemotePort, string& strLocalIp, int nLocalPort);
	//
	//virtual int		CreateObject(string& strServiceName, int64 i64IdFrom, int64& i64IdTo);
	//����ͨ���Ķ��󴴽�
	//����һ��rpc���� CreateService �ⲿ�������ӻ��޷�ͨ���� ò�ƺ�windows ʲô�⺯����ͻ
	//����ͨ���� Dedicate, �ͻ��˵�
	template <class T>
	int		CreateServiceIf(T*&pNewService, int64 i64IdFrom, OUT_P int64& i64IdTo, OUT_P string& strRemoteIp, OUT_P int &nRemotePort, string& strLocalIp, int& nLocalPort);
	//����ͨ���� shared
	template <class T>
	int		CreateServiceIf(T*&pNewService, int64 i64IdFrom, OUT_P int64& i64IdTo);
	//����
	int		DestroyServiceIf(CRpcService* pService);
	//
	CSimpleRpc*	GetScp() const;
	void	SetScp(CSimpleRpc* val) { m_pRpc = (CSimpleRpc*)val; }

	CServiceFactory* GetServiceFactory() const { return m_pServiceFactory; }
	void SetServiceFactory(CServiceFactory* val) { m_pServiceFactory = val; }
	//��Ϣ���ͳ�ʱ��
	int GetRequestTimeOut() const { return m_nRequestTimeOut; }
	void SetRequestTimeOut(int val) { m_nRequestTimeOut = val; }

	CRpcService* GetParent() const { return m_pParent; }
	void SetParent(CRpcService* val) { m_pParent = val; }
	int		AppendChild(CRpcService* pService);
	int		RemoveChild(CRpcService* pService);

	bool	GetAutoKeepAlive() const { return m_bAutoKeepAlive; }
	void	SetAutoKeepAlive(bool val) { m_bAutoKeepAlive = val; }
	//������Ϣ, one way ��Ϣ
	int		KeepAlive();
	//
	//��ͨ�ų�ʱ��
	virtual int		OnNoMessageTimeout(int nTimes);
	//milli seconds;
	virtual	int		SetNoMessageTimeout(int nTimeout);;
	virtual	int		GetNoMessageTimeout();
	//�ͻ�������֪ͨ
	//virtual	int		OnConnect();
	//Ĭ�ϵĽӿں���

	virtual int		CreateServiceIf(string& strServiceName, int64 i64IdFrom, OUT_P int64& i64IdTo, OUT_P string& strRemoteIp, OUT_P int &nRemotePort, string& strLocalIp, int& nLocalPort);
	virtual int		DestroyServiceIf(string& strServiceName, int64 i64IdFrom, int64  i64IdTo);
protected:	
	//virtual int		CreateObject(string &strName, string& strRemoteIp, int &nRemotePort, string& strLocalIp, int nLocalPort);
	virtual int		OnCreateService(CFunctionParams* pParams);
	virtual int		OnCreateService(string &strName, int64 i64IdFrom, OUT_P int64& i64IdTo, OUT_P string& strRemoteIp, OUT_P int &nRemotePort, string& strLocalIp, int& nLocalPort);


	virtual int		OnDestroyService(CFunctionParams* pParams);
	virtual int		OnDestroyService(string& strServiceName, int64 i64IdFrom, int64  i64IdTo);
	//�Ҳ��� service
	virtual	int		OnServiceLost(CRpcDispatcher* pDispatcher, string& strName, int64 i64IdFrom, int64 i64IdTo, CRpcService*& pService);
	virtual CRpcService*		GetService(string& strName,  int64 i64IdTo);
	//void	CloneService(CRpcService *pService);
	//service�� function�ַ������
	virtual int		OnFunction(string &strFunction, CFunctionParams* pParams);
	//������Ϣ
	virtual int		OnKeepAlive(CFunctionParams* pParams);
	virtual int		OnKeepAlive();
	//
	//�յ��Զ˵�root close ��Ϣ ������û�ж���root create ��Ϣ��
	//��ʾһ·rootͨ�Źر�,��Ҫ���� root service֮��ͨ�š�
	//��ͨ�� service Ϊ DestroyService��Ϣ
	virtual	int		OnClose();
	//

protected:
	//virtual int     OnFunction(string &strFunction, CFunctionParams* pParams);
	//�Լ�������
	string		m_strName;
	//���������
	string		m_strServiceName;

	//
	int64		m_i64ObjectIdC;
	int64		m_i64ObjectIdTo;

	int64		m_i64ObjectId;
	//����ӳ�䵽����
	map<string, ServiceFunctionHandle>	m_mapName2Function;
	//
	CSession*		m_pSession;
	CRpcDispatcher*	m_pProcessor;

	//��Ϣ����ʱ�䡣δ�ȵ���Ӧ
	int				m_nRequestTimeOut;
	//����Ϣ��ʱʱ��
	int				m_nNoMessageTimeOut;
	//
	bool			m_bAutoClone;
	//���񹤳� �����Զ�������Ҫ����
	CServiceFactory*	m_pServiceFactory;
	//child
	//
	//vector<CRpcService*>	m_lstChildService;
	//
	CRpcService*		m_pParent;
	//
	CServiceContainer*		m_pChildServiceContainer;
	//

	//����ͨ��������� ���ڱ���scp�� Ҳ������ root service��
	//�������� root service ���õ����
	CSimpleRpc*				m_pRpc;
	//Ĭ������������ס ������Ϣ�������� ���ڰ�ȫ�˳���
	SimpleCpp::CMutex*		m_pMutex;
	bool					m_bAutoKeepAlive;

};
//����ͨ���ģ� �����ʹ�����Ϣ
template <class T>
int SimpleCpp::CRpcService::CreateServiceIf(T*&pNewService, int64 i64IdFrom, OUT_P int64& i64IdTo)
{
	T* pNewServiceTmp = new T();
	CRpcService *pRpcService = dynamic_cast<CRpcService*>(pNewServiceTmp);
	if (!pNewServiceTmp)
	{
		return -1;
	}
	string strRemoteIp;
	int nRemotePort=0;
	string strLocalIp;
	int  nLocalPort=0;

	if (i64IdFrom == -1)
	{
		i64IdFrom = (int64)pRpcService;
	}
	
	pRpcService->SetObjectId(i64IdFrom);

	int nRet =0;
	nRet =	CreateServiceIf(pRpcService->GetServiceName(), i64IdFrom, i64IdTo, strRemoteIp, nRemotePort, strLocalIp, nLocalPort);
	if (nRet < 0)
	{
		goto false_ret;
	}
	pRpcService->SetObjectIdTo(i64IdTo);
	//if (nLocalPort <= 0 || nRemotePort<=0)
	{//�Ƕ���ͨ����
		pRpcService->Open(GetProcessor());
	}
	debug("%s: CreateService <%s> new channel ;ok\n", __FUNCTION__, typeid(T).name() );

	pNewService = pNewServiceTmp;
	return nRet;
false_ret:
	if (pNewServiceTmp)
	{
		delete pNewServiceTmp;
		pNewServiceTmp = NULL;
	}

	return nRet;
}
//�����ͻ���ͨ��, �����ʹ�����Ϣ
template <class T>
int SimpleCpp::CRpcService::CreateServiceIf(T*&pNewService, int64 i64IdFrom, OUT_P int64& i64IdTo, OUT_P string& strRemoteIp, OUT_P int &nRemotePort, string& strLocalIp, int& nLocalPort)
{
	T* pNewServiceTmp = new T();
	CRpcService *pRpcService = dynamic_cast<CRpcService*>(pNewServiceTmp);
	if (!pNewServiceTmp)
	{
		return -1;
	}
 	int nRet =0;
	if (i64IdFrom == -1)
	{
		i64IdFrom = (int64)pRpcService;
	}
 	pRpcService->SetObjectId(i64IdFrom);
// 	nRet = pRpcService->Open(strRemoteIp, nRemotePort, strLocalIp, nLocalPort);
// 	
// 	pNewService = pNewServiceTmp;
// 
// 	return nRet;
	;

	nRet =	CreateServiceIf(pRpcService->GetServiceName(), i64IdFrom, i64IdTo, strRemoteIp, nRemotePort, strLocalIp, nLocalPort);
	pRpcService->SetObjectIdTo(i64IdTo);
	if (/*nLocalPort <= 0 ||*/ nRemotePort<=0)
	{//�Ƕ���ͨ����,�Է�û���� �˿ڣ�ֻ�ܴ򿪹���˿ڡ� 
		pRpcService->Open(GetProcessor());
		debug("%s: request open dedicate channel, but server open shared channel, open shared channel ok\n", __FUNCTION__);
	}
	else
	{//���ӵ��µ�ͨ����
		//�ͻ��˴�������ͨ��
		//����Ҫ���ʹ�����Ϣ�ˡ���Ϊ�Ѿ�֪ͨ�����ˡ�
		nRet = pRpcService->Open(strRemoteIp, nRemotePort, strLocalIp, nLocalPort, false);
		if (nRet < 0)
		{
			debug("%s: open dedicated session false [%s:%d]->[%s:%d]\n ", __FUNCTION__, strLocalIp.c_str(), nLocalPort, strRemoteIp.c_str(), nRemotePort);
		}
		else
		{
			debug("%s: open dedicated session ok    [%s:%d]->[%s:%d]\n ", __FUNCTION__, strLocalIp.c_str(), nLocalPort, strRemoteIp.c_str(), nRemotePort);
			//pScp->AppendSession(pNewSession);
		}

		goto ret;
#if 0
// 		nRet = pRpcService->Open(strRemoteIp, nRemotePort, strLocalIp, nLocalPort);
 		CSimpleRpc* pScp = GetScp();
// 		pScp->AppendService(pRpcService);		
// 		
		CSession* pNewSession = pScp->CreateSession();
		if (!pNewSession)
		{
			debug("%s: create dedicated session false\n", __FUNCTION__);
			nRet = -1;
			goto false_ret;
		}

		nRet = pNewSession->Open(strRemoteIp, nRemotePort, strLocalIp, nLocalPort);

		if (nRet < 0)
		{
			debug("%s: open dedicated session false [%s:%d]->[%s:%d]\n ", __FUNCTION__, strLocalIp.c_str(), nLocalPort, strRemoteIp.c_str(), nRemotePort);
			pScp->RemoveSession(pNewSession);
		}
		else
		{
			debug("%s: open dedicated session ok    [%s:%d]->[%s:%d]\n ", __FUNCTION__, strLocalIp.c_str(), nLocalPort, strRemoteIp.c_str(), nRemotePort);
			pRpcService->Open((CRpcDispatcher*)pNewSession->GetProcessor());
			//pScp->AppendSession(pNewSession);
		}
#endif
	}
ret:
	pNewService = pNewServiceTmp;
	debug("%s: CreateService <%s> new channel ;ok\n", __FUNCTION__, typeid(T).name() );
	return nRet;
false_ret:
	if (pNewServiceTmp)
	{
		delete pNewServiceTmp;
		pNewServiceTmp = NULL;
	}
	return nRet;
}


}