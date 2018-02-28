
#include "StdAfx.h"
#include "QtGlRender.h"
#ifdef WIN32
#include <MMSystem.h>
#endif
#include "VideoFramePinBuffer.h"
#include "MediaSdkDef.h"
#include <stdio.h>


#ifdef QT_OPENGL
#include <QHBoxLayout>

#define  TIMER_PRECISION 10
#define STAT_FRAME 200
CQtGlRender::CQtGlRender(void)
:m_pGlWidget(0)
{
}

CQtGlRender::~CQtGlRender(void)
{
	QWidget *pParent = m_pGlWidget->parentWidget();
	if (pParent)
	{
		QHBoxLayout *pLayout = (QHBoxLayout*)pParent->layout();
		pLayout->removeWidget(m_pGlWidget);
		m_pGlWidget->hide();
		delete m_pGlWidget;
	}
}

int CQtGlRender::Open( HWND pParent, int nPlayBuffer/*=5*/ )
{
	if (m_pGlWidget)
		return 1;
	if (!pParent)
		return -1;
	
	m_pGlWidget = new CGlWindow((QWidget*)pParent);
	QLayout *pOldLayout = ((QWidget*)pParent)->layout();
	if (pOldLayout)
	{
		delete pOldLayout;
	}	
	QHBoxLayout *pLayout = new QHBoxLayout();
	pLayout->setContentsMargins(0, 0, 0 ,0);
	pLayout->addWidget(m_pGlWidget);
	m_pGlWidget->show();

	((QWidget*)pParent)->setLayout(pLayout);

	return CRender::Open(0, nPlayBuffer);
}

