#pragma once
#include "PackageParser.h"
#include "MediaSdkDef.h"

#ifdef WIN32
#ifdef VIVSMEDIABOX_EXPORTS
#define MEDIASDK_API __declspec(dllexport)
#else
#define MEDIASDK_API __declspec(dllimport)
#endif
#else
#define MEDIASDK_API
#define __stdcall
#endif

class CDataFilter;
class CMediaFilter;
class MEDIASDK_API CParserVivsH264 :
	public CPackageParser
{
public:
	CParserVivsH264(void);
	virtual ~CParserVivsH264(void);

	virtual int Init(int nBufferCount=10);

	virtual int InputData(char *pData, int nLen);
	virtual int DoFilter();
protected:	
	virtual CMediaFilter *CreateObject();
	virtual int ParsePackage(char *pData, int nLen, CFilterPinBuffer *pOut, int &nOutLen, int &nAvDataEndType);
	int ParseH264Nal(CFilterPinBuffer *pH264Stream, CFilterPinBuffer *pNal);

	//
	//
	bool	m_bParseAvdataEnd;
	int		m_nFTMV;
	//���� ��������buffer
	CFilterPinBuffer *m_pBufferInputTmp;

	//���ڱ��� ����ְ� ȥ�� ftmv �� avdataend �� ����
	CFilterPinBuffer *m_pBufferStreamTmp; 
	//ͬ�ϣ� ��Ƶ��
	CFilterPinBuffer *m_pBufferAudioStream;
	CFilterPinBuffer *m_pBufferVideoStream;
	bool    m_bFrameEnd;
	//���� ��ǰ�� avdata end �ṩ�� �������� nal�ְ�ʹ�á�
	sAvDataEnd m_avDataEnd;
};

extern CParserVivsH264 g_parserVivsH264;
