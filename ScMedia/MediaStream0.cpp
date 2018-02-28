

#include "StdAfx.h"


#include "MediaSdk.h"
#include "MediaStream.h"
#include "PackageParser.h"
#include "Decoder.h"
#include "Render.h"
#include "Thread.h"
#include "StreamBuilder.h"
#include "DataFilter.h"
#include "Mutex.h"
#include "MediaFile.h"
#include "VivsMediaFile.h"
#include "VideoFramePinBuffer.h"
#include "MediaFile.h"
#include "VivsMediaFile.h"
#include "FfmpegFormat.h"

#ifdef WIN32
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <time.h>
#endif



#ifdef WIN32
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#endif

using namespace SThread;
CMediaStream::CMediaStream(void)
:m_pVideoDecoder(0)
/*, m_pMediaFile(NULL)*/
, m_pVideoRender(0)
, m_pAudioDecoder(0)
, m_pAudioRender(0)
, m_pPackageParser(0)
, m_pThreadDecode(0)
, m_pThreadRender(0)
, m_pInputDataBuffer(NULL)
, m_pMutexInputBuffer(NULL)
, m_state(eSS_Run)
, m_nPlayBuffer(10)
, m_pVivsMediaFile(NULL)
, m_pThreadReadFile(NULL)
, m_bFileSeek(false)
, m_cbPlayFileTimeStamp(NULL)
, m_pCbPlayFileReversed(0)
, m_pCbPlayFileUserData(0)
, m_s64PlayFileTimeStamp(0)
, m_fPlaySpeed(1.0)
, m_cbDecode(NULL)
, m_pCbDecodeUserData(NULL)
, m_pCbDecodeReversed(NULL)
, m_pFfmpegFormatAvi(NULL)
, m_pThrTransFile2Avi(NULL)
{
	m_pMutexInputBuffer = new CMutex();
	m_pInputDataBuffer = new CFilterPinBuffer(512*1024, 1*1024*024);
}

CMediaStream::~CMediaStream(void)
{
	m_state = eSS_Stop;
	
	if (m_pThreadRender)
	{
		m_pThreadRender->Stop();
		m_pThreadRender->Sleep(100);
		delete m_pThreadRender;
		m_pThreadRender = NULL;
	}
	if (m_pThreadDecode)
	{
		m_pThreadDecode->Stop();
		m_pThreadDecode->Sleep(100);
		delete m_pThreadDecode;
		m_pThreadDecode = NULL;
	}
	if (m_pThreadReadFile)
	{
		m_pThreadReadFile->Stop();
		m_pThreadReadFile->Sleep(50);
		delete m_pThreadReadFile;
		m_pThreadReadFile = NULL;
	}

	if (m_pPackageParser)
	{
		delete m_pPackageParser;
		m_pPackageParser = NULL;
	}
	if (m_pVideoDecoder)
	{
		delete m_pVideoDecoder ;
		m_pVideoDecoder = NULL;
	}
	if (m_pVideoRender)
	{
		delete m_pVideoRender;
		m_pVideoRender = NULL;
	}
	if (m_pAudioDecoder)
	{
		delete m_pAudioDecoder;
		m_pAudioDecoder = NULL;
	}
	if (m_pAudioRender)
	{
		delete m_pAudioRender;
		m_pAudioRender = NULL;
	}
	if (m_pInputDataBuffer)
	{
		delete m_pInputDataBuffer;
		m_pInputDataBuffer = NULL;
	}
	if (m_pMutexInputBuffer)
	{
		delete m_pMutexInputBuffer;
		m_pMutexInputBuffer = NULL;
	}
// 	if (m_pMediaFile)
// 	{
// 		delete m_pMediaFile;
// 		m_pMediaFile = NULL;
// 	}
	if (m_pVivsMediaFile)
	{
		m_pVivsMediaFile->Close();
		delete m_pVivsMediaFile;
		m_pVivsMediaFile = NULL;
	}
}
/*
//�����ļ���ʱ��ʹ�õ� 
int CMediaStream:: ThrReadFileProc(void *pParam)
{
	CMediaStream *pStream = (CMediaStream*)pParam;
	
	unsigned char *pSzFrameTmp =new unsigned char [1024*1024];
	int nFrameLen = 0;
	//��ǰ ʱ�� ��ʧ�Ķ���
	long lTimeElapse=0, lTimeLastRead=0, lTimeNow=0, lTimeStart=0;
	
	//�ļ���Ҫ �������� ʱ�䣬���ݱ��ټ���
	long lFileTimeNeedToRead=0;
	int64_t lFileTimeStamp=0, lFileTimeStampLast=0;
	bool bEndOfFile = false;
	while (pStream->m_state != eSS_Stop)
	{
		if (!pStream->m_pVivsMediaFile)
		{
			pStream->m_pThreadReadFile->Sleep(100);
			continue;
		}
		if (pStream->m_bFileSeek)
		{//ִ����ת
			pStream->m_pVivsMediaFile->SeekTo(pStream->m_lFileSeekToTimeStamp);
			lFileTimeStampLast = pStream->m_lFileSeekToTimeStamp;
			lFileTimeStamp = lFileTimeStampLast;
			pStream->m_bFileSeek = false;
			bEndOfFile = false;
		}
		if (pStream->m_state == eSS_Pause)
		{//��ͣ
			pStream->m_pThreadReadFile->Sleep(100);
			lTimeLastRead = timeGetTime();
			continue;
		}
		lTimeNow = timeGetTime();
		if (lTimeLastRead <= 0)
		{
			lTimeLastRead = lTimeNow;
		}

		lTimeElapse = lTimeNow - lTimeLastRead;
		lFileTimeNeedToRead = lTimeElapse*pStream->m_fPlaySpeed;

		//��ȡ ֱ�� ����ý���ļ���ʱ�� ����Ҫ�� ���ŵ�ʱ����ࡣ
		while (pStream->m_state != eSS_Stop &&
			pStream->m_state != eSS_Pause && 
			lFileTimeStamp-lFileTimeStampLast < lFileTimeNeedToRead 
			&& !bEndOfFile)
		{
			int nRet = pStream->m_pVivsMediaFile->ReadFrame((char*)pSzFrameTmp, nFrameLen, lFileTimeStamp);
			if (nFrameLen <= 0 || nRet<0)
			{//��ȡ���ļ���β�ˡ�
				bEndOfFile = true;
				break;
			}
		
			pStream->m_pMutexInputBuffer->Lock();
			pStream->m_pInputDataBuffer->Append((char*)pSzFrameTmp, nFrameLen);
			//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
			pStream->m_pMutexInputBuffer->Unlock();
		}
		if (lFileTimeStampLast/1000 != lFileTimeStamp/1000)
		{//�ϱ�ʱ��
			debug("play file time stamp : %d, second\n", (long)lFileTimeStamp/1000);
			if (pStream->m_cbPlayFileTimeStamp)
			{
				(pStream->m_cbPlayFileTimeStamp)(lFileTimeStamp, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}
		else if (bEndOfFile)
		{//�����ļ�����
			if (pStream->m_cbPlayFileTimeStamp)
			{
				pStream->m_cbPlayFileTimeStamp(-1, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}
		lFileTimeStampLast = lFileTimeStamp;
		lTimeLastRead = timeGetTime();
		pStream->m_pThreadReadFile->Sleep(100);
	}

	delete pSzFrameTmp;

	return 0;
}*/
int  CMediaStream::SetDecodeCb(MB_CbDecode cbDecode, void *pUserData, void *pReversed)
{

	m_cbDecode = cbDecode;
	m_pCbDecodeUserData = pUserData;
	m_pCbDecodeReversed = pReversed;

	return 0;
}

