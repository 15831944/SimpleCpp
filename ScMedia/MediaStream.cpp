#include "StdAfx.h"
#include "MediaStream.h"
#include "MediaFilter.h"
#include "Thread.h"
#include "Mutex.h"
#include "Render.h"
#include "SourceFilter.h"
#include "Decoder.h"
#include "SourceFilter.h"
#include <MMSystem.h>

CMediaStream::CMediaStream(void)
:m_pThrStream(NULL)
//, m_pMutexFilters(NULL)
, m_dataMode(eSDM_Push)
, m_cbEvent(NULL)
, m_pCbEventUserData(0)
, m_pCbEventReversed(0)
, m_cbFinished(NULL)
, m_pCbFinishedUserData(0)
, m_pCbFinishedReversed(0)
, m_cbProgress(NULL)
, m_pCbProgressReversed(0)
, m_pCbProgressUserData(0)
, m_playMode(eSPM_None)
, m_fSpeed(1.0)
, m_bIsStreamEnd(false)
{

	//m_pMutexFilters = new CMutex();
}

CMediaStream::~CMediaStream(void)
{

	if (m_pMutexFilters)
	{
		delete m_pMutexFilters;
		m_pMutexFilters = NULL;
	}
	if (m_pThrStream)
	{
		delete m_pThrStream;
		m_pThrStream = NULL;
	}
	for (int i=0; i<m_lstFilter.size() /*&& m_state != eSS_Stop*/; i++)
	{
		CMediaFilter *pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (pFilter)
		{
			pFilter->Release();
			m_lstFilter.at(i) = NULL;
		}

		//delete*m_lstFilter.at(i);
	}
	m_lstFilter.clear();
}
CSourceFilter *CMediaStream::GetSourceFilter()
{
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop && m_state != eSS_ToStop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		//push mode �ҵ� source, ����� pull mode ��Ҫ�ҵ� accepter
		if (!pFilter->IsKind(FILTER_KIND_SOURCE))
			continue;
		return  dynamic_cast<CSourceFilter*>(pFilter);
	}
	return NULL;
}
int CMediaStream::ThrStreamProc( void *pParam )
{
	CMediaStream *pStream = NULL;
	pStream = (CMediaStream *)pParam;
	if (pStream)
	{
		pStream->ThrStreamProc();
	}
	return 0;
}
int CMediaStream::ThrStreamProc()
{
// 	while (m_state != eSS_Stop
// 		 && m_state != eSS_ToStop)
// 	{
// 		if (m_state == eSS_Pause)
// 		{
// 			Sleep(20);
// 			continue;;
// 		}
// 		int nSleepTime = 0;
// 		int nExtLoopTime = 1;
// 		CSourceFilter *pSource  = 0;
// 
// 		float fSpeed = 1.0;
// 		pSource = GetSourceFilter();
// 		if (pSource)
// 		{
// 			nSleepTime = pSource->GetPumperSleepTime();
// 			fSpeed = pSource->GetPlaySpeed();
// 			m_bIsStreamEnd = pSource->IsStreamEnd();
// 		}
// 		if (nSleepTime < 4)
// 		{
// 			if (fSpeed > 12 )
// 			{
// 				nExtLoopTime=4;
// 			}
// 			else if (fSpeed > 6)
// 			{
// 				nExtLoopTime=2;
// 			}
// 		}
// 		
// 		 
// 		m_pMutexFilters->Lock();
// 		while (nExtLoopTime--)
// 		{//����cpuʹ��
// 			CMediaFilter *pFilter = NULL;
// 			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop && m_state != eSS_ToStop; i++)
// 			{
// 				pFilter = m_lstFilter.at(i);
// 				if (!pFilter)
// 					continue;
// 				//push mode �ҵ� source, ����� pull mode ��Ҫ�ҵ� accepter
// 				//if (!pFilter->IsKind(FILTER_KIND_SOURCE))
// 				//	continue;
// 				pFilter->DoFilter();
// 				CSourceFilter *pSource = dynamic_cast<CSourceFilter*>(pFilter);
// 				if (pSource)
// 				{
// 					nSleepTime = pSource->GetPumperSleepTime();
// 				}
// 			}
// 		}
// 		m_pMutexFilters->Unlock();
// 		//sleep(0) ���ǿ��Ի�ȡ�ǳ����cpu�ġ� sleep(1)���Ի�ȡ 1% 
// 		Sleep(nSleepTime);
// 	}
// 	m_state = eSS_Stop;

	return 0;
 }
