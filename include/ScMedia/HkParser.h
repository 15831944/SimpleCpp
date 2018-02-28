#pragma once
#include "packageparser.h"
#include "MediaSdkDef.h"

#define HK_PKG_MIN_LEN  (16*1024)
#define HK_PKG_MAX_LEN  (4*1024*1024)

class CHkParser :
	public CPackageParser
{
public:
	CHkParser(void);
	virtual ~CHkParser(void);


	virtual int Open(int nBufferCount=100);

	virtual int InputData(char *pData, int nLen);

	void SetParseAvdataEnd(bool bParse=false);
protected:
	virtual int ParsePackage(char *pData, int nLen, CFilterPinBuffer *pOut, int &nOutLen, int &nAvDataEndType);

	bool	m_bParseAvdataEnd;
	int		m_nFTMV;
	//���� ��ǰ�� avdata end �ṩ�� �������� nal�ְ�ʹ�á�
	sAvDataEnd m_avDataEnd;
	//���ڱ��� ����ְ� ȥ�� ftmv �� avdataend �� ����
	CFilterPinBuffer *m_pBufferStreamTmp; 

	CBuffer *m_pBufferStream;
	//��С��, ̫С�� �����ͳ�ȥ,
	int m_nMinLen;
};
