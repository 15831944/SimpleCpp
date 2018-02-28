#pragma once

//#include "Session.h"
#include "RpcService.h"
#include "ScpDefine.h"


namespace Scp{
	class CSession;
	class CFunctionParams;
	class CRpcClientHandler{
	public:
		CRpcClientHandler();
		~CRpcClientHandler();

		virtual void OnMessage(CFunctionParams *pParams);

	};
	//һ���ͻ���ֻ������һ�� service.
	//����ͨ�� ���� protocol��ʽ �����ͬ���Ϳͻ���/���� ���� һ������ͨ��
	// �ͻ���/������ �ǵ�һ��Ӧ�ķ�ʽ��������˫��� �ͻ��˷�����ͬʱ������һ��ͨ����ͬһ��
	class SCP_API CRpcClient
		: public CRpcService
	{
	public:
		CRpcClient(void);
		virtual ~CRpcClient(void);
		//
		//
		virtual int Open(CSession *pSession);

		virtual int Function(int nSize);
		//
		//�ص�������ʽ��
		//virtual int OnMessage(CRpcMessage *pMessage);
	protected:
		//
		//
		string		m_strService;
		CSession*	m_pSession;
		//��Ϣ�����̳߳�
		//CThreadPool*	m_pThreadPool;
		//CProtocol* m_pProtocol;
		//CMessagerProcessor* m_pProcessor;
		//�ص����
		//CRpcClientHandler *m_pHandler;
	};

}