// int CMediaStream::Start()
// {
// 	CBasePipeLine::Start();
// 
// 	if (m_pThrStream)
// 	{
// 		return -1;
// 	}
// // 	m_pThrStream = new CThread();
// // 	m_state = eSS_Pause;
// // 	m_playMode = eSPM_None;
// //  	m_pThrStream->Create(ThrStreamProc, this);
// // 	m_pThrStream->SetPriority(eThreadPriority_Normal);
// //  	m_state = eSS_Run;
// 	//m_pMutexFilters->Lock();
// 	CMediaFilter *pFilter = NULL;
// 	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
// 	{
// 		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
// 		if (!pFilter)
// 			continue;
// 
// 		pFilter->Start();
// 	}
// 	//m_pMutexFilters->Unlock();
// 
// 	return 0;
// }
// int CMediaStream::Stop()
// {
// 	CBasePipeLine::Stop();
// // 	if (!m_pThrStream)
// // 	{
// // 		return -1;
// // 	}
// // 	m_state = eSS_ToStop;
// // 	
// // 	int nTries = 0;
// // 	debug("%s, stop ++ \n", __FUNCTION__);
// // 	while (m_state != eSS_Stop
// // 		/*&& nTries--*/)
// // 	{
// // 		nTries++;
// // 		Sleep(10);
// // 	}
// // 	if (m_state == eSS_Stop)
// // 	{
// // 		debug("%s, stop success, tries : %d times\n", __FUNCTION__, nTries);
// // 	}
// // 	else
// // 	{
// // 		debug("%s, stop in unusually way\n", __FUNCTION__);
// // 	}
// // 	m_pThrStream->Stop();
// // 
// // 	delete m_pThrStream;
// // 	m_pThrStream = NULL;
// // 	for (int i=0; i<m_lstFilter.size(); i++)
// // 	{
// // 		m_lstFilter.at(i)->Stop();
// // 	}
// // 	debug("%s, --\n", __FUNCTION__);
// 	return 0;
// }
// int CMediaStream::Pause()
// {
// // 	m_state = eSS_Pause;
// // 	m_playMode = eSPM_None;
// // 	m_pMutexFilters->Lock();
// // 	CMediaFilter *pFilter = NULL;
// // 	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
// // 	{
// // 		pFilter = m_lstFilter.at(i);
// // 		if (!pFilter)
// // 			continue;
// // 		
// // 		pFilter->Pause();
// // 	}
// // 	m_pMutexFilters->Unlock();
// 	return 0;
// }
int CMediaStream::Resume()
{
	if (m_playMode == eSPM_PlayPrevFrame)
	{//��Ҫ���� seek ��λ����ǰ ���ŵ�pts
		int64 s64RenderPts = -1;
		CMediaFilter *pFilter = 0;
		CRender *pRender = 0;
		pFilter = FindFilterByKind(FILTER_KIND_RENDER);
		if (pFilter)
		{
			pRender = dynamic_cast<CRender*>(pFilter);
		}
		if (pRender)
		{
			s64RenderPts = pRender->GetPts();
		}
		if (s64RenderPts >= 0)
		{
			SeekToTimestamp(s64RenderPts, eSSF_UntilDecode|eSSF_Backward);
		}

	}
//	m_state = eSS_Run;
	m_playMode = eSPM_Play;
	m_pMutexFilters->Lock();
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		
		pFilter->SetPlayMode(eFPM_Play);
		pFilter->Resume();
	}
	m_pMutexFilters->Unlock();
	return 0;
}
int CMediaStream::Seek(int64 s64TimeToSeek, int nFlag/*=0*/)
{
	debug("%s: time: %lld", __FUNCTION__, s64TimeToSeek)
	m_bIsStreamEnd = false;
	
	int nPlayStateOld = m_state;
	int nPlayModeOld = m_playMode;
	//���ţ�ֱ�� ���������뵽 ��ʱ��λ��
	CDecoder *pDecoder = dynamic_cast<CDecoder*>(FindFilterByKind(FILTER_KIND_DECODER));
// 	if (!pDecoder)
// 		return -1;
	CSourceFilter *pSource = dynamic_cast<CSourceFilter*>(FindFilterByKind(FILTER_KIND_SOURCE));
// 	if (!pSource)
// 		return -2;
	CRender *pRender = dynamic_cast<CRender*>(FindFilterByKind(FILTER_KIND_RENDER));
// 	if (!pRender)
// 		return -3;
// 	int64 s64Timestamp = 0;
// 	s64Timestamp = pSource->TimeToTimestamp(s64Time);
// 	
// 	int nRet = 0;
// 	nRet = SeekToTimestamp(s64Timestamp, nFlag);
// 
// 	return nRet;


	int64 s64OldPlayTime = 0;
	if (pDecoder && pSource)
	{
		s64OldPlayTime =   pRender->GetPts();
		s64OldPlayTime = pSource->TimestampToTime(s64OldPlayTime);
	}
	Pause();
	m_pMutexFilters->Lock();
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		
		pFilter->Seek(s64TimeToSeek, nFlag);
	}
	//m_pMutexFilters->Unlock();
	float fSpeedOld = m_fSpeed;
	if (nFlag & eSSF_UntilDecode
		&& pSource && pDecoder)
	{//�ȴ�����
		//Resume();

		int64 s64RenderTime = 0;
		int64 s64RenderTimestamp=0;


		bool bRenderVisible = pRender->IsVisible();
		pRender->SetVisible(false);
		//SetPlaySpeed(32);

		bool bSeekOk =false;
		int nTries = 300;
		int nTotal = nTries;
		//Sleep(10);
		long lTimeBegin = timeGetTime();
		long lTimeNow = timeGetTime();
		long lTimeOut = 3*1000;
		do{
			s64RenderTimestamp = pRender->GetPts();
			s64RenderTime = pSource->TimestampToTime(s64RenderTimestamp);
			debug("%s: tries: %d , decode time %I64d, need seek time: %I64d\n", __FUNCTION__, nTries, s64RenderTime, s64TimeToSeek);
			
			//����������ұ� ��Ҫseek�����
			if (s64OldPlayTime > s64TimeToSeek)
			{//�Ѿ����ŵ�����ȥ�ģ���Ҫ��ͼ��ʱ���� ���ŵ�ʱ������
				if (s64OldPlayTime >0 && s64RenderTime >= s64OldPlayTime)
				{//�����ʱ�仹û���˻�ȥ
					debug("%s, decode time is newer than old play time, decode[%I64d]:old[%I64d], seek data is not arrive \n", 
						__FUNCTION__,
						s64RenderTime, s64OldPlayTime);
					PlayNextFramePriv();
					continue;
				}
				else
				{
					//Pause();
					//break;
				}
			}
			else
			{//��ǰ���󲥷ŵģ���Ҫ��ͼ�� ʱ��Ȳ���ʱ��� Զ �ұ�
				//Pause();
				//break;
			}
			if (s64RenderTime >= s64TimeToSeek)
			{//�Ѿ����ŵ���Ҫ��λ��
				pRender->SetVisible(bRenderVisible);
				PlayNextFramePriv();
				break;
			}

			lTimeNow = timeGetTime();
			PlayNextFramePriv();
		}while ( nTries-- > 0 
			&& (lTimeNow-lTimeBegin)<lTimeOut );

		if (nTries <= 0)
		{ 
			debug("%s, try seek I frame and decode to pos timeout..., try to seek any pos \n", __FUNCTION__);
			//Seek(s64Time, AVSEEK_FLAG_ANY);
			//m_pMutexFilters->Lock();
			CMediaFilter *pFilter = NULL;
			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
			{
				pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
				if (!pFilter)
					continue;

				pFilter->Seek(s64TimeToSeek, AVSEEK_FLAG_ANY);
			}
			//m_pMutexFilters->Unlock();
			pRender->SetVisible(bRenderVisible);
			PlayNextFramePriv();
			pRender->Refresh();
			bSeekOk = true;
		}
		else
		{
			debug("%s, try [%d]times, time[%lld]:[%lld], seek I frame and decode to pos success\n", __FUNCTION__, nTotal-nTries, 
				s64RenderTime, s64TimeToSeek);
			bSeekOk = true;
		}

		//SetPlaySpeed(fSpeedOld);
		//Resume();
		//Sleep(100);
		pRender->SetVisible(bRenderVisible);
		pRender->Refresh();
	}
	else
	{//���þ�ȷ��λ
		PlayNextFramePriv();
		PlayNextFramePriv();
		pRender->Refresh();
	}
	//m_pMutexFilters->Lock();
	SetPlayModePriv(nPlayModeOld);
	SetPlayStatePriv(nPlayStateOld);
	m_pMutexFilters->Unlock();

	return 0;
}
int CMediaStream::SeekToTimestamp(int64 s63Timestamp, int nFlag/*=0*/)
{
	m_bIsStreamEnd = false;

	
	//���ţ�ֱ�� ���������뵽 ��ʱ��λ��
	CDecoder *pDecoder = dynamic_cast<CDecoder*>(FindFilterByKind(FILTER_KIND_DECODER));
	// 	if (!pDecoder)
	// 		return -1;
	CSourceFilter *pSource = dynamic_cast<CSourceFilter*>(FindFilterByKind(FILTER_KIND_SOURCE));
	// 	if (!pSource)
	// 		return -2;
	CRender *pRender = dynamic_cast<CRender*>(FindFilterByKind(FILTER_KIND_RENDER));
	// 	if (!pRender)
	// 		return -3;
	int nPlayStateOld = 0;
	nPlayStateOld = m_state;
	Pause();
	m_pMutexFilters->Lock();

	int64 s64OldPlayTime = 0;
	int64 s64OldPlayTimestamp = 0;
	if (pDecoder && pSource)
	{
		s64OldPlayTimestamp =  pRender->GetPts();;// pDecoder->GetTimestamp();
		s64OldPlayTime = pSource->TimestampToTime(s64OldPlayTimestamp);
	}
	int64 s64TimeNeedToBe = 0;
	s64TimeNeedToBe = pSource->TimestampToTime(s63Timestamp);
	debug("%s: pts: %I64d, time: %I64d\n", __FUNCTION__, s63Timestamp, s64TimeNeedToBe);
	debug("%s, old pts: %I64d, time; %I64d\n", __FUNCTION__, s64OldPlayTimestamp, s64OldPlayTime);

	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;

		//pFilter->Seek(s64TimeNeedToBe, nFlag);
		pFilter->SeekToTimestamp(s63Timestamp, nFlag);
	}
	
	//m_pMutexFilters->Unlock();

	bool bSeekOk =false;

	float fSpeedOld = m_fSpeed;
	if (nFlag & eSSF_UntilDecode
		&& pSource && pDecoder)
	{//�ȴ�����
		//Resume();

		int64 s64RenderTime = 0;
		int64 s64RenderTimestamp=0;

		bool bRenderVisible = pRender->IsVisible();
		pRender->SetVisible(false);
		//SetPlaySpeed(32);

		int nTries = 300;
		int nTotal = nTries;
		//Sleep(10);
		//Pause();
		long lTimeBegin = timeGetTime();
		long lTimeNow = timeGetTime();
		long lTimeOut = 3*1000;
		do{
			//s64DecodeTimestamp = pDecoder->GetTimestamp();
			s64RenderTimestamp = pRender->GetPts();
			s64RenderTime = pSource->TimestampToTime(s64RenderTimestamp);
			//debug("%s: decode time %d, need seek time: %d\n", __FUNCTION__, (int)s64DecodeTime, (int)s64TimeNeedToBe);


			//�ж���ǰ���ŵ�ʱ���ǲ��Ǳ���Ҫ��ʱ�� ����
			if (s64OldPlayTime > s64TimeNeedToBe)
			{//�Ѿ����ŵ�����ȥ�ģ���Ҫ��ͼ��ʱ���� ���ŵ�ʱ������
				if (s64OldPlayTime >0 && s64RenderTime >= s64OldPlayTime)
				{//�����ʱ�仹û���˻�ȥ
					//debug("%s, decode time is newer than old play time[%I64d]:[%I64d], seek data is not arrive \n", 
					//	__FUNCTION__,
					//	s64DecodeTime, s64OldPlayTime);
					PlayNextFramePriv();
					continue;
				}
				else
				{//���뵽��Ҫ��ʱ�����
					//Pause();
					//break;
				}
			}
			else
			{//��ǰ���󲥷ŵģ���Ҫ��ͼ�� ʱ��Ȳ���ʱ��� Զ �ұ�
				//���뵽��Ҫ��ʱ�����
				//Pause();
				
			}
			if (s64RenderTime >= s64TimeNeedToBe)
			{
				debug("%s success\n", __FUNCTION__);
				pRender->SetVisible(bRenderVisible);
				PlayNextFramePriv();
				break;
			}

			lTimeNow = timeGetTime();
			/*Sleep(10);*/
			PlayNextFramePriv();

		}while ( nTries-- > 0 
			&& (lTimeNow-lTimeBegin)<lTimeOut );

		if (nTries <= 0)
		{ 
			debug("%s, try seek I frame and decode to pos timeout..., try to seek any pos \n", __FUNCTION__);
			//Seek(s64TimeNeedToBe, AVSEEK_FLAG_ANY);
			//m_pMutexFilters->Lock();
			CMediaFilter *pFilter = NULL;
			nFlag =  eSSF_Any;
			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
			{
				pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
				if (!pFilter)
					continue;
				pFilter->SeekToTimestamp(s63Timestamp, nFlag);
			}

			//m_pMutexFilters->Unlock();
			pRender->SetVisible(bRenderVisible);
			PlayNextFramePriv();

			bSeekOk = false;
		}
		else
		{
			debug("%s, try [%d]times, seek I frame and decode to pos success\n", __FUNCTION__, nTotal-nTries);
			bSeekOk = true;
		}

		//SetPlaySpeed(fSpeedOld);
		//Resume();
		//Sleep(100);
		pRender->SetVisible(bRenderVisible);
		pRender->Refresh();

	}
	else
	{
		PlayNextFramePriv();
		PlayNextFramePriv();
		pRender->Refresh();
	}
	//m_pMutexFilters->Lock();
	SetPlayStatePriv(nPlayStateOld);
	m_pMutexFilters->Unlock();
	
	int nRet = 0;
	if (bSeekOk)
	{
		nRet = 0;
	}
	else
	{
		nRet = -1;
	}
	int64 s64RenderPts = 0;
	s64RenderPts = pRender->GetPts();
	debug("%s --: render pts %I64d\n", __FUNCTION__, s64RenderPts);

	return nRet;
}
int CMediaStream::PlayNextFrame()
{//���ϲ��� next frame ֱ�� ���е� filter ��������ȷ��ֵ��
	debug("%s ++\n", __FUNCTION__);

	//����Ƿ��� ��֡
	if (m_playMode == eSPM_PlayPrevFrame)
	{//��Ҫ���� seek ��λ����ǰ ���ŵ�pts
		int64 s64RenderPts = -1;
		CMediaFilter *pFilter = 0;
		CRender *pRender = 0;
		pFilter = FindFilterByKind(FILTER_KIND_RENDER);
		if (pFilter)
		{
			pRender = dynamic_cast<CRender*>(pFilter);
		}
		if (pRender)
		{
			s64RenderPts = pRender->GetPts();
		}
		if (s64RenderPts >= 0)
		{
			SeekToTimestamp(s64RenderPts, eSSF_UntilDecode|eSSF_Backward);
		}
		
		debug("%s, old play is playPrevFrame, need to seek: %I64d \n", __FUNCTION__, s64RenderPts);

	}
		
	//m_state = eSS_Pause;
	m_playMode = eSPM_PlayNextFrame;
	m_pMutexFilters->Lock();

	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		pFilter->SetPlayMode(eFPM_PlayNextFrame);
		pFilter->Pause();
	}
 

	int nRet = 0;
	bool bRenderNextFrameSuccess = false;
	int nTries = 100;
	int nTried = 0;
	do 
	{
		bool bHaveRender = false;
		for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
		{
			pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
			if (!pFilter)
				continue;
			if (pFilter->IsKind(FILTER_KIND_RENDER))
			{
				bHaveRender = true;
				nRet = pFilter->PlayNextFrame();
				if (nRet >= 0)
				{
					debug("%s, play next frame success \n", __FUNCTION__);
					bRenderNextFrameSuccess = true;
					break;
				}
				else
				{
					debug("%s, play next frame false need decode more \n", __FUNCTION__);
				}
			}
		}
		if (!bHaveRender)
		{//�ӽ����� ��ȡ �Ƿ�ɹ�

		}
		if (!bRenderNextFrameSuccess)
		{//����û�ɹ��� ����û�����ˣ���Ҫ���ε� fliter������
			debug("%s, no frame, need decode more ..\n", __FUNCTION__);
			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
			{
				pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
				if (!pFilter)
					continue;
				if (pFilter->IsKind(FILTER_KIND_SOURCE))
				{//ִ��һ�����ݿ�����
					pFilter->PlayNextFrame();
				}
			}
		}
		nTried++;
		debug("%s, tries: %d\n", __FUNCTION__, nTried);
	} while (!bRenderNextFrameSuccess 
		&& nTries--
		&& !IsStreamEnd());
	m_pMutexFilters->Unlock();
 
	if (bRenderNextFrameSuccess)
	{
		nRet = 0;
	}
	else
	{
		nRet = -1;
	}
	debug("%s -- %d\n", __FUNCTION__, nRet);
	return nRet;
}
int CMediaStream::PlayPrevFrame()
{
	debug("%s ++\n", __FUNCTION__);
	//���ϲ��� next frame ֱ�� ���е� filter ��������ȷ��ֵ��
	//m_state = eSS_Pause;
	m_playMode = eSPM_PlayPrevFrame;

	m_pMutexFilters->Lock();
	CMediaFilter *pFilter = NULL;
	int nRet = 0;
	bool bRenderPrevFrameSuccess = false;
	int nTries = 300;
	int nTried = 0;
	//������� ����
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
	
		 //pFilter->Flush();
		 pFilter->Pause();
		 pFilter->SetPlayMode(eFPM_PlayPrevFrame);
	}

	do 
	{
		int64 s64Pts = 0;
		for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
		{
			pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
			if (!pFilter)
				continue;
			
			if (pFilter->IsKind(FILTER_KIND_RENDER))
			{
				nRet = pFilter->PlayPrevFrame();
				if (nRet >= 0)
				{
					debug("%s, play prev frame success \n", __FUNCTION__);
					bRenderPrevFrameSuccess = true;
					m_nIndexInGop--;
					break;
				}
				else
				{
					debug("%s, play prev frame false ,need decode more \n", __FUNCTION__);
				}
				CRender *pRender = dynamic_cast<CRender*>(pFilter);
				if (pRender)
					s64Pts = pRender->GetPts();
			}
			else
			{//��Ҫ����һ�¶��������������
				//pFilter->PlayPrevFrame();
			}
		}
		if (!bRenderPrevFrameSuccess)
		{//����û�ɹ��� ����û�����ˣ���Ҫ���ε� fliter������
			//���ý��������Ա��ͷ����һ֡ �����ظ����������
			CMediaFilter *pDecoder = FindFilterByKindPriv(FILTER_KIND_DECODER);
			if (pDecoder)
			{
				pDecoder->Reset();
			}
			//
			int nRetSourcePlay = 0;
			debug("%s, no frame, need decode more, pts: %I64d ..\n", __FUNCTION__, s64Pts);
			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
			{
				pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
				if (!pFilter)
					continue;
				if (pFilter->IsKind(FILTER_KIND_SOURCE))
				{//ִ��һ�����ݿ�����,��s64PtsΪ�̶ȵ�ǰһ֡
					
					nRetSourcePlay = pFilter->PlayPrevFrame(s64Pts);
					
				}
			}
			if (nRetSourcePlay < 0)
			{
				//Դ����ʧ�� �����ѵ��
				nRet = -1;
				goto ret;
			}
		}
		nTried++;
		debug("%s, tries: %d\n", __FUNCTION__, nTried);
	} while (!bRenderPrevFrameSuccess
		&& nTries--
		&& !IsStreamEnd());
	
	if (bRenderPrevFrameSuccess == false)
	{//��󲥷�ʧ��
		nRet = -1;
	}
	else
		nRet = 0;

