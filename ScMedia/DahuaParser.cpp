#include "StdAfx.h"
#include "DahuaParser.h"
#include "MediaSdkDef.h"
#include "Buffer.h"
#include "FilterPinBuffer.h"

using namespace SimpleCpp;
CDahuaParser::CDahuaParser(void)
: m_pBufferStream (NULL)
, m_nMinLen(DAHUA_PKG_MIN_LEN)
, m_bParseAvdataEnd(true)
, m_nFTMV(FTMV_FLAG)
{
	m_pBufferStreamTmp = new CFilterPinBuffer(2*1024*1024, 2*1024*1024);
}

CDahuaParser::~CDahuaParser(void)
{
	if (m_pBufferStream)
	{
		delete m_pBufferStream;
		m_pBufferStream = NULL;
	}

	if (m_pBufferStreamTmp)
	{
		delete m_pBufferStreamTmp;
		m_pBufferStreamTmp = NULL;
	}
}

int CDahuaParser::Open( int nBufferCount/*=100*/ )
{
	CPackageParser::Open();
	
	m_pBufferStream = new CBuffer();

	CFilterPin *pInOut = m_lstPinOut.at(0);
	if (pInOut)
	{
		pInOut->Clear();
		pInOut->CreateBuffer<CFilterPinBuffer>(nBufferCount);
	}

	return 0;
}
//ȥ��  ftmv, zxelec  �Ϳ�����.
int CDahuaParser::InputData( char *pData, int nLen )
{

	int nPassedPos = 0;
	int nAvDataEndType = eADET_NotEnd;
	
	m_pBufferStreamTmp->Clear();

	//���� FTMV avdataend 
	while (m_state == eFilterState_Run)
	{
		int nOutLen = 0;
		int nRtPassed = ParsePackage(pData+nPassedPos, nLen-nPassedPos, m_pBufferStreamTmp, nOutLen, nAvDataEndType);
		
		if ( (nRtPassed > 0 && nRtPassed <=nLen) )
		{
			nPassedPos += nRtPassed;
		}
		else
		{

			break;
		}

		if (nAvDataEndType != eADET_NotEnd)
		{//���ݵ�ĩβ,����Ƶ������Ƶ
			break;
		}
		
	}
	if (nAvDataEndType == eADET_NotEnd )
		return 0;

	if (m_pBufferStreamTmp->GetLength() <= 0)
		return nPassedPos;

#ifdef debug_hk_pkg
	static FILE *file = NULL;
	if (!file)
	{
		file =	fopen("f:\\tmp\\hk-1.hkpkg", "w+b");
	}
	if (file)
	{
		fwrite(m_pBufferStreamTmp->GetData(), m_pBufferStreamTmp->GetLength(), 1, file);
		fflush(file);
	}
#endif
	m_pBufferStream->Append((unsigned char*)m_pBufferStreamTmp->GetData(), m_pBufferStreamTmp->GetLength());
	m_pBufferStreamTmp->Clear();
	
	if (m_pBufferStream->GetLength()>DAHUA_PKG_MAX_LEN)
	{// warning
		m_pBufferStream->Clear();
		return nPassedPos;
	}
	
	//���뵽 ���buffer
	if (!m_bParseAvdataEnd && m_pBufferStream->GetLength() < DAHUA_PKG_MIN_LEN)
	{//����������֡�������,��Ҫ ȷ�� һ������Ƭ�ι�С.
		return nPassedPos;
	}

	CFilterPin *pPinOut = m_lstPinOut.at(0);
	if (!pPinOut)
	{
		return nPassedPos;
	}
	CFilterPinBuffer *pPinBufferOut = NULL;
	pPinOut->GetFreeBuffer(&pPinBufferOut);
	if (!pPinBufferOut)
		return nPassedPos;
	pPinBufferOut->Clear();

	pPinBufferOut->Append((char*)m_pBufferStream->GetData(), m_pBufferStream->GetLength());
	m_pBufferStream->Clear();

	pPinOut->PutPreparedBuffer(pPinBufferOut);

	return nPassedPos;
}

int CDahuaParser::ParsePackage( char *pData, int nLen, CFilterPinBuffer *pBufferOut, int &nOutLen, int &nAvDataEndType )
{
	int nMaxPos = nLen-FTMV_SIZE;
	int nPos0 = -1, nPos1=-1;
	//
	nOutLen = 0;
	// �ֲ� FTMV �� avdata end 
	for (int i=0; i<nMaxPos; i++)
	{
		//		int nTmp = *((int*)(pData+i) );
		if (m_nFTMV ==  *((int*)(pData+i)) )
		{// FTMV flag
			if (nPos0==-1)
			{
				nPos0 = i+FTMV_SIZE;
				continue;
			}
			nPos1 = i;
			//��� "zxel" ʱ�� ��
			if ( i>sizeof(sVivsTimeStamp)
				&& VIVS_TIME_FLAG == *((unsigned int*)(pData+i- sizeof(sVivsTimeStamp))) 
				)
			{
				nOutLen = nPos1-nPos0-sizeof(sVivsTimeStamp);
				pBufferOut->Append(pData+nPos0, nOutLen);
				nPos0 = nPos1+FTMV_SIZE;
				continue;
			}
			if (m_bParseAvdataEnd)
			{//�Ƴ� avdata end; [stream header]; 
				int nPktLen = nPos1-nPos0;
				if (nPktLen == sizeof(sAvStreamInfo)
					&& 0 == memcmp(pData+nPos0, GW_AV_STREAM_END_FLAG, GW_MAX_AV_STREAM_END_FLAG_LEN) )
				{// stream header 

					sAvStreamInfo *pStreamHeader = (sAvStreamInfo *)(pData + nPos0);
					if (GW_AV_DATA_TYPE_AUDIO == pStreamHeader->ucMediaType)
					{
						//nAvDataEndType = eADET_Audio;
					}
					else
					{
						//nAvDataEndType = eADET_Video;
					}
					//
					break;
				}
				else if (nPos1-nPos0 == sizeof(_sAvDataEnd))
				{//
					char *pAvdataEnd = pData + nPos1 - sizeof(_sAvDataEnd);
					if (memcmp(pAvdataEnd, GW_AV_END_FLAG, GW_AV_END_FLAG_LENGTH) == 0)
					{//�ҵ� avdataend���ӵ���
						nOutLen = 0;
						nPos0 = i+FTMV_SIZE;
						//nPos1 = -1;
						//���� avdata end�������в��ŵ�ʱ��osd��Ϣ
						memcpy(&m_avDataEnd, pAvdataEnd, sizeof(sAvDataEnd));
						nAvDataEndType = eADET_Video;
						//
						break;
					}
				}
				//���� avdata end��
				nOutLen = nPos1-nPos0;
				pBufferOut->Append(pData+nPos0, nOutLen);
				nPos0 = nPos1+FTMV_SIZE;
			}
			else{
				//
				nOutLen = nPos1-nPos0;

				pBufferOut->Append(pData+nPos0, nOutLen);
				nPos0 = nPos1+FTMV_SIZE;
			}
		}
	}
	if (!m_bParseAvdataEnd)
	{
		nAvDataEndType = eADET_Video;
	}
	//
	if (nPos1 == -1)
	{
		nPos1 = 0;
	}
	nAvDataEndType = eADET_Video;
	return nPos1;
}

void CDahuaParser::SetParseAvdataEnd( bool bParse/*=false*/ )
{
	m_bParseAvdataEnd = bParse;
}
