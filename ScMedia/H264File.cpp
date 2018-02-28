#include "StdAfx.h"
#include "H264File.h"
#include "MediaFileIndex.h"
#include "Buffer.h"
#include "FfmpegCodec.h"
#include <io.h>
#include <sys/stat.h>

extern "C"
{

#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avio.h"
}

CH264File::CH264File(void)
: m_pFile(NULL)
, m_pIndex(NULL)
, m_bExit(false)
, m_pFileRead(NULL)
, m_pFileFixRead(NULL)
, m_pBufferFixRead(NULL)
, m_s64FixFrameCount(0)
, m_s64FixTimestamp(0)
, m_s64FileTotalSize(0)
{

}

CH264File::~CH264File(void)
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
	if (m_pFileRead)
	{
		fclose(m_pFileRead);
		m_pFileRead = NULL;
	}
	if (m_pIndex)
	{
		m_pIndex->Close();
		delete m_pIndex;
		m_pIndex = NULL;
	}
	if (m_pFileFixRead)
	{
		fclose(m_pFileFixRead);
		m_pFileFixRead = NULL;
	}
	if (m_pBufferFixRead)
	{
		delete m_pBufferFixRead;
		m_pBufferFixRead = NULL;
	}
}
int CH264File::Open(char *pSzFile, int nOpenMode)
{
	if (m_pFile)
	{
		return -2;
	}
	if (m_pIndex)
	{
		return -3;
	}
	char szOpenFlag[32];
	memset(szOpenFlag, 0, sizeof(szOpenFlag));
	if (nOpenMode & AVIO_FLAG_WRITE)
	{
		sprintf(szOpenFlag, "w+b");
	}
	else
	{
		sprintf(szOpenFlag, "r+b");
	}
	m_pFile = fopen(pSzFile, szOpenFlag);
	if (!m_pFile)
		return -4;
	m_pFileRead = fopen(pSzFile, szOpenFlag);

	int nParseMaxLen = 1024*1024;
	char *pParseData = new char[nParseMaxLen];
	int nParseDatalen = 0;

	nParseDatalen = fread(pParseData, 1, nParseMaxLen, m_pFile);

	int nRet = 0;
	nRet = ProbInfo(pParseData, nParseDatalen);
	delete pParseData;
	if (nRet < 0)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
	else
	{
		strcpy(m_szFile, pSzFile);
		_fseeki64(m_pFile, 0, SEEK_SET);
		m_pIndex = new CMediaFileIndex();
		char szIndexFile[256];
		memset(szIndexFile, 0, sizeof(szIndexFile));
		sprintf(szIndexFile, "%s.idx",pSzFile);
		int nCheckIndex = 0;
		nCheckIndex = CheckIndex(pSzFile, szIndexFile);
		if (nCheckIndex < 0)
		{//��Ҫ�ؽ�����
			m_bNeedFix = true;
			//ɾ���ļ�
			remove(szIndexFile);
		}
		nRet = m_pIndex->Open( szIndexFile /*"f:\\1.index.db" */);
		if (nRet < 0)
		{
			debug("%s, open index false\n", __FUNCTION__);
		}
		else
		{
			debug("%s, open index success\n", __FUNCTION__);
		}
		if (nCheckIndex < 0)
		{
			//DoFixFile();
			//m_pIndex->Flush();
			m_pIndex->SetTimebase(m_nTimebaseNum, m_nTimebaseDen);
			m_pIndex->SetFps(m_nFps);
		}
		m_s64TotalTime = m_pIndex->GetTotalTime();
	}

	return nRet;
}
int CH264File::Close()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
	if (m_pFileRead)
	{
		fclose(m_pFileRead);
		m_pFileRead = NULL;
	}
	if (m_pIndex)
	{
		m_pIndex->Close();
		delete m_pIndex;
		m_pIndex = NULL;
	}
	return 0;
}

