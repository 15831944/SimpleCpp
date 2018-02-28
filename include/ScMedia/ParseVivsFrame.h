#pragma once
#ifndef PARSE_VIVS_FRAME_H
#define PARSE_VIVS_FRAME_H
#include <list>
#include "VivsMediaDef.h"
#include "VivsMediaDef.h"

#ifndef VIVSMEDIABOX_API
#define  VIVSMEDIABOX_API
#endif

using namespace std;


typedef enum _eVivsFrameType{
	eVFT_Audio,
	eVFT_VideoIFrame,
	eVFT_VideoPFrame,
	eVFT_VideoSFrame,
}eVivsFrameType;



class CBuffer;
//����һ֡
class VIVSMEDIABOX_API CStreamFrame
{
public:
	CStreamFrame();
	~CStreamFrame();
public:
	CBuffer *m_pBufferFrame;
	int     m_eFrameType;
	int m_nW;
	int m_nH;
	//ʱ���
	unsigned short m_nYear;
	unsigned short m_nMonth;
	unsigned short m_nDay;
	unsigned short m_nHour;
	unsigned short m_nMinute;
	unsigned short m_nSecond;
	unsigned short m_nMiniSecond;
};
/*
* ���̰߳�ȫ
*/
class VIVSMEDIABOX_API CParseVivsFrame
{
	typedef enum _eParserVivsFrameState{
		ePVFS_Run,
		ePVFS_Stop,
	}eParserVivsFrameState;
public:
	CParseVivsFrame(void);
	~CParseVivsFrame(void);
	
	long Init(int nBufferSize=1024*1024);
	long Close();
	// ret <0 if false
	//����Ϊ��׼ ������ʹ����Ϣ
	long Parse2Std(char *pData, int nLen);
	// ���� avdataend�� ���ָ�Լ�֡���ͣ������������ݣ�
	long ParseAvdataEnd(char *pData, int nLen);
	// @pFrame,  user alloc the memory and pass to this fun. the size must big enough, 512kB eg.
	// @nLen,    in & out. the frame data length
	// @nFrameType, eVivsFrameType
	// @ret,      <0 if false, and nLen <= 0;
	// @notes: user must call this fun several times , to get all frames.
	long GetFrame(char *pFrame, int &nLen, int &nFrameType);
	//
	long GetFrame(CStreamFrame *pFrame);
	//����ý��ʱ�䣬����оͷ���ʱ�䣬û����Ϊ-1, ����������
	static long ParseTimeStamp(char *pData, int nLen, unsigned int &lSecond, unsigned int &lMilliSecond);
protected:
	//begin parse2h264nal
	//���� avdata �ְ�, ��������ͷ���� �ֽ�Ϊ h264 nal ��Ԫ
	int ParsePackage(char *pData, int nLen, CBuffer *pOut, int &nOutLen, int &nAvDataEndType);
	int Split2AvdataPackage(char *pData, int nLen, CBuffer *pOut, int &nOutLen, int &nAvDataEndType);
	//����h264����
	int ParseH264Nal(CBuffer *pH264Stream, CBuffer *pNal, int &nFrameType);
	//end parse2h264nal

	//��������
	CBuffer *m_pBufferStream;
	CBuffer *m_pBufferStreamTmp;
	CBuffer *m_pBufferVideoStream;
	CBuffer *m_pBufferAudioStream;
	//
	CStreamFrame *m_pStreamFrameTmp;
	//�Ѿ������� frame
	list<CStreamFrame *> m_lstFrame;
	int m_eState;
	//
	int m_nFTMV;
	bool	m_bParseAvdataEnd;
	//���� ��ǰ�� avdata end �ṩ�� �������� nal�ְ�ʹ�á�
	sAvDataEnd m_avDataEnd;
};

/*
* ���̰߳�ȫ
*/
#ifdef __cplusplus
extern "C" {
#endif
	// must larger than 512kB
	long Vivs_FrameParserInit(int nBufferSize);
	void Vivs_FrameParserClose(long lHandle);

	long Vivs_FrameParserInputData(long lParserHandle, char *pData, int nLen);
	// @pFrame,  user alloc the memory and pass to this fun. the size must big enough, 512kB eg.
	// @nLen,    in & out. the frame data length
	// @nFrameType, eVivsFrameType
	// @ret,      <0 if false, and nLen <= 0;
	// @notes: user must call this fun several times , to get all frames.
	long Vivs_FrameParserGetFrame(long lParserHandle, char *pFrame, int *pLen, int *pFrameType);
#ifdef __cplusplus
}
#endif

#endif //PARSE_VIVS_FRAME_H