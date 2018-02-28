#include "StdAfx.h"
#include "PsPackage.h"
#include "Buffer.h"

#define printf
#ifndef TRACE
#define TRACE
#endif

#define MAX_STREAM_BUFFER (2*1024*1024)
CPsPackage::CPsPackage(int nW, int nH, int nFPS, int nBitRate)
:m_pBufferH264(NULL)
, m_nTimeStamp(0)
, m_nW(nW)
, m_nH(nH)
, m_nFPS(nFPS)
, m_nBitRate(nBitRate)
{
	m_pBufferH264 = new CBuffer(MAX_STREAM_BUFFER);
}

CPsPackage::~CPsPackage(void)
{
	if (m_pBufferH264)
	{
		delete m_pBufferH264;
		m_pBufferH264 = NULL;
	}
}
//�� ps�����.���Ϊ ��׼ h264  
int CPsPackage::UnPackage(unsigned char *pPsStream, int nLen, unsigned char *pH264Stream, int &nLenOut)
{
	m_pBufferH264->Append(pPsStream, nLen);
	//
	bool bFindPsHeader = false;
	char *pPos = (char*)m_pBufferH264->GetData();
	int nMaxPos = m_pBufferH264->GetLength() - PS_HEADER_FLAG_LEN; 
	nLenOut = 0;
	int nPesLen = 0;
	int nValidPos = 0;
	for (int i=0; i<nMaxPos; /*i++*/)
	{
		//
		pPos = (char*)m_pBufferH264->GetData() + i;
		unsigned int *pFlag  = (unsigned int *)pPos;
		//�ж� �Ƿ��� ps ͷ���. sys, psm, pes 
		if (*pFlag == PS_HEADER_FLAG)
		{//ps header
			if (nMaxPos-i < PS_HEADER_FLAG_LEN)
			{//���ݳ��Ȳ���
				break;
			}
			PS_HEADER_LEN;
			i += PS_HEADER_LEN;
			nPesLen = 0;
		}else if (*pFlag == PS_SYS_FLAG)
		{// sys header
			if (nMaxPos-i < PS_SYS_LEN)
			{//���ݳ��Ȳ���
				break;
			}
			i += PS_SYS_LEN;
			nPesLen = 0;
		}else if (*pFlag == PS_PSM_FLAG)
		{//psm header
			if (nMaxPos-i < PS_PSM_FLAG)
			{//���ݳ��Ȳ���
				break;
			}
			i += PS_PSM_LEN;
			nPesLen = 0;
		}else if ( (*pFlag&0xff)>>8 == PS_PES_HEADER_FLAG )
		{// pes flag len
			int nPesHeaderStart = i;
			//���ݳ��Ȳ���
			if (nMaxPos-i < 16)
			{//���ݲ���
				break;
			}
			i += 3;
			int nPesHeahderLen = 0;
			// streamid 1bytes
			i += 1;
			// 5,6 pes package len 
			i += 2;
			nPesLen =  *(pPos+4)<<8|*(pPos+5);
			// 7  optional PES HEADER�ĵ�һ���ֽڡ�Ŀǰ��д����ֵ���Ժ�Ӧ����չ�ɿ����õġ�
			i += 1;
			//header len
			char *pPesHeaderLen = pPos+i;
			nPesHeahderLen = *pPesHeaderLen;
			i += 1;
			// 8 ps ts
			unsigned int *pPsTsFlag = (unsigned int*)(pPos + 7);
			i += 1;
			if (*pPsTsFlag & OPTIONAL_FIELDS_PTS_DTS)
			{
				i+=10;
			}
			else if (*pPsTsFlag & OPTIONAL_FIELDS_ONLY_PTS)
			{
				i+=5;
			}else{
				i+=5;
			}
			//����headerlen 16 (�ֽ�)
			i = nPesHeaderStart + nPesHeahderLen/* - (i-)*/;
			// pes ����
			//nPesLen - nPesHeahderLen;
			if (nMaxPos-i < nPesLen)
			{//���ݲ���
				break;
			}
			//
			memcpy(pH264Stream, m_pBufferH264->GetData()+i, nPesLen-nPesHeahderLen );
			nLenOut += nPesLen-nPesHeahderLen;
			//
			i += nPesLen-nPesHeahderLen;
			//��¼��Ч����λ��,��������ɾ�� ʹ�ù�������
			nValidPos = i;
		}
		else
		{//���Ǳ��,������
			i++;
		}
		//
	}
	m_pBufferH264->Clear(0, nValidPos);


	return 0;
}
int CPsPackage::UnPackage(unsigned char *pPsStream, int nLen, CBuffer *pBufferH264)
{
	if (m_pBufferH264->GetLength() > MAX_STREAM_BUFFER)
	{
		m_pBufferH264->Clear();
	}
	m_pBufferH264->Append(pPsStream, nLen);
	//
	bool bFindPsHeader = false;
	char *pPos = (char*)m_pBufferH264->GetData();
	int nMaxPos = m_pBufferH264->GetLength() - PS_HEADER_FLAG_LEN; 
	
	int nPesLen = 0;
	int nPassedPos = 0;
	for (int i=0; i<nMaxPos; /*i++*/)
	{
		//
		pPos = (char*)m_pBufferH264->GetData() + i;
		unsigned int *pFlag  = (unsigned int *)pPos;
		//�ж� �Ƿ��� ps ͷ���. sys, psm, pes 
		if (*pFlag == PS_HEADER_FLAG)
		{//ps header
			if (nMaxPos-i < PS_HEADER_FLAG_LEN)
			{//���ݳ��Ȳ���
				break;
			}
			PS_HEADER_LEN;
			i += PS_HEADER_LEN;
			nPesLen = 0;
		}else if (*pFlag == PS_SYS_FLAG)
		{// sys header
			if (nMaxPos-i < PS_SYS_LEN)
			{//���ݳ��Ȳ���
				break;
			}
			i += PS_SYS_LEN;
			nPesLen = 0;
		}else if (*pFlag == PS_PSM_FLAG)
		{//psm header
			if (nMaxPos-i < PS_PSM_LEN)
			{//���ݳ��Ȳ���
				break;
			}
			i += PS_PSM_LEN;
			nPesLen = 0;
 		}
//			else if ()
// 		{//���� h264 �� ���� 00 00 00 1 
// 
// 		}
		else if ( (*pFlag&0x00ff0000)<<8 == PS_PES_HEADER_FLAG )
		{// pes flag len
			int nPesHeaderStart = i;
			unsigned char *pPesStart = (unsigned char *)pFlag;
			int nPesPos = 0;
			//���ݳ��Ȳ���
			if (nMaxPos-i < 16)
			{//���ݲ���
				break;
			}
			nPesPos += 3;
			int nPesHeaderDataLen = 0;
			// streamid 1bytes
			nPesPos += 1;
			// 5,6 pes package len 
			nPesPos += 2;
			nPesLen = (*((unsigned char *)pPesStart+ 4)<<8|*((unsigned char *)pPesStart+ 5))&0xffff;
			// 7  optional PES HEADER�ĵ�һ���ֽڡ�Ŀǰ��д����ֵ���Ժ�Ӧ����չ�ɿ����õġ�
			nPesPos += 1;
			//pes header  data len, ����� �ֽ� ֮������ݳ���, ps ts + ff ���,  9 �ֽ� ֮���.
			//9, header data len, ����headerlen 16 (�ֽ�)
			unsigned char *pPesHeaderLen = (unsigned char*)pPesStart + 8;
			nPesHeaderDataLen = *pPesHeaderLen;
			nPesPos += 1;
			// 9 ps ts
			unsigned int *pPsTsFlag = (unsigned int*)(pPesStart + 9);
			nPesPos += 1;
			if (*pPsTsFlag & OPTIONAL_FIELDS_PTS_DTS)
			{
				i+=10;
			}
			else if (*pPsTsFlag & OPTIONAL_FIELDS_ONLY_PTS)
			{
				i+=5;
			}else{
				i+=5;
			}
			i = nPesHeaderStart + nPesHeaderDataLen + 9/* - (i-)*/;
			// pes ����
			//nPesLen - nPesHeahderLen;
			if (nMaxPos-nPesHeaderStart < nPesLen-3)
			{//���ݲ���
				break;
			}
			//
			int nPesDataLen = nPesLen-nPesHeaderDataLen-3;
			if (nPesDataLen > 0 )
			{
				pBufferH264->Append(m_pBufferH264->GetData()+i, nPesDataLen);
				TRACE("pes: start [%d]-[%d], pes data len[%d], pes len[%d]\n", 
					nPesHeaderStart, nPesHeaderStart+nPesLen, nPesDataLen, nPesLen);
				//
				i += nPesDataLen; //;nPesLen-nPesHeaderDataLen-9;
				//��¼��Ч����λ��,��������ɾ�� ʹ�ù�������
				nPassedPos = i;
			}
		}
		else
		{//���Ǳ��,������
			i++;
		}
		//
	}
	m_pBufferH264->Clear(0, nPassedPos);

	return 0;
}
int CPsPackage::Package(unsigned char *pH264, int nLen, unsigned char *pPsStream, int &nLenOut)
{
	m_pBufferH264->Append(pH264, nLen);
	

	
	return 0;

}
int CPsPackage::Package(unsigned char *pH264, int nLen, CBuffer *pBufferPsPkg)
{
	m_pBufferH264->Append(pH264, nLen);
	CBuffer bufferFrame;
	int nFrameType = 0;
	do{
		bufferFrame.Clear();
		nFrameType = -1;
		ParseH264Frame(m_pBufferH264, &bufferFrame, nFrameType);
		if (bufferFrame.GetLength() <= 0)
			return -1;
		//AUD
		unsigned char szAUD[8];
		memset(szAUD, 0, 8);
		szAUD[3] = 1;
		szAUD[4] = 9;
		szAUD[5] = 30;
// 		CBuffer bufferAud;
// 		bufferAud.Append(szAUD, sizeof(szAUD));
		//PackageH2642Ps(&bufferAud, pBufferPsPkg, eFT_P);
		//
		int nPsLen = PackageH2642Ps(&bufferFrame, pBufferPsPkg, nFrameType);
	}while (1);
	
	return 0;
}
int CPsPackage::PackageFrame(unsigned char *pH264Frame, int nLen, int nFrameType, CBuffer *pBufferPsPkg)
{

	int nPsLen = PackageH2642Ps(pH264Frame,  nLen, nFrameType, pBufferPsPkg);

	return nPsLen;
}
//h264 ��֡
//ÿ�ε��� ֻ�ܽ���һ֡���ݣ���Ҫ��������, 5 7 8 ��Ϊ I֡ 1 Ϊ P֡��P֮֡ǰ�� Ϊһ��I֡,����Ϊһ��P֡
int CPsPackage::ParseH264Frame(CBuffer *pBufferH264, CBuffer *pBufferFrame,int &nFrameType)
{
	int nPos0=-1, nPos1=-1;
	int nMaxPos = pBufferH264->GetLength()-4;
	unsigned char *pPos = pBufferH264->GetData();
	for (int i=0; i<nMaxPos; i++)
	{
		if ( pPos[i] == 0
			&& pPos[i+1] == 0
			&& pPos[i+2] == 0
			&& pPos[i+3] == 1)
		{//
			if (nPos0 == -1)
			{
				nPos0 = i;

				if ((pPos[i+4]&0x1f) == 5
					|| (pPos[i+4]&0x1f) == 7
					/*|| (pPos[i+4]&0x1f) == 8*/)
				{
					nFrameType = eFT_I;
				}
				else
					nFrameType = eFT_P;
				i+=3;
				continue;
			}
			if ( nFrameType == eFT_I )
			{//��ǰ ��I֡��������p frame, һ��������֡ ����
				if ( (pPos[i+4]&0x1f) == 1 )
				{
					nPos1 = i;
					break;
				}
			}
			else
			{//p֡�� ����һ�� 000001 ������
				nPos1 = i;
				break;
			}
		}
		else if (pPos[i] == 0
			&& pPos[i+1] == 0
			&& pPos[i+2] == 1
			)
		{
			if (nPos0 == -1)
			{
				nPos0 = i;

				if ((pPos[i+3]&0x1f) == 5
					|| (pPos[i+3]&0x1f) == 7
					/*|| (pPos[i+3]&0x1f) == 8*/)
				{
					nFrameType = eFT_I;
				}
				else
					nFrameType = eFT_P;	
				i+=2;
				continue;
			}
			if ( nFrameType == eFT_I )
			{//��ǰ ��I֡��������p frame, һ��������֡ ����
				if ( (pPos[i+3]&0x1f) == 1 )
				{
					nPos1 = i;
					break;
				}
			}
			else
			{//p֡�� ����һ�� 000001 ������
				nPos1 = i;
				break;
			}
		}
	}
	int nRtPos = 0;
	if (nPos0 != -1
		&& nPos1 != -1)
	{
		//h264 AUD: 00 00 00 01 09 30 00 00 
		/*unsigned char szAUD[8];
		memset(szAUD, 0, 8);
		szAUD[3] = 1;
		szAUD[4] = 9;
		szAUD[5] = 30;
		pBufferFrame->Append(szAUD, sizeof(szAUD));
		*/
		pBufferFrame->Append(pPos+nPos0, nPos1-nPos0);
		pBufferH264->Clear(0, nPos1);
		nRtPos = nPos1;
	}
	else if (nPos0 != -1)
	{
		pBufferH264->Clear(0, nPos0);
		nRtPos = nPos0;
	}
	return 0;
}
/*
*���� stPSInof.u64SCR ����ʱ�����300���Ĺ�ϵpstMediaInfo->u32TimeStamp += 3600 25֡������� pstMediaInfo->u32TimeStamp�Ǹ����� 3600�����ʱ��оƬ��ȡʱ���ŶЭ�� �涨 1��̶� �� 90000��ղ� �Ǹ�3000�Ǵ�������� ���õ�pstMediaInfo->u32TimeStampֵ���ۼ�
*
*/
int CPsPackage::PackageH2642Ps(CBuffer *pBufferFrame, CBuffer *pBufferPsPkg, int nFrameType)
{

	StMediaInfo mediaInfo;
	if (nFrameType == eFT_I)
		mediaInfo.s32MediaType = 0x01;
	else
	{
		mediaInfo.s32MediaType = 0x02;
	}
	mediaInfo.s32VideoHeight = m_nH;
	mediaInfo.s32VideoWidth = m_nW;
	mediaInfo.s32VideoFPS = m_nFPS;

	mediaInfo.u32TimeStamp = m_nTimeStamp;
	m_nTimeStamp += 90000/m_nFPS;/*3000*/;//???

	StMediaInfo *pstMediaInfo = &mediaInfo;
	StPSInfo stPSInof;
	memset(&stPSInof, 0, sizeof(StPSInfo));
	stPSInof.u64SCR = pstMediaInfo->u32TimeStamp * 300;
	stPSInof.u32MuxRate = m_nBitRate/50.0;//188*8.0/3.0;	//Ӧ���� ����/50 ���Ӧ��������ʱд�����Ժ�Ҫ��������ϵ������
	stPSInof.s32MediaType = pstMediaInfo->s32MediaType;
	//stPSInof.s32Flag |= (pstMediaInfo->s32LaunchFlag & 0x01) ? 0x01 :0x00;
	stPSInof.s32Flag = (mediaInfo.s32MediaType==0x01)? 0x01:0x00;

	int nOutLen = 0;
	char szPsTmp[MAX_PS_SIZE];
	memset(szPsTmp, 0, MAX_PS_SIZE);
	int s32Ret = Media2PSPacket(pBufferFrame->GetData(), pBufferFrame->GetLength(), 
		&stPSInof, (unsigned char*)szPsTmp, &nOutLen);
	
	if(s32Ret != 0)
	{
		//�ͷŶ�̬����Ŀռ�
		//PrintErrInfo(__FILE__, __LINE__, "��PSʧ��!");
		return -1;
	}
	pBufferPsPkg->Append((unsigned char*)szPsTmp, nOutLen);

	return nOutLen;
}
int CPsPackage::PackageH2642Ps(unsigned char *pFrame, int nLen, int nFrameType, CBuffer *pBufferPsPkg)
{

	StMediaInfo mediaInfo;
	if (nFrameType == eFT_I)
		mediaInfo.s32MediaType = 0x01;
	else
	{
		mediaInfo.s32MediaType = 0x02;
	}
	mediaInfo.s32VideoHeight = m_nH;
	mediaInfo.s32VideoWidth = m_nW;
	mediaInfo.s32VideoFPS = m_nFPS;

	mediaInfo.u32TimeStamp = m_nTimeStamp;
	m_nTimeStamp += 90000/m_nFPS;/*3000*/;//???

	StMediaInfo *pstMediaInfo = &mediaInfo;
	StPSInfo stPSInof;
	memset(&stPSInof, 0, sizeof(StPSInfo));
	stPSInof.u64SCR = pstMediaInfo->u32TimeStamp * 300;
	stPSInof.u32MuxRate = m_nBitRate/50.0;//188*8.0/3.0;	//Ӧ���� ����/50 ���Ӧ��������ʱд�����Ժ�Ҫ��������ϵ������
	stPSInof.s32MediaType = pstMediaInfo->s32MediaType;
	//stPSInof.s32Flag |= (pstMediaInfo->s32LaunchFlag & 0x01) ? 0x01 :0x00;
	stPSInof.s32Flag = (mediaInfo.s32MediaType==0x01)? 0x01:0x00;

	int nOutLen = 0;
	char szPsTmp[MAX_PS_SIZE];
	memset(szPsTmp, 0, MAX_PS_SIZE);
	int s32Ret = Media2PSPacket(pFrame, nLen, 
		&stPSInof, (unsigned char*)szPsTmp, &nOutLen);

	if(s32Ret != 0)
	{
		//�ͷŶ�̬����Ŀռ�
		//PrintErrInfo(__FILE__, __LINE__, "��PSʧ��!");
		return -1;
	}
	pBufferPsPkg->Append((unsigned char*)szPsTmp, nOutLen);

	return nOutLen;
}
#define  PrintErrInfo 
int CPsPackage::Media2PSPacket(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPSInfo *pstPsInfo, \
				   OUT unsigned char *pPSBuf, OUT int *pPSBufSize)
{
	//�������
	if(NULL == pMediaBuf || s32MediaBufSize < 0 || NULL == pstPsInfo || NULL == pPSBuf)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	unsigned char *pBuf = pPSBuf;
	int s32BufSize = 0;

	//дpack_start_code 4�ֽ�
	Write32bit(&pBuf[s32BufSize], 0x000001ba);
	s32BufSize += 4;

	//дsystem_clock_reference_base 6�ֽ�
	WriteSCR(&pBuf[s32BufSize], pstPsInfo->u64SCR);
	s32BufSize += 6;

	//дprogram_mux_rate 3�ֽ�
	pBuf[s32BufSize ++] = (pstPsInfo->u32MuxRate >> 14) & 0xff;
	pBuf[s32BufSize ++] = (pstPsInfo->u32MuxRate >> 6) & 0xff;//zsyddl
	pBuf[s32BufSize ++] = ((pstPsInfo->u32MuxRate << 2) & 0xfc) | 0x03;
	
	//------ ����4+6 + 3 = 13 bytes;
	//дpack_stuffing_length 1�ֽ�
	unsigned short u16StuffingLen = BYTE_ALIGNMENT - (s32BufSize + 1/*��Ӧ�ü���ϵͳͷ�ĳ���*/) % BYTE_ALIGNMENT;
	pBuf[s32BufSize ++] = (u16StuffingLen & 0x07) | 0xf8;

	//дstuffing_byte ��pack_stuffing_length�йأ�һ��һ���ֽ�
	int i = 0;
	for(i = 0; i < u16StuffingLen; i ++)
	{
		pBuf[s32BufSize ++] = 0xff;
	}
	// end ps header  16 bytes

	//���������Ҫ���ϵͳͷ(system_header)����������Ҫ����ʱ�����
	//todo��

	//I֡ǰ��Ҫ���PSMͷ��SYSͷ
	unsigned int u32PSMSize = 0;
	unsigned int u32SYSSize = 0;
	//if(pstPsInfo->s32MediaType & 0x01)
	if(pstPsInfo->s32Flag & 0x01)
	{

		//sysͷ��Ҫ����
		//PS����Ϣ�еı�־λ
#define FIXED_FLAG_SYS_HEADER					(1 << 1)	//ϵͳͷ��fixed_flag��־
#define CSPS_FLAG_SYS_HEADER					(1 << 2)	//ϵͳͷ��CSPS��־
#define SYSTEM_AUDIO_LOCK_FLAG_SYS_HEADER		(1 << 3)	//ϵͳͷ��system_audio_lock_flag��־
#define SYSTEM_VIDEO_LOCK_FLAG_SYS_HEADER		(1 << 4)	//ϵͳͷ��system_video_lock_flag��־
#define PACKET_RATE_RESTRICTION_FLAG_SYS_HEADER	(1 << 5)	//ϵͳͷ��packet_rate_restriction_flag��־
#define PSTD_BUFFER_BOUND_SCALE_SYS_HEADER		(1 << 6)	//ϵͳͷ��P-STD_buffer_size_bound��־
		//дsys��
		unsigned int u32SysHeadFlag = 0;
		u32SysHeadFlag = (u32SysHeadFlag | SYSTEM_VIDEO_LOCK_FLAG_SYS_HEADER | PSTD_BUFFER_BOUND_SCALE_SYS_HEADER);
		//18 bytes
		if(0 != WriteSystemHeader(&pBuf[s32BufSize], (unsigned short*)&u32SYSSize, u32SysHeadFlag, 9 + 3, 272250, 0, 1, 0XE0, 7169))
		{
			PrintErrInfo(__FILE__, __LINE__, "���SYSͷʧ��!");
			return -1;
		}
		else
		{
			s32BufSize += u32SYSSize;
		}


		//дpsm 24bytes
		if(0 != CreatePSM(STREAM_TYPE_VIDEO_H264, STREAM_TYPE_AUDIO_G711, &pBuf[s32BufSize], &u32PSMSize))
		{
			PrintErrInfo(__FILE__, __LINE__, "���PSMͷʧ��!");
			return -1;
		}
		else
		{
			s32BufSize += u32PSMSize;
		}
	}

	//��PES���Ľṹ�帳ֵ
	StPESInfo stPesInfo;
	memset(&stPesInfo, 0, sizeof(StPESInfo));
	if(0x10 == pstPsInfo->s32MediaType)
	{
		stPesInfo.u8StreamID = 0xC0;    //��Ƶ��streamIdΪ0xC0
	}
	else if(0x0B && pstPsInfo->s32MediaType)
	{
		stPesInfo.u8StreamID = 0xE0;    //��Ƶ��streamIdΪ0xE0
	}
	//stPesInfo.u8StreamID = 0xE0;  
	stPesInfo.u32Flag |=  OPTIONAL_FIELDS_ONLY_PTS;//zsy OPTIONAL_FIELDS_ONLY_PTS;    //ֻ����ʾʱ���(PTS)�ֶ�
	stPesInfo.u64Pts = pstPsInfo->u64SCR / 300;       //��ʾʱ����͵���SCR
	//stPesInfo.u64Dts = stPesInfo.u64Pts;
	//�����PES��
	int s32PESSize = 0;
	int s32Ret = Media2PESStream(pMediaBuf, s32MediaBufSize, &stPesInfo, &pBuf[s32BufSize], &s32PESSize);
	if(s32Ret != 0)
	{
		PrintErrInfo(__FILE__, __LINE__, "��װPESʧ��!");
		return -1;
	}
	else
	{
		s32BufSize += s32PESSize;
		*pPSBufSize = s32BufSize;
	}

	return 0;
}

