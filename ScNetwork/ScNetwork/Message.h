#pragma once

#include "ScpDefine.h"


namespace SimpleCpp{
	class CMutex;
	class CEvent;
	class CBuffer;
}

namespace SimpleCpp{
	typedef enum _eMessageType{
		eMessageType_None=-1,
		eMessageType_Base,
		eMessageType_Request,
		eMessageType_Response,
		eMessageType_Oneway,
		eMessageType_Register,
		eMessageType_RegisterAck,

	}eMessageType;

	typedef enum _eMessageParseState{
		eMessageParseState_Error = -1,
		eMessageParseState_NoHeader,
		eMessageParseState_NeedMore,
		eMessageParseState_Success,
	}eMessageParseState;


using namespace SimpleCpp;

class CSession;
class SCP_API CMessage
{
	friend class CSession;
public:
	CMessage(void);
	virtual ~CMessage(void);

	virtual int		Build();
	virtual eMessageParseState		Parse(CBuffer *pBuffer, int &nPassedLen);;
	virtual CBuffer*	GetBuffer(){return m_pBuffer;};

	virtual void	Clear();
	virtual bool	IsValid();
	//
	virtual void	SetSession(CSession* pSession){m_pSession = pSession;}
	virtual CSession* GetSession(){return m_pSession;}
	//
	int		SetMessageId(int nId){m_nMessageId = nId; return 0;}
	int		GetMessageId(){return m_nMessageId;}
	int		GetType(){return m_nType;};
	void	SetType(int nType){m_nType = nType;};

	void	SetResponse(CMessage* pMessage){m_pReponse = pMessage;};

	//CEvent*			GetResponseEvent(){return m_pEventResponse;};
	CEvent*	GetEvent(){return m_pEventResponse;}
	//
	CEvent*		m_pEventResponse;
protected:
	//
	CSession*	m_pSession;
	CBuffer*	m_pBuffer;
	//��Ϣ��Ӧ
	CMessage*	m_pReponse;
	//
	int		m_nSessionId;
	// messid Ҳ�� CSeq;
	int		m_nMessageId;
	int		m_nType;

	char	m_szHeadFlag[4];//'ScpH'
	//header ���ȡ����� payload �ĳ���
	int		m_nHeaderLength;
	//������Ϣ���ĳ��ȣ� len, ���� header flag �� len����
	int 	m_nPackageLength; 
	//int		m_nSessionId;
	// messid Ҳ�� CSeq;
	//int		m_nMessageId;
	//
	eMessageParseState m_parseState;
};

}