ret:
	m_pMutexFilters->Unlock();

	return nRet;
}

int CMediaStream::SetPlaySpeed(float fSpeed)
{
	m_pMutexFilters->Lock();
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;

		pFilter->SetPlaySpeed(fSpeed);
	}
	m_pMutexFilters->Unlock();
	
	m_fSpeed = fSpeed;

	return 0;
}
float CMediaStream::GetPlaySpeed()
{
	
	return m_fSpeed;
}
bool CMediaStream::IsPaused()
{
	return (m_state == eSS_Pause)? true:false;
}
bool CMediaStream::IsStoped()
{
	return (m_state == eSS_Stop)? true:false;
}
bool CMediaStream::IsStreamEnd()
{

	return m_bIsStreamEnd;
}
//���� ͼ����Ҫ��ʾ�����򣬽� �趨��������ʾ�����������С����������š�
int CMediaStream::SetShowRect(int nX, int nY, int nW, int nH)
{
	return 0;
}
//ֻ�� ��  BufferSource ��Ч
int CMediaStream::FillData(char *pData, int nLen)
{

	return 0;
}
int CMediaStream::Refresh()
{
	if (!m_pMutexFilters)
		return -1;
	//����� Ч�ʱȽϵͣ� Ϊɶ�� 
	m_pMutexFilters->Lock();
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		//push mode �ҵ� source, ����� pull mode ��Ҫ�ҵ� accepter
		if (!pFilter->IsKind(FILTER_KIND_RENDER))
			continue;
		CRender *pRender = (CRender *)pFilter;
		pRender->Refresh();
	}
	m_pMutexFilters->Unlock();
	return 0;
}
// int CMediaStream::AppendFilter(CMediaFilter *pFilter)
// {
// 	if (!m_pMutexFilters)
// 		return -1;
// 	m_pMutexFilters->Lock();
// 	m_lstFilter.push_back(pFilter);
// 
// 	//pFilter->SetEventCb(m_cbEvent, m_pCbEventUserData, m_pCbEventReversed);
// 	//pFilter->SetProgressCb(m_cbProgress, m_pCbProgressUserData, m_pCbProgressReversed);
// 	//pFilter->SetFinishedCb(m_cbFinished, m_pCbFinishedUserData, m_pCbFinishedReversed);
// 
// 	m_pMutexFilters->Unlock();
// 
// 	return 0;
// }
int CMediaStream::SetProgressCb(FilterCB_Progress cbProgress, void *pUserData, void *pReversed)
{
	return  0;
	int nRet = 0;
// 	m_pMutexFilters->Lock();
// 
// 	m_cbProgress =	cbProgress;
// 	m_pCbProgressUserData = pUserData;
// 	m_pCbProgressReversed = pReversed;
// 	for (int i=0; i<m_lstFilter.size(); i++)
// 	{
// 		CMediaFilter *pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
// 		if (pFilter->IsKind("source"))
// 			m_lstFilter.at(i)->SetProgressCb(cbProgress, pUserData, pReversed);
// 	}
// 
// 	m_pMutexFilters->Unlock();
	return nRet;
}
int CMediaStream::SetFinishedCb(FilterCB_Finished cbFinished, void *pUserData, void *pReversed)
{
	return  0;
	int nRet = 0;

// 	m_pMutexFilters->Lock();
// 
// 	m_cbFinished = cbFinished;
// 	m_pCbFinishedUserData = pUserData;
// 	m_pCbFinishedReversed = pReversed;
// 
// 	for (int i=0; i<m_lstFilter.size(); i++)
// 	{
// 		m_lstFilter.at(i)->SetFinishedCb(cbFinished, pUserData, pReversed);
// 	}
// 
// 	m_pMutexFilters->Unlock();
	return nRet;
}
int CMediaStream::SetEventCb(FilterCB_Event cbEvent, void *pUserData, void *pReversed)
{
	return  0;
	int nRet = 0;

// 	m_pMutexFilters->Lock();
// 
// 
// 	m_cbEvent = cbEvent;
// 	m_pCbEventUserData = pUserData;
// 	m_pCbEventReversed = pReversed;
// 	
// 	for (int i=0; i<m_lstFilter.size(); i++)
// 	{
// 		m_lstFilter.at(i)->SetEventCb(cbEvent, pUserData, pReversed);
// 	}
// 
// 	m_pMutexFilters->Unlock();

	return nRet;
}

