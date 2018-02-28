#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <map>
#include <set>
#include <list>
#include "ScNetworkDefine.h"
#include "Socket.h"
#include "Thread.h"
#include "AsyncSocket.h"
#include "Semaphore.h"
#include "mutex.h"
#include "Event.h"
#include "Socket.h"
#include "AsyncSocket.h"
#include "SelectPumper.h"
#include "Http.h"
using namespace std;
using namespace SimpleCpp;

namespace SimpleCpp{
	class SCNETWORK_API CHttpClient
	{
	public:
		CHttpClient();
		virtual ~CHttpClient();

		//ͬ��socket
		virtual 	int Open(string &strRemoteIp, int nRemotePort = 8500, int nConnectMode = ST_TCP);
		//�첽socket����ʱ��ʵ��
		virtual 	int Open(CSocket* pSocket);
		virtual int Request(CHttpRequest *pReqMsg, CHttpResponse *pRspMsg, int nTimeOut = 5000);
		virtual int Request(string strReqMsg, string strRspMsg, int nTimeOut);
		
		//������ʱ����
		void SetLocalAddress(string &strLocalIp, int nLocalPort);
		//������յ�����Ϣ

		virtual int Close();

	private:
		string m_strLocalIp;
		int m_nLocalPort;
		string m_strRemoteIp;
		int m_nRemotePort;
		int m_nConnectMode;

		CSocket *m_pSocket;
		char *m_pBuf;
		int m_nBufLen;
	};
}

#endif