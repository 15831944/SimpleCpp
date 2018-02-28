#include "StdAfx.h"
#include "FilterManager.h"
#include "MediaFilter.h"
#include "SourceFilter.h"

//ʹ��ָ�룬��֤ �� �������� filter ������
//���� ��ʹ��ģ�� �� Ϊ�˷������ �� �����롣
CFilterManager *g_pFilterManager=NULL;

//���ڶ� g_pFilterManager ���Զ��ͷ�
class CFilterManagerDestructor{
public:
	CFilterManagerDestructor(){

	}
	~CFilterManagerDestructor(){
		if (g_pFilterManager )
		{
			delete g_pFilterManager;
			g_pFilterManager = NULL;
		}
	}
};
//�ͷ���
CFilterManagerDestructor g_managerDestructor;

CFilterManager::CFilterManager(void)
{
}

CFilterManager::~CFilterManager(void)
{
}

CFilterManager * CFilterManager::GetManager()
{
	if (g_pFilterManager == NULL)
	{
		g_pFilterManager = new CFilterManager();
	}
	return g_pFilterManager;
}
int CFilterManager::RegistFilter(CMediaFilter* pFilter)
{
	if (g_pFilterManager == NULL)
	{
		g_pFilterManager = new CFilterManager();
	}
	g_pFilterManager->RegistFilterImp(pFilter);

	return 0;
}

void CFilterManager::RegistFilterImp( CMediaFilter* pFilter )
{
	if (pFilter == NULL)
		return ;
	bool bExist = false;
	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilterTmp = m_lstFilter.at(i);
		if (/*strcmp(pFilterTmp->m_szKind, pFilter->m_szKind) ==0 
			&&*/ strcmp(pFilterTmp->m_szType, pFilter->m_szType) ==0 )
		{
			bExist = true;
			break;
		}
	}
	if (!bExist)
	{
		m_lstFilter.push_back(pFilter);
	}
	return ;
}

int CFilterManager::CreateFilter(char *pTypeName, CMediaFilter **pFilter)
{
	if (g_pFilterManager == NULL)
	{
		g_pFilterManager = new CFilterManager();
	}
	return g_pFilterManager->CreateFilterImp(pTypeName, pFilter);
}

int CFilterManager::CreateFilterImp( char *pTypeName, CMediaFilter **pFilter )
{
	CMediaFilter *pFilterFind = NULL;
	for (int i=0; i<m_lstFilter.size(); i++)
	{
		CMediaFilter *pFilterTmp = m_lstFilter.at(i);
		if (/*strcmp(pFilterTmp->m_szKind, pFilter->m_szKind) ==0 
			&&*/ strcmp(pFilterTmp->m_szType, pTypeName) == 0 )
		{
			pFilterFind = pFilterTmp;
			break;
		}
	}
	if (!pFilterFind)
	{
		*pFilter = NULL;
		return -1;
	}
	*pFilter = pFilterFind->CreateObject();
	return 0;
}

void CFilterManager::FreeFilter(CMediaFilter *pFilter)
{
	delete pFilter;
}

int CFilterManager::GetSourceFilter( vector<CSourceFilter*> &lstSourceFilter )
{
	CFilterManager *pFilterManager = GetManager();
	vector<CMediaFilter *> &lstFilter = pFilterManager->m_lstFilter;
	for (int i=0; i<lstFilter.size(); i++)
	{
		CMediaFilter *pFilterTmp = lstFilter.at(i);
		if (/*strcmp(pFilterTmp->m_szKind, pFilter->m_szKind) ==0 
			&&*/ strcmp(pFilterTmp->m_szKind, FILTER_KIND_SOURCE) == 0 )
		{
			
			if (strcmp(pFilterTmp->m_szName , FILTER_SOURCE_FFMPEG_FILE) == 0)
			{
				lstSourceFilter.insert(lstSourceFilter.begin(), 1, dynamic_cast<CSourceFilter*>(pFilterTmp) );
			}
			else
			{
				lstSourceFilter.push_back((CSourceFilter*)pFilterTmp );
			}
		}
	}

	return 0;
}
