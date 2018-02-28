#pragma once

#include "MediaSdkDef.h"

//#define FFMPEG_52
#define FFMPEG_80
#ifndef UINT64_C
#define UINT64_C unsigned long long 
#endif

#ifndef TRACE
#ifdef WIN32
#define TRACE(format, ...)	do{ \
	char szMsg[255];\
	memset(szMsg, 0, sizeof(szMsg));\
	sprintf(szMsg, format, __VA_ARGS__);\
	OutputDebugStringA(szMsg);  \
}while (0);
#else
#define TRACE(format, ...)	do{ \
    char szMsg[255];\
    memset(szMsg, 0, sizeof(szMsg));\
    sprintf(szMsg, format, __VA_ARGS__);\
    printf(szMsg);  \
}while (0);
#define debug printf
#endif
#endif

extern "C"
{

#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avio.h"
}
#include <vector>
using namespace std;
#include "FfmpegCodec.h"

#include "AvFromatMp4.h"

#define AvFormat_Ffmpeg "AvFormat_Ffmpeg"

#define  FfmpegFileFlag "RIFF"
class CH264File;
class MEDIASDK_API CFfmpegFormat
{
public:
	CFfmpegFormat(void);
	virtual ~CFfmpegFormat(void);

	long Create(char *pFormat="mkv", bool bReadOrWrite=true);

	int AddStream(int nStreamId);
	int AddStream(int nStreamId, sFfmpegStreamInfo &streamInfo);
	int Open(char *pSzFile, int nFlag=AVIO_FLAG_READ);


	void Close();

	int ReadFrame(char *pBuffer, int &nLen, int64_t &nTimeStamp, int &nStreamId);
	int WriteFrame(char *pBuffer, int nLen, int64_t nTimeStamp=-1, int nFlag=0, int nStreamId=0);
	//int WriteFrame(char *pBuffer, int nLen, int64_t nTimeStamp=-1);
	//�ýӿ� �������Ƶ��ʼʱ��
	int SeekTo(int64_t &nTime, int nFlag=AVSEEK_FLAG_ANY, int nStreamId=0);
	int SeekTo(int nFrameIndex);
	//ʱ�������Ƶ�ڲ���ԭʼʱ���
	int SeekToTimestamp(int64_t nTimestamp, int nFlag=AVSEEK_FLAG_ANY, int nStreamId=0);
	int SeekToNextKeyFrame();
	int SeekToPrevKeyFrame(int64 nTimestamp=-1);
	bool IsKeyFrame();
	
	AVStream *GetStream(int nIndex);
	int GetStreamCount();
	void GetStreamInfo(sFfmpegStreamInfo &streamInfo, int nIndex);
	int GetStreamType(int nIndex);
	AVStream *GetStreamByType(int nType/*=AVMEDIA_TYPE_VIDEO*/);

	void GetFrameRate(int &nNum, int &nDen);

	void GetTimeBase(int &nNum, int &nDen);
	//����Ƶ��ʼ��Ϊ0  �����ʱ�� 
	int64 TimeToTimestamp(int64 s64MilliSeconds);
	int64 TimestampToTime(int64 s64Timestamp);
	//����ǻ���֮���ʱ�䣬�����Ҫʱ�������Ҫͨ��timeBase ����
	//�ļ������ʱ��ƫ��:GetTotalTime
	int64_t GetCurrentTime();
	int64_t GetCurrentTimestamp();
	//
	int64_t GetStartTime();
	int64_t GetStartTimestamp();
	//ʱ�䳤��
	int64_t GetTotalTime();
	//
	int GetVideoWidth();
	int GetVideoHeight();
	//
	int64 GetFileSize(){return m_s64FileSize;};
	int64 GetFilePos() ;
	//
	bool	IsNeedFix();
	int     DoFixFile(int64 &s64Total, int64 &s64Pos);
	//

	char *GetFormatName(){return AvFormat_Ffmpeg;}
	AVFormatContext *GetFormatContext(){return m_pAvFormatContext;};
protected:
	//
	int ParseMp4H264Info();
	//����֧��H264 file
	CH264File		*m_pH264File;

	AVOutputFormat *m_pAvOutFormat;
	AVInputFormat  *m_pAvInFormat;

	AVFormatContext *m_pAvFormatContext;
	AVDictionary   *format_opts;

	vector<AVStream *> m_lstStream;
	int  m_nOpenFlag;
	int64_t	 m_s64VideoTimeStamp;
	int64_t  m_s64AudioTimeStamp;
	int64_t  m_s64TimeStampLastKeyFrame;
	uint32	 m_u32FrameFlag;
	bool    m_bSeek;
	int     m_nSeekFlag;
	//
//	char	*m_pH264PpsSps;
//	int		m_nH264InfoSize;
	bool    m_bMp4H264;
	//
	int64   m_s64FileSize;
	//��ȡ��֡�Ĵ�С��˳���ȡ���м�ֵ��������Ϊ�ο�
	int64   m_s64ReadSize;
	//
	H264BSFContext *m_pMp4H264Ctx;
};

