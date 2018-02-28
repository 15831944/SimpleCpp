#pragma once
#include "sourcefilter.h"

//��ʱ����Ҫ������ 
class CVideoSummaryFile;
class CVideoSummarySource :
	public CSourceFilter
{
public:
	CVideoSummarySource(void);
	virtual ~CVideoSummarySource(void);

	virtual int Init(char *pSzParam=0);
	virtual int DoFilter();

protected:
	virtual CDataFilter* CreateObject();

	CVideoSummaryFile *m_pFile;
};
