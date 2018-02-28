#include "StdAfx.h"
#include "SourceFfmpegFile.h"
#include "Buffer.h"
#include "FfmpegFormat.h"
#include "MediaStream.h"
#include "H264File.h"
/*#include "MediaFileIndex.h"*/
#include "FilterManager.h"

#ifdef WIN32
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <time.h>
#endif



CSourceFfmpegFile g_regSourceFfmpegFile;
CSourceFfmpegFile::CSourceFfmpegFile(void)
: m_pFfmpegFile(NULL)
, m_pReadBuffer(NULL)
, m_lTimeLastRead(0)
, m_nFinishedCount(0)
, m_pH264File(NULL)
{
	strcpy(m_szType, FILTER_SOURCE_FFMPEG_FILE);
	strcpy(m_szName, FILTER_SOURCE_FFMPEG_FILE);
	strcpy(m_szFormatName, AvFormat_Ffmpeg);

	m_pReadBuffer = new CBuffer();
	m_pReadBuffer->SetAllocSize(4*1024*1024);

	CFilterManager::RegistFilter(&g_regSourceFfmpegFile);
}

CSourceFfmpegFile::~CSourceFfmpegFile(void)
{
	if (m_pReadBuffer)
	{
		delete m_pReadBuffer;
	}
	if (m_pFfmpegFile)
	{
		m_pFfmpegFile->Close();
		delete m_pFfmpegFile;
		m_pFfmpegFile = NULL;
	}
	if (m_pH264File)
	{
		m_pH264File->Close();
		delete m_pH264File;
		m_pH264File = NULL;
	}
}
//��ʹ��ģ�� ��Ϊ�� ����
CMediaFilter* CSourceFfmpegFile::CreateObject()
{

	return new CSourceFfmpegFile;
}
/*
* mp4 �� h264 ���� ԭʼ h264������Ҫȡ�� pps sps�� ͬʱ������ֽڲ���264���ݣ��������Ϊ 00 00 00 01 xx
*/
int CSourceFfmpegFile::Open(char *pSzParam)
{
	CSourceFilter::Open(pSzParam);
	
	m_lLastProgressTime = 0;
	//////////////////////////////////////////////////////////////////////////
	if (m_pFfmpegFile)
	{
		return 1;
	}
	//2013-6-21 ������ڴ������⡣release ģʽ���������
	//2013-6-26 �����������ˡ��� register release ����ġ� ���� ���� ���� δʹ�� ���ü��ɽ��
	m_pFfmpegFile = new CFfmpegFormat;
	

	string strFile ;
	strFile = m_mapParamValue["source"];
	
	int nRet = 0;
	char szFile[256];
	
	strcpy(szFile, strFile.data());
	
	nRet = m_pFfmpegFile->Open(szFile, AVIO_FLAG_READ);
	
	if (nRet < 0)
		return -1;

	m_bNeedFix = m_pFfmpegFile->IsNeedFix();

	AVStream *pStream = NULL;
	pStream = m_pFfmpegFile->GetStreamByType(AVMEDIA_TYPE_VIDEO);
	if (pStream)
	{//֡�ʱ�����������㡣
		m_nTimePerFrame = 1000*pStream->r_frame_rate.den/pStream->r_frame_rate.num;
		if (m_nTimePerFrame == 0)
		{
			m_nTimePerFrame = 40;
		}
		else if (m_nTimePerFrame < 30)
		{
			m_nTimePerFrame = 40;
		}
		//m_nTimePerFrame = 10;
	}
	sFfmpegStreamInfo streamInfo;

	m_pFfmpegFile->GetStreamInfo(streamInfo, 0);

	m_nW = m_pFfmpegFile->GetVideoWidth();
	m_nH = m_pFfmpegFile->GetVideoHeight();
	m_s64LastMediaTimestamp = 0;
	m_lMediaTimeInc = 10;
	m_lTimeInc = 0;
	
	int64 s64TotalTime(0);
	s64TotalTime =  m_pFfmpegFile->GetTotalTime();
	if (s64TotalTime <= 0 && 0)
	{//��Ҫ��������
		m_pH264File = new CH264File();
		nRet = m_pH264File->Open(szFile, AVIO_FLAG_READ);
		// 	CH264File file;
		// 	nRet = file.Open(pSzFile, AVIO_FLAG_READ);
		if (nRet >= 0)
		{
			debug("%s, open H264 file success\n", __FUNCTION__);
		}
		else
		{
			debug("%s, open H264 file false\n", __FUNCTION__);
		}
	}


	return 0;
}
int CSourceFfmpegFile::Open( char *pUrl, bool bHasThread/*=false*/ )
{
	CSourceFilter::Open(pUrl, false);
	
	m_lLastProgressTime = 0;
	//////////////////////////////////////////////////////////////////////////
	if (m_pFfmpegFile)
	{
		return 1;
	}
	//2013-6-21 ������ڴ������⡣release ģʽ���������
	//2013-6-26 �����������ˡ��� register release ����ġ� ���� ���� ���� δʹ�� ���ü��ɽ��
	m_pFfmpegFile = new CFfmpegFormat;


	string strFile ;
	strFile = m_mapParamValue["source"];

	int nRet = 0;
	char szFile[256];

	strcpy(szFile, strFile.data());

	nRet = m_pFfmpegFile->Open(szFile, AVIO_FLAG_READ);

	if (nRet < 0)
		return -1;

	m_bNeedFix = m_pFfmpegFile->IsNeedFix();

	AVStream *pStream = NULL;
	pStream = m_pFfmpegFile->GetStreamByType(AVMEDIA_TYPE_VIDEO);
	if (pStream)
	{//֡�ʱ�����������㡣
		m_nTimePerFrame = 1000*pStream->r_frame_rate.den/pStream->r_frame_rate.num;
		if (m_nTimePerFrame == 0)
		{
			m_nTimePerFrame = 40;
		}
		else if (m_nTimePerFrame < 30)
		{
			m_nTimePerFrame = 40;
		}
		//m_nTimePerFrame = 10;
	}
	sFfmpegStreamInfo streamInfo;

	m_pFfmpegFile->GetStreamInfo(streamInfo, 0);

	m_nW = m_pFfmpegFile->GetVideoWidth();
	m_nH = m_pFfmpegFile->GetVideoHeight();
	m_s64LastMediaTimestamp = 0;
	m_lMediaTimeInc = 10;
	m_lTimeInc = 0;

	int64 s64TotalTime(0);
	s64TotalTime =  m_pFfmpegFile->GetTotalTime();
	if (s64TotalTime <= 0 && 0)
	{//��Ҫ��������
		m_pH264File = new CH264File();
		nRet = m_pH264File->Open(szFile, AVIO_FLAG_READ);
		// 	CH264File file;
		// 	nRet = file.Open(pSzFile, AVIO_FLAG_READ);
		if (nRet >= 0)
		{
			debug("%s, open H264 file success\n", __FUNCTION__);
		}
		else
		{
			debug("%s, open H264 file false\n", __FUNCTION__);
		}
	}
	//�����߳�
	//
	m_state = eFilterState_Pause;
	CreateFilterThread(bHasThread);

	return 0;
}