//�����ļ���ʱ��ʹ�õ� 
int CMediaStream:: ThrReadFileProc(void *pParam)
{
	CMediaStream *pStream = (CMediaStream*)pParam;
	
	unsigned char *pSzFrameTmp =new unsigned char [1024*1024];
	int nFrameLen = 0;
	//��ǰ ʱ�� ��ʧ�Ķ���
	long lTimeElapse=0, lTimeLastRead=0, lTimeNow=0  ;
	
	//�ļ���Ҫ �������� ʱ�䣬���ݱ��ټ���
	long  lTimeNeedToWait=0;
	int64_t lFileTimeStamp=0, lFileTimeStampLast=0,  lFileTimeNeedTo=0;


	bool bEndOfFile = false;

	while (pStream->m_state != eSS_Stop)
	{
		if (!pStream->m_pVivsMediaFile)
		{
			pStream->m_pThreadReadFile->Sleep(100);
			continue;
		}
		if (pStream->m_bFileSeek)
		{//ִ����ת
			pStream->m_pVivsMediaFile->SeekTo(pStream->m_lFileSeekToTimeStamp);

			lFileTimeStamp = pStream->m_lFileSeekToTimeStamp;
			lFileTimeStampLast = lFileTimeStamp;
			lTimeLastRead = timeGetTime();
			
			pStream->m_bFileSeek = false;
			bEndOfFile = false;
		}
		if (bEndOfFile)
		{
			pStream->m_pThreadReadFile->Sleep(100);
			continue;;
		}
		if (pStream->m_state == eSS_Pause)
		{//��ͣ
			pStream->m_pThreadReadFile->Sleep(100);
			lTimeLastRead = timeGetTime();

			continue;
		}
		//���㲥��ʱ��

		lTimeNow = timeGetTime();
		if (lTimeLastRead <= 0)
		{
			lTimeLastRead = lTimeNow;
		}
		lTimeElapse = lTimeNow - lTimeLastRead;
		if (lTimeElapse <= lTimeNeedToWait)
		{//��Ҫ���ߣ���֤ ʱ���ߵ� �ļ�ʱ���ǰ��ȥ
			pStream->m_pThreadReadFile->Sleep(10);
			continue;
		}
		//�ļ���Ҫ ��ȡ��ʱ��
		lFileTimeNeedTo = (lTimeElapse-lTimeNeedToWait )*pStream->m_fPlaySpeed;

		//debug("time stamp: %d, need to %d\n", (long)lFileTimeStamp, (long)lFileTimeNeedTo);

		lTimeLastRead = timeGetTime();
		//��ȡ ֱ�� ����ý���ļ���ʱ�� ����Ҫ�� ���ŵ�ʱ����ࡣ
		while (pStream->m_state != eSS_Stop &&
			pStream->m_state != eSS_Pause && 
			(lFileTimeStamp-lFileTimeStampLast) < lFileTimeNeedTo 
			&& !bEndOfFile)
		{
			int nRet = pStream->m_pVivsMediaFile->ReadFrame((char*)pSzFrameTmp, nFrameLen, lFileTimeStamp);
			if (nFrameLen <= 0 || nRet<0)
			{//��ȡ���ļ���β�ˡ�
				bEndOfFile = true;
				break;
			}
		
			pStream->m_pMutexInputBuffer->Lock();
			pStream->m_pInputDataBuffer->Append((char*)pSzFrameTmp, nFrameLen);
			//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
			pStream->m_pMutexInputBuffer->Unlock();
		}
		if (lFileTimeStampLast<=0)
		{
			lFileTimeStampLast = lFileTimeStamp;
		}
		//��Ҫ�ȴ���ʱ��
		lTimeNeedToWait = (lFileTimeStamp-lFileTimeStampLast-lFileTimeNeedTo)/pStream->m_fPlaySpeed;
		if (lTimeNeedToWait < 0)
			lTimeNeedToWait = 0;
		//ʱ��ص� ֪ͨ
		int64_t s64StartTime=0, s64EndTime=0;
		pStream->m_pVivsMediaFile->GetTime(s64StartTime, s64EndTime);
		if (lFileTimeStampLast/1000 != lFileTimeStamp/1000)
		{//�ϱ�ʱ��
			debug("play file time stamp : %d, second\n", (long)lFileTimeStamp/1000);
			if (pStream->m_cbPlayFileTimeStamp)
			{
				
				(pStream->m_cbPlayFileTimeStamp)((long)pStream, lFileTimeStamp, pStream->m_fPlaySpeed, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}
		else if (bEndOfFile)
		{//�����ļ�����
			if (pStream->m_cbPlayFileTimeStamp)
			{
				pStream->m_cbPlayFileTimeStamp((long)pStream, -1, pStream->m_fPlaySpeed, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}

		lFileTimeStampLast = lFileTimeStamp;
		pStream->m_pThreadReadFile->Sleep(10);
	}

	delete pSzFrameTmp;

	return 0;
}
#define BUFFER_LOCK_SIZE_LIMIT (10*1024)
//�������� ������
int  CMediaStream::ThrDecodeProc(void *pParam)
{
	CMediaStream *pStream = (CMediaStream*)pParam;

	
	while (pStream->m_state != eSS_Stop)
	{
		CPackageParser *pPackageParser = pStream->m_pPackageParser;
		if (!pPackageParser)
		{
			pStream->m_pThreadDecode->Sleep(10);
			continue;
		}
		//
		pStream->m_pMutexInputBuffer->Lock();
		

		int nPassedPos = 0;
		//nPassedPos = pPackageParser->InputData(pStream->m_pInputDataBuffer->GetData(), pStream->m_pInputDataBuffer->GetLength());
		while (pStream->m_state != eSS_Stop 
			&& pStream->m_pInputDataBuffer->GetLength()>0)
		{//������
			nPassedPos = pPackageParser->InputData(pStream->m_pInputDataBuffer->GetData(), pStream->m_pInputDataBuffer->GetLength());
			if (nPassedPos<=0)
				break;
			pPackageParser->DoFilter();
			pStream->m_pInputDataBuffer->Clear(0, nPassedPos);
			//debug("%s, parse passed %d, bytes, remain %d \n", __FUNCTION__, nPassedPos, pStream->m_pInputDataBuffer->GetLength());		
		}
		
		pStream->m_pMutexInputBuffer->Unlock();
		if (pStream->m_state == eSS_Stop )
			break;
#ifdef debug_parser0
		static FILE *pfile0 = 0;
		if (pfile0 == NULL)
		{
			pfile0 = fopen("F:\\tmp\\0.vd", "w+b");
		}
		if (pfile0)
		{
			fwrite(pStream->m_pInputDataBuffer->GetData(), nPassedPos, 1, pfile0);
			fflush(pfile0);
		}
#endif
		

		//ȡ�����������ݣ� ���뵽 ������
		CFilterPinBuffer *pParsedPkg = 0;
		
		pPackageParser->GetBuffer(&pParsedPkg, eFPT_Out);
		if (pParsedPkg)
		{
/*#define debug_parser1*/
#ifdef debug_parser1
			static FILE *pfile1 = 0;
			if (pfile1 == NULL)
			{
				pfile1 = fopen("F:\\tmp\\1.vd", "w+b");
			}
			if (pfile1)
			{
				fwrite(pParsedPkg->GetData(), pParsedPkg->GetLength(), 1, pfile1);
				fflush(pfile1);
			}
#endif
			//
		}
		else
		{
			//debug("get none buffer from parser--\n");
		}
		//
		//��ʼ����
		CDecoder *pVideoDecoder = pStream->m_pVideoDecoder;
		CDecoder *pAudioDecoder = pStream->m_pAudioDecoder;
// 		if (!pVideoDecoder)
// 		{
// 			pStream->m_pThreadDecode->Sleep(10);
// 			continue;
// 		}
		while (pParsedPkg/* && pStream->m_state != eSS_Stop*/ )
		{
			if (pParsedPkg->GetLength() > 0)
			{
				//��һ�� ����֮��� �� ���� �� decoder �� pin in ��
				if (pParsedPkg->m_nDataType < eFT_Audio)
				{//��Ƶ����
					pVideoDecoder->PutBuffer(pParsedPkg, eFPT_In);
					pVideoDecoder->DoFilter();

				}
				else
				{//��Ƶ����
					if (pAudioDecoder)
					{
						pAudioDecoder->PutBuffer(pParsedPkg, eFPT_In);
						pAudioDecoder->DoFilter();

						//pPackageParser->PutBuffer(pParsedPkg, eFPT_Out);
					}
					else
					{
						pPackageParser->PutBuffer(pParsedPkg, eFPT_Out, BUFFER_LOCK_SIZE_LIMIT);
					}
				}
			}
			else
			{
				pPackageParser->PutBuffer(pParsedPkg, eFPT_Out, BUFFER_LOCK_SIZE_LIMIT);
			}
			pParsedPkg = NULL;
			pPackageParser->GetBuffer(&pParsedPkg, eFPT_Out);
		}
		if (pParsedPkg)
		{//�رյ�ʱ����� 
			if (pParsedPkg->m_nDataType < eFT_Audio)
				pVideoDecoder->PutBuffer(pParsedPkg, eFPT_In);
			else
			{
				if (pAudioDecoder)
				{
					pAudioDecoder->PutBuffer(pParsedPkg, eFPT_In);
					//pPackageParser->PutBuffer(pParsedPkg, eFPT_Out);
				}
				else
				{
					pPackageParser->PutBuffer(pParsedPkg, eFPT_Out, BUFFER_LOCK_SIZE_LIMIT);
				}
			}
			pParsedPkg = NULL;
		}
		if (pStream->m_state == eSS_Stop )
		{
			break;
		}
		//

		//��ȡһ������filter��ʹ����� buffer ���뵽 parser ��pin out��
		pParsedPkg = 0;
		pVideoDecoder->GetBuffer(&pParsedPkg, eFPT_In);
		while (pParsedPkg != 0)
		{//��Ƶ��
			pParsedPkg->Clear();
			pPackageParser->PutBuffer(pParsedPkg, eFPT_Out, BUFFER_LOCK_SIZE_LIMIT);			
			//
			pParsedPkg = 0;
			pVideoDecoder->GetBuffer(&pParsedPkg, eFPT_In);
		}
		pParsedPkg = 0;
		if (pAudioDecoder)
		{//��Ƶ�� 
			pAudioDecoder->GetBuffer(&pParsedPkg, eFPT_In);
			while (pParsedPkg != 0)
			{//��Ƶ��
				pParsedPkg->Clear();
				pPackageParser->PutBuffer(pParsedPkg, eFPT_Out, BUFFER_LOCK_SIZE_LIMIT);			
				//
				pParsedPkg = 0;
				pAudioDecoder->GetBuffer(&pParsedPkg, eFPT_In);
			}
		}
		//
		pStream->m_pThreadDecode->Sleep(10);
	}
	pStream->m_bThreadInputExit = true;

	return 0;
}

int  CMediaStream::ThrRenderProc(void *pParam)
{
	CMediaStream *pStream = (CMediaStream*)pParam;
	while (pStream->m_state != eSS_Stop)
	{
		CRender *pVideoRender =pStream->m_pVideoRender;
		if (!pVideoRender)
		{
			pStream->m_pThreadRender->Sleep(10);
			continue;
		}
		//��Ƶ���� 
		//�� decoderȡһ�� buffer
		CFilterPinBuffer *pDecodeBuffer = 0;
		pStream->m_pVideoDecoder->GetBuffer(&pDecodeBuffer, eFPT_Out);
		//�������ݻص�
		if (pStream->m_cbDecode)
		{
			CVideoFramePinBufer *pVideoFrame = dynamic_cast<CVideoFramePinBufer*>(pDecodeBuffer);
			if (pVideoFrame)
			{//��Ƶ��
				pStream->m_cbDecode(pVideoFrame->GetData(), pVideoFrame->GetLength(), 
					pVideoFrame->m_nPixFormat, pVideoFrame->m_nWidth, pVideoFrame->m_nHeight,
					pStream->m_pCbDecodeUserData, pStream->m_pCbDecodeReversed);
			}
			else
			{//д��־��ʧ�ܼ�¼

			}
		}
		if (pStream->m_state == eSS_Stop)
			break;
		//��buffer ���뵽 render �н�����ʾ 
		if (pDecodeBuffer)
		{
			pVideoRender->PutBuffer(pDecodeBuffer, eFPT_In);
		}
		
		//render �ڲ������ؼ���
		pVideoRender->DoFilter();
		if (pStream->m_state == eSS_Stop)
			break;
		//
		CFilterPinBuffer *pRenderFreeBuffer = 0;
		//ȡһ�� �Ѿ��� renderʹ�õ� buffer �Żص� decoder ����
		pVideoRender->GetBuffer(&pRenderFreeBuffer, eFPT_In);
		if (pRenderFreeBuffer)
		{//�Ż� �� decoder
			pStream->m_pVideoDecoder->PutBuffer(pRenderFreeBuffer, eFPT_Out);
		}
		//��Ƶ����
		//�Ƿ񲥷� ����
		CDecoder *pAudioDecoder = pStream->m_pAudioDecoder;
		CRender  *pAudioRender = pStream->m_pAudioRender;
		if (pAudioDecoder && pAudioRender )
		{
			pDecodeBuffer = NULL;
			pAudioDecoder->GetBuffer(&pDecodeBuffer, eFPT_Out);
			if (pDecodeBuffer)
			{
				if (pStream->m_bPlayAudio)
					pAudioRender->PutBuffer(pDecodeBuffer, eFPT_In);
				else
					pAudioDecoder->PutBuffer(pDecodeBuffer, eFPT_Out);
			}
			pAudioRender->DoFilter();
			//ȡ ����������ݷŻص� ������
			pDecodeBuffer = NULL;
			pAudioRender->GetBuffer(&pDecodeBuffer, eFPT_In);
			if(pDecodeBuffer)
			{
				pAudioDecoder->PutBuffer(pDecodeBuffer, eFPT_Out);
			}
		}
		//
		pStream->m_pThreadRender->Sleep(10);
	}
	
	pStream->m_bThreadRenderExit = true;
	return 0;
}
int CMediaStream::Open(char *pInfo, long hWndShow)
{
	if (m_pThreadRender 
		|| m_pThreadDecode 
		|| m_pPackageParser
		|| m_pVideoDecoder
		|| m_pVideoRender)
	{
		return -1;
	}
	m_state = eSS_Run;
	int nRt = 0;
	nRt = CStreamBuilder::GetDefaultStreamBuilder()->BuildStream(pInfo, this, (HWND)hWndShow);
	if (nRt<0)
	{
		return -2;
	}
	if (!m_pVideoRender)
	{
		return 0;
	}
	nRt = m_pVideoRender->InitRender((HWND)hWndShow);
	if (nRt < 0)
	{
		debug("init ddraw to windows: %d, false\n", hWndShow);
	}
	else{
		debug("init ddraw to windows: %d, success\n", hWndShow);
	}
	
	m_pThreadDecode = new SThread::CThread();
	if (!m_pThreadDecode)
	{
		return -2;
	}
	
	nRt = m_pThreadDecode->Create(ThrDecodeProc, this);
	if (nRt != 0)
	{//
		return -3;
	}
	m_bThreadInputExit = false;

	m_pThreadRender = new SThread::CThread();
	if (!m_pThreadRender)
		return -4;
	nRt = m_pThreadRender->Create(ThrRenderProc, this);
	if (nRt != 0)
	{
		return -5;
	}
	m_bThreadRenderExit = false;
	

	return 0;
}
int CMediaStream::Open(sVivsStreamInfo *pStreamInfo, long hWndShow)
{
	if (m_pThreadRender 
		|| m_pThreadDecode 
		|| m_pPackageParser
		|| m_pVideoDecoder
		|| m_pVideoRender)
	{
		return -1;
	}
	m_state = eSS_Run;
	int nRt = 0;
	nRt = CStreamBuilder::GetDefaultStreamBuilder()->BuildStream(pStreamInfo, this, (HWND)hWndShow);
	if (nRt<0)
	{
		return -2;
	}
	nRt = m_pVideoRender->InitRender((HWND)hWndShow);
	if (nRt < 0)
	{
		debug("init ddraw to windows: %d, false\n", hWndShow);
	}
	else{
		debug("init ddraw to windows: %d, success\n", hWndShow);
	}

	m_pThreadDecode = new SThread::CThread();
	if (!m_pThreadDecode)
	{
		return -2;
	}

	nRt = m_pThreadDecode->Create(ThrDecodeProc, this);
	if (nRt != 0)
	{//
		return -3;
	}
	m_bThreadInputExit = false;

	m_pThreadRender = new SThread::CThread();
	if (!m_pThreadRender)
		return -4;
	nRt = m_pThreadRender->Create(ThrRenderProc, this);
	if (nRt != 0)
	{
		return -5;
	}
	m_bThreadRenderExit = false;

	return 0;
}
char *CMediaStream::CodecType2CodecInfo(int nCodecType)
{
	return VIVS_CODEC_H264;
}
int CMediaStream::SetPlayFileTimeCb(MB_CbPlayFileTimeStamp cbTime, void *pUserData, void *pReversed)
{
	m_cbPlayFileTimeStamp = cbTime;
	m_pCbPlayFileReversed = pReversed;
	m_pCbPlayFileUserData = pUserData;

	return 0;
}
int CMediaStream::OpenFile(char *pFile, long hWndShow, bool bPlayOrPause)
{
	
	if (m_pVivsMediaFile)
		return 1;
	
	m_pVivsMediaFile = new CVivsMediaFile();
	if (m_pVivsMediaFile->Open(pFile, true) <0)
	{
		return -1;
	}
	int nVideoCodec = m_pVivsMediaFile->GetVideoCodec();
	int nRet = 0;
	sVivsStreamInfo streamInfo;
	streamInfo.m_nStreamType = eVST_VivsH264;
	nRet = Open(&streamInfo, hWndShow);
	if (nRet < 0)
	{
		return -2;
	}
	if (m_pThreadReadFile)
	{
		m_pThreadReadFile->Stop();
		delete m_pThreadReadFile;
	}
	if (!bPlayOrPause)
	{
		m_state = eSS_Pause;
	}
	m_pThreadReadFile = new CThread();
	nRet = m_pThreadReadFile->Create(ThrReadFileProc, this);
	if (nRet < 0)
	{
		return -3;
	}

	return 0;
}

int CMediaStream::OpenFile( char *pVivsFile, char *pAviFile, bool bStartOrPause /*= true */ )
{

	if (m_pVivsMediaFile)
		return 1;
	int nRet = 0;

	m_pVivsMediaFile = new CVivsMediaFile();
	if (m_pVivsMediaFile->Open(pVivsFile, true) <0)
	{
		return -1;
	}
	m_pFfmpegFormatAvi = new CFfmpegFormat();

	nRet = m_pFfmpegFormatAvi->Create("avi", false);
	if (nRet < 0)
	{
		return -2;
	}
	sFfmpegStreamInfo streamInfo;
	streamInfo.m_nStreamType = eVST_VivsH264;
	streamInfo.m_nDataType = eFDT_Video;
	streamInfo.m_nCodecId = CODEC_ID_H264;
	streamInfo.m_videoInfo.m_nBitRate = 2*1024*1024;
	streamInfo.m_videoInfo.m_nGopSize = 25;
	streamInfo.m_videoInfo.m_nHeight = m_pVivsMediaFile->GetHeight();
	streamInfo.m_videoInfo.m_nWidth = m_pVivsMediaFile->GetWidth();
	streamInfo.m_videoInfo.m_nPixFormat = PIX_FMT_YUV420P;
	streamInfo.m_videoInfo.m_nCodecId = CODEC_ID_H264;
	streamInfo.m_videoInfo.m_nFps = 25;
	nRet = m_pFfmpegFormatAvi->AddStream(0, streamInfo);
	//
	nRet = m_pFfmpegFormatAvi->Open(pAviFile, AVIO_FLAG_READ);
	if (nRet < 0)
	{
		return -3;
	}

	sVivsStreamInfo vivsStreamInfo;
	vivsStreamInfo.m_nStreamType = eVST_VivsH264;
	vivsStreamInfo.m_nDataType = eFDT_Video;
	int nVideoCodec = m_pVivsMediaFile->GetVideoCodec();


	nRet  = CStreamBuilder::GetDefaultStreamBuilder()->AllocParser(&vivsStreamInfo, &m_pPackageParser);

	
	if (!m_pPackageParser)
	{
		return -2;
	}

	if (bStartOrPause)
	{
		m_state = eSS_Run;
	}
	else
	{
		m_state = eSS_Pause;
	}
	m_pThrTransFile2Avi = new CThread();
	nRet = m_pThrTransFile2Avi->Create(ThrFileTrans2AviProc, this);
	if (nRet < 0)
	{
		return -3;
	}


	return 0;
}

int CMediaStream::GetFileTime(int64_t &s64StartTime, int64_t &s64EndTime)
{
	if (!m_pVivsMediaFile)
		return -1;

	m_pVivsMediaFile->GetTime(s64StartTime, s64EndTime);

	return 0;
}
int CMediaStream::GetVideoCodec(int &nCodec)
{
	if (!m_pVivsMediaFile)
		return -1;

	nCodec = m_pVivsMediaFile->GetVideoCodec();

	return 0;
}
int CMediaStream::Close()
{
	m_state = eSS_Stop;

	if (m_pThreadRender)
	{	
		m_pThreadRender->Sleep(50);

		if (m_bThreadRenderExit)
		{
			debug("render thread exit\n");
		}
		else
		{
			debug("render thread not exit\n");
		}
		m_pThreadRender->Stop();
	
		delete m_pThreadRender;
		m_pThreadRender = NULL;
	}
	if (m_pThreadDecode)
	{	
		m_pThreadDecode->Sleep(50);
		if (m_bThreadInputExit)
		{
			debug("input thread exit\n");
		}
		else
		{
			debug("input thread not exit\n");
		}
		m_pThreadDecode->Stop();
	
		delete m_pThreadDecode;
		m_pThreadDecode = NULL;
	}
	if (m_pThreadReadFile)
	{
		m_pThreadReadFile->Stop();
		delete m_pThreadReadFile;
		m_pThreadReadFile = NULL;
	}
	if (m_pVivsMediaFile)
	{
		m_pVivsMediaFile->Close();
		delete m_pVivsMediaFile;
		m_pVivsMediaFile = NULL;
	}
	if (m_pPackageParser)
	{
		delete m_pPackageParser;
		m_pPackageParser = NULL;
	}
	if (m_pVideoRender)
	{
		delete m_pVideoRender;
		m_pVideoRender = NULL;
	}
	if (m_pVideoDecoder)
	{
		delete m_pVideoDecoder;
		m_pVideoDecoder = NULL;
	}

	return 0;
}
int CMediaStream::Start()
{
	m_state = eSS_Run;
	return 0;
}
int CMediaStream::Pause()
{
	m_state = eSS_Pause;
	return 0;
}
int CMediaStream::Resume()
{
	m_state = eSS_Run;
	return 0;
}
int CMediaStream::Stop()
{
	m_state = eSS_Stop;
	return 0;
}
int CMediaStream::SetPlaySpeed(float fSpeed)
{
	m_fPlaySpeed = fSpeed;
	return 0;
}
int CMediaStream::SetPlayPos(int64_t lTimeStamp)
{
	m_pMutexInputBuffer->Lock();
	m_bFileSeek = true;
	m_lFileSeekToTimeStamp = lTimeStamp;
	m_pMutexInputBuffer->Unlock();
	return 0;
}
int CMediaStream::InputData(char *pData, int nLen)
{
	if (m_state != eSS_Run && m_state != eSS_Pause)
		return -1;
	if (!m_pInputDataBuffer)
		return -1;
	//�����ļ����ýӿ���Ч
	if (m_pVivsMediaFile)
		return -2;
	//
	m_pMutexInputBuffer->Lock();
	int nRet = m_pInputDataBuffer->Append(pData, nLen);
	//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
	
	m_pMutexInputBuffer->Unlock();
	
	if (nRet <= 0)
	{
		nRet = 0;
	}

	return nRet;
}
int CMediaStream::SetInputBuffer(int nLen)
{
	if (!m_pInputDataBuffer)
		return -1;
	//�����ļ����ýӿ���Ч
	if (m_pVivsMediaFile)
		return -2;
	//
	m_pMutexInputBuffer->Lock();
	m_pInputDataBuffer->SetMaxSize(nLen);
	//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
	m_pMutexInputBuffer->Unlock();
	return 0;
}
int CMediaStream::SetDisplayBuffer(int nCount)
{
	if (!m_pVideoRender)
		return -1;
	m_nPlayBuffer = nCount;


	m_pVideoRender->SetPlayBuffer(nCount);

	return 0;
}
int CMediaStream::SetOsdText(int nIndex, char *pText)
{
	if (!m_pVideoRender)
		return -1;

	m_pVideoRender->SetOsdText(nIndex, pText);

	return 0;
}
int CMediaStream::SetOsdPos(int nIndex, int nX, int nY)
{
	if (!m_pVideoRender)
		return -1;
	
	m_pVideoRender->SetOsdPos(nIndex, nX, nY);

	return 0;
}
void CMediaStream::AttachParser(CPackageParser *pParser)
{
	m_pPackageParser = pParser;
}
// void CMediaStream::AttachParser(CDataFilter *pParser)
// {
// 	m_pPackageParser = pParser;
// }
void CMediaStream::AttachDecoder(CDecoder *pDecoder)
{
	m_pVideoDecoder = pDecoder;
}
void CMediaStream::AttachRender(CRender *pRender)
{
	m_pVideoRender = pRender;
}
void CMediaStream::AttachAudioRender(CRender *pRender)
{
	m_pAudioRender = pRender;
}
void CMediaStream::AttachAudioDecoder(CDecoder *pDecoder)
{
	m_pAudioDecoder = pDecoder;
}
/*
* ������ open������µ��á�
* ���̰߳�ȫ������
*/
int CMediaStream::SnapShot(char *pSaveFile) 
{
	if (!m_pVideoRender)
	{
		return -1;
	}
	
	return m_pVideoRender->SnapShot(pSaveFile);

}

int CMediaStream::Refresh()
{
	if (!m_pVideoRender)
	{
		return -1;
	}
	 m_pVideoRender->Refresh();
	 return 0;
}
//��������
int CMediaStream::SetOsdFont( int nIndex, char *pSzName, int nSize, long lColor )
{
	if (!m_pVideoRender)
	{
		return -1;
	}
	m_pVideoRender->SetOsdFont(nIndex, pSzName, nSize, lColor);
	return 0;
}
int CMediaStream::SetOsdShow(int nIndex, bool bShowOrHide)
{
	if (!m_pVideoRender)
	{
		return -1;
	}
	m_pVideoRender->SetOsdShow(nIndex, bShowOrHide);
	
	return 0;
}

int CMediaStream::PlayAudio()
{
	m_bPlayAudio = true;
	return 0;
}

int CMediaStream::StopAudio()
{

	m_bPlayAudio = false;
	return 0;
}

int  CMediaStream::ThrFileTrans2AviProc( void *pParam )
{
	CMediaStream *pMediaStream = (CMediaStream*)pParam;
	pMediaStream->m_pThrTransFile2Avi = 0;
	CMediaStream *pStream = (CMediaStream*)pParam;

	unsigned char *pSzFrameTmp =new unsigned char [1024*1024];
	int nFrameLen = 0;
/*	//��ǰ ʱ�� ��ʧ�Ķ���
	long lTimeElapse=0, lTimeLastRead=0, lTimeNow=0  ;

	//�ļ���Ҫ �������� ʱ�䣬���ݱ��ټ���
	long  lTimeNeedToWait=0;*/
	int64_t lFileTimeStamp=0, lFileTimeStampLast=0,  lFileTimeNeedTo=0;

	int64_t s64TimeStampAvi = 0;
	bool bEndOfFile = false;
	

	CPackageParser *pPackageParser = pMediaStream->m_pPackageParser;
	while (pStream->m_state != eSS_Stop)
	{
		if (pStream->m_state != eSS_Pause)
		{
			pStream->m_pThreadReadFile->Sleep(100);
			continue;
		}
		if (!pStream->m_pVivsMediaFile || !pMediaStream->m_pPackageParser)
		{
			pStream->m_pThreadReadFile->Sleep(100);
			continue;
		}
		pPackageParser = pMediaStream->m_pPackageParser;
		
		int nRet = pStream->m_pVivsMediaFile->ReadFrame((char*)pSzFrameTmp, nFrameLen, lFileTimeStamp);
		if (nFrameLen <= 0 || nRet<0)
		{//��ȡ���ļ���β�ˡ�
			bEndOfFile = true;

			if (pStream->m_cbPlayFileTimeStamp)
			{
				pStream->m_cbPlayFileTimeStamp((long)pStream, -1, pStream->m_fPlaySpeed ,  pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
			break;
		}
		pStream->m_pInputDataBuffer->Append((char*)pSzFrameTmp, nFrameLen);
		int nPassedPos = 0;
		//nPassedPos = pPackageParser->InputData(pStream->m_pInputDataBuffer->GetData(), pStream->m_pInputDataBuffer->GetLength());
		while (pStream->m_state != eSS_Stop 
			&& pStream->m_pInputDataBuffer->GetLength()>0)
		{//������
			nPassedPos = pPackageParser->InputData(pStream->m_pInputDataBuffer->GetData(), pStream->m_pInputDataBuffer->GetLength());
			if (nPassedPos<=0)
				break;
			pPackageParser->DoFilter();
			pStream->m_pInputDataBuffer->Clear(0, nPassedPos);
			//debug("%s, parse passed %d, bytes, remain %d \n", __FUNCTION__, nPassedPos, pStream->m_pInputDataBuffer->GetLength());		
		}
		//ȡ������������ ���浽 AVI�ļ�
		CFilterPinBuffer *pParsedPkg = 0;

		pPackageParser->GetBuffer(&pParsedPkg, eFPT_Out);

		while (pParsedPkg && pStream->m_state != eSS_Stop )
		{
			//��һ�� ����֮��� �� ���� �� decoder �� pin in ��
			if (pParsedPkg->m_nDataType < eFT_Audio)
			{//��Ƶ����
				s64TimeStampAvi++;
				pStream->m_pFfmpegFormatAvi->WriteFrame((char*)pParsedPkg->GetData(), pParsedPkg->GetLength(), s64TimeStampAvi);
			}
			else
			{//��Ƶ����
				//��ʱ����
			}
			
			//debug("write frame %d\n", pParsedPkg->GetLength());
			//����Ż�ȥ
			pPackageParser->PutBuffer(pParsedPkg, eFPT_Out);

			pParsedPkg = NULL;
			pPackageParser->GetBuffer(&pParsedPkg, eFPT_Out);
		}
		
		//ʱ��ص� ֪ͨ
		int64_t s64StartTime=0, s64EndTime=0;
		pStream->m_pVivsMediaFile->GetTime(s64StartTime, s64EndTime);
		if (lFileTimeStampLast/1000 != lFileTimeStamp/1000)
		{//�ϱ�ʱ��
			debug("play file time stamp : %d, second\n", (long)lFileTimeStamp/1000);
			if (pStream->m_cbPlayFileTimeStamp)
			{

				(pStream->m_cbPlayFileTimeStamp)((long)pStream, lFileTimeStamp,  pStream->m_fPlaySpeed , pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}
		else if (bEndOfFile)
		{//�����ļ�����
			if (pStream->m_cbPlayFileTimeStamp)
			{
				pStream->m_cbPlayFileTimeStamp((long)pStream, -1,  pStream->m_fPlaySpeed ,  pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
			}
		}
	}
	pStream->m_pFfmpegFormatAvi->Close();
	delete pSzFrameTmp;
	return 0;
}