unsigned short CPsPackage::Write16bit(OUT unsigned char *pBuf, IN unsigned short u16Value)
{
	//�������
	if(NULL == pBuf)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	*pBuf ++ = (u16Value >> 8) & 0xff;
	*pBuf = u16Value & 0xff;

	return 0;
}
unsigned short CPsPackage::Write32bit(OUT unsigned char *pBuf, IN unsigned int u32Value)
{
	//�������
	if(NULL == pBuf)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	*pBuf ++ = (u32Value >> 24) & 0xff;
	*pBuf ++ = (u32Value >> 16) & 0xff;
	*pBuf ++ = (u32Value >> 8) & 0xff;
	*pBuf ++ = u32Value & 0xff;

	return 0;
}

int CPsPackage::WriteSCR(OUT unsigned char *pBuf, IN unsigned long long u64SCR)
{
	//�������
	if(NULL == pBuf || u64SCR <= 0)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	unsigned long long u64SCRBase = u64SCR / 300;
	unsigned short u16SCRExtern = u64SCR % 300;
	*pBuf ++ = ((u64SCRBase >> 27) & 0x38) | ((u64SCRBase >> 28) & 0x03) | 0x44;
	*pBuf ++ = (u64SCRBase >> 20) & 0xff;
	*pBuf ++ = ((u64SCRBase >> 12) & 0xf8) | ((u64SCRBase >> 13) & 0x03) | 0x04;
	*pBuf ++ = (u64SCRBase >> 5) & 0xff;
	*pBuf ++ = ((u64SCRBase << 3) & 0xf8) | ((u16SCRExtern >> 7) & 0x03) | 0x04;
	*pBuf ++ = ((u16SCRExtern << 1) & 0xfe) | 0x01;

	return 0;
}
//18 bytes
int CPsPackage::WriteSystemHeader(unsigned char *pBuf, unsigned short *pu16bufLen, unsigned int u32SysHeadFlag, \
					  unsigned short u16HeaderLength, unsigned int u32RateBound, unsigned char u8AudioBound, \
					  unsigned char u8Videobound, unsigned char u8StreamID, unsigned short u16PSTDBufSize)
{	
	//�������	
	if((u32RateBound > 0x3fffff) || (u8AudioBound > 0x3f) || (u8Videobound > 0x1f) || (u16PSTDBufSize > 0x1fff) || (NULL == pBuf))	
	{		
		printf("WriteSystemHeader:�������ʧ��\n");		
		return -1;	
	}	

	//����ռ�	
	unsigned char *p = pBuf;	

	//дsystem_header_start_code 4�ֽ�	
	Write32bit(p, 0x000001bb);	
	p += 4;	

	//дheader_length 2�ֽ�	
	Write16bit(p, u16HeaderLength);	
	p += 2;

	//дrate_bound 3�ֽ�	
	*p ++ = ((u32RateBound >> 15) & 0x7f) | 0x80;	
	*p ++ = (u32RateBound >> 7) & 0xff;	
	*p ++ = ((u32RateBound << 1) & 0xfe) | 0x01;	
   
	//дaudio_bound����־λ	
	*p ++ = ((u8AudioBound << 2) & 0xfc) | (u32SysHeadFlag & FIXED_FLAG_SYS_HEADER) | ((u32SysHeadFlag & CSPS_FLAG_SYS_HEADER) >> 2);	

	//дvideo_bound����־λ	
	*p ++ = (u8Videobound & 0x1f) | ((u32SysHeadFlag & SYSTEM_AUDIO_LOCK_FLAG_SYS_HEADER) << 4) | \
		((u32SysHeadFlag & SYSTEM_VIDEO_LOCK_FLAG_SYS_HEADER) << 2) | 0x20;	

	//дpacket_rate_restriction_flag��־λ	
	*p ++ = ((u32SysHeadFlag & PACKET_RATE_RESTRICTION_FLAG_SYS_HEADER) << 3) | 0x7f;	

	/*	 
	* ����Ϊ��Ŀ���а����Ľ�Ŀ�����ܰ�����Ƶ����Ƶ��Ŀǰֻ����һ����Ƶ����������������Ժ���չ	 
	*/	
	//дvideo stream_id	
	*p ++ = u8StreamID;	
	//дP-STD_buffer_bound_scale��P-STD_buffer_size_bound	
	*p ++ = 0xc0 | ((u32SysHeadFlag & PSTD_BUFFER_BOUND_SCALE_SYS_HEADER) >> 1) | ((u16PSTDBufSize >> 8) & 0x1f);	
	*p ++ = (u16PSTDBufSize & 0xff);	


	//дaudio stream_id	
	*p ++ = 0xc0;	
	//дP-STD_buffer_bound_scale��P-STD_buffer_size_bound	
	*p ++ = 0xc0 | ((u32SysHeadFlag & PSTD_BUFFER_BOUND_SCALE_SYS_HEADER) >> 1) | ((u16PSTDBufSize >> 8) & 0x1f);	
	*p ++ = (u16PSTDBufSize & 0xff);	

	*pu16bufLen = p - pBuf;
	///--4 + 2 + 3 + + 9= 18  
	return 0;
}

