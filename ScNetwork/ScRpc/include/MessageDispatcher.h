#pragma once

#include <map>
#include <string>
#include "MessageProcessor.h"
using namespace std;
/*
*�ַ���Ϣ
*/
namespace Scp{

	class CService;
	class CMessage;
	class CMessageDispatcher:public CMessageProcessor
{
public:
	CMessageDispatcher(void);
	virtual ~CMessageDispatcher(void);
	//
	virtual int		Dispatch(CMessage *pMessage);
	//
protected:
	map<string, CService*> m_mapName2Service;
};

}