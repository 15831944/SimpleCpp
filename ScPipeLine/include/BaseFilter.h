#pragma once

#include "PipeLineDef.h"
/*
#include <sigc++/trackable.h>
#include <sigc++/signal.h>
#include <sigc++/connection.h>
#include <sigc++/functors/ptr_fun.h>
#include <sigc++/functors/mem_fun.h>*/
#include <string>
#include <vector>
#include <map>

class CBuffer;

namespace SimpleCpp{
	class CThread;
}

namespace PipeLine{
	using namespace std;
	using namespace SimpleCpp;
	
	class CBasePipeLine;
	class CFilterPinBuffer;
	class CBaseFilter;
	class CFilterPin;
	//�ź� ���
//typedef sigc::signal<int, CBaseFilter*, int, CFilterPinBuffer* >	SigPinOut;
	typedef enum _eFilterState{
		eFilterState_Invalid=-1,
		eFilterState_Open =0,
		eFilterState_Run ,
		eFilterState_ToStop,
		eFilterState_Stop,
		eFilterState_Pause,
		eFilterState_Unknown,
	}eFilterState;
// 	typedef long long int64;
// 	typedef long long int64_t;
#ifndef int64_t
#define  int64_t long long 
#endif

	typedef void (__stdcall *FilterCB_Progress)(float fSpeed, int64_t s64CurPos,  int64_t s64Total, void *pUserData, void *pReversed);
	typedef void (__stdcall *FilterCB_Finished)(void *pUserData, void *pReversed);
	typedef void (__stdcall *FilterCB_Event)(void *pEvent, int nEventLen, void *pUserData, void *pReversed);


	class PIPELINE_API CBaseFilter
{
public:
	CBaseFilter(CBasePipeLine* pStream =NULL);
	virtual ~CBaseFilter(void);

	virtual int Attach(CBasePipeLine* pStream);
	//
	virtual int		Open(char* pParam, bool bHasThread=false);

	virtual int		Close();
	void			CreateFilterThread( bool bHasThread );
	bool			HasFilterThread() const;

	//
	virtual int		Start();
	virtual int		Pause();
	virtual int		Resume();
	virtual int		Stop();
	//
	eFilterState GetState(){return m_state;}
	virtual bool IsKind(char *pSzKind);
	virtual char *GetType();
	virtual char *GetName();
	virtual char *GetKind();
	//
	CFilterPin*		GetPinOut(int nIndex);
	CFilterPin*		GetPinIn(int nIndex);
	//					ǰһ��pinOut, ��ǰ��pinIn, buffer;
	//ÿһ�����ݶ��ᱻ����һ��
	virtual int  OnPinIn(CFilterPin* pPrevPinOut, CFilterPin* pPinIn, CFilterPinBuffer *pPinBuffer);
	//
	//����������ÿ��filter�������������ִ�еĻ��ᡣ
	// ������ �ж����̻߳���û�ж����̡߳��������յ�������������ִ�л���
	virtual int DoFilter();
	//
	//filter �����̵߳��õĺ�����
	virtual int Run();
	//
	const char*	GetParam(char *pName);

	virtual CBaseFilter* CreateObject();
	virtual void DeleteObject(CBaseFilter* pFilter);
	//
	static void ParseParam(char *pParam, int nLen, map<string, string> &mapParamValue);
	static void ParseParamCmd(char *pParam, char *pName, char *pVal);

	//
	int		SetEventCb(FilterCB_Event cbEvent, void *pUserData, void *pReversed);
	int		SetProgressCb(FilterCB_Progress cbProgress, void *pUserData, void *pReversed);
	int		SetFinishedCb(FilterCB_Finished cbFinished, void *pUserData, void *pReversed);

protected:
	//
	static int __stdcall ThreadProc(void *pData);
	//
	string  m_strName;
	string	m_strKind;
	string	m_strType;
	//�ͺ����֣� �����������
	char	m_szType[32];
	//���� source  decoder encoder render��
	char	m_szKind[32];
	//����Ķ������� �û������趨 ��
	char	m_szName[32];

	CBasePipeLine*	m_pStream;
	//�����̡߳�һ����source ����ʹ�á�����filter ���Բ���ᡣ
	CThread*	m_pThread;
	bool		m_bHasFilterThread;
	
	//void		HasFilterThread(bool val) { m_bHasFilterThread = val; }
	//״̬
	eFilterState	m_state;
	int				m_nSleepTime;
	//
	vector<CFilterPin *> m_lstPinIn;
	vector<CFilterPin *> m_lstPinOut;
	//
	string  m_strParam;
	// cmd line ������ ���ֺͺ��� ��Ӧ
	map<string, string> m_mapParamValue;
	//�����ƽʱ����

	//�ص�����
	FilterCB_Progress	m_cbProgress;
	void *m_pCbProgressUserData;
	void *m_pCbProgressReversed;
	FilterCB_Finished	m_cbFinished;

	void *m_pCbFinishedUserData;
	void *m_pCbFinishedReversed;
	FilterCB_Event		m_cbEvent;
	void *m_pCbEventUserData;
	void *m_pCbEventReversed;
};
#ifdef int64_t
#undef  int64_t
#endif

}