int CSourceFfmpegFile::DoFilter()
{
	//CSourceFilter::Init();
	if (  !m_pFfmpegFile)
	{
		return CSourceFilter::DoFilter();
	}
	long lTimeNow = timeGetTime();
	if (m_fSpeed > 16)
	{//���ٿ����ٶ�

	}//��֡�ʿ����޸�Ϊʱ��������ٶ�, ����һ֡��ȥ��ʧ��ʱ�� Ҫ�ȵ� ��ý�����ӵ�ʱ�����
	//else if (lTimeNow - m_lTimeLastRead < m_nTimePerFrame/m_fSpeed)
	else if (lTimeNow - m_lTimeLastRead < m_lMediaTimeInc/m_fSpeed)
	{//����ʱ��
		Sleep(5);
		return CSourceFilter::DoFilter();
	}
	//�����趨����ʱ��ε����
	if (m_s64SegmentTimeEnd > m_s64SegmentTimeBegin
		&& m_s64SegmentTimeBegin >= 0)
	{
		if (m_pFfmpegFile->GetCurrentTime() >= m_s64SegmentTimeEnd)
		{//Ӧ�ý�����
		
			m_bIsStreamEnd = true;
			m_nNeedSleep = 10;
			if (m_cbFinished  && (m_nFinishedCount%50==0) )
			{//1���ϱ�һ��
				m_cbFinished(m_pCbFinishedUserData, m_pCbFinishedReversed);
			}
			m_nFinishedCount++;

			return CSourceFilter::DoFilter();
		}
	}
	//

	CFilterPin *pPinOut = 0;
	pPinOut = m_lstPinOut.at(0);
	if (pPinOut->GetFreeBufferCount() <= 0)
	{
		Sleep(5);
		return CSourceFilter::DoFilter();
	}
	int nRead = 0;
	int nReadMax = m_pReadBuffer->GetAllocSize();
	int64_t nPts = 0;
	int nStreamId = 0;
	int nFrameType = 0;
	//��ȡһ֡����
	do{//
		nReadMax = m_pReadBuffer->GetAllocSize();
		int nReadBegin = timeGetTime();
		if (m_pH264File)
		{
			
			nRead = m_pH264File->Read((char*)m_pReadBuffer->GetData(), nReadMax, nPts, nStreamId, nFrameType);
		}
		else
		{
			nRead = m_pFfmpegFile->ReadFrame((char*)m_pReadBuffer->GetData(), nReadMax, nPts, nStreamId); 
			if (m_pFfmpegFile->IsKeyFrame())
			{
				nFrameType = eFFT_I;
			}
			else
			{
				nFrameType = eFFT_P;
			}
		}
		int nReadEnd = timeGetTime();
		//debug("%s, read frame, time used: %d\n", __FUNCTION__, nReadEnd - nReadBegin);
		//debug("%s, read frame pts: %d\n", __FUNCTION__, (int)nPts);
		//if (16866562 == nPts)
		//{
		//	debug("%s, last frame\n", __FUNCTION__);
		//}
		//debug("%s: read frame ret: %d, pts: %I64d\n", __FUNCTION__, nRead, nPts);
		if (nRead <=  0)
		{//������
			m_bIsStreamEnd = true;
			//debug ("%s, finished\n", __FUNCTION__);
			if (m_cbFinished /*&& (m_nFinishedCount%100==0)*/ )
			{//1���ϱ�һ��
				m_cbFinished(m_pCbFinishedUserData, m_pCbFinishedReversed);
			}
			m_nFinishedCount++;
			//�������̱߳��ֱȽϵ͵� ���ȼ�
			m_nNeedSleep = 10;
			m_pReadBuffer->SetUsed(0);
			goto ret;
		}
		else if (nRead == 0)
		{
			m_nNeedSleep = 0;
			//m_nNeedSleep = 1;
			goto ret;
		}
		else
		{
			m_bIsStreamEnd = false;
			
			m_pReadBuffer->SetUsed(nRead);
		}

		sFfmpegStreamInfo streamInfo;
		if (m_pH264File){
			break;
		}else{
			m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
			if (streamInfo.m_nStreamType == AVMEDIA_TYPE_VIDEO)
			{//һֱҪ��ȡ��һ�� ��Ƶ���� �� �С� 
				break;
			}
			else
			{//�����ݷ��뵽 ��Ƶ��pin (pin1)
				//debug("audio\n");
			}
		}
	}while(m_state != eFilterState_Stop 
		&& m_state != eFilterState_ToStop);
	//�������µ� pts�� ���� pts
	if (nPts != AV_NOPTS_VALUE)
	{
		if (nPts > m_s64LastMediaTimestamp)
		{
			m_lMediaTimeInc = m_pFfmpegFile->TimestampToTime(nPts) - m_pFfmpegFile->TimestampToTime(m_s64LastMediaTimestamp);
			//debug("time now : %I64d\n", m_pFfmpegFile->TimestampToTime(nPts));
			if (m_lMediaTimeInc > 100)
			{
				m_lMediaTimeInc = 100;
			}
			else if (m_lMediaTimeInc < 10)
			{
				m_lMediaTimeInc = 10;
			}
			m_s64LastMediaTimestamp = nPts;

			m_lTimeLastRead = lTimeNow;
		}
		else
		{
			nPts = m_s64LastMediaTimestamp;
		}
		
	}else{
		//��Ч��pts
		nPts = m_s64LastMediaTimestamp;
	}
	//�����ϱ�
	if (m_cbProgress)
	{
		float fNow = 0;
		fNow = m_pFfmpegFile->GetCurrentTime();//*100.0/m_pFfmpegFile->GetTotalTime();
		//�������Ƶ�����ύ����, �����ϱ�һ��
		if (abs(lTimeNow - m_lLastProgressTime) >= 200)
		{
			int64 s64CurPos(0), s64Total(0);
			if (m_pH264File){
				s64CurPos = m_pH264File->GetCurrTime();
				s64Total = m_pH264File->GetTotalTime();
			}else{
				s64CurPos = m_pFfmpegFile->GetCurrentTime();
				s64Total = m_pFfmpegFile->GetTotalTime();
				if (s64Total <= 0)
				{//�޷���ȡʱ�䳤�ȵ�ʱ��ʹ���ļ���С����λ�� ��Ϊ��������
					s64CurPos = m_pFfmpegFile->GetFilePos();
					s64Total = m_pFfmpegFile->GetFileSize();
				}
			}
			if (m_s64SegmentTimeEnd > m_s64SegmentTimeBegin
				&& m_s64SegmentTimeBegin >= 0)
			{//��ʱ��� ���ŵ����
				s64CurPos -= m_s64SegmentTimeBegin;
				s64Total = m_s64SegmentTimeEnd - m_s64SegmentTimeBegin;
			}

			m_cbProgress(m_fSpeed, s64CurPos, s64Total,  m_pCbProgressUserData, m_pCbProgressReversed);

			m_lLastProgressTime = lTimeNow; //m_pFfmpegFile->GetCurrentTime();
		}
	}
	
	if (nRead == 0)
	{
		m_nNeedSleep = 0;
		goto ret;
	}
	//�������
	CFilterPinBuffer *pPinBuffer = 0;
	pPinOut->GetFreeBuffer(&pPinBuffer);
	if ( pPinBuffer)
	{
		pPinBuffer->Clear();
		CBuffer *pBufferEx =pPinBuffer->GetExtData();

		pPinBuffer->Append((char*)m_pReadBuffer->GetData(), m_pReadBuffer->GetUsedSize());
		
		sFfmpegFrameInfo frameInfo;
		memset(&frameInfo, 0, sizeof(frameInfo));
		frameInfo.m_nDataType = AVMEDIA_TYPE_VIDEO;
		frameInfo.m_s64Pts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
		frameInfo.m_s64Dts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
		
		frameInfo.m_nFrameType = nFrameType;
		
		
		sFfmpegStreamInfo streamInfo;
		m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
		frameInfo.m_videoInfo = streamInfo.m_videoInfo;
		frameInfo.m_s64Bts = streamInfo.m_s64StartTimestamp;
 
		m_pFfmpegFile->GetTimeBase(frameInfo.m_nTimeNum, frameInfo.m_nTimeDen);
		
		//debug("%s,  pts: %d\n", __FUNCTION__, (int)nPts);
		if (pBufferEx)
		{
			pBufferEx->Clear();
			pBufferEx->Append((uint8*)&frameInfo, sizeof(frameInfo));
		}

		pPinOut->PutPreparedBuffer(pPinBuffer);
	}
	//�ⲿ����Ҫ̫�����ߣ��ɱ��������� 
	if (!m_bIsStreamEnd)
		m_nNeedSleep = 0;
	else 
	{
		m_nNeedSleep = 10;
	}

ret:
	return CSourceFilter::DoFilter();
}
int CSourceFfmpegFile::PlayPrevFrame(int64 s64PtsNow/*=0*/)
{
	if (!m_pFfmpegFile)
	{
		return 0;
	}
	int64_t s64TimestampNow = 0;
	int64_t s64TimePrevKeyFrame = 0;
	//��¼��ǰ�� ʱ�����һ���� render��ȡ��������
	if (s64PtsNow > 0)
	{
		s64TimestampNow = s64PtsNow;
	}
	else
	{
		s64TimestampNow = m_pFfmpegFile->GetCurrentTimestamp();
	}
	//�ƶ���ǰһ�� key frame
	
	m_pFfmpegFile->SeekToPrevKeyFrame();
	s64TimePrevKeyFrame = m_pFfmpegFile->GetCurrentTimestamp();

	debug("%s, curr progess: %d, prev key frame: %d\n", __FUNCTION__, (int)s64TimestampNow, (int)s64TimePrevKeyFrame);
	//ѭ����ȡ���ݣ�ֱ��  ʱ��� == s64TimeNow 
	int nRead = 0;
	int nReadMax = m_pReadBuffer->GetAllocSize();
	int64_t s64TimeStampRead = 0;
	int64 nPts = 0;
	int nStreamId = 0;
	int nTried = 0;
	long lTimeNow = timeGetTime();

	s64TimePrevKeyFrame = -1;

	CFilterPin *pPinOut = 0;
	pPinOut = m_lstPinOut.at(0);
	do{//������ȡ ֱ�� ���֡��λ�� 
		//��ȡһ֡��Ƶ
		do{//
			nReadMax = m_pReadBuffer->GetAllocSize();
			nRead = m_pFfmpegFile->ReadFrame((char*)m_pReadBuffer->GetData(), nReadMax, nPts, nStreamId); 
			//debug("%s, read frame pts: %d\n", __FUNCTION__, (int)nPts);
			if (nRead <=  0)
			{//������
				m_bIsStreamEnd = true;
				//debug ("%s, finished\n", __FUNCTION__);
				if (m_cbFinished /*&& (m_nFinishedCount%100==0)*/ )
				{//1���ϱ�һ��
					m_cbFinished(m_pCbFinishedUserData, m_pCbFinishedReversed);
				}
				m_nFinishedCount++;
				//�������̱߳��ֱȽϵ͵� ���ȼ�
				m_pReadBuffer->SetUsed(0);
				goto ret;
			}
			else
			{
				m_bIsStreamEnd = false;
				m_pReadBuffer->SetUsed(nRead);
			}

			sFfmpegStreamInfo streamInfo;
			m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
			if (streamInfo.m_nStreamType == AVMEDIA_TYPE_VIDEO)
			{//һֱҪ��ȡ��һ�� ��Ƶ���� �� �С� 
				
				break;
			}
			else
			{//�����ݷ��뵽 ��Ƶ��pin (pin1)
				//debug("audio\n");
			}
		}while(m_state != eFilterState_Stop 
			&& m_state != eFilterState_ToStop);
		//�������µ� pts
		if (nPts != AV_NOPTS_VALUE)
		{
			m_s64LastMediaTimestamp = nPts;
		}else{
			//��Ч��pts
			nPts = m_s64LastMediaTimestamp;
		}

		if (s64TimePrevKeyFrame == -1)
		{
			s64TimePrevKeyFrame = nPts;
		}
		//��һ֡������
		if (nPts >= s64TimestampNow )
		{
			break;
		}

		float fProgress = 0;
		fProgress = 100.0*m_pFfmpegFile->GetCurrentTime()/m_pFfmpegFile->GetTotalTime();
		if (m_cbProgress)
		{
			float fNow = 0;
			fNow = m_pFfmpegFile->GetCurrentTime();//*100.0/m_pFfmpegFile->GetTotalTime();
			//�������Ƶ�����ύ����, �����ϱ�һ��
			if (abs(lTimeNow - m_lLastProgressTime) >= 100)
			{
				int64 s64CurPos(0), s64Total(0);
				s64CurPos = m_pFfmpegFile->GetCurrentTime();
				s64Total = m_pFfmpegFile->GetTotalTime();
				if (s64Total <= 0)
				{//�޷���ȡʱ�䳤�ȵ�ʱ��ʹ���ļ���С����λ�� ��Ϊ��������
					s64CurPos = m_pFfmpegFile->GetFilePos();
					s64Total = m_pFfmpegFile->GetFileSize();
				}
				m_cbProgress(m_fSpeed, s64CurPos, s64Total,  m_pCbProgressUserData, m_pCbProgressReversed);

				m_lLastProgressTime = lTimeNow; //m_pFfmpegFile->GetCurrentTime();
			}
		}
		
		CFilterPinBuffer *pPinBuffer = 0;
		pPinOut->GetFreeBuffer(&pPinBuffer);
		if ( pPinBuffer)
		{
			pPinBuffer->Clear();
			CBuffer *pBufferEx =pPinBuffer->GetExtData();

			pPinBuffer->Append((char*)m_pReadBuffer->GetData(), m_pReadBuffer->GetUsedSize());

			sFfmpegFrameInfo frameInfo;
			memset(&frameInfo, 0, sizeof(frameInfo));
			frameInfo.m_nDataType = AVMEDIA_TYPE_VIDEO;
			frameInfo.m_s64Pts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
			frameInfo.m_s64Dts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
			if (m_pFfmpegFile->IsKeyFrame())
			{
				frameInfo.m_nFrameType = eFFT_I;
			}
			else
			{
				frameInfo.m_nFrameType = eFFT_Unknown;
			}

			sFfmpegStreamInfo streamInfo;
			m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
			frameInfo.m_videoInfo = streamInfo.m_videoInfo;
			frameInfo.m_s64Bts = streamInfo.m_s64StartTimestamp;

			m_pFfmpegFile->GetTimeBase(frameInfo.m_nTimeNum, frameInfo.m_nTimeDen);

			if (pBufferEx)
			{
				pBufferEx->Clear();
				pBufferEx->Append((uint8*)&frameInfo, sizeof(frameInfo));
			}

			pPinOut->PutPreparedBuffer(pPinBuffer);
		}
		s64TimeStampRead = nPts;

		nTried ++;
		//debug("%s, tried: %d, pts: %d\n", __FUNCTION__, nTried, (int)s64TimeStampRead);
		CSourceFilter::DoFilter();
	}while(s64TimeStampRead < s64TimestampNow 
		&& m_state != eFilterState_Stop 
		&& m_state != eFilterState_ToStop
		&& nTried <= 1000);
	

	CSourceFilter::DoFilter();
	CSourceFilter::DoFilter();

	//CSourceFilter::DoFilter();
	//CSourceFilter::DoFilter();
	//��λ����ȡ�Ŀ�ʼ�ط������� ��һ�� prev ����
	debug("%s, seek back to last key %d\n", __FUNCTION__, (int)s64TimePrevKeyFrame);
	m_pFfmpegFile->SeekToTimestamp(s64TimePrevKeyFrame);

ret:

	return CSourceFilter::PlayPrevFrame();
}
int CSourceFfmpegFile::Resume()
{
	if (m_playMode == eFPM_PlayPrevFrame)
	{//��Ҫ ���¶�λһ��
		//m_pFfmpegFile->SeekTo(0);
	}
	

	return  CSourceFilter::Resume();
}
int CSourceFfmpegFile::Seek(int64 s64Time, int nFlag/*=0*/ )
{
	if (m_pFfmpegFile)
	{
		//nFlag = AVSEEK_FLAG_ANY;
		int nFlagFfmpeg = 0;
		if (nFlag & eSSF_Any)
		{
			nFlagFfmpeg |= AVSEEK_FLAG_ANY;
		}
		if (nFlag & eSSF_Backward)
		{
			nFlagFfmpeg |= AVSEEK_FLAG_BACKWARD;
		}
	 
		m_pFfmpegFile->SeekTo(s64Time, nFlagFfmpeg);
		
		m_s64LastMediaTimestamp = m_pFfmpegFile->GetCurrentTimestamp( );
	}
	//ý��û����ʱ��
	m_lMediaTimeInc = 0;
	m_lTimeLastRead = timeGetTime();
	m_bIsStreamEnd = false;
	//m_lTimeLastRead = timeGetTime();
	//m_s64LastProgress = s64Time;
	
	return CSourceFilter::Seek(s64Time);
}
//����һ��ʹ�������Ƶ�� ��ʵʱ���
int CSourceFfmpegFile::SeekToTimestamp(int64 s64Timestamp, int nFlag/*=0*/ )
{
	if (m_pFfmpegFile)
	{
		int64 s64StartTimestamp = 0;
		int nFlagFfmpeg = 0;
		if (nFlag & eSSF_Any)
		{
			nFlagFfmpeg |= AVSEEK_FLAG_ANY;
		}
		if (nFlag & eSSF_Backward)
		{
			nFlagFfmpeg |= AVSEEK_FLAG_BACKWARD;
		}
		s64StartTimestamp = m_pFfmpegFile->GetStartTimestamp();
		m_pFfmpegFile->SeekToTimestamp(s64Timestamp/*+s64StartTimestamp*/, nFlagFfmpeg);
	}
	m_s64LastMediaTimestamp = m_pFfmpegFile->GetCurrentTimestamp();

	m_lMediaTimeInc = 0;
	m_lTimeLastRead = timeGetTime();
	m_bIsStreamEnd = false;

	return CSourceFilter::SeekToTimestamp(s64Timestamp);
}
int64 CSourceFfmpegFile::GetTotalTime()
{
	if (m_pFfmpegFile)
	{
		return  m_pFfmpegFile->GetTotalTime();
	}

	return m_s64TotalTime;
}
int64 CSourceFfmpegFile::GetCurrTime()
{
	if (!m_pFfmpegFile)
		return 0;

	return m_pFfmpegFile->GetCurrentTime();
	
}
void CSourceFfmpegFile::GetTimeBase(int &nNum, int nDen)
{
	if (!m_pFfmpegFile)
		return ;
	
	m_pFfmpegFile->GetTimeBase(nNum, nDen);
}