int CH264File::Write(char *pData, int nDataLen)
{
	return 0;
}
int CH264File::Read(char *pData, int &nBufferLen, int64 &s64Timestamp, int &nStreamId, int &nFrameType)
{
	if (!m_pIndex)
	{
		return -1;
	}
	int nId(0);
	int64   s64FramePosition(0);
	int nFrameLen(0);
	int nRet = 0;
	int nTries = 5;
	while (nTries--)
	{
		nRet = m_pIndex->Read(nId, s64Timestamp, nStreamId, nFrameType, s64FramePosition, NULL, nFrameLen);
		if (nRet < 0)
		{
			return -2;
		}
		else if (nRet == 0)
		{

		}
		else
		{
			break;
		}
	}
	if (nBufferLen < nFrameLen)
	{
		nBufferLen = nFrameLen;
		return -3;
	}
	_fseeki64(m_pFileRead, s64FramePosition, SEEK_SET);

	nBufferLen = fread(pData, 1, nFrameLen, m_pFileRead);

	m_s64CurrTimestamp = s64Timestamp;

	return nBufferLen;
}
int CH264File::Seek(int64 s64Time, int nSeekFlag)
{
	if (!m_pIndex)
	{
		return -1;
	}
	m_pIndex->Seek(s64Time, nSeekFlag);
	return 0;
}
int CH264File::SeekToTimestamp(int64 s64Timestamp, int nSeekFlag)
{
	if (!m_pIndex)
	{
		return -1;
	}
	m_pIndex->SeekToTimestamp(s64Timestamp, nSeekFlag);
	return 0;
}

int CH264File::ProbInfo( char *pData, int nLen )
{
	unsigned char *pDataTmp = (unsigned char *)pData;
	bool bFindNal = false;
	for (int i=0; i<nLen; i++)
	{
		int *pNalHeader = (int*)((unsigned char *)pData + i);
		if (*pNalHeader == H264_NAL_FLAG)
		{
			unsigned char nNalType = *(pData + i + 4);
			nNalType = (nNalType&0x1f);
			if (nNalType == 1
				|| nNalType == 5
				|| nNalType == 7
				|| nNalType == 8
				|| nNalType == 9)
			{
				bFindNal = true;
				break;
			}
		}
	}
	int nRet = 0;
	if (!bFindNal)
		nRet = -1;

	return nRet;
}