CMediaFilter * CMediaStream::FindFilterByKind( char *pSzKind )
{
	CMediaFilter *pFilter(NULL);
	if (!m_pMutexFilters)
		return NULL;
	m_pMutexFilters->Lock();

	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilterTmp = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilterTmp)
			continue;
		if (pFilterTmp->IsKind(pSzKind))
		{
			pFilter = pFilterTmp;
			break;
		}
	}
	m_pMutexFilters->Unlock();

	return pFilter;
}

CMediaFilter * CMediaStream::FindFilterByKindPriv( char *pSzKind )
{
	CMediaFilter *pFilter(NULL);
	if (!m_pMutexFilters)
		return NULL;

	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilterTmp = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilterTmp)
			continue;
		if (pFilterTmp->IsKind(pSzKind))
		{
			pFilter = pFilterTmp;
			break;
		}
	}


	return pFilter;
}
int CMediaStream::SetParam( char *pName, char *pValue )
{
	map<string, string>::iterator item;
	item = m_mapParam.find(pName);
	if (item == m_mapParam.end())
	{//������

	}
	m_mapParam[pName] = pValue;

	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		pFilter->SetParam(pName, pValue);
	}

	return 0;
}
int CMediaStream::GetParam(char *pSzName, char *pSzValue)
{

	return 0;
}