int CQtGlRender::DoFilter()
{
	
	CFilterPin *pPinIn = m_lstPinIn.at(0);
	if (!pPinIn)
		return -1;
	if (m_nTimePerFrame<=0)
	{
		m_nTimePerFrame = 1000.0/m_nFps;
	}
	//���� ��ǰʵ�� ��һ֡ʱ��
	int nFrameCount = 0;
	long nTimePerFrameNow = m_nTimePerFrame;
	nFrameCount = pPinIn->GetPreparedBufferConut();
	if (nFrameCount <= 0)
		return -2;
	int  nNicePlayBuffer = m_nPlayBuffer/2;
	//���� ��ǰʵ�� ��һ֡ʱ��, ����֡�Ķ��ٽ��е���

	int nFrameDiff = /*abs*/(nFrameCount - nNicePlayBuffer);// -nNicePlayBuffer ~  nNicePlayBuffer;
	// ̫�࣬ �ͼ��ٲ���һ֡��ʱ�䣬̫�� �� ���Ӳ���һ֡��ʱ��
	float fScale = 1.0;
	if (nFrameDiff <= nNicePlayBuffer/5)
	{//���Ӳ���ʱ��
		fScale =  (float)nNicePlayBuffer/(nFrameCount+nNicePlayBuffer/5);//1+(float)nFrameDiff/nNicePlayBuffer;
	}
	else if (nFrameDiff > nNicePlayBuffer/5)
	{//���ٲ���ʱ��
		fScale = (float)nNicePlayBuffer/(nFrameCount-nNicePlayBuffer/5)*0.8;
	}
	else
	{
	
	}
	nTimePerFrameNow = fScale*nTimePerFrameNow;
	//debug("stat. time per frame: %d, cal time per frame: %d, frame: %d:%d\n", m_nTimePerFrame, nTimePerFrameNow, nNicePlayBuffer, nFrameCount );

	// ���㵱ǰʱ���Ƿ���Բ���
	long nTimeNow = timeGetTime();
	long nTimeElapse = nTimeNow - m_nTimeLastFrame;

	if (nTimeElapse < nTimePerFrameNow-TIMER_PRECISION/2)
	{//ʱ�䲻��
		return -3;
	}


	//
	
	//ȡ һ�� pinIn �� papared ����
	CFilterPinBuffer *pBufferInPapared = 0;
	
	pPinIn->GetPreparedBuffer(&pBufferInPapared);
	//��Ⱦ������
	CVideoFramePinBufer *pVideoFrame = dynamic_cast<CVideoFramePinBufer*>(pBufferInPapared);
	bool bWndVisible = false;
	bWndVisible = m_pGlWidget->isVisible();
	if (bWndVisible 
		&& pVideoFrame 
		&& pVideoFrame->m_nHeight > 0 
		&& pVideoFrame->m_nWidth>0)
	{
		//ʱ�䵽�� ���Բ���
		//ͳ��֡ƽ��ʱ��
		m_nFrameCount++;
		if (m_nFrameCount>STAT_FRAME && m_nTimeStatBegin>0)
		{
			m_nTimePerFrame = (nTimeNow-m_nTimeStatBegin)/m_nFrameCount;
			if (m_nTimePerFrame > 500)
			{
				m_nTimePerFrame = 500;
			}
			m_nTimeStatBegin = nTimeNow;
			m_nFrameCount = 0;
		}
		m_nTimeLastFrame = nTimeNow;
        //debug("%s, render a frame, time elapse [%d]:need time[%d], nice buffers[%d], now[%d] \n", __FUNCTION__, nTimeElapse, nTimePerFrameNow, nNicePlayBuffer, nFrameCount);
		
		m_pGlWidget->SetPicture( pVideoFrame->m_pY, pVideoFrame->m_nWidth, pVideoFrame->m_nHeight);
	/*	if (!m_p3dItemImage)
		{
			m_p3dItemImage = new C3dItemImage(m_p3dGraphics, pVideoFrame->m_nWidth, pVideoFrame->m_nHeight );
			m_p3dItemImage->Create(0, 0, 0);
			m_p3dItemImage->SetSize(2, 2, 0.01);
			m_p3dGraphics->AddItem2Head(m_p3dItemImage);
		}
		if (m_p3dItemImage && m_p3dGraphics)
		{
			if (m_p3dItemImage->m_nTextureXPix != pVideoFrame->m_nWidth
				|| m_p3dItemImage->m_nTextureYPix != pVideoFrame->m_nHeight)
			{
				m_p3dGraphics->RemoveItem(m_p3dItemImage);
				delete m_p3dItemImage;
				m_p3dItemImage = new C3dItemImage(m_p3dGraphics, pVideoFrame->m_nWidth, pVideoFrame->m_nHeight );
				m_p3dItemImage->Create(0, 0, 0);                                                                                                                 
				m_p3dItemImage->SetSize(2, 2, 0.01);
				m_p3dGraphics->AddItem2Head(m_p3dItemImage);
			}
			m_p3dItemImage->SetImageData((char*)pVideoFrame->m_pY, pVideoFrame->m_nWidth, pVideoFrame->m_nHeight, ImgPF_YV420);
			//��ʾ ʱ��sod
			sAvDataEnd *pAvDataEnd = 0;
			CBuffer *pExtData = pVideoFrame->GetExtData();
			if ( pExtData)
			{
				pAvDataEnd = (sAvDataEnd *)pExtData->GetData();
				if (pAvDataEnd 
					&& pAvDataEnd->stOsdTime.wYear != 0
					&& pAvDataEnd->stOsdTime.wMonth != 0
					&& pAvDataEnd->stOsdTime.wDay != 0)
				{
					char szOsdTime[255];
					memset(szOsdTime, 0, sizeof(szOsdTime));
					sprintf(szOsdTime,"%d-%.2d-%.2d %.2d:%.2d:%.2d", pAvDataEnd->stOsdTime.wYear, pAvDataEnd->stOsdTime.wMonth, pAvDataEnd->stOsdTime.wDay,
						 pAvDataEnd->stOsdTime.wHour, pAvDataEnd->stOsdTime.wMinute, pAvDataEnd->stOsdTime.wSecond);
					//debug("time osd: %s\n", szOsdTime);
					//Ϊʲô �ڴ�й¶��
					if (m_p3dItemTextTimeOsd)
						m_p3dItemTextTimeOsd->SetText(szOsdTime);
				}
			}
			//
			m_p3dGraphics->Refresh();
		}*/
	}	
	else{
		//������ ֱ�ӷŻ� ����Ҫ����

		//
	}
	//�Ż� �� pin in �� free ���ݶ���
	pPinIn->PutFreeBuffer(pBufferInPapared);

	return 0;
}


#endif
