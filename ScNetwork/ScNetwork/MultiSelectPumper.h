#pragma once
#include <vector>
#include "SocketPumper.h"
#include "ScNetworkDefine.h"

/*
*�Զ����߳�ƽ��� select pumper
*/
using namespace std;

namespace SimpleCpp{

#define SOCKET_PER_SELECT 625

class CSelectPumper;

class SCNETWORK_API CMultiSelectPumper :
	public CSocketPumper
{
public:
	CMultiSelectPumper(void);
	virtual ~CMultiSelectPumper(void);
	//
	virtual int Open();
	virtual int CreatePumper(int nCount = 5);
	virtual int DestroyPumper();

	virtual int Append(CAsyncSocket *pSocket);
	virtual int Remove(CAsyncSocket *pSocket);

protected:
	CSelectPumper*	GetFreePumper();
protected:
	//��Լ һ���߳� 500 �� socket
	CSelectPumper *m_pSelectedPumper;
	vector<CSelectPumper *> m_vecSelectPumper;
};

}