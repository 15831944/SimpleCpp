#include "StdAfx.h"
#include "AudioDecoder.h"
#include "FfmpegCodec.h"

CAudioDecoder::CAudioDecoder(void)
:m_pFfmpeg(0)
{
}
 
CAudioDecoder::~CAudioDecoder(void)
{
	if (m_pFfmpeg)
	{
		delete m_pFfmpeg;
		m_pFfmpeg = NULL;
	}
}
int CAudioDecoder::Open(int nCodec)
{
	m_pFfmpeg = new CFfmpegCodec( /*(CodecID)nCodec*/);//CODEC_ID_H264
	
	return 0;
}
int CAudioDecoder::DoFilter()
{
	//ȡһ�� pin in�� prepared buffer
	
	//���룬���������ݷŵ� pin out �� prepared buffer
	
	//��pin in �� buffer �Żص� free buffer��

	return 0;
}