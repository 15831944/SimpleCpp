#pragma once

#include <vector>
#include <map>
#include "MediaSdkDef.h"
//#include "MediaFilter.h"
#include "FfmpegFormat.h"
#include "BasePipeLine.h"
#include "BaseFilter.h"
//#include "BaseStream.h"
/*
#ifdef WIN32
#ifdef VIVSPLAYSDK_EXPORTS
#define VIVSPLAYSDK_API __declspec(dllexport)
#else
#define VIVSPLAYSDK_API __declspec(dllimport)
#endif
#else
#define VIVSPLAYSDK_API
#endif

#define VIVSPLAYSDK_API  
*/

using namespace std;
using namespace SimpleCpp;

// eFS_Run = 0,
// eFS_ToStop,
// eFS_Stop,
// eFS_Pause,
typedef	enum _eStreamState{
	eSS_Run = 0,
	eSS_ToStop = 1,
	eSS_Stop ,
	eSS_Pause,
}eStreamState;

typedef	enum _eStreamControlState{
	eSPM_None = 0,
	eSPM_Play ,
	eSPM_PlayNextFrame,
	eSPM_PlayPrevFrame,
}eStreamPlayMode;

typedef enum _eStreamDataMode{
	eSDM_Push = 0,
	eSDM_Pull,
}eStreamDataMode;

typedef enum _sStreamSeekFlag{
	eSSF_IFrame = 0,
	eSSF_Any = AVSEEK_FLAG_ANY,
	eSSF_Backward = AVSEEK_FLAG_BACKWARD,
	eSSF_UntilDecode = 8,
	eSSF_UntilDisplay = 16,
}sStreamSeekFlag;

class CMediaFilter;
class CSourceFilter;
namespace SimpleCpp{
class CThread;
class CMutex;
}
 
using namespace SimpleCpp;
class MEDIASDK_API CMediaStream
	:public CBasePipeLine
{
public:
	CMediaStream(void);
	virtual ~CMediaStream(void);
	
	//void TestStdAllocator(vector<int> &lstValue ) ;
// 	virtual int Start();
// 	virtual int Stop();
// 	virtual int Pause();
	virtual int Resume();
	//�ƶ���һ��λ�ã����ǲ��ȴ�����
	virtual int Seek(int64 s63Time, int nFlag=AVSEEK_FLAG_ANY);
	virtual int SeekToTimestamp(int64 s63Timestamp, int nFlag=AVSEEK_FLAG_ANY);
	virtual int PlayNextFrame();
	virtual int PlayPrevFrame();
	virtual int SetParam(char *pName, char *pValue);
	virtual int GetParam(char *pSzName, char *pSzValue);

	//��������
	virtual int Control(char *pSzName, char *pSzValue);
	
	virtual int SetPlaySpeed(float fSpeed);
	virtual float GetPlaySpeed();
	bool IsPaused();
	bool IsStoped();
	bool IsStreamEnd();

	//���� ͼ����Ҫ��ʾ�����򣬽� �趨��������ʾ�����������С����������š�
	virtual int SetShowRect(int nX, int nY, int nW, int nH);
	//�ڴ�����Ҫˢ�µ�ʱ����øýӿ�
	virtual int Refresh();
	//
	virtual int Snapshot(char *pSzSaveFile);
	//����ָ��ʱ���һ�Ž�ͼ���ýӿڻᵼ����Ƶ���ŵ�λ���ƶ�
	//
	virtual int Snapshot(char *pSzSaveFile, int64 s64Time);
	virtual int Snapshot(char *pImage, int &nLen, int &nW, int &nH, int64 s64Time);
	//�ýӿ�ֻ�Ƕ� �ڴ� ��������ģʽ��Ч�����ļ� ���ڲ��Զ�ģʽ��Ч
	virtual int FillData(char *pData, int nLen);
	CMediaFilter *FindFilterByKind(char *szKind);

	//virtual int AppendFilter(CMediaFilter *pFilter);
	int SetProgressCb(FilterCB_Progress cbProgress, void *pUserData, void *pReversed);
	int SetFinishedCb(FilterCB_Finished cbFinished, void *pUserData, void *pReversed);
	int SetEventCb(FilterCB_Event cbEvent, void *pUserData, void *pReversed);
	CSourceFilter *GetSourceFilter();
protected:
	CMediaFilter *FindFilterByKindPriv(char *szKind);
	//��ǰ����һ֡�� ����
	int PlayNextFramePriv();
	int SetPlayStatePriv(int nState);
	int SetPlayModePriv(int nMode);
	//�������ӵ� filter
	//vector<CMediaFilter *> m_lstFilter;
	//
	
	CThread         *m_pThrStream;
	static int __stdcall ThrStreamProc(void *pParam);
	virtual int ThrStreamProc();
	//eStreamState m_state;
	//
	bool m_bIsStreamEnd;
	//��֡���ŵȿ���
	eStreamPlayMode m_playMode;
	int m_nIndexInGop; //��һ�� I֡ ֮���  ��š� ���ڿ��Ƶ�֡����֮�� �������� 
	//
	float m_fSpeed;
	//����ģʽ �ơ���
	eStreamDataMode m_dataMode;
	//
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
//
class CPlayLiveStream{

};
class CPlayFileStream{

};
class CTransFileStream{

};
class CWriteFileStream{

};


