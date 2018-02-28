#include "StdAfx.h"
#include "SourceVivsFile.h"
#include "Buffer.h"
#include "VivsMediaFile.h"

#ifdef WIN32
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <time.h>
#endif

CSourceVivsFile::CSourceVivsFile(void)
:CSourceFilter()
, m_pVivsMediaFile(NULL)
, m_bEndOfFile(true)
{
	strcpy(m_szName, "vivs file");
	strcpy(m_szType, "vivs file");
}

CSourceVivsFile::~CSourceVivsFile(void)
{
	if (m_pBufferRead)
	{
		delete m_pBufferRead;
		m_pBufferRead = NULL;
	}
}

int CSourceVivsFile::DoFilter()
{
	//��ȡ�ļ����뵽 outpin

	CFilterPin *pPinOut = NULL;
	pPinOut = m_lstPinOut.at(0);
	if (!pPinOut)
		return -1;
	CFilterPinBuffer *pPinBuffer = NULL;
	//��ȡ����
	//ReadFrame();
	ReadOneFrame();
	//
	// ȡ����ȥһ�� ���ӵ� pin 
	if (m_pBufferRead->GetLength()>0)
	{
		pPinOut->GetFreeBuffer(&pPinBuffer);
		if (pPinBuffer)
		{
			int nAppend = 0;
			if (pPinBuffer->GetMaxSize() < m_pBufferRead->GetLength())
			{
				pPinBuffer->SetMaxSize(m_pBufferRead->GetLength());
			}
			nAppend = pPinBuffer->Append((char*)m_pBufferRead->GetData(), m_pBufferRead->GetLength());
			if (nAppend <= 0)
			{
				debug("source append to out pin <= 0\n");
			}
			m_pBufferRead->Clear(0, nAppend);
			pPinOut->PutPreparedBuffer(pPinBuffer);
		}
		else
		{
			debug("source filter, out buffer busy\n");
		}
	}
	else
	{
		debug("source filter, read buffer is empty\n");
	}
	Sleep(40);
	//
	return CSourceFilter::DoFilter();
}

