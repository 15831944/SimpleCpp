#pragma once

/*#include "VivsMediaBox.h"*/
/*#include "SThread/Thread.h"*/
/*#include "SThread/Mutex.h"*/
/*#include "FfmpegCodec.h"*/
#include "MediaSdkDef.h"

#include "BaseStream.h"
// stream type
#define VIVS_CODEC_H264  "vivs-h264"
#define VIVS_CODEC_H264_STD   "h264"
#define VIVS_CODEC_H264_PS "ps-h264"
#define VIVS_CODEC_DH    "dh"
#define VIVS_CODEC_HK    "hk"

#ifndef int64_t
typedef long long int64_t;
#endif

typedef int (__stdcall *MB_CbPlayFileTimeStamp)(long hHandle, int64_t s64TimeStamp, float fScale, void *pUserData, void *pReversed);
typedef int (__stdcall *MB_CbDecode)(char *pData, int nLen, int nPixFormat, int nW, int nH, void *pUserData, void *pReversed);

class CVivsMediaFile;
class CMediaFile;
class CDataFilter;
class CDecoder;
class CRender;
class CPackageParser;
class CFilterPinBuffer;
class CFfmpegFormat;
namespace SThread{
class CThread;
class CMutex;
}
// #ifndef sFfmpegAudioInfo
// struct sFfmpegAudioInfo;
// #endif
// #ifndef sFfmpegVideoInfo
// struct sFfmpegVideoInfo;
// #endif

using namespace SThread;

class VIVSMEDIABOX_API CMediaStream
{
	friend class CStreamBuilder;

	//friend static int __stdcall ThrDecodeProc(void *pParam);
	//friend static int __stdcall ThrRenderProc(void *pParam);
public:
	CMediaStream(void);
	virtual ~CMediaStream(void);
	//
	
//	int SetBitRate(int nBitrate=10*1024*1024);
//	int SetResolution(int nW=1280, int nH=720);
	int Open(char *pInfo, long hWndShow);
	int Open(sVivsStreamInfo *pStreamInfo, long hWndShow);
	//�����ļ��Ľӿ�
	int OpenFile(char *pFile, long hWndShow, bool bPlayOrPause=true);
	//�ļ�ת���� avi
	int OpenFile(char *pVivsFile, char *pAviFile, bool bStartOrPause = true );

	//
	int SetPlayFileTimeCb(MB_CbPlayFileTimeStamp cbTime, void *pUserData, void *pReversed);
	int GetFileTime(int64_t &s64StartTime, int64_t &s64EndTime);
	int GetVideoCodec(int &nCodec);
	

	int Close();
	int Start();
	int Pause();
	int Resume();
	int Stop();
	//���ļ����� ����
	int SetPlaySpeed(float fSpeed);
	int SetPlayPos(int64_t lTimeStamp);
	//
	int	SetPlayBuffer(int nCount=20);
	//���������ݻص���rgb yuv...
	int SetDecodeCb(MB_CbDecode cbDecode, void *pUserData, void *pReversed);
	//���Ű���
	int PlayAudio();
	int StopAudio();
	//
	int InputData(char *pData, int nLen);
	int SetDisplayBuffer(int nCount=10);
	int SetOsdText(int nIndex, char *pText);
	int SetOsdPos(int nIndex, int nX, int nY);
	int SetOsdFontSize(int nIndex, int nSize);
	int SetOsdFontColor(int nIndex, long lColorRGB);
	int SetOsdFont(int nIndex, char *pSzName, int nSize, long lRGB);
	int SetOsdShow(int nIndex, bool bShowOrHide);
	//�������� ��avi�ļ�
	int Save2Avi(char *pSzFilePath);
	//
	int SetInputBuffer(int nLen);
	//���̰߳�ȫ��
	int SnapShot(char *pSaveFile);
	//ˢ�´�����ʾ
	int Refresh();
	//int SnapShot(char *pBuffer, int &nLen);
protected:
	static int __stdcall ThrDecodeProc(void *pParam);
	static int __stdcall ThrRenderProc(void *pParam);
	static int __stdcall ThrReadFileProc(void *pParam);
	static int __stdcall ThrFileTrans2AviProc(void *pParam);

	void AttachParser(CPackageParser *pParser);
	void AttachParser(CDataFilter *pParser);
	void AttachDecoder(CDecoder *pDecoder);
	void AttachRender(CRender *pRender);
	void AttachAudioDecoder(CDecoder *pDecoder);
	void AttachAudioRender(CRender *pRender);

	char *CodecType2CodecInfo(int nCodecType);
	// ���� ������ avi�ļ�
	int Write2AviFrame(char *pData, int nLen);

	CPackageParser *m_pPackageParser;
	
	//�����ļ���ʱ��ʹ��
/*	CMediaFile	*m_pMediaFile;*/
	CVivsMediaFile	*m_pVivsMediaFile;
	int64_t			m_lFileSeekToTimeStamp;
	int64_t			m_s64PlayFileTimeStamp;
	MB_CbPlayFileTimeStamp m_cbPlayFileTimeStamp;
	void *m_pCbPlayFileUserData;
	void *m_pCbPlayFileReversed;
	//�ļ�ת�� �� avi
	CFfmpegFormat *m_pFfmpegFormatAvi;
	CThread		  *m_pThrTransFile2Avi;
	//�����Ļص�
	MB_CbDecode m_cbDecode;
	void *m_pCbDecodeUserData;
	void *m_pCbDecodeReversed;

	CDecoder *m_pVideoDecoder;
	CRender  *m_pVideoRender;
	CDecoder *m_pAudioDecoder;
	CRender  *m_pAudioRender;

	CThread  *m_pThreadDecode;
	bool	 m_bThreadInputExit;
	CThread  *m_pThreadRender;
	bool	 m_bThreadRenderExit;
	CThread  *m_pThreadReadFile;

	CMutex   *m_pMutexInputBuffer;
	eStreamState m_state;
	float	m_fPlaySpeed;
	//ִ�� ������ת
	bool	m_bFileSeek;
	//���ݻ���
	int		m_nPlayBuffer;
	//�Ƿ񲥷Ű���
	bool	m_bPlayAudio;
	//
	CFilterPinBuffer *m_pInputDataBuffer;
	//Ϊʲô����� �ṹ��� delete ���� ����
	//sFfmpegAudioInfo *m_pAudioInfo;
	//sFfmpegVideoInfo *m_pVideoInfo;
};
