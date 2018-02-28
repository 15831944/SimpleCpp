// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SCP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SCP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�


#ifndef SCP_H
#define SCP_H

#include <vector>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <list>
#include "ScpDefine.h"
#include "Types.h"

using namespace std;
namespace SimpleSocket{
	class CAsyncSocket;
	class CSocket;
	class CSocketPumper;
}
namespace SThread{
	class CThread;
	class CMutex;
	class CThreadPool;
}
using namespace SimpleSocket;
using namespace SThread;
namespace Scp{
	class CMessage;
	class CRequest;
	class CResponse;
	class CRegister;
	class CRegisterAck;
	class CSession;
	class CListenSocketHandler;
	class CSessionSocketHandler;
	class CScp;
	class CMessageHandler;
	class CProtocol;
	class CMessageProcessor;
	class CTransport;
	
class CRpcDispatcher;
class CRpcService;
class CFactory;
class CServiceContainer;
// �����Ǵ� Scp.dll ������; 
class SCP_API CScp {
	friend class CListenSocketHandler;
	friend class CSession;

public:
	CScp(void);
	~CScp();
	//
	static int Init();
	static int Free();
	//
	int		Open(string strLocalIp, int nLocalPort/*, string strRemoteIp, int nRemotePort*/);
	void	Close();
	//
	//
	void	SetListenSocket(CSocket* pSocket);;
	CSocket *GetListenSocket();;
	//void	SetMessageHandler(CMessageHandler* pHandler);
	void	SetMessageProcessor(CMessageProcessor *pProcessor){m_pProcessor = pProcessor;};
	CMessageProcessor *GetMessageProcessor(){return m_pProcessor;};
	void	SetProtocol(CProtocol *pProcotol){m_pProcotol = pProcotol;}
	CProtocol *GetProtocol(){return m_pProcotol;}
	void	SetTransport(CTransport *pTransport);
	CTransport*	GetTransport(){return m_pTransport;};
	//ͬ���ȴ����ص���Ϣ
	int		Send(CMessage *pRequest, CMessage **pResponse, int nMilliSeconds );
	int		Send(CResponse *pResponse);
	int		Send(CRequest  *pRequest);
	int		Send(CMessage*	pMessage);

	CSession*	FindSession( int nId );
	//ͨ�����ڿͻ���
	virtual CSession*	CreateSession();;
	virtual void		DestroySession(CSession* pSession);
	//�ǼǻỰ 
	int		RegisterSession(int nId, CSession* pSession);
	//
	//


	//�ڲ����õ�
	int		AppendSession(CSession* pSession);
	void	RemoveSession(CSession* pSession);
	void	RemoveSession(int nId);
	map<CSession*, CSession*>& GetSessions(){return m_mapId2Session;}
	//
	//CMessage*	FindRequestMessage(int nMessageId);
	//
	void		SetFactory(CFactory *pFactory){m_pFactory = pFactory;};
	CFactory*	GetFactory(){return  m_pFactory;}
	

	CSocketPumper *GetSocketPumper(){return m_pSocketPumper;};

	//virtual int OnServiceConnect(CSession*pSession, string& strServieName, int64 i64IdFrom, int64 i64IdTo);

//�ڲ����ýӿ�
	//virtual int		AppendService(CRpcService* pService);
	//virtual int		RemoveService(CRpcService* pService);
	//CRpcService*	GetService(string& strName, int64 i64IdTo);
	//virtual	int		OnSessionServiceLost(CSession* pSession, string& strName, int64 i64IdTo);
	//session ͨ�� ��ʱ��
	virtual int		OnNoMessageTimeout(CSession* pSession, int nTimes);
protected:
	//���յ���������Ϣ
	/*int			PushRecvMessage(CMessage* pMessage);
	CMessage*	PopRecvMessage();
	//���͵���Ϣ���У����ڵȴ�ͬ����Ϣ����
	int			AppendSendMessage(CMessage* pMessage);
	int			RemoveSendMessage(CMessage*pMessage);
	//
	static int __stdcall	ThreadMessageHandler(void *pParam);
	int			RunMessageHandler();*/
protected:

	CMessageHandler*	m_pMessageHandler;
	CMutex*				m_pMutexMessageHandler;

	map<CSession*, CSession*>	m_mapId2Session;
	list<CSession*>				m_lstSession;
	CMutex*				m_pMutexSessions;
	
	//map<int, CSession*>	m_mapId2Session;
	CMutex*				m_pMutexMapId;


	CSocket*			m_pSocketListen;
	CListenSocketHandler*	m_pListenHandler;
	//���յ���Ϣ���С�
	//queue<CMessage*>	m_queueRecvMessage;
	//CMutex*				m_pMutexRecvMessage;
	//
	//CThread*			m_pThreadMessageHandler;
	//���͵���Ϣӳ����У� ���ڵȴ�������Ϣ֮��Ļ�Ӧ��ͬ����Ϣ
	map<int, CMessage*>	m_mapId2SendMessage;
	CMutex*				m_pMutexMapSendMessage;
	//
	CFactory*			m_pFactory;
	//
	CMessageProcessor*	m_pProcessor;
	//
	CProtocol*			m_pProcotol;
	//CTransport
	CTransport*			m_pTransport;
	//CThreadPool

	CSocketPumper *		m_pSocketPumper;
	//���еķ��� �� dispatcher, �����ǲ�ѯ�á������� dispatch
	//vector<CRpcService*>	m_lstService;
	//CRpcDispatcher*			m_pDispatcher;
	//CServiceContainer*		m_pServiceContainer;
	//��service�� ȫ�ַ��񣬱���CreateObject, DestroyObject, Connect OnConnect
	//�������� Dispatcher�� �̳߳ء�
	CThreadPool*		m_pThreadPoolProcessor;;
};
}
extern SCP_API int nScp;

SCP_API int fnScp(void);

#endif