int CSourceFfmpegFile::ProbMediaInfo( char *pSzFile )
{

	int nRet = -1;
	CFfmpegFormat *pFfmpegFormat = new CFfmpegFormat;
	if (pFfmpegFormat->Open(pSzFile) >= 0)
	{
		nRet = 0;
		//
		AVStream *pStream;
		int nStreams = 0;
		nStreams = pFfmpegFormat->GetStreamCount();
		for (int i=0; i<nStreams; i++)
		{
			pStream = pFfmpegFormat->GetStream(i);
			if (pStream->codec->codec_type != AVMEDIA_TYPE_VIDEO)
				continue;

			m_nW = pStream->codec->width;
			m_nH = pStream->codec->height;
			break;
		}
		m_s64TotalTime = pFfmpegFormat->GetTotalTime();

		AVFormatContext *pFormatContext = pFfmpegFormat->GetFormatContext();
		if (pFormatContext)
		{
			strcpy(m_szFormatSubName, pFormatContext->iformat->name );
		}
		else
		{
			nRet = -1;
		}

		m_bNeedFix = pFfmpegFormat->IsNeedFix();
	}
	

	pFfmpegFormat->Close();
	delete pFfmpegFormat;

	if (strstr(m_szFormatSubName, "h264") != NULL)
	{
		if (m_s64TotalTime < 0)
			m_s64TotalTime = 1;
	}
// 	CH264File file;
// 	nRet = file.Open(pSzFile, AVIO_FLAG_READ);
// 	if (nRet >= 0)
// 	{
// 		debug("open success\n");
// 	}


	return nRet;
}