//24 bytes
int CPsPackage::CreatePSM(IN unsigned int u32VideoType, IN unsigned int u32AudioType, OUT unsigned char *pBuf, OUT unsigned int *pBufSize)
{
	//�������
	if(NULL == pBuf || NULL == pBufSize)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}
	else
	{
		*pBufSize = 0;
	}

	unsigned char *p = pBuf;
	unsigned int u32Count = 0;
	//дpacket_start_code_prefix 3�ֽ�
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x01;

	//дmap_stream_id 1�ֽ�
	p[u32Count ++] = 0xbc;

	//дprogram_stream_map_length 2�ֽ� ��û��descriptor()��ֻ��һ·��Ŀ����£�program_stream_map_length = 14�ֽڡ�
	//��·��Ŀ(����Ƶ)ʱ����4���ֽ�
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x0e + 4;

	//дcurrent_next_indicator��program_stream_map_version
	p[u32Count ++] = 0xe0;

	//����һ���ֽ�Ϊ����ֶ�
	p[u32Count ++] = 0xff;

	//дprogram_stream_info_length 2�ֽ�
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x00;

	//дelementary_stream_map_length,��û��descriptor()����ֻ��һ·��Ŀ����£�elementary_stream_map_length = 4�ֽ�
	//��·��Ŀ(����Ƶ)ʱ����4���ֽ�
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x04 + 4;

	//д��Ƶ��Ŀ
	//дstream_type
	p[u32Count ++] = u32VideoType;

	//дelementary_stream_id
	p[u32Count ++] = 0xe0;

	//дelementary_stream_info_length
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x00;

	//д��Ƶ��Ŀ
	//дstream_type
	p[u32Count ++] = u32AudioType;

	//дelementary_stream_id
	p[u32Count ++] = 0xc0;

	//дelementary_stream_info_length
	p[u32Count ++] = 0x00;
	p[u32Count ++] = 0x00;

	//CRCУ��
	unsigned int u32CRC = 0; //CalcCrc32(p, u32Count); zsy ???
	Write32bit(&p[u32Count], u32CRC);
	u32Count += 4;

	*pBufSize = u32Count;

	return 0;
}
//pes header ĿǰΪ 16 bytes
int CPsPackage::Media2PESStream(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPESInfo *pstPesInfo, \
					OUT unsigned char *pPESBuf, OUT int *pPESBufSize)
{
	//�������
	if(NULL == pMediaBuf || s32MediaBufSize <= 0 || NULL == pstPesInfo || NULL == pPESBuf || \
		NULL == pPESBufSize)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}
	else
	{
		*pPESBufSize = 0;
	}

	//�ж�ý��������û�д��ڹ涨�ĳ���(���ý�����ݳ�����SPLIT_PACKET_LENGTH�궨��)���������з�֡����
	int s32RemainDataLen = s32MediaBufSize;
	int u32OutDataLen = 0;
	unsigned char *pSplitPacketInBuf = pMediaBuf;
	unsigned char *pSplitPacketOutBuf = pPESBuf;
	unsigned u32PacketNum = 0;
	StPESInfo stSplitePacketPesInfo;
	//��stSplitePacketPesInfo��ֵ���ǵ�һ����PESͷ���Լ򻯣�ȥ�������ֶ�
	memset(&stSplitePacketPesInfo, 0, sizeof(StPESInfo));
	stSplitePacketPesInfo.u8StreamID = pstPesInfo->u8StreamID;

	while(s32RemainDataLen > 0)
	{
		if(s32RemainDataLen > SPLIT_PACKET_LENGTH)
		{
			if(0 == u32PacketNum)
			{
				Media2PESPacket(pSplitPacketInBuf, SPLIT_PACKET_LENGTH, pstPesInfo, pSplitPacketOutBuf, &u32OutDataLen);
			}
			else
			{
				Media2PESPacket(pSplitPacketInBuf, SPLIT_PACKET_LENGTH, &stSplitePacketPesInfo, pSplitPacketOutBuf, &u32OutDataLen);
			}

			s32RemainDataLen -= SPLIT_PACKET_LENGTH;
			pSplitPacketInBuf += SPLIT_PACKET_LENGTH;
			pSplitPacketOutBuf += u32OutDataLen;
			*pPESBufSize += u32OutDataLen;
		}
		else
		{
			if(0 == u32PacketNum)
			{
				Media2PESPacket(pSplitPacketInBuf, s32RemainDataLen, pstPesInfo, pSplitPacketOutBuf, &u32OutDataLen);
			}
			else
			{
				Media2PESPacket(pSplitPacketInBuf, s32RemainDataLen, &stSplitePacketPesInfo, pSplitPacketOutBuf, &u32OutDataLen);
			}

			s32RemainDataLen -= s32RemainDataLen;
			pSplitPacketInBuf += s32RemainDataLen;
			pSplitPacketOutBuf += u32OutDataLen;
			*pPESBufSize += u32OutDataLen;
		}
	}

	return 0;
}
//���ȸ��� ���λ ���� ,�ɱ�
int CPsPackage::Media2PESPacket(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPESInfo *pstPesInfo, \
					OUT unsigned char *pPESBuf, OUT int *pPESBufSize)
{
	//�������
	if(NULL == pMediaBuf || s32MediaBufSize < 0 || NULL == pstPesInfo || NULL == pPESBuf)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}
	else
	{
		*pPESBufSize = 0;
	}

	//����PES_header_data_length�ֶεĳ���
	unsigned char u8PESHeaderDataLength = 0;
	int s32Ret = CalculatePESHeaderDataLength(pstPesInfo);
	//PES_header_data_length�ֶεĳ�����һ���ֽڱ�ʾ����˱���С��0xff��ͬʱ��Ҫ�����Ժ��ֽڶ���ʱ��ӵ����λ����
	if( s32Ret< 0 || s32Ret > 0xff - BYTE_ALIGNMENT)
	{
		PrintErrInfo(__FILE__, __LINE__, "����PES_header_data_length�ֶγ���ʧ��!");
		return -1;
	}
	else
	{
		u8PESHeaderDataLength = s32Ret;
	}
	/*
	//����PES_packet_length�ֶεĳ���
	unsigned short u16PESPacketLength = 3 + u8PESHeaderDataLength + s32MediaBufSize;//����Э���֪

	//��֤��װ���PES�����ֽڶ���ġ����δ���룬������u8PESHeaderDataLength��ֵ������PESͷ�����������λ
	u8PESHeaderDataLength += BYTE_ALIGNMENT - (u16PESPacketLength + 6) % BYTE_ALIGNMENT;//+6����ΪPES_packet_length�ֶ�ǰ����6�ֽڵ�����
	u16PESPacketLength += BYTE_ALIGNMENT - (u16PESPacketLength + 6) % BYTE_ALIGNMENT;
	*/

	//unsigned char u8PESHeaderStuffLen = BYTE_ALIGNMENT - (u8PESHeaderDataLength + 9) % BYTE_ALIGNMENT;//+9����ΪPES_packet_length�ֶ�ǰ����9�ֽڵ�����
	unsigned char u8PESHeaderStuffLen = BYTE_ALIGNMENT - (u8PESHeaderDataLength + 9) % BYTE_ALIGNMENT;//+9����ΪPES_packet_length�ֶ�ǰ����9�ֽڵ�����
	u8PESHeaderDataLength += u8PESHeaderStuffLen;
	//����PES_packet_length�ֶεĳ���
	//unsigned short u16PESPacketLength = 3 + u8PESHeaderDataLength + s32MediaBufSize;//����Э���֪
	//zsyddl // ��ʾ ��  u16PESPacketLength �ֶκ� �ж����ֽ�, Ŀǰ�� 6 ���ֽ� 
	unsigned short u16PESPacketLength = 3 + u8PESHeaderDataLength + s32MediaBufSize;//����Э���֪

	////////////////////////////////////////////////////
	/*
	if(pMediaBuf[4] == 0x67){
	printf("--->u8PESHeaderDataLength %x\n", u8PESHeaderDataLength);
	printf("s32MediaBufSize %x\n", s32MediaBufSize);
	printf("u16PESPacketLength %x\n", u16PESPacketLength);
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	}
	*/

	/*
	unsigned char u16PESPacketStuffLen = BYTE_ALIGNMENT - (u16PESPacketLength + 6) % BYTE_ALIGNMENT;
	u16PESPacketLength += u16PESPacketStuffLen;
	*/

	unsigned char *pPesStream = pPESBuf;    //��PES����buf������֮��������������
	unsigned int s32PesStreamLen = 0;       //PES���ĳ���,��pPesStream�ĳ���

	//дpacket_start_code_prefix  24bits ֵΪ�̶���0x000001
	pPesStream[s32PesStreamLen ++] = 0x00;
	pPesStream[s32PesStreamLen ++] = 0x00;
	pPesStream[s32PesStreamLen ++] = 0x01;
	//дstream_id    8bits
	pPesStream[s32PesStreamLen ++] = pstPesInfo->u8StreamID;
	//дPES_packet_length    16bits
	if(0 != Write16bit(&pPesStream[s32PesStreamLen], u16PESPacketLength))
	{
		PrintErrInfo(__FILE__, __LINE__, "дPESý�����ݳ���ʧ��!");
		return -1;
	}
	else
	{
		s32PesStreamLen += 2;
	}
	//дoptional PES HEADER�ĵ�һ���ֽڡ�Ŀǰ��д����ֵ���Ժ�Ӧ����չ�ɿ����õġ�
	pPesStream[s32PesStreamLen ++] = 0x80;
	//дoptional PES HEADER�ڶ����ֽ�(7����־λ)
	unsigned char u8TempFlag = (pstPesInfo->u32Flag & 0x3f);
	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ONLY_PTS)
	{
		u8TempFlag |= 0x80;
	}
	else if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PTS_DTS)
	{
		u8TempFlag |= 0xC0;
	}
	pPesStream[s32PesStreamLen ++] = u8TempFlag;
	//дPES_header_data_length�ֶεĳ���
	pPesStream[s32PesStreamLen ++] = u8PESHeaderDataLength;
	//дoptional fields
	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PTS_DTS)
	{
		//дPTS DTS
		if(WriteTimeStamp(&pPesStream[s32PesStreamLen], 0x03, pstPesInfo->u64Pts))
		{
			PrintErrInfo(__FILE__, __LINE__, "дPTSʧ��!");
			return -1;
		}
		s32PesStreamLen += 5;
		//
		if(WriteTimeStamp(&pPesStream[s32PesStreamLen], 0x01, pstPesInfo->u64Dts))
		{
			PrintErrInfo(__FILE__, __LINE__, "дDTSʧ��!");
			return -1;
		}
		s32PesStreamLen += 5;
	}
	else if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ONLY_PTS)
	{
		//дPTS
		if(WriteTimeStamp(&pPesStream[s32PesStreamLen], 0x02, pstPesInfo->u64Pts))
		{
			PrintErrInfo(__FILE__, __LINE__, "дPTSʧ��!");
			return -1;
		}
		s32PesStreamLen += 5;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ESCR)
	{
		//todo дESCR�ֶ�
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ES_RATE)
	{
		//todo дES_RATE�ֶ�
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_DSM_TRICK_MODE)
	{
		//todo дDSM_TRICK_MODE�ֶ�
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ADDITIONAL_COPY_INFO)
	{
		//todo дADDITIONAL_COPY_INFO�ֶ�
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PREVIOUS_PES_CRC)
	{
		//todo дPREVIOUS_PES_CRC�ֶ�
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PES_EXTENSION)
	{
		//todo дPES_EXTENSION�ֶ�
	}

	/*
	//PESͷ�������ֽڣ���֤�ֽڶ���
	while((int)(u16PESPacketLength + 6 - s32PesStreamLen - s32MediaBufSize) > 0) //+6ʱ��ΪPESPacketLength�ֶ�ǰ����6���ֽڵ�����
	{
	pPesStream[s32PesStreamLen ++] = 0xFF;
	}
	*/
	//PESͷ�������ֽڣ���֤�ֽڶ���
	while(u8PESHeaderStuffLen > 0)
	{
		pPesStream[s32PesStreamLen ++] = 0xFF;
		u8PESHeaderStuffLen --;
	}    

	memcpy(&pPesStream[s32PesStreamLen], pMediaBuf, s32MediaBufSize);
	s32PesStreamLen += s32MediaBufSize;

	/*
	//H264����ֽڣ���֤�ֽڶ���
	while(u16PESPacketStuffLen > 0)
	{
	pPesStream[s32PesStreamLen ++] = 0xFF;
	u16PESPacketStuffLen --;
	}    
	*/
	*pPESBufSize = s32PesStreamLen;

	return 0;
}

