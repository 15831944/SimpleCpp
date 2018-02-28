#pragma once
#include "MediaSdk.h"
#include "encoder.h"



class CFfmpegCodec;

typedef struct _sFfmpegVideoInfo sFfmpegVideoInfo;
typedef struct _sFfmpegAudioInfo sFfmpegAudioInfo;
typedef struct _sFfmpegFrameInfo sFfmpegFrameInfo;
class MEDIASDK_API CFfmpegEncoderFilter :
	public CEncoder
{
public:
	CFfmpegEncoderFilter(void);
	virtual ~CFfmpegEncoderFilter(void);

	virtual int Open(char* pSzParam, bool bHasThread=false);
	virtual int DoFilter();
	
protected:
	virtual CMediaFilter *CreateObject();
	//��� ��Ƶ�� ���� �Ƿ�仯 ��Ҫ ���³�ʼ�� ������ 
	bool CheckStreamChanged(sFfmpegVideoInfo &videoInfo, sFfmpegAudioInfo &audioInfo );
	int  ReCreateCodec();

protected:
	CFfmpegCodec *m_pFfmpegCodec;
	sFfmpegVideoInfo *m_pVideoInfo;
	sFfmpegAudioInfo *m_pAudioInfo;
	sFfmpegFrameInfo *m_pFrameInfo;
};
