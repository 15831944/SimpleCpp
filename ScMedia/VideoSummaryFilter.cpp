#include "StdAfx.h"
#include "VideoSummaryFilter.h"

CVideoSummaryFilter g_regVideoSummary;
CVideoSummaryFilter::CVideoSummaryFilter(void)
:CDataFilter()
{
	strcpy(m_szKind, "VideoAnalyse");
	strcpy(m_szType, "VideoSummary");
	strcpy(m_szName, "VideoSummary");

	CFilterManager::RegistFilter(&g_regVideoSummary);
}

CVideoSummaryFilter::~CVideoSummaryFilter(void)
{
}
CDataFilter * CVideoSummaryFilter::CreateObject()
{
	return new CVideoSummaryFilter();
}
int CVideoSummaryFilter::Init( char *pParam )
{

	CDataFilter::Init(pParam);


	return 0;
}

int CVideoSummaryFilter::DoFilter()
{
	//ȡ���ݣ������� Ȼ�� ����� ������ʾ������

	return CDataFilter::DoFilter();
}


