#pragma once
#include "render.h"
#include "BufferPool.h"


/*#include "Thread.h"*/

// 2 ѡһ
//#define GRAPH_DDRAW
//#define GRAPH_D3D

//#include "VideoSummary.h"
/*#include "VideoSummaryFrame.h"*/
/*#include "VideoSummaryFile.h"*/

#ifdef GRAPH_DDRAW
#include "DirectDrawer.h"
#endif

//�Զ��߳� ƽ��������, ms
#define TIMER_PRECISION 10
//10�� ͳ��һ��
#define STAT_FRAME       (5*25)
//
namespace SimpleCpp{
	class CThread;
	class CMutex;
};
/*class SThread::CThread;*/
using namespace SimpleCpp;
class C3dGraphics;
class C3dItemImage;
class C3dItemText2d;
class CVideoFramePinBufer;

template <class T>
class CBufferPool;

class CFileBuffer;


class MEDIASDK_API CSmartRender :
	public CRender
{

	friend static int __stdcall  RenderProc(void *pParam);
public:
	CSmartRender(void);
	virtual ~CSmartRender(void);

	
	virtual int Open(HWND hWnd, int nPlayBuffer);
	virtual int Open(char *pParam, bool bHasThread=false);
	//filter��ִ�� ���� 
	virtual int DoFilter();

	virtual int Stop();

	virtual int SetPlaySpeed(float fSpeed);
	virtual int SetOsdText(int nIndex, char *pText);
	virtual int SetOsdPos(int nIndex, int nX, int nY);
	virtual int SetOsdFont(int nIndex, char *pSzName, int nSize, long lColor);
	virtual int SetOsdShow(int nIndex, bool bShowOrHide);
	virtual int SnapShot(char *pSaveFile);
	virtual int SnapShot(unsigned char *pBuffer, int &nW, int &nH);
	virtual int SnapShotVideoPicture(unsigned char *pBuffer, int &nW, int &nH);
	virtual int SnapShotVideoPicture(char *pSaveFile);

	virtual int Refresh();
	virtual int PlayNextFrame();
	virtual int PlayPrevFrame(int64 s64PtsNow=0);
	virtual int Pause();
	virtual int Resume();
	virtual int Flush();
	virtual int GetVideoWidth();
	virtual int GetVideoHeight();
	
	//����ͼƬ�û�����ģ�rgba ��ʽ
	int SetImage(int nLevel, uint8 *pImage, int nW, int nH, float fPosX, float fPosY, float fSizeX, float fSizeY);
	int AppendImage(uint8 *pImage, int nW, int nH, float fPosX, float fPosY, float fSizeX, float fSizeY);
	C3dItemImage *GetImage(int nIndex);
	int GetImageCount();
	void SetImageVisible(bool bVisible);
	//
protected:
	virtual CMediaFilter *CreateObject();
	static int __stdcall  RenderProc(void *pParam);
	int RenderProc();
	//���ϻ�ȡ�������Ƶ�������� play prev��ʱ��
	void TryGetVideoFrame();


	CThread *m_pThreadRender;
	CMutex  *m_pMutex3DGraphics;


	C3dGraphics *m_p3dGraphics;
	C3dItemImage *m_p3dItemImage;
	C3dItemImage *m_p3dItemLogo;

	vector<C3dItemImage *> m_lstUserImage;
#ifdef GRAPH_DDRAW
	CDirectDrawer *m_pDDraw;
#endif
	//video
	int m_nVideoWidth;
	int m_nVideoHeight;
	int	  m_nDropFrames;
	// OSD 
	vector<C3dItemText2d* > m_lst3dItemText2d;
	//��������ʱ��
	//��һ֡���ŵ�ʱ���, ms
	long m_nTimeLastFrame;
	//ƽ��ÿ֡��Ҫ��ʱ��, ms
	long m_nTimePerFrame;
	//ʱ��ͳ��
	long m_nTimeStatBegin;
	long m_nFrameCount;
	//���� ��֡���� �����ݻ���ӿڣ�
	//vector<CFilterPinBuffer *> m_lstPlayPrevBufferBusy;
	//vector<CFilterPinBuffer *> m_lstPlayPrevBufferFree;
	CFilterPin  *m_pFilterPinPlayPrevFrame;

	/*summary����
	*/
	
	CVideoFramePinBufer *m_pLastVideoFrame;
	 
	//���� ��Ƶ֡��һ�����ڵ���
	CBufferPool<CFileBuffer>  m_bpVideoFrames;
	CMutex *m_pMutexBufferPool;
	//���浱ǰ��֡��ʱ�����
	
};
//extern CSmartRender g_smartRender;