int CPsPackage::CalculatePESHeaderDataLength(IN StPESInfo *pstPesInfo)
{
	//�������
	if(NULL == pstPesInfo)
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	/*
	//������PES��ͷ(optional PES HEADER)�е�7����־λ
	#define OPTIONAL_FIELDS_ONLY_PTS              (1 << 7)  //  |-��OPTIONAL_FIELDS_PTS_DTSΪһ����־λ--|
	#define OPTIONAL_FIELDS_PTS_DTS               (1 << 6)  //  |-��OPTIONAL_FIELDS_ONLY_PTSΪһ����־λ-|
	#define OPTIONAL_FIELDS_ESCR                  (1 << 5)
	#define OPTIONAL_FIELDS_ES_RATE               (1 << 4)
	#define OPTIONAL_FIELDS_DSM_TRICK_MODE        (1 << 3)
	#define OPTIONAL_FIELDS_ADDITIONAL_COPY_INFO  (1 << 2)
	#define OPTIONAL_FIELDS_PREVIOUS_PES_CRC      (1 << 1)
	#define OPTIONAL_FIELDS_PES_EXTENSION         (1 << 0)
	*/

	int s32Length = 0;
	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ONLY_PTS)
	{
		s32Length += 5;
	}
	else if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PTS_DTS)
	{
		s32Length += 10;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ESCR)
	{
		s32Length += 6;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ES_RATE)
	{
		s32Length += 3;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_DSM_TRICK_MODE)
	{
		s32Length += 1;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_ADDITIONAL_COPY_INFO)
	{
		s32Length += 1;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PREVIOUS_PES_CRC)
	{
		s32Length += 4;
	}

	if(pstPesInfo->u32Flag & OPTIONAL_FIELDS_PES_EXTENSION)
	{
		//OPTIONAL_FIELDS_PES_EXTENSION�Ƚϸ��ӣ���ʱҲû�õ����������û�д�����ֶε�������Ժ���Ҫ������չ
	}

	return s32Length;
}

