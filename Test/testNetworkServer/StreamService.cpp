#include "StdAfx.h"
#include "StreamService.h"
#include "Stream.h"

CStreamService::CStreamService(void)
: m_pStream(NULL)
{
}

CStreamService::~CStreamService(void)
{
	if (m_pStream)
	{
		delete m_pStream;
		m_pStream = NULL;
	}
}

int CStreamService::OnOpen()
{
	debug("%s: %d \n",__FUNCTION__, __LINE__);
	return 0;
}

// 
// int CStreamService::OnLogin(string& strUser , string& strPWD , OUT_P int& nReturn )
// {
// 	debug("%s: %s;%s; %d \n",__FUNCTION__, strUser.c_str(), strPWD.c_str(), nReturn);
// 	
// 	nReturn++;
// 	//������slot������� function�����������޷��յ��ظ�
// 
// 	return 0;
// }
// //���ɾ����
// int CStreamService::OnGetDevices(string& strName , OUT_P vector<CDeviceInfo*>& arrDevices)
// {
// 	debug("%s: %s\n", __FUNCTION__, strName.c_str());
// 	CDeviceInfo* pNewDevice = new CDeviceInfo();
// 	pNewDevice->m_strName = "111";
// 	pNewDevice->m_nId = 1;
// 	arrDevices.push_back(pNewDevice);
// 	return 0;
// }