int64 CSourceFfmpegFile::TimestampToTime( int64 s64Timestamp )
{
	if (!m_pFfmpegFile)
	{
		return 0;
	}
	return m_pFfmpegFile->TimestampToTime(s64Timestamp);
}
int64 CSourceFfmpegFile::TimeToTimestamp(int64 s64Time)
{
	if (!m_pFfmpegFile)
	{
		return 0;
	}
	return m_pFfmpegFile->TimeToTimestamp(s64Time);
}
int CSourceFfmpegFile::PlayNextFrame()
{
	CSourceFilter::PlayNextFrame();

	if (  !m_pFfmpegFile)
	{
		return CSourceFilter::DoFilter();
	}
	 
	CFilterPin *pPinOut = 0;
	pPinOut = m_lstPinOut.at(0);
	if (pPinOut->GetFreeBufferCount() <= 0)
	{
		Sleep(5);
		return CSourceFilter::DoFilter();
	}
	long lTimeNow = timeGetTime();

	int nRead = 0;
	int nReadMax = m_pReadBuffer->GetAllocSize();
	int64_t nPts = 0;
	int nStreamId = 0;
	do{//
		nReadMax = m_pReadBuffer->GetAllocSize();
		nRead = m_pFfmpegFile->ReadFrame((char*)m_pReadBuffer->GetData(), nReadMax, nPts, nStreamId); 

		if (nRead <=  0)
		{//������
			m_bIsStreamEnd = true;
			//debug ("%s, finished\n", __FUNCTION__);
			if (m_cbFinished /*&& (m_nFinishedCount%100==0)*/ )
			{//1���ϱ�һ��
				m_cbFinished(m_pCbFinishedUserData, m_pCbFinishedReversed);
			}
			m_nFinishedCount++;
			//�������̱߳��ֱȽϵ͵� ���ȼ�
			m_nNeedSleep = 10;
			m_pReadBuffer->SetUsed(0);
			goto ret;
		}
		else if (nRead == 0)
		{
			m_nNeedSleep = 0;
			//m_nNeedSleep = 1;
			goto ret;
		}
		else
		{
			m_bIsStreamEnd = false;
			
			m_pReadBuffer->SetUsed(nRead);
		}

		sFfmpegStreamInfo streamInfo;
		m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
		if (streamInfo.m_nStreamType == AVMEDIA_TYPE_VIDEO)
		{//һֱҪ��ȡ��һ�� ��Ƶ���� �� �С� 
			break;
		}
		else
		{//�����ݷ��뵽 ��Ƶ��pin (pin1)
			//debug("audio\n");
		}
	}while(m_state != eFilterState_Stop 
		&& m_state != eFilterState_ToStop);
	//�������µ� pts
	if (nPts != AV_NOPTS_VALUE)
	{
		if (nPts > m_s64LastMediaTimestamp)
		{
			m_lMediaTimeInc = m_pFfmpegFile->TimestampToTime(nPts) - m_pFfmpegFile->TimestampToTime(m_s64LastMediaTimestamp);
			if (m_lMediaTimeInc > 100)
			{
				m_lMediaTimeInc = 100;
			}
			else if (m_lMediaTimeInc < 10)
			{
				m_lMediaTimeInc = 10;
			}
			m_s64LastMediaTimestamp = nPts;


			m_lTimeLastRead = lTimeNow;
		}
		else
		{
			nPts = m_s64LastMediaTimestamp;
		}
		
	}else{
		//��Ч��pts
		nPts = m_s64LastMediaTimestamp;
	}

	float fProgress = 0;
	fProgress = 100.0*m_pFfmpegFile->GetCurrentTime()/m_pFfmpegFile->GetTotalTime();
	if (m_cbProgress)
	{
		float fNow = 0;
		fNow = m_pFfmpegFile->GetCurrentTime();//*100.0/m_pFfmpegFile->GetTotalTime();
		//�������Ƶ�����ύ����, �����ϱ�һ��
		if (abs(lTimeNow - m_lLastProgressTime) >= 100)
		{
			int64 s64CurPos(0), s64Total(0);
			s64CurPos = m_pFfmpegFile->GetCurrentTime();
			s64Total = m_pFfmpegFile->GetTotalTime();
			if (s64Total <= 0)
			{//�޷���ȡʱ�䳤�ȵ�ʱ��ʹ���ļ���С����λ�� ��Ϊ��������
				s64CurPos = m_pFfmpegFile->GetFilePos();
				s64Total = m_pFfmpegFile->GetFileSize();
			}
			m_cbProgress(m_fSpeed, s64CurPos, s64Total,  m_pCbProgressUserData, m_pCbProgressReversed);

			m_lLastProgressTime = lTimeNow; //m_pFfmpegFile->GetCurrentTime();
		}
	}
	//debug ("%s, progress: %.2f, [%d/%d]\n", __FUNCTION__, fProgress, (int)m_pFfmpegFile->GetCurrentTime()/1000, (int)m_pFfmpegFile->GetTotalTime()/1000);
	//Sleep(100);
	if (nRead > 1*1024*1024)
	{
		debug("%s  read: %d, pts: %d\n", __FUNCTION__, nRead, (int)nPts);
	}

	if (nRead == 0)
	{
		m_nNeedSleep = 0;
		goto ret;
	}
	
	CFilterPinBuffer *pPinBuffer = 0;
	pPinOut->GetFreeBuffer(&pPinBuffer);
	if ( pPinBuffer)
	{
		pPinBuffer->Clear();
		CBuffer *pBufferEx =pPinBuffer->GetExtData();

		pPinBuffer->Append((char*)m_pReadBuffer->GetData(), m_pReadBuffer->GetUsedSize());
		
		sFfmpegFrameInfo frameInfo;
		memset(&frameInfo, 0, sizeof(frameInfo));
		frameInfo.m_nDataType = AVMEDIA_TYPE_VIDEO;
		frameInfo.m_s64Pts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
		frameInfo.m_s64Dts = nPts; //(nPts - m_pFfmpegFile->GetStartTimestamp() );
		if (m_pFfmpegFile->IsKeyFrame())
		{
			frameInfo.m_nFrameType = eFFT_I;
		}
		else
		{
			frameInfo.m_nFrameType = eFFT_Unknown;
		}
		
		sFfmpegStreamInfo streamInfo;
		m_pFfmpegFile->GetStreamInfo(streamInfo, nStreamId);
		frameInfo.m_videoInfo = streamInfo.m_videoInfo;
		frameInfo.m_s64Bts = streamInfo.m_s64StartTimestamp;
 
		m_pFfmpegFile->GetTimeBase(frameInfo.m_nTimeNum, frameInfo.m_nTimeDen);
		
		//debug("%s,  pts: %d\n", __FUNCTION__, (int)nPts);
		if (pBufferEx)
		{
			pBufferEx->Clear();
			pBufferEx->Append((uint8*)&frameInfo, sizeof(frameInfo));
		}

		pPinOut->PutPreparedBuffer(pPinBuffer);
	}

ret:
	return CSourceFilter::DoFilter();
}

void CSourceFfmpegFile::SetSegment( int64_t s64TimeBegin, int64_t s64TimeEnd )
{
	m_s64SegmentTimeBegin = s64TimeBegin;
	m_s64SegmentTimeEnd = s64TimeEnd;

	if (!m_pFfmpegFile)
	{
		return ;
	}
	if (m_pFfmpegFile->GetCurrentTime() < s64TimeBegin)
	{
		m_pFfmpegFile->SeekTo(s64TimeBegin, eSSF_Backward, 0);
	}
}
int   CSourceFfmpegFile::DoFixFile(int64 &s64Total, int64 &s64Pos)
{
	if (!m_pFfmpegFile)
		return -1;
	int nRet = 0;
	nRet = m_pFfmpegFile->DoFixFile(s64Total, s64Pos);

	return nRet;
}


int CSourceFfmpegFile::RunFilter()
{
	//
	while(m_state == eFilterState_Run
		 || m_state == eFilterState_Pause
		 )
	{
		if (m_state == eFilterState_Pause)
		{
			Sleep(1);
			continue;
		}
		DoFilter();

		Sleep(1);
	}
	//
	return 0;
}



int CSourceFfmpegFile::Stop()
{
	CBaseFilter::Stop();

	
	return 0;
}