unsigned short CPsPackage::WriteTimeStamp(OUT unsigned char *pBuf, IN unsigned char u8ID, IN unsigned long long u64TimeStamp)
{
	//�������
	if((NULL == pBuf) || (u8ID <= 0) || (u64TimeStamp < 0))
	{
		PrintErrInfo(__FILE__, __LINE__, "�������ʧ��!");
		return -1;
	}

	/* 1: 4 bit id value | TS [32..30] | marker_bit */
	*pBuf ++ = ((u8ID << 4) | ((u64TimeStamp >> 29) & 0x0E) | 0x01) & 0xff;
	/* 2, 3: TS[29..15] | marker_bit */
	if(0 != Write16bit(pBuf, ((u64TimeStamp >> 14) & 0xfffe) | 0x01))
	{
		PrintErrInfo(__FILE__, __LINE__, "дʱ���2��3�ֽ�ʧ��!");
		return -1;
	}
	pBuf += 2;
	/* 4, 5: TS[14..0] | marker_bit */
	if(0 != Write16bit(pBuf, ((u64TimeStamp << 1) & 0xfffe) | 0x01))
	{
		PrintErrInfo(__FILE__, __LINE__, "дʱ���4��5�ֽ�ʧ��!");
		return -1;
	}

	return 0;
}