int CH264File::DoFixFile()
{
	if (!m_pFile)
		return -1;

	debug("%s++\n", __FUNCTION__);
	CBuffer bufferTmp(4*1024*1024, 4*1024*1024);
	bufferTmp.SetAllocSize(4*1024*1024);
	int nFrameCount = 0;
	bool bPrevIsParamNal = false;
	int64 s64FilePos = 0;
	int64 s64Timestamp = 0;
	int64 s64LastFramePos = -1;
	int   nFrameLen = 0;
	int   nLastFramType = eFFT_I;
	while (!m_bExit)
	{
		int nBufferLen = bufferTmp.GetLength()-5;
		unsigned char *pDataTmp = 0;
		int nPassed = 0;
		for (int i=0; i<nBufferLen; i++)
		{
			pDataTmp = bufferTmp.GetData() + i;
			if (*(int*)pDataTmp == H264_NAL_FLAG)
			{
				nFrameCount++;
				unsigned char nNalType = *(pDataTmp + 4);
				nNalType = (nNalType&0x1f);
				if (nNalType == 5
					)
				{//I֡
					//debug("frames: %d, I\n", nFrameCount);
					if (bPrevIsParamNal)
					{//��˴�����I֡��ʼ�� 7 8  5 ����һ������I֡��

					}
					else
					{//������һ��I֡
						int nLen=0;
						s64Timestamp = nFrameCount;// nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
						//m_pIndex->Write(nFrameCount, s64Timestamp, 0, eFFT_I, s64FilePos+i, 0, nLen);
						//s64Timestamp = nFrameCount;
						//д����һ�� ֡
						if (s64LastFramePos != -1)
						{
							nFrameLen = s64FilePos+i - s64LastFramePos;
							m_pIndex->Write(nFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
						}

						s64LastFramePos = s64FilePos+i;
						nLastFramType = eFFT_I;
					}
					bPrevIsParamNal = false;
				}
				else if (nNalType == 7
					|| nNalType == 8)
				{//��������
					//debug("frames: %d, I param\n", nFrameCount);
					//�� I֡��ʼ
					int nLen=0;
					s64Timestamp = nFrameCount;
					//s64Timestamp = nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
					if (bPrevIsParamNal == false)
					{//�Ѿ��ҵ�һ�� 7 ����д�롣 8 ��д
						//m_pIndex->Write(nFrameCount, s64Timestamp, 0, eFFT_I, s64FilePos+i, 0, nLen);
						if (s64LastFramePos != -1)
						{
							nFrameLen = s64FilePos+i - s64LastFramePos;
							m_pIndex->Write(nFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
						}
						s64LastFramePos = s64FilePos+i;
						nLastFramType = eFFT_I;
					}
					bPrevIsParamNal = true;
				}
				else
				{//��ͨ֡
					//debug("frames: %d, B P\n", nFrameCount);
					//s64Timestamp = nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
					s64Timestamp = nFrameCount;
					//д����һ�� ֡
					if (s64LastFramePos != -1)
					{
						nFrameLen = s64FilePos+i - s64LastFramePos;
						m_pIndex->Write(nFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
					}

					s64LastFramePos = s64FilePos+i;
					nLastFramType = eFFT_P;
					bPrevIsParamNal = false;
				}
				nPassed = i;
			}
			
		}
		bufferTmp.Clear(0, nPassed);

		int nRead =0;
		s64FilePos = _ftelli64(m_pFile) - bufferTmp.GetLength();
		nRead = fread(bufferTmp.GetData()+bufferTmp.GetLength(), 1, bufferTmp.GetAllocSize()-bufferTmp.GetLength(), m_pFile );

		if (nRead <= 0)
		{
			break;
		}
		bufferTmp.SetUsed(bufferTmp.GetLength() + nRead);
	}
	m_pIndex->SetComplete(true);
	struct _stat64  buf;
	int result;
	char timebuf[26];
	errno_t err;
	// ��ý���ļ����Ȳ����
	result = _stati64( m_szFile, &buf );
	m_pIndex->SetFileSize(buf.st_size);

	m_s64TotalTime = s64Timestamp*1000*m_nTimebaseNum/m_nTimebaseDen;
	debug("%s--, total frames: %d\n", __FUNCTION__, nFrameCount);
	return 0;
}

int CH264File::DoFixFile( int64 &s64Total, int64 &s64Pos )
{
	if (!m_bNeedFix)
	{
		return -3;
	}
	if (!m_pFileFixRead)
	{
		m_pFileFixRead = fopen(m_szFile, "r+b");
	}
	if (!m_pFileFixRead)
		return -1;
	
	if (!m_pIndex)
	{
		return -2;
	}

	if (!m_pBufferFixRead)
	{
		m_pBufferFixRead = new CBuffer(4*1024*1024, 4*1024*1024);
		m_pBufferFixRead->SetAllocSize(4*1024*1024);
	}
	if (feof(m_pFileFixRead))
	{//�ļ�������
		return -4;
	}
	//CBuffer bufferTmp(4*1024*1024, 4*1024*1024);
	//bufferTmp.SetAllocSize(4*1024*1024);

	bool bPrevIsParamNal = false;
	int64 s64FilePos = 0;
	int64 s64Timestamp = 0;
	int64 s64LastFramePos = -1;
	int   nFrameLen = 0;
	int   nLastFramType = eFFT_I;
	bool  bFileEnd = false;

	int nPassed = 0;
	while (1)
	{
		int nRead =0;
		s64FilePos = _ftelli64(m_pFile) - m_pBufferFixRead->GetLength();
		nRead = fread(m_pBufferFixRead->GetData()+m_pBufferFixRead->GetLength(), 1, m_pBufferFixRead->GetAllocSize()-m_pBufferFixRead->GetLength(), m_pFile );

		m_pBufferFixRead->SetUsed(m_pBufferFixRead->GetLength() + nRead);

		int nBufferLen = m_pBufferFixRead->GetLength()-5;
		unsigned char *pDataTmp = 0;
		nPassed = 0;
		bool bFindFrameEnd = false;
		int nCurFrameTye = eFFT_P;
		for (int i=0; i<nBufferLen; i++)
		{
			pDataTmp = m_pBufferFixRead->GetData() + i;
			if (*(int*)pDataTmp == H264_NAL_FLAG)
			{
				bFindFrameEnd = false;
				unsigned char nNalType = *(pDataTmp + 4);
				nNalType = (nNalType&0x1f);
				if (nNalType == 1
					|| nNalType == 2
					|| nNalType == 3
					|| nNalType == 4)
				{//P֡
					if (bPrevIsParamNal )
					{//��һ���ǲ���֡���򻹵ü���ɨ�衣��֪����֡��֡��������
						nLastFramType = eFFT_P;
						bPrevIsParamNal = false;
					}
					else{//debug("frames: %d, B P\n", nFrameCount);
						//�ҵ�һ�� p��ʼ����һ֡����д�롣
						nCurFrameTye = eFFT_P;
						bFindFrameEnd = true;
					}
					m_s64FixFrameCount++;
				}
				else if (nNalType == 5)
				{//I ֡
					if (bPrevIsParamNal )
					{//��һ���ǲ���֡���򻹵ü���ɨ�衣��֪����֡��֡��������
						nLastFramType = eFFT_I;
						bPrevIsParamNal = false;
					}
					else
					{//s64Timestamp = nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
						nCurFrameTye = eFFT_I;
						bFindFrameEnd = true;
					}
					m_s64FixFrameCount++;
				}
				else
				{//�������������ݵ�. ��ʱ���԰���һ֡��Ƶ����д��
					//debug("frames: %d, I param\n", nFrameCount);
					if (bPrevIsParamNal == false)
					{//֮ǰ������ͨ֡
						bFindFrameEnd = true;
						bPrevIsParamNal = true;
						nCurFrameTye = eFFT_Param;
					}
					else
					{//֮ǰһֱ�ǲ���֡
						bPrevIsParamNal = true;
					}

				}
				if (bFindFrameEnd)
				{//�ҵ�һ�� ֡�Ľ���������д��
					s64Timestamp = m_s64FixFrameCount*(m_nTimebaseDen/m_nTimebaseNum/(m_nFps) );;
					//д����һ�� ֡
					if (s64LastFramePos != -1)
					{
						nFrameLen = s64FilePos+i - s64LastFramePos;
						m_pIndex->Write(m_s64FixFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
						nPassed = i;
					}

					s64LastFramePos = s64FilePos+i;
					nLastFramType = nCurFrameTye;
				}
				/*if (nNalType == 5
					)
				{//I֡
					//debug("frames: %d, I\n", nFrameCount);
					if (bPrevIsParamNal)
					{//��˴�����I֡��ʼ�� 6 7 8  5 ����һ������I֡��

					}
					else
					{//������һ��I֡
						int nLen=0;
						//s64Timestamp = m_s64FixFrameCount;// nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
						s64Timestamp = m_s64FixFrameCount*(m_nTimebaseDen/m_nTimebaseNum/(m_nFps) );;
						//m_pIndex->Write(nFrameCount, s64Timestamp, 0, eFFT_I, s64FilePos+i, 0, nLen);
						//s64Timestamp = nFrameCount;
						//д����һ�� ֡
						if (s64LastFramePos != -1)
						{
							nFrameLen = s64FilePos+i - s64LastFramePos;
							m_pIndex->Write(m_s64FixFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
							nPassed = i;
						}

						s64LastFramePos = s64FilePos+i;
						nLastFramType = eFFT_I;
					}
					bPrevIsParamNal = false;
				}
				else if (nNalType == 7
					|| nNalType == 8
					|| nNalType == 6)
				{//��������
					//debug("frames: %d, I param\n", nFrameCount);
					//�� I֡��ʼ
					int nLen=0;
					//s64Timestamp = m_s64FixFrameCount;
					s64Timestamp = m_s64FixFrameCount*(m_nTimebaseDen/m_nTimebaseNum/(m_nFps) );;
					//s64Timestamp = nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
					if (bPrevIsParamNal == false)
					{//�Ѿ��ҵ�һ�� 7 ����д�롣 8 ��д
						//m_pIndex->Write(nFrameCount, s64Timestamp, 0, eFFT_I, s64FilePos+i, 0, nLen);
						if (s64LastFramePos != -1)
						{
							nFrameLen = s64FilePos+i - s64LastFramePos;
							m_pIndex->Write(m_s64FixFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
							nPassed = i;
						}
						s64LastFramePos = s64FilePos+i;
						nLastFramType = eFFT_I;
					}
					bPrevIsParamNal = true;
				}
				else
				{//��ͨ֡
					//debug("frames: %d, B P\n", nFrameCount);
					//s64Timestamp = nFrameCount*1000*m_nTimebaseNum/m_nTimebaseDen;
					s64Timestamp = m_s64FixFrameCount*(m_nTimebaseDen/m_nTimebaseNum/(m_nFps) );;
					//д����һ�� ֡
					if (s64LastFramePos != -1)
					{
						nFrameLen = s64FilePos+i - s64LastFramePos;
						m_pIndex->Write(m_s64FixFrameCount, s64Timestamp, 0, nLastFramType, s64LastFramePos, 0, nFrameLen);
						nPassed = i;
					}

					s64LastFramePos = s64FilePos+i;
					nLastFramType = eFFT_P;
					bPrevIsParamNal = false;
				}*/
			}

		}
		m_pBufferFixRead->Clear(0, nPassed);

		if (nRead <= 0 )
		{//���԰����һ֡д����Ƶ������
			//
			//
			bFileEnd = true;
		}
		break;
	}
	struct _stat64  buf;
	// ��ý���ļ����ȣ� �Ƿ���������ж��ļ��Ƿ��滻�����޸Ĺ�
	int nRet(0);
	nRet = _stati64( m_szFile, &buf );
	m_s64FileTotalSize = buf.st_size;

	if (bFileEnd)
	{//�����������
		m_pIndex->SetComplete(true);
		m_pIndex->SetFileSize(buf.st_size);
		m_pIndex->SetFps(m_nFps);
		m_pIndex->SetTimebase(m_nTimebaseNum, m_nTimebaseDen);

		m_pIndex->Flush();
		m_pIndex->Save();

		s64Total = m_s64FileTotalSize;
		s64Pos = s64Total;
	}
	else
	{
		s64Total = m_s64FileTotalSize;
		s64Pos = (s64FilePos + nPassed);
	}
	m_s64TotalTime = s64Timestamp*1000*m_nTimebaseNum/m_nTimebaseDen;
	//debug("%s--, current frames: %d\n", __FUNCTION__, m_s64FixFrameCount);
	return 0;
}

//����Ƿ��������
//�ļ��޸����ڲ����������������޸�
int CH264File::CheckIndex(char *pSzMediaFile, char *pSzIndexFile)
{
	if (pSzIndexFile == NULL
		|| strlen(pSzIndexFile) <= 0)
	{
		return -1;
	}
	int nRet = 0;
	nRet = access(pSzIndexFile, 0);
	if (nRet < 0)
	{//������
		return -1;
	}
	//�Լ���Ӧ���ļ�ʱ��

	//������ݿ������ԣ��Լ���Ӧ���ļ�ʱ��
	CMediaFileIndex indexFile;
	indexFile.Open(pSzIndexFile);
	if (!indexFile.IsComplete())
	{
		return -1;
	}
	//
	//�ļ�����
	struct _stat64 buf;
	int result;
	char timebuf[26];
	errno_t err;
	// ��ý���ļ����Ȳ����
	result = _stati64( pSzMediaFile, &buf );
	if (buf.st_size != indexFile.GetFileSize())
	{
		return -2;
	}
	m_s64FileTotalSize = buf.st_size;


	return 0;
}