int CMediaStream::Control( char *pSzName, char *pSzValue )
{
	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		pFilter->Control(pSzName, pSzValue);
	}
	return 0;
}
int CMediaStream::Snapshot(char *pSzSaveFile)
{
	int nRet = 0;

	debug("%s: ++n", __FUNCTION__);
	CMediaFilter *pFilter(0);
	CRender *pRender(0);
	pFilter = FindFilterByKind(FILTER_KIND_RENDER);

	if(pFilter)
	{
		pRender = dynamic_cast<CRender*>(pFilter);
		nRet = pRender->SnapShot(pSzSaveFile);
	}

	return 0;
}

//����ָ��ʱ���һ�� ��ͼ
int CMediaStream::Snapshot( char *pSzSaveFile, int64 s64Time )
{
	//���ţ�ֱ�� ���������뵽 ��ʱ��λ��
	CDecoder *pDecoder = dynamic_cast<CDecoder*>(FindFilterByKind(FILTER_KIND_DECODER));
	if (!pDecoder)
		return -1;
	CSourceFilter *pSource = dynamic_cast<CSourceFilter*>(FindFilterByKind(FILTER_KIND_SOURCE));
	if (!pSource)
		return -2;

#ifdef OLD
	int nRet = 0;
	//seek ��һ��λ�� s64Time
	//��λ��һ��I֡
	float fSpeed = m_fSpeed;

	int64 s64OldPlayTime = 0;
	s64OldPlayTime =   pDecoder->GetTimestamp();
	s64OldPlayTime = pSource->TimestampToTime(s64OldPlayTime);
	SetPlaySpeed(32);
	//�ҵ� ǰһ�� I֡ 
	Seek(s64Time, AVSEEK_FLAG_BACKWARD);
	Resume();

	int64 s64DecodeTime = 0;
	int64 s64DecodeTimestamp=0;
	
	bool bSeekOk =false;
	int nTries = 5000;
	int nTotal = nTries;
	long lTimeBegin = timeGetTime();
	long lTimeNow = timeGetTime();
	long lTimeOut = 5*1000;

	Sleep(10);
	do{
		s64DecodeTimestamp = pDecoder->GetTimestamp();
		s64DecodeTime = pSource->TimestampToTime(s64DecodeTimestamp);
		debug("%s: need to seek,  decode time %I64d, need seek time: %I64d\n", 
			__FUNCTION__,  
			s64DecodeTime, s64Time);
		
		if (s64DecodeTime >= s64Time)
		{
			if (s64OldPlayTime > s64Time)
			{//�Ѿ����ŵ�����ȥ�ģ���Ҫ��ͼ��ʱ���� ���ŵ�ʱ������
				if (s64OldPlayTime >0 && s64DecodeTime >= s64OldPlayTime)
				{//�����ʱ�仹û���˻�ȥ
					debug("%s, decode time is newer than old play time[%I64d]:[%I64d], seek data is not arrive \n", 
						__FUNCTION__,
						s64DecodeTime, s64OldPlayTime);
					continue;
				}
				else
				{
					Pause();
					break;
				}
			}
			else
			{//��ǰ���󲥷ŵģ���Ҫ��ͼ�� ʱ��Ȳ���ʱ��� Զ �ұ�
				Pause();
				break;
			}
		}
		
		Sleep(10);
		lTimeNow = timeGetTime();
	}while ( nTries-- > 0
		&& (lTimeNow-lTimeBegin)<lTimeOut );

	if (nTries < 0)
	{ 
		debug("%s, try seek I frame and decode to pos timeout..., try to seek any pos \n", __FUNCTION__);
		Seek(s64Time, AVSEEK_FLAG_ANY);

		Sleep(40);
		Pause();
		bSeekOk = true;
	}
	else
	{
		debug("%s, try [%d]times, seek I frame and decode to pos success , decode timestamp[%I64d]\n", 
			__FUNCTION__, nTotal-nTries, pDecoder->GetTimestamp()
			);
		bSeekOk = true;
	}
	
	//�ӽ�������ȡ ͼƬ
	if (bSeekOk)
	{//�ҵ�ͼƬ
		int nH = pSource->GetHeight();
		int nW = pSource->GetWidth();
		int nLen = nW*nH*4;
		char *pImage = new char[nLen];
		int nCopyLen = nLen;
		pDecoder->CopyFrame((unsigned char*)pImage, nCopyLen, nW, nH, AV_PIX_FMT_YUV420P);
		
		if (nCopyLen > 0)
		{//����
			CFfmpegCodec *pCodec = new CFfmpegCodec();
			sFfmpegVideoInfo videoInfo;
			videoInfo.m_nBitRate = 40*1024*8;
			videoInfo.m_nCodecId = CODEC_ID_MJPEG;//CODEC_ID_JPEG2000;
			videoInfo.m_nGopSize = 1;
			videoInfo.m_nPixFormat = PIX_FMT_YUV420P;
			videoInfo.m_nHeight = nH;
			videoInfo.m_nWidth = nW;

			pCodec->SetVideoParam(videoInfo);
			int nRet = 0;
			nRet = pCodec->Open(false);
			if (nRet < 0)
			{
				debug("%s, open ffmpeg to encode jpeg false [%d] \n", __FUNCTION__, nRet);
			}
			//ѹ���ʼٶ�Ϊ 5 
			int nJpegLen = nW*nH*3/2/5;
			char *pJpeg = new char[nJpegLen];
			pCodec->Encode((unsigned char*)pImage, videoInfo.m_nWidth*videoInfo.m_nHeight*3/2, 
				(uint8*)pJpeg, nJpegLen);
			//nJpegLen = 0;
			if (nJpegLen > 0)
			{
				debug("%s: encode picture success, data len[%d]\n", __FUNCTION__, nJpegLen);
				FILE *pFile = 0;
				pFile = fopen(pSzSaveFile, "w+b");
				if (pFile)
				{
					fwrite(pJpeg, nJpegLen, 1, pFile);
					fclose(pFile);
					pFile = NULL;
				}
			}
			else
			{
				debug("%s: encode picture false\n", __FUNCTION__);
			}

			delete pJpeg;
			delete pCodec;
		}

		delete pImage;
	}
	else{
		nRet = -3;
	}

	SetPlaySpeed(fSpeed);
	
	Resume();
#else
	int nRet = 0;
	int64 s64Timestamp(0);
	s64Timestamp = pSource->TimeToTimestamp(s64Time);
	int nOldeState = m_state;
	Pause();
	nRet = SeekToTimestamp(s64Timestamp, eSSF_UntilDecode|eSSF_Backward);
	if (nRet >= 0)
	{
		debug("%s: seek to timestamp false\n", __FUNCTION__);
		CMediaFilter *pFilter(0);
		CRender *pRender(0);
		pFilter = FindFilterByKind(FILTER_KIND_RENDER);
		if(pFilter)
		{
			pRender = dynamic_cast<CRender*>(pFilter);
			nRet = pRender->SnapShot(pSzSaveFile);
		}
	}

	m_pMutexFilters->Lock();
	SetPlayStatePriv(nOldeState);
	m_pMutexFilters->Unlock();
#endif


	return nRet;
}
int CMediaStream::Snapshot(char *pImage, int &nLen, int &nW, int &nH, int64 s64Time)
{

 
	//���ţ�ֱ�� ���������뵽 ��ʱ��λ��
	CDecoder *pDecoder = dynamic_cast<CDecoder*>(FindFilterByKind(FILTER_KIND_DECODER));
	if (!pDecoder)
		return -1;
	CSourceFilter *pSource = dynamic_cast<CSourceFilter*>(FindFilterByKind(FILTER_KIND_SOURCE));
	if (!pSource)
		return -2;

#ifdef OLD
	int nRet = 0;
	//seek ��һ��λ�� s64Time
	//��λ��һ��I֡
	float fSpeed = m_fSpeed;



	int64 s64OldPlayTime = 0;
	s64OldPlayTime =   pDecoder->GetTimestamp();
	s64OldPlayTime = pSource->TimestampToTime(s64OldPlayTime);
	SetPlaySpeed(32);
	//�ҵ� ǰһ�� I֡ 
	Seek(s64Time, AVSEEK_FLAG_BACKWARD);
	Resume();

	int64 s64DecodeTime = 0;
	int64 s64DecodeTimestamp=0;

	bool bSeekOk =false;
	int nTries = 5000;
	int nTotal = nTries;
	long lTimeBegin = timeGetTime();
	long lTimeNow = timeGetTime();
	long lTimeOut = 5*1000;

	Sleep(10);
	do{
		s64DecodeTimestamp = pDecoder->GetTimestamp();
		s64DecodeTime = pSource->TimestampToTime(s64DecodeTimestamp);
		debug("%s: need to seek,  decode time %I64d, need seek time: %I64d\n", 
			__FUNCTION__,  
			s64DecodeTime, s64Time);

		if (s64DecodeTime >= s64Time)
		{
			if (s64OldPlayTime > s64Time)
			{//�Ѿ����ŵ�����ȥ�ģ���Ҫ��ͼ��ʱ���� ���ŵ�ʱ������
				if (s64OldPlayTime >0 && s64DecodeTime >= s64OldPlayTime)
				{//�����ʱ�仹û���˻�ȥ
					debug("%s, decode time is newer than old play time[%I64d]:[%I64d], seek data is not arrive \n", 
						__FUNCTION__,
						s64DecodeTime, s64OldPlayTime);
					continue;
				}
				else
				{
					Pause();
					break;
				}
			}
			else
			{//��ǰ���󲥷ŵģ���Ҫ��ͼ�� ʱ��Ȳ���ʱ��� Զ �ұ�
				Pause();
				break;
			}
		}

		Sleep(10);
		lTimeNow = timeGetTime();
	}while ( nTries-- > 0
		&& (lTimeNow-lTimeBegin)<lTimeOut );

	if (nTries < 0)
	{ 
		debug("%s, try seek I frame and decode to pos timeout..., try to seek any pos \n", __FUNCTION__);
		Seek(s64Time, AVSEEK_FLAG_ANY);

		Sleep(40);
		Pause();
		bSeekOk = true;
	}
	else
	{
		debug("%s, try [%d]times, seek I frame and decode to pos success , decode timestamp[%I64d]\n", 
			__FUNCTION__, nTotal-nTries, pDecoder->GetTimestamp()
			);
		bSeekOk = true;
	}

	//�ӽ�������ȡ ͼƬ
	if (bSeekOk)
	{//�ҵ�ͼƬ
		int nH = pSource->GetHeight();
		int nW = pSource->GetWidth();
		int nLen = nW*nH*4;
		//char *pImage = new char[nLen];
		int nCopyLen = nLen;
		pDecoder->CopyFrame((unsigned char*)pImage, nCopyLen, nW, nH, AV_PIX_FMT_BGRA);
		nLen = nW*nH*4;
	}
	else{
		nRet = -3;
	}

	SetPlaySpeed(fSpeed);

	Resume();

#else
	
	int nRet = 0;
	int64 s64Timestamp = 0;
	if (s64Time <0)
	{
		 
		CMediaFilter *pFilter(0);
		CRender *pRender(0);
		pFilter = FindFilterByKind(FILTER_KIND_RENDER);

		if(pFilter)
		{
			pRender = dynamic_cast<CRender*>(pFilter);
			nRet = pRender->SnapShot((unsigned char*)pImage, nW, nH);
		}
	}
	else{
		s64Timestamp = pSource->TimeToTimestamp(s64Time);
		int nOldeState = m_state;
		Pause();
		nRet = SeekToTimestamp(s64Timestamp, eSSF_UntilDecode|eSSF_Backward);
		if (nRet >= 0)
		{

			int nH = pSource->GetHeight();
			int nW = pSource->GetWidth();
			int nLen = nW*nH*4;
			//char *pImage = new char[nLen];
			int nCopyLen = nLen;
			pDecoder->CopyFrame((unsigned char*)pImage, nCopyLen, nW, nH, AV_PIX_FMT_BGRA);
			nLen = nW*nH*4;

		}
		m_pMutexFilters->Lock();
		SetPlayStatePriv(nOldeState);
		m_pMutexFilters->Unlock();
	}
#endif


	return nRet;
}