int CSourceVivsFile::Init()
{
	m_pBufferRead = new CBuffer();
	return CSourceFilter::Init();
}
int CSourceVivsFile::Open(char *pUrl)
{
	if (m_pVivsMediaFile)
		return -1;
	m_pVivsMediaFile = new CVivsMediaFile();
	if (m_pVivsMediaFile->Open(pUrl, true) <0)
	{
		return -1;
	}
	m_bEndOfFile = false;
	return 0;
}
int CSourceVivsFile::Close()
{
	if (m_pVivsMediaFile)
	{
		m_pVivsMediaFile->Close();
		delete m_pVivsMediaFile;
		m_pVivsMediaFile = NULL;
	}
	return 0;
}
int CSourceVivsFile::ReadOneFrame()
{
	if (!m_pVivsMediaFile)
		return -1;
	if (m_pBufferRead->GetMaxSize()-m_pBufferRead->GetLength() <10* 1024 )
		return 0;
	int nFrameLen = 1024*1024;
	unsigned char *pSzFrameTmp =new unsigned char [nFrameLen];

	int nRet = m_pVivsMediaFile->ReadFrame((char*)pSzFrameTmp, nFrameLen, m_s64TimeStamp);
	if (nFrameLen <= 0 || nRet<0)
	{//��ȡ���ļ���β�ˡ�
		m_bEndOfFile = true;
		//break;
	}

	//pStream->m_pMutexInputBuffer->Lock();
	if (nFrameLen > 0)
	{
		m_pBufferRead->Append((unsigned char*)pSzFrameTmp, nFrameLen);
	}

#ifdef debug_source
	static FILE *pfileSource = 0;
	if (pfileSource == NULL)
	{
		pfileSource = fopen("F:\\tmp\\vivs_h264-source.vd", "w+b");
	}
	if (pfileSource)
	{
		fwrite(pSzFrameTmp, nFrameLen, 1, pfileSource);
		fflush(pfileSource);
	}
#endif
	//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
	//pStream->m_pMutexInputBuffer->Unlock();

	delete pSzFrameTmp;

	return 0;
}
int CSourceVivsFile::ReadFrame()
{
	if (!m_pVivsMediaFile)
		return -1;
	if (m_bSeek)
	{//ִ����ת
		m_pVivsMediaFile->SeekTo(m_s64SeekTime);

		m_s64TimeStamp = m_s64SeekTime;
		m_s64TimeLastTimeStamp = m_s64TimeStamp;
		m_s64TimeLastRead = timeGetTime();

		m_bSeek = false;
		m_bEndOfFile = false;
	}
	if (m_bEndOfFile)
	{
		return -1;;
	}
	if (m_state == eFS_Pause)
	{//��ͣ
		//pStream->m_pThreadReadFile->Sleep(100);
		m_s64TimeLastRead = timeGetTime();
		return -1;
	}
	//���㲥��ʱ��

	long lTimeNow = timeGetTime();
	if (m_s64TimeLastRead <= 0)
	{
		m_s64TimeLastRead = lTimeNow;
	}
	long lTimeElapse = lTimeNow - (long)m_s64TimeLastRead;
	if (lTimeElapse <= (long)m_s64imeNeedToWait)
	{//��Ҫ���ߣ���֤ ʱ���ߵ� �ļ�ʱ���ǰ��ȥ
		return -1;
	}
	//�ļ���Ҫ ��ȡ��ʱ��
	long lFileTimeNeedTo = (lTimeElapse-(long)m_s64imeNeedToWait )*m_fSpeed;

	//debug("time stamp: %d, need to %d\n", (long)lFileTimeStamp, (long)lFileTimeNeedTo);

	m_s64TimeLastRead = timeGetTime();
	//��ȡ ֱ�� ����ý���ļ���ʱ�� ����Ҫ�� ���ŵ�ʱ����ࡣ
	int nFrameLen = 1024*1024;
	unsigned char *pSzFrameTmp =new unsigned char [nFrameLen];
	while (m_state != eFS_Stop &&
		m_state != eFS_Pause && 
		(m_s64TimeStamp-m_s64TimeLastTimeStamp) < lFileTimeNeedTo 
		&& !m_bEndOfFile)
	{
		int nRet = m_pVivsMediaFile->ReadFrame((char*)pSzFrameTmp, nFrameLen, m_s64TimeStamp);
		if (nFrameLen <= 0 || nRet<0)
		{//��ȡ���ļ���β�ˡ�
			m_bEndOfFile = true;
			debug("%s: read frame: %d end..... \n", __FUNCTION__, nFrameLen);
			break;
		}
		debug("%s: read frame: %d \n", __FUNCTION__, nFrameLen);
		//pStream->m_pMutexInputBuffer->Lock();
		m_pBufferRead->Append((unsigned char*)pSzFrameTmp, nFrameLen);
		//debug("%s, input data buffer len: %d\n", __FUNCTION__, m_pInputDataBuffer->GetLength());
		//pStream->m_pMutexInputBuffer->Unlock();
	}
	delete pSzFrameTmp;
	if (m_s64TimeLastTimeStamp<=0)
	{
		m_s64TimeLastTimeStamp = m_s64TimeStamp;
	}
	//��Ҫ�ȴ���ʱ��
	m_s64imeNeedToWait = (m_s64TimeStamp-m_s64TimeLastTimeStamp-lFileTimeNeedTo)/m_fSpeed;
	if (m_s64imeNeedToWait < 0)
		m_s64imeNeedToWait = 0;
	//ʱ��ص� ֪ͨ
	int64_t s64StartTime=0, s64EndTime=0;
	m_pVivsMediaFile->GetTime(s64StartTime, s64EndTime);
	if (m_s64TimeLastTimeStamp/1000 != m_s64TimeStamp/1000)
	{//�ϱ�ʱ��
		debug("play file time stamp : %d, %d-%d second\n", (long)m_s64TimeStamp/1000, (long)s64StartTime/1000, (long)s64EndTime/1000);
		/*if (m_cbPlayFileTimeStamp)
		{

			(pStream->m_cbPlayFileTimeStamp)((long)pStream, lFileTimeStamp, pStream->m_fPlaySpeed, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
		}*/
	}
	else if (m_bEndOfFile)
	{//�����ļ�����
		debug("play file time stamp : %d, second\n", (long)m_s64TimeStamp/1000);
		/*if (m_cbPlayFileTimeStamp)
		{
			m_cbPlayFileTimeStamp((long)pStream, -1, pStream->m_fPlaySpeed, pStream->m_pCbPlayFileUserData, pStream->m_pCbPlayFileReversed);
		}
		*/
	}

	m_s64TimeLastTimeStamp = m_s64TimeStamp;

	return 0;
}