int CMediaStream::PlayNextFramePriv()
{
	//debug("%s ++\n", __FUNCTION__);

	//m_state = eSS_Pause;
	m_playMode = eSPM_PlayNextFrame;
  
	CMediaFilter *pFilter = NULL;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		pFilter->SetPlayMode(eFPM_PlayNextFrame);
		pFilter->Pause();
	}


	int nRet = 0;
	bool bRenderNextFrameSuccess = false;
	int nTries = 100;
	int nTried = 0;
	do 
	{
		bool bHaveRender = false;
		for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
		{
			pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
			if (!pFilter)
				continue;
			if (pFilter->IsKind(FILTER_KIND_RENDER))
			{
				bHaveRender = true;
				nRet = pFilter->PlayNextFrame();
				if (nRet >= 0)
				{
					//debug("%s, play next frame success \n", __FUNCTION__);
					bRenderNextFrameSuccess = true;
					break;
				}
				else
				{
					//debug("%s, play next frame false need decode more \n", __FUNCTION__);
				}
			}
		}
		if (!bHaveRender)
		{//�ӽ����� ��ȡ �Ƿ�ɹ�

		}
		if (!bRenderNextFrameSuccess)
		{//����û�ɹ��� ����û�����ˣ���Ҫ���ε� fliter������
			//debug("%s, no frame, need decode more ..\n", __FUNCTION__);
			for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
			{
				pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
				if (!pFilter)
					continue;
				if (pFilter->IsKind(FILTER_KIND_SOURCE))
				{//ִ��һ�����ݿ�����
					pFilter->PlayNextFrame();
				}
			}
		}
		nTried++;
		//debug("%s, tries: %d\n", __FUNCTION__, nTried);
	} while (!bRenderNextFrameSuccess 
		&& nTries--
		&& !IsStreamEnd());
 
	if (bRenderNextFrameSuccess)
	{
		nRet = 0;
	}
	else
	{
		nRet = -1;
	}
	//debug("%s -- %d\n", __FUNCTION__, nRet);
	return nRet;
}

int CMediaStream::SetPlayStatePriv( int nState )
{
	
	CMediaFilter *pFilter = 0;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		 pFilter->SetPlayState(nState);
	}

	m_state = (ePipeLineState)nState;
	return 0;
}

int CMediaStream::SetPlayModePriv( int nMode )
{

	CMediaFilter *pFilter = 0;
	for (int i=0; i<m_lstFilter.size() && m_state != eSS_Stop; i++)
	{
		pFilter = dynamic_cast<CMediaFilter*>(m_lstFilter.at(i));
		if (!pFilter)
			continue;
		pFilter->SetPlayMode((eFilterPlayMode)nMode);
	}

	m_playMode = (eStreamPlayMode)nMode;

	return 0;
}

// void CBaseStream::TestStdAllocator( vector<int> &lstValue )
// {
// 	for (int i=0; i<1000; i++)
// 	{
// 		lstValue.push_back(i);
// 	}
// 	
// }
