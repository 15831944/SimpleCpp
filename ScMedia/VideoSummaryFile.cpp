#include "StdAfx.h"
#include "VideoSummaryFile.h"
#include <io.h>
#include <string>
#include "tinyxml.h"
#include "Mutex.h"

#ifdef _WIN32
#include <direct.h>
#endif

CVideoSummaryFilePicture::CVideoSummaryFilePicture()
:m_pData(NULL)
, m_nDataLen(0)
, m_nObjectId(0)
, m_nPictureId(0)
, m_nW(0)
, m_nH(0)
, m_nX(0)
, m_nY(0)
, m_nCount(0)

{
	memset(m_szBkg, 0, sizeof(m_szBkg));
	memset(m_szFile, 0, sizeof(m_szFile));
	memset(m_szFullPath, 0, sizeof(m_szFullPath));
}
CVideoSummaryFilePicture::~CVideoSummaryFilePicture()
{
	if (m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}

}
int CVideoSummaryFilePicture::SetSize(int nW, int nH)
{
	m_nW = nW;
	m_nH = nH;
	return 0;
}
int CVideoSummaryFilePicture::GetSize(int &nW, int &nH)
{
	nW = m_nW;
	nH = m_nH;

	return 0;
}
int CVideoSummaryFilePicture::SetPos(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
	return 0;
}
int CVideoSummaryFilePicture::GetPos(int &nX, int &nY)
{
	nX = m_nX;
	nY = m_nY;
	return 0;
}
int CVideoSummaryFilePicture::SetData(char *pData, int nLen)
{
	if (m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}
	m_nDataLen = nLen;
	m_pData = new char[nLen];
	memcpy(m_pData, pData,  nLen);

	return 1;
}
int CVideoSummaryFilePicture::SetBackground(char *pSzBkg)
{
	strcpy(m_szBkg, pSzBkg);
	return 0;
}
bool CVideoSummaryFilePicture::PointTest(int nX, int nY)
{
	bool bRet = false;
	if ( nX>=m_nX &&  nX <= m_nX+m_nW
		&& nY>=m_nY && nY<= m_nY+m_nH)
	{
		bRet = true;
	}

	return bRet;
}

CVideoSummaryFileObject::CVideoSummaryFileObject()
: m_pXmlDoc(NULL)
, m_bUpdated(false)
, m_nFrames(0)
, m_pFile(NULL)
, m_pElePos(NULL)
, m_pPicture(NULL)
{

	m_pPicture = new CVideoSummaryFilePicture();
}
CVideoSummaryFileObject::~CVideoSummaryFileObject()
{
	if (m_pXmlDoc)
	{
		delete m_pXmlDoc;
		m_pXmlDoc = NULL;
	}
	if (m_pPicture)
	{
		delete m_pPicture;
		m_pPicture = NULL;
	}
	
}
int CVideoSummaryFileObject::Create(char *pSzFile)
{
	if (m_pXmlDoc)
	{
		return 2;
	}
	m_pXmlDoc = new TiXmlDocument();
	char *pSzXmlFile = "<?xml version=\"1.0\" ?>"
		"<VsObject></VsObject>";
	m_pXmlDoc->Parse(pSzXmlFile);

	strcpy(m_szFile, pSzFile);

	m_pXmlDoc->SaveFile(pSzFile);

	return 0;
}
int CVideoSummaryFileObject::Load(char *pSzFile)
{
	if (m_pXmlDoc)
	{
		return -1;
	}
	m_pXmlDoc = new TiXmlDocument();
	bool bRet = false;
	bRet = m_pXmlDoc->LoadFile(pSzFile);
	if (bRet)
	{
		m_pElePos = m_pXmlDoc->RootElement()->FirstChildElement();
	}
	else
	{
		delete m_pXmlDoc;
		m_pXmlDoc = NULL;
	}
	strcpy(m_szFile, pSzFile);

	while (m_pElePos != NULL)
	{
		m_lstXmlItemPicture.push_back(m_pElePos);
		m_pElePos = m_pElePos->NextSiblingElement();
	}
	m_pElePos = m_pXmlDoc->RootElement()->FirstChildElement();
	m_nElePos = 0;

	//m_pCurEle = 

	return 0;
}
int CVideoSummaryFileObject::Save()
{
	m_pXmlDoc->SaveFile(m_szFile);
	return 0;
}
int CVideoSummaryFileObject::Save(char *pSzFile)
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	m_pXmlDoc->SaveFile(pSzFile);
	return 0;
}

int CVideoSummaryFileObject::WritePicture(CVideoSummaryFilePicture *pPicture)
{

	TiXmlElement *pEleRoot = 0;
	pEleRoot = m_pXmlDoc->RootElement();
	TiXmlElement eleNew("Picture");

	char szName[64];
	sprintf(szName, "%d-%d.jpeg", pPicture->m_nObjectId, pPicture->m_nPictureId);
	eleNew.SetAttribute("name", szName);
	eleNew.SetAttribute("bkg",  pPicture->m_szBkg);
	eleNew.SetAttribute("x",  pPicture->m_nX);
	eleNew.SetAttribute("y",  pPicture->m_nY);
	eleNew.SetAttribute("w",  pPicture->m_nW);
	eleNew.SetAttribute("h",  pPicture->m_nH);

	//debug("%s: file: %s\n", __FUNCTION__, szName);
	//ʱ���
	char szTime[32];
	sprintf(szTime, "%I64d", pPicture->m_s64TimeStamp);
	eleNew.SetAttribute("pts",  szTime);

	m_pElePos = (TiXmlElement*)pEleRoot->InsertEndChild(eleNew);

	m_nFrames++;
	return 0;
}
int CVideoSummaryFileObject::ReadPicture(CVideoSummaryFilePicture **pPicture, int nMoveFlag/*=eVSFOMC_Next*/)
{
	
	if (!m_pElePos)
		return -1;
	TiXmlElement *pEle = m_pElePos->ToElement();
	
	const char *pName = pEle->Attribute("name");
	strcpy(m_pPicture->m_szFile, pName);

	sscanf(pName, "%d-%d", &(m_pPicture->m_nObjectId), &(m_pPicture->m_nPictureId));
	
	const char *pBkg = pEle->Attribute("bkg");
	strcpy(m_pPicture->m_szBkg, pBkg);

	pEle->Attribute("x", &(m_pPicture->m_nX));
	pEle->Attribute("y", &(m_pPicture->m_nY));
	pEle->Attribute("w", &(m_pPicture->m_nW));
	pEle->Attribute("h", &(m_pPicture->m_nH));
	const char *pTs = NULL;
	pTs = pEle->Attribute("pts");
	if (pTs)
		sscanf(pTs, "%I64d", &(m_pPicture->m_s64TimeStamp));

	
	
	m_pElePos = pEle->NextSiblingElement();

	
	*pPicture = m_pPicture;

	if (m_pPicture->m_nY < 0
		|| m_pPicture->m_nX < 0
		|| m_pPicture->m_nW < 0
		|| m_pPicture->m_nH < 0)
	{
		debug("%s, error\n", __FUNCTION__);
	}
	//debug("%s: pic: %s, bkg: %s,  pos[%d,%d] size[%d,%d]\n", 
	//	__FUNCTION__, pName, pBkg, m_pPicture->m_nX, m_pPicture->m_nY, m_pPicture->m_nW, m_pPicture->m_nH);

	return 0;
}
int CVideoSummaryFileObject::Seek(int nPos)
{
	TiXmlElement *pEleChild(NULL);
	if (!m_pXmlDoc)
	{
		return -1;
	}
	pEleChild = m_pXmlDoc->RootElement();
	if (!pEleChild)
		return -2;

	pEleChild = pEleChild->FirstChildElement();

	int nPosTmp = 0;
	while (pEleChild && nPosTmp < nPos)
	{
		pEleChild = pEleChild->NextSiblingElement();
		nPosTmp++;
	}
	if (nPosTmp != nPos)
	{//�Ƿ��ҵ�
		pEleChild = NULL;
		m_pElePos = NULL;
		return -4;
	}
	m_pElePos = pEleChild;

	return 0;
}
int CVideoSummaryFileObject::GetPictureCount()
{
	return m_lstXmlItemPicture.size();
}

CVideoSummaryFile::CVideoSummaryFile(void)
: m_pXmlDoc(NULL)
, m_nDensity(4)
, m_nH(0)
, m_nW(0)
, m_pMutextReadWrite(NULL)
, m_pSummaryObject(NULL)
, m_nTotalPicture(0)
, m_pEleCursor(NULL)
, m_s64StartTimestamp(0)
{
	memset(m_szFile, 0, sizeof(m_szFile));
	memset(m_szPath, 0, sizeof(m_szPath));
	memset(m_szCurBkgFile, 0, sizeof(m_szCurBkgFile));

	m_pMutextReadWrite = new CMutex();
}

CVideoSummaryFile::~CVideoSummaryFile(void)
{
 
	vector<CVideoSummaryFileObject*>::iterator item;
	for (item = m_lstObject.begin(); item != m_lstObject.end(); item++)
	{
		delete *item;
	}
	m_lstObject.clear();

	list<CVideoSummaryFileObject *>::iterator item1;
	for (item1 = m_lstLastFrameObject.begin(); item1 != m_lstLastFrameObject.end(); item1++)
	{
		CVideoSummaryFileObject *pObject = *item1;
		pObject->Save();
		delete pObject;
	}
	m_lstLastFrameObject.clear();
	m_mapId2Object.clear();
	if (m_pXmlDoc)
	{
		m_pXmlDoc->SaveFile(m_szFile);
		delete m_pXmlDoc;
		m_pXmlDoc = NULL;
	}
	for (int i=0; i<m_lstPictureGetTmp.size(); i++)
	{
		if (m_lstPictureGetTmp.at(i) == NULL)
			continue;
		delete m_lstPictureGetTmp.at(i);
		m_lstPictureGetTmp[i] = NULL;
	}
	m_lstPictureGetTmp.clear();

	if (m_pSummaryObject)
	{
		delete m_pSummaryObject;
		m_pSummaryObject = NULL;
	}

	if (m_pMutextReadWrite)
	{
		delete m_pMutextReadWrite;
		m_pMutextReadWrite = NULL;
	}
}
/*
*
*/
int CVideoSummaryFile::Open(char *pSzFile, int nOpenMode)
{
	if (m_pXmlDoc)
		return 1;
	//

	//
	m_nAbsPos = 0;

	strcpy(m_szFile, pSzFile);
	
	string str(pSzFile);
	int nPos = -1;
	nPos = str.find_last_of('\\');
	if (nPos == -1)
	{
		nPos = str.find_last_of('/');
	}
	if (nPos == -1)
	{//Ŀ¼�쳣
		return -1;
	}
	strncpy(m_szPath, pSzFile, nPos);

	m_pXmlDoc = new TiXmlDocument();
	/*FILE *pFileXml = NULL;
	if (nOpenMode & eVSFOM_Trancate)
	{//��ղ�����
		pFileXml = fopen(pSzFile, "w+b");
	}
	else  
	{//������� 
		// ��������ڣ� ��д�� �򴴽�
		if (nOpenMode & eVSFOM_Write)
		{
			if (0)
			{//����
				pFileXml = fopen(pSzFile, "r+b");
			}
			else
			{//�����ڣ�����
				pFileXml = fopen(pSzFile, "w+b");
			}
		}
		else if (nOpenMode & eVSFOM_Read)
		{
			pFileXml = fopen(pSzFile, "r+b");
		}
	}
	*/
	bool bExist = false;
	int nRet = 0;

	if (_access(pSzFile, 0) == -1)
	{
		bExist = false;
	}
	else
	{
		bExist = true;
	}
	bool bLoad = false;
	//������ڣ��� �򿪣�
	if (bExist)
	{
		bLoad = m_pXmlDoc->LoadFile(pSzFile);
		if (!bLoad)
		{
			delete m_pXmlDoc;
			m_pXmlDoc = NULL;
			return -1;
		}
		TiXmlElement *pNodeRoot = m_pXmlDoc->RootElement();
		if (pNodeRoot)
		{//���ڵ�����
			//char szBTS[64];
			//memset(szBTS, 0, sizeof(szBTS));
			const char *pSzBTS = 0;
			//��ʼʱ���, �ܶ���Ƶ ʱ��� ���� �� 0 ��ʼ�� 
			pSzBTS = pNodeRoot->Attribute("bts");
			if (pSzBTS)
			{
				sscanf(pSzBTS, "%I64d", &m_s64StartTimestamp);
			}
		}
		TiXmlElement *pNode;
		pNode = m_pXmlDoc->RootElement()->FirstChildElement();

/*		int nNodeCount = 0;*/
		while (pNode != NULL)
		{
			m_lstXmlItemObject.push_back(pNode);
			pNode = pNode->NextSiblingElement();
		}

		TiXmlElement *pNodeNew = m_pXmlDoc->RootElement()->FirstChildElement();
		if (pNodeNew != NULL)	
		{//wei��ĩβ�� ��ȡһ��object ����
			m_lstCurEle.push_back(pNodeNew);
			CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
			//��ȡ����
			const char *pBkgFile = pNodeNew->Attribute("bkg");
			strcpy(m_szCurBkgFile, pBkgFile);
			pNodeNew->Attribute("bkg-w", &m_nW);
			pNodeNew->Attribute("bkg-h", &m_nH);
			
			const char *pTs = NULL;
			//�� item��ʼ��ʱ���
			pTs = pNodeNew->Attribute("bts");
			if (pTs)
			{
				sscanf(pTs, "%I64d", &m_s64TimeStamp);
				//m_s64StartTimestamp = m_s64TimeStamp;
			}
			//����ʱ���
			pTs = pNodeNew->Attribute("ets");
			if (pTs)
			{
				sscanf(pTs, "%I64d", &m_s64CurItemsEndTimeStamp);
			}



			const char *pFile = pNodeNew->Attribute("name");
			char szFile[256];
			sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
			pObject->Load(szFile);
			debug("load new object: %s\n", szFile);
			m_lstLastFrameObject.push_back(pObject);
		}
		m_pEleCursor = m_pXmlDoc->RootElement()->FirstChildElement();
		m_nElePos = 0;
	}
	else
	{//��������ڣ��򴴽��µ�
		char *pSzXmlFile = "<?xml version=\"1.0\" ?>"
							"<VsFile bts=\"0\" ets=\"0\" ></VsFile>";
		m_pXmlDoc->Parse(pSzXmlFile);

		bLoad = true;
	}
	if (bLoad)
	{
		nRet = 0;
	}
	else
		nRet = -1;

	//fclose(pFileXml);
	//ȷ��Ŀ¼���ڡ�pic Ŀ¼�� object Ŀ¼
	char szSubDir[256];

	sprintf(szSubDir, "%s\\%s", m_szPath, PIC_FOLDER);
	if (_access(szSubDir, 0) == -1)
	{//������
		nRet = _mkdir(szSubDir);
		if (nRet == 0)
		{
			debug("mkdir pic folder success\n")
		}
		else
		{
			debug("mkdir pic folder false\n")
		}
	}
	sprintf(szSubDir, "%s\\%s", m_szPath, OBJECT_FOLDER);
	if (_access(szSubDir, 0) == -1)
	{//������
		nRet = _mkdir(szSubDir);
		if (nRet == 0)
		{
			debug("mkdir pic folder success\n")
		}
		else
		{
			debug("mkdir pic folder false\n")
		}
	}
	sprintf(szSubDir, "%s\\%s", m_szPath, VIDEO_FOLDER);
	if (_access(szSubDir, 0) == -1)
	{//������
		nRet = _mkdir(szSubDir);
		if (nRet == 0)
		{
			debug("mkdir pic folder success\n")
		}
		else
		{
			debug("mkdir pic folder false\n")
		}
	}

	return nRet;
}
int CVideoSummaryFile::Save()
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	m_pXmlDoc->SaveFile(m_szFile);

	return 0;
}
int CVideoSummaryFile::Close()
{
	if (!m_pXmlDoc)
		return -1;

	delete m_pXmlDoc;
	m_pXmlDoc = NULL;

	vector<CVideoSummaryFileObject*>::iterator item;
	for (item = m_lstObject.begin(); item != m_lstObject.end(); item++)
	{
		delete *item;
	}
	m_lstObject.clear();

	return 0;
}
int64 CVideoSummaryFile::GetCurrTime()
{
	return m_s64TimeStamp;
}
int64 CVideoSummaryFile::GetStartTimestamp()
{
	return m_s64StartTimestamp;
}
int64 CVideoSummaryFile::GetTotalTime()
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	const char *pETS = m_pXmlDoc->RootElement()->Attribute("ets");
	int nETS = 0;
	sscanf(pETS, "%d", &nETS);

	return nETS;
}
void CVideoSummaryFile::GetTimeBase(int &nNum, int &nDen)
{
	if (!m_pXmlDoc)
	{
		return ;
	}
	
	m_pXmlDoc->RootElement()->Attribute("VideoTimeBaseNum", &nNum);
	m_pXmlDoc->RootElement()->Attribute("VideoTimeBaseDen", &nDen);
}
int CVideoSummaryFile::GetObjectCount()
{

	return m_lstXmlItemObject.size();
	//
	if (!m_pXmlDoc)
	{
		return -1;
	}
	int nCount = 0;

	TiXmlElement *pNode = m_pXmlDoc->RootElement()->FirstChildElement();

	while(pNode)
	{
		nCount++;
		pNode = pNode->NextSiblingElement();
	}
	return nCount;
}
//����object id
int CVideoSummaryFile::GetObjectPictureCount(int nObjectIndex)
{
	if (nObjectIndex <0 || nObjectIndex >= m_lstXmlItemObject.size()-1)
	{
		return -1;
	}
	

	return 0;
}
//���� object ��� ��ȡ picture
int CVideoSummaryFile::ReadObjectPicture(int nObjectIndex, int nPicIndex, CVideoSummaryFilePicture *pPicture)
{
	if (nObjectIndex <0 || nObjectIndex > m_lstXmlItemObject.size()-1)
	{
		return -1;
	}
	if (!m_pXmlDoc)
	{
		return -1;
	}
	int nCount = 0;

	TiXmlElement *pNodeObject = 0;
	pNodeObject = m_lstXmlItemObject.at(nObjectIndex);
	if (!pNodeObject)
		return -1;
	//�������
	CVideoSummaryFileObject *pVsObject = new CVideoSummaryFileObject();
	//��ȡ����ͼƬ��Ϣ
	const char *pBkgFile = pNodeObject->Attribute("bkg");
	strcpy(m_szCurBkgFile, pBkgFile);
	pNodeObject->Attribute("bkg-w", &m_nW);
	pNodeObject->Attribute("bkg-h", &m_nH);

	const char *pFile = pNodeObject->Attribute("name");
	char szFile[256];
	sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
	pVsObject->Load(szFile);
	debug("%s: load new object: %s\n", __FUNCTION__, szFile);
	
	CVideoSummaryFilePicture *pPictureRead = 0;

	pVsObject->Seek(nPicIndex);
	pVsObject->ReadPicture(&pPictureRead);
	if (pPictureRead != NULL)
	{
		sprintf(pPictureRead->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szFile);
		sprintf(pPictureRead->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szBkg);
		*pPicture = *pPictureRead;
	}


	delete pVsObject;


	return 0;
}
void CVideoSummaryFile::FreeObjectPicture(vector<CVideoSummaryFilePicture*> *lstPicture)
{

}
CVideoSummaryFileObject *CVideoSummaryFile::GetVsObject(int nObjectIndex)
{
	if (nObjectIndex < 0 || nObjectIndex >= m_lstXmlItemObject.size())
	{
		return NULL;
	}

	TiXmlElement *pNodeObject = 0;
	pNodeObject = m_lstXmlItemObject.at(nObjectIndex);
	if (!pNodeObject)
		return NULL;
	//�������
	CVideoSummaryFileObject *pVsObject = new CVideoSummaryFileObject();
	//��ȡ����ͼƬ��Ϣ
	const char *pBkgFile = pNodeObject->Attribute("bkg");
	strcpy(m_szCurBkgFile, pBkgFile);
	pNodeObject->Attribute("bkg-w", &m_nW);
	pNodeObject->Attribute("bkg-h", &m_nH);
	//pNodeObject->Attribute("bkg-h", &(pVsObject->m_nObjectId) );

	const char *pFile = pNodeObject->Attribute("name");
	char szFile[256];
	sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
	pVsObject->Load(szFile);

	return pVsObject;
}
void CVideoSummaryFile::FreeVsObject(CVideoSummaryFileObject *pObject)
{
	delete pObject;
}
int CVideoSummaryFile::GetPictureCount()
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	if (m_nTotalPicture != 0)
		return m_nTotalPicture;

	int nTotal= 0;

	TiXmlElement *pNode = m_pXmlDoc->RootElement()->FirstChildElement();

	while(pNode)
	{
		int nCount = 0;
		pNode->Attribute("count", &nCount);
		nTotal += nCount;
		pNode = pNode->NextSiblingElement();
	}
	m_nTotalPicture = nTotal;

	return nTotal;
}
int CVideoSummaryFile::Pos()
{
	return m_nAbsPos;
}
//���� picture �� ����λ�ã� ��λ��
int CVideoSummaryFile::Seek(int nAbsPos)
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	if (nAbsPos < 0  )
		nAbsPos = 0;
	if (nAbsPos >  GetPictureCount() - 1)
		nAbsPos = GetPictureCount() ;
	//debug("%s: %d\n", __FUNCTION__, nAbsPos);

	if (m_pSummaryObject)
	{
		delete m_pSummaryObject;
		m_pSummaryObject = NULL;
	}

	int nPos= 0;

	TiXmlElement *pNode = m_pXmlDoc->RootElement()->FirstChildElement();
	TiXmlElement *pNodeNext = NULL;
	int nLastObjectPictureCount = 0;
	while(pNode && nPos < nAbsPos)
	{
		int nCount = 0;
		pNode->Attribute("count", &nCount);
		nPos += nCount;
		nLastObjectPictureCount = nCount;
		pNodeNext = pNode->NextSiblingElement();
		if (pNodeNext == NULL)
		{
			break;
		}
		pNode = pNodeNext;
	}
	if (nPos < nAbsPos)
	{
		m_pEleCursor = pNode;
		
		//return nPos;
	}
	if (pNodeNext == NULL)
	{//��ĩβ��
		m_pEleCursor = pNode;
	}
	else
	{//û��ĩβ
		TiXmlNode *pPrevNode = pNode->PreviousSibling();
		if (pPrevNode)
			m_pEleCursor = pPrevNode->ToElement();
		else
			m_pEleCursor = pNode->ToElement();
	}
	if (m_pEleCursor == NULL)
		return -1;
	//���¶�λ
	int nPicInObject = nLastObjectPictureCount - (nPos - nAbsPos);
	
	m_pSummaryObject = new CVideoSummaryFileObject;
	//��ȡ����ͼƬ��Ϣ
	const char *pBkgFile = m_pEleCursor->Attribute("bkg");
	strcpy(m_szCurBkgFile, pBkgFile);
	m_pEleCursor->Attribute("bkg-w", &m_nW);
	m_pEleCursor->Attribute("bkg-h", &m_nH);

	const char *pFile = m_pEleCursor->Attribute("name");
	char szFile[256];
	sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
	int nRet = 0 ;
	nRet = m_pSummaryObject->Load(szFile);
	m_pSummaryObject->Seek(nPicInObject);

	m_nAbsPos = nAbsPos;
	
	return 0;
}
//��ȡһ��ͼƬ��λ���Զ�����ƶ�
int CVideoSummaryFile::ReadPicture(CVideoSummaryFilePicture **pPicture)
{
	if (!m_pXmlDoc || !m_pEleCursor)
	{
		return -1;
	}
	CVideoSummaryFilePicture *pPictureRead = NULL;
	if (!m_pSummaryObject)
	{
		m_pSummaryObject = new CVideoSummaryFileObject();
		//��ȡ����ͼƬ��Ϣ
		const char *pBkgFile = m_pEleCursor->Attribute("bkg");
		strcpy(m_szCurBkgFile, pBkgFile);
		m_pEleCursor->Attribute("bkg-w", &m_nW);
		m_pEleCursor->Attribute("bkg-h", &m_nH);

		const char *pFile = m_pEleCursor->Attribute("name");
		char szFile[256];
		sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
		int nRet = 0 ;
		nRet = m_pSummaryObject->Load(szFile);
	}

	int nRet = 0;
	nRet = m_pSummaryObject->ReadPicture(&pPictureRead);
	if (pPictureRead)
	{
		sprintf(pPictureRead->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szBkg);
		sprintf(pPictureRead->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szFile);

	}
	else 
	{//��ȡʧ�ܣ� �ƶ�����һ�� object 
		if (!m_pEleCursor)
			return -1;
		m_pEleCursor = m_pEleCursor->NextSiblingElement();
		if (!m_pEleCursor)
			return -2;
		delete m_pSummaryObject;
		m_pSummaryObject = new CVideoSummaryFileObject();
		//��ȡ����ͼƬ��Ϣ
		const char *pBkgFile = m_pEleCursor->Attribute("bkg");
		strcpy(m_szCurBkgFile, pBkgFile);
		m_pEleCursor->Attribute("bkg-w", &m_nW);
		m_pEleCursor->Attribute("bkg-h", &m_nH);

		const char *pFile = m_pEleCursor->Attribute("name");
		char szFile[256];
		sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
		
		nRet = m_pSummaryObject->Load(szFile);

		nRet = m_pSummaryObject->ReadPicture(&pPictureRead);
		if (pPictureRead)
		{
			sprintf(pPictureRead->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szBkg);
			sprintf(pPictureRead->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPictureRead->m_szFile);
		}
		
	}
	*pPicture = pPictureRead;
	m_nAbsPos++;

	return nRet;
}
int CVideoSummaryFile::WriteVideoInfo(int nW, int nH, int nTimeBaseNum, int nTimeBaseDen, int64 s64StartTimestamp)
{
	if (!m_pXmlDoc)
	{
		return -1;
	}
	m_pXmlDoc->RootElement()->SetAttribute("VideoWidth", nW);
	m_pXmlDoc->RootElement()->SetAttribute("VideoHeidht", nH);
	m_pXmlDoc->RootElement()->SetAttribute("VideoTimeBaseNum", nTimeBaseNum);
	m_pXmlDoc->RootElement()->SetAttribute("VideoTimeBaseDen", nTimeBaseDen);
	char szTimestamp[64];
	memset(szTimestamp, 0, sizeof(szTimestamp));
	sprintf(szTimestamp, "%I64d", m_s64StartTimestamp);
	m_pXmlDoc->RootElement()->SetAttribute("bts", szTimestamp);
	m_s64StartTimestamp = s64StartTimestamp;
 
	memset(szTimestamp, 0, sizeof(szTimestamp));
	sprintf(szTimestamp, "%I64d", m_s64StartTimestamp);
	m_pXmlDoc->RootElement()->SetAttribute("ets", szTimestamp);

	

	return 0 ;
}
//д�뱳��
int CVideoSummaryFile::WriteBackground(CVideoSummaryFilePicture *pPicture)
{
	FILE *pFilePic = 0;
	char szPicPath[256];
	sprintf(szPicPath, "%s\\%s\\bkg-%d.jpeg", m_szPath, PIC_FOLDER,  pPicture->m_nPictureId);
	pFilePic = fopen(szPicPath, "w+b");
	if (pFilePic)
	{
		fwrite(pPicture->m_pData, 1, pPicture->m_nDataLen, pFilePic);
		fclose(pFilePic);
	}
	m_nW = pPicture->m_nW;
	m_nH = pPicture->m_nH;
	sprintf(m_szCurBkgFile, "bkg-%d.jpeg", pPicture->m_nPictureId);

	return 0;
}
int CVideoSummaryFile::BeginFrame()
{
	//д�룺
	//�����±�� ���, ��� һ������ �ڸ�֡ û���µ�����д�룬���� �ö�����ʧ�� 
	list<CVideoSummaryFileObject *>::iterator item;
	for (item = m_lstLastFrameObject.begin(); item != m_lstLastFrameObject.end(); item++)
	{
		CVideoSummaryFileObject *pObject = *item;
		pObject->m_bUpdated = false;
	}
	return 0;
}
int CVideoSummaryFile::WritePicture(CVideoSummaryFilePicture *pPicture)
{
	if (!m_pXmlDoc)
		return -1;
	//����ʱ��
	m_pXmlDoc->RootElement()->SetAttribute("ets", (int)pPicture->m_s64TimeStamp);
	//����id ���Ҷ��� 
	CVideoSummaryFileObject *pObject = 0;
	
	pPicture->SetBackground(m_szCurBkgFile);

	map<int, CVideoSummaryFileObject*>::iterator item;
	item = m_mapId2Object.find(pPicture->m_nObjectId);
	if (item != m_mapId2Object.end() && item->second != NULL)
	{//���ҵ�
		pObject = item->second;
		pObject->m_bUpdated = true;
		pObject->WritePicture(pPicture);
		//debug("old object pic to save\n");
		//���½���ʱ��
		char szTime[32];
		sprintf(szTime, "%I64d", pPicture->m_s64TimeStamp);
		//	pObject->m_pEleInVsFile->SetAttribute("bts", szTime);
		pObject->m_pEleInVsFile->SetAttribute("ets", szTime);
		pObject->m_pEleInVsFile->SetAttribute("count", pObject->m_nFrames);
	}
	else
	{//δ�ҵ�
		debug("new object to save\n");
		pObject = new CVideoSummaryFileObject;
		pObject->m_nObjectId = pPicture->m_nObjectId;
		pObject->m_bUpdated = true;

		m_lstLastFrameObject.push_back(pObject);
		m_mapId2Object[pObject->m_nObjectId] = pObject;

		char szObjectPath[256];
		sprintf(szObjectPath, "%s\\%s\\%d.vso", m_szPath, OBJECT_FOLDER, pObject->m_nObjectId);
		pObject->Create(szObjectPath);
		pObject->WritePicture(pPicture);
		//��ӵ� xml ���ļ��ڵ�
		TiXmlElement *pEleRoot = 0;
		pEleRoot = m_pXmlDoc->RootElement();
		TiXmlElement eleNew("VsObject");
		char szObject[64];
		sprintf(szObject, "%d.vso", pObject->m_nObjectId);
		eleNew.SetAttribute("name", szObject);
		//����ͼƬ ���� 
		eleNew.SetAttribute("bkg", m_szCurBkgFile);
		eleNew.SetAttribute("bkg-w", m_nW);
		eleNew.SetAttribute("bkg-h", m_nH);
		//��ʼ�ͽ���ʱ��
		char szTime[32];
		sprintf(szTime, "%I64d", pPicture->m_s64TimeStamp);
		eleNew.SetAttribute("bts", szTime);
		eleNew.SetAttribute("ets", szTime);
	
		//��¼���ڸ���ʱ��
		pObject->m_pEleInVsFile = (TiXmlElement*)(pEleRoot->InsertEndChild(eleNew));
		//���¶���ͼƬ������
		pObject->m_pEleInVsFile->SetAttribute("count", pObject->m_nFrames);
		//
	}
	//pObject->Save();
	//�����ļ�
	FILE *pFilePic = 0;
	char szPicPath[256];
	sprintf(szPicPath, "%s\\%s\\%d-%d.jpeg", m_szPath, PIC_FOLDER, pObject->m_nObjectId, pPicture->m_nPictureId);
	pFilePic = fopen(szPicPath, "w+b");
	if (pFilePic)
	{
		fwrite(pPicture->m_pData, 1, pPicture->m_nDataLen, pFilePic);
		fclose(pFilePic);
	}
	//������һ�������� ֮�� ����һ��
	//Save();
	//
	return 0;
}
int CVideoSummaryFile::EndFrame( )
{
	//��������  object �ر�

	//
	list<CVideoSummaryFileObject *>::iterator item;
	for (item = m_lstLastFrameObject.begin(); item != m_lstLastFrameObject.end(); /*item++*/)
	{
		CVideoSummaryFileObject *pObject = *item;
		if (!pObject->m_bUpdated)
		{//�����Ѿ�������Ӧ��ɾ�� һ������ 
			pObject->Save();
			//�� map �Ƴ�
			map<int, CVideoSummaryFileObject*>::iterator itemMap;
			itemMap = m_mapId2Object.find(pObject->m_nObjectId);
			if (itemMap != m_mapId2Object.end())
			{//���ҵ�
				m_mapId2Object.erase(itemMap);
			}

			item = m_lstLastFrameObject.erase(item);

			delete pObject;
		}
		else
		{
			item++;
		}
	}
	
	//
	return 0;
}
//��ȡ һ֡ ��ͼƬ�� �����кܶ�������ͼƬ
int CVideoSummaryFile::ReadFrame(vector<CVideoSummaryFilePicture*> **lstPicture, int nMoveCursor)
{
	m_pMutextReadWrite->Lock();
	m_lstFramePicture.clear();
	m_pMutextReadWrite->Unlock();
	if (!m_pXmlDoc)
		return -1;

	int nRet = 0;
	//��ȡ ���ļ��� object ����
/*	if (m_lstCurEle.size() <= 0)
	{
		TiXmlElement *pEle = m_pXmlDoc->RootElement()->FirstChildElement();
		m_lstCurEle.push_back(pEle);
	}*/
	//����ʱ�������ȡ��ʱ�佻���� item;
	while (m_pEleCursor)
	{
		if (nMoveCursor == eVSFMC_Next)
		{
			TiXmlElement *pNodeTail = m_pEleCursor;
			
			TiXmlElement *pNodeNew = pNodeTail->NextSiblingElement();
			if (pNodeNew == NULL)
				break;
			int64 s64ETS(0), s64BTS(0);

			const char *pTs = NULL;
			pTs = pNodeNew->Attribute("bts");
			if (pTs)
				sscanf(pTs, "%I64d", &s64BTS);
			pTs = pNodeNew->Attribute("ets");
			if (pTs)
				sscanf(pTs, "%I64d", &s64ETS);
			//item�� ��ʼʱ��� ʱ��� С��˵���ü���һ��ͼƬ
			if (s64BTS < m_s64TimeStamp)
			{

				m_lstCurEle.push_back(pNodeNew);
				CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
				//��ȡ����ͼƬ��Ϣ
				const char *pBkgFile = pNodeNew->Attribute("bkg");
				strcpy(m_szCurBkgFile, pBkgFile);
				pNodeNew->Attribute("bkg-w", &m_nW);
				pNodeNew->Attribute("bkg-h", &m_nH);
				pObject->m_s64BTS = s64BTS;
				pObject->m_s64ETS = s64ETS;

				const char *pFile = pNodeNew->Attribute("name");
				char szFile[256];
				sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
				pObject->Load(szFile);
				debug("load new object: %s\n", szFile);
				m_lstLastFrameObject.push_back(pObject);
				m_pEleCursor = pNodeNew;
			}
			else{
				//ʱ�䲻��
				break;
			}
		}
	}
	//�����ܶ� ��ȡ���� ����
	while (m_lstCurEle.size() < m_nDensity && m_pEleCursor)
	{
		if (nMoveCursor == eVSFMC_Next)
		{
			TiXmlElement *pNodeTail = m_pEleCursor;
			TiXmlElement *pNodeNew = pNodeTail->NextSiblingElement();
			if (pNodeNew == NULL)	
			{//��ĩβ��
				//nRet = -1;
				break;
			}
			m_pEleCursor = pNodeNew;

			m_lstCurEle.push_back(pNodeNew);
			CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
			//��ȡ����ͼƬ��Ϣ
			const char *pBkgFile = pNodeNew->Attribute("bkg");
			strcpy(m_szCurBkgFile, pBkgFile);
			pNodeNew->Attribute("bkg-w", &m_nW);
			pNodeNew->Attribute("bkg-h", &m_nH);

			const char *pFile = pNodeNew->Attribute("name");
			char szFile[256];
			sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
			pObject->Load(szFile);
			debug("load new object: %s\n", szFile);
			m_lstLastFrameObject.push_back(pObject);
		}
		else if (nMoveCursor == eVSFMC_Prev)
		{
			TiXmlElement *pNodeHead = m_pEleCursor;//m_lstCurEle.front();
			TiXmlElement *pNodeNew = (TiXmlElement*)pNodeHead->PreviousSibling();
			if (pNodeNew == NULL)	
			{//����ʼ�ˣ�û���µ���
				//nRet = -1;
				break;
			}
			m_pEleCursor = pNodeNew;

			m_lstCurEle.push_front(pNodeNew);
			CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
			
			//��ȡ����ͼƬ��Ϣ
			const char *pBkgFile = pNodeNew->Attribute("bkg");
			strcpy(m_szCurBkgFile, pBkgFile);
			pNodeNew->Attribute("bkg-w", &m_nW);
			pNodeNew->Attribute("bkg-h", &m_nH);
			//��ȡ������Ϣ 
			const char *pFile = pNodeNew->Attribute("name");
			char szFile[256];
			sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
			pObject->Load(szFile);

			debug("load new object: %s\n", szFile);

			m_lstLastFrameObject.push_front(pObject);
		}

	}
	//���ݶ��� ��ȡ����� ֡ 
	list<CVideoSummaryFileObject*> ::iterator item;
	int nPicMoveFlag = 0;
	if (nMoveCursor == eVSFMC_Next)
	{
		nPicMoveFlag = eVSFOMC_Next;
	}
	else
		nPicMoveFlag = eVSFOMC_Prev;
	//���ݻ�ȡ�Ķ��󣬶�ȡһ֡ ���� ͼƬ
	//
	m_pMutextReadWrite->Lock();
	for (item=m_lstLastFrameObject.begin(); item != m_lstLastFrameObject.end(); )
	{
		CVideoSummaryFileObject *pObject = *item;
		CVideoSummaryFilePicture *pPicture = 0;
		pObject->ReadPicture(&pPicture, nPicMoveFlag);
		if (pPicture == NULL)
		{//��ȡ������ ��������, �����ٴ����� ��������� 
			// ɾ�� m_lstCurEle �Ķ�Ӧ����
			list<TiXmlElement *>::iterator item1;
			for (item1 = m_lstCurEle.begin(); item1 != m_lstCurEle.end(); )
			{
				TiXmlElement *pEle = *item1;
				const char *pFile = pEle->Attribute("name");
				char szFile[256];
				sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
				if (strcmp(szFile, pObject->m_szFile) == 0)
				{
					item1 = m_lstCurEle.erase(item1);
					//��Ҫ�ٶ���һ�� 
				}
				else
				{
					item1++;
				}
			}
			delete pObject;
			item = m_lstLastFrameObject.erase(item);
			//�����µ� ����
			while (m_lstCurEle.size() < m_nDensity && m_pEleCursor)
			{
				if (nMoveCursor == eVSFMC_Next)
				{
					TiXmlElement *pNodeTail = m_pEleCursor;
					TiXmlElement *pNodeNew = pNodeTail->NextSiblingElement();
					if (pNodeNew == NULL)	
					{//��ĩβ��
						//nRet = -1;
						break;
					}
					m_pEleCursor = pNodeNew;

					m_lstCurEle.push_back(pNodeNew);
					CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
					//��ȡ����ͼƬ��Ϣ
					const char *pBkgFile = pNodeNew->Attribute("bkg");
					strcpy(m_szCurBkgFile, pBkgFile);
					pNodeNew->Attribute("bkg-w", &m_nW);
					pNodeNew->Attribute("bkg-h", &m_nH);

					const char *pFile = pNodeNew->Attribute("name");
					char szFile[256];
					sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
					pObject->Load(szFile);
					debug("load new object: %s\n", szFile);
					m_lstLastFrameObject.push_back(pObject);
					
					pObject->ReadPicture(&pPicture, nPicMoveFlag);
					break;
				}
				else if (nMoveCursor == eVSFMC_Prev)
				{
					TiXmlElement *pNodeHead = m_pEleCursor;//m_lstCurEle.front();
					TiXmlElement *pNodeNew = (TiXmlElement*)pNodeHead->PreviousSibling();
					if (pNodeNew == NULL)	
					{//����ʼ�ˣ�û���µ���
						//nRet = -1;
						break;
					}
					m_pEleCursor = pNodeNew;

					m_lstCurEle.push_front(pNodeNew);
					CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();

					//��ȡ����ͼƬ��Ϣ
					const char *pBkgFile = pNodeNew->Attribute("bkg");
					strcpy(m_szCurBkgFile, pBkgFile);
					pNodeNew->Attribute("bkg-w", &m_nW);
					pNodeNew->Attribute("bkg-h", &m_nH);
					//��ȡ������Ϣ 
					const char *pFile = pNodeNew->Attribute("name");
					char szFile[256];
					sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
					pObject->Load(szFile);

					debug("load new object: %s\n", szFile);

					m_lstLastFrameObject.push_front(pObject);
				}
				
			}

		}
		if (pPicture != NULL)
		{//��ȷ��ȡ��
			if (pPicture->m_nW < 0
				|| pPicture->m_nH <0
				|| pPicture->m_nX < 0
				|| pPicture->m_nY < 0)
			{
				debug("%s, pic error\n", __FUNCTION__);
			}
			m_lstFramePicture.push_back(pPicture);
			if (m_lstFramePicture.size() > 9)
			{
				debug("%s, pic error, size to many\n", __FUNCTION__);
			}

			m_s64TimeStamp = pPicture->m_s64TimeStamp;
			//
			sprintf(pPicture->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPicture->m_szFile);
			sprintf(pPicture->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pPicture->m_szBkg);
			
			
			if (item == m_lstLastFrameObject.end())
			{
				break;
			}
			else
			{
				item++;
			}
		}
	}
	m_pMutextReadWrite->Unlock();
	*lstPicture = &m_lstFramePicture;

	if (m_lstFramePicture.size() > 9)
	{
		debug("%s, pic error, size to many\n", __FUNCTION__);
	}
	
	if (m_lstFramePicture.size() <= 0)
		nRet = -1;

	return nRet;
}
//�ӵ�ǰ֡���� ����ѡȡ �� x y ���ڵ� ͼƬ
int CVideoSummaryFile::GetFramePicture(vector<CVideoSummaryFilePicture*> **lstPicture, int nX, int nY)
{
	for (int i=0; i<m_lstPictureGetTmp.size(); i++)
	{
		delete m_lstPictureGetTmp.at(i);
	}
	m_lstPictureGetTmp.clear();

	m_pMutextReadWrite->Lock();
	for (int i=0; i<m_lstFramePicture.size(); i++)
	{
		CVideoSummaryFilePicture *pPicture = m_lstFramePicture.at(i);
		if (!pPicture)
			continue;
		if (pPicture->PointTest(nX, nY))
		{//ѡ��
			CVideoSummaryFilePicture *pNewGetPicture = new CVideoSummaryFilePicture;
			*pNewGetPicture = *pPicture;
			m_lstPictureGetTmp.push_back(pNewGetPicture);
		}
	}
	m_pMutextReadWrite->Unlock();

	*lstPicture = &m_lstPictureGetTmp;

	return 0;
}
//��ȡ��ǰ֡ͼƬ
int CVideoSummaryFile::GetFramePicture(vector<CVideoSummaryFilePicture*> **lstPicture)
{
	for (int i=0; i<m_lstPictureGetTmp.size(); i++)
	{
		delete m_lstPictureGetTmp.at(i);
	}
	m_lstPictureGetTmp.clear();

	m_pMutextReadWrite->Lock();
	for (int i=0; i<m_lstFramePicture.size(); i++)
	{
		CVideoSummaryFilePicture *pPicture = m_lstFramePicture.at(i);
		if (!pPicture)
			continue;

		CVideoSummaryFilePicture *pNewGetPicture = new CVideoSummaryFilePicture;
		*pNewGetPicture = *pPicture;
		m_lstPictureGetTmp.push_back(pNewGetPicture);

	}
	m_pMutextReadWrite->Unlock();

	*lstPicture = &m_lstPictureGetTmp;

	return 0;
}
//���� ʱ�� ��ȡͼƬ 
//ͬһ�� ����ķ���һ�𡣶���
//����λ�ã� ��ȡָ��������ͼƬ
//
int CVideoSummaryFile::GetPicture(vector<CVideoSummaryFilePicture*> **lstPicture, int64 s64TimeB, int64 s64TimeE)
{
	for (int i=0; i<m_lstPictureGetTmp.size(); i++)
	{
		delete m_lstPictureGetTmp.at(i);
	}
	m_lstPictureGetTmp.clear();

	//

	//

	return 0;
}
//���� object pos   picture pos ��ȡͼƬ
int CVideoSummaryFile::GetPicture(vector<CVideoSummaryFilePicture*> **lstPicture, int &nObjectPos, int &nPicturePos, int nCount)
{
	for (int i=0; i<m_lstPictureGetTmp.size(); i++)
	{
		delete m_lstPictureGetTmp.at(i);
	}
	m_lstPictureGetTmp.clear();
	if (!m_pXmlDoc)
		return -1;
	
	TiXmlElement *pEleObject = NULL;
	pEleObject = GetChildElement(m_pXmlDoc->RootElement(), nObjectPos);
	if (!pEleObject)
	{
		return -1;
	}
	int nRead = 0;
	//�ȶ�ȡ��һ�� element object
	CVideoSummaryFileObject *pObject = new CVideoSummaryFileObject();
	//��ȡ����ͼƬ��Ϣ
	const char *pBkgFile = pEleObject->Attribute("bkg");
	strcpy(m_szCurBkgFile, pBkgFile);
	pEleObject->Attribute("bkg-w", &m_nW);
	pEleObject->Attribute("bkg-h", &m_nH);

	const char *pFile = pEleObject->Attribute("name");
	char szFile[256];
	sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
	int nRet = 0 ;
	nRet = pObject->Load(szFile);
	if (nRet < 0)
	{
		delete pObject;
	}
	debug("load new object: %s\n", szFile);
	pObject->Seek(nPicturePos);
	do
	{
		CVideoSummaryFilePicture *pPicture = 0;
		nRet = pObject->ReadPicture(&pPicture, eVSFOMC_Next);
		if (nRet < 0)
		{
			debug("read false, at end of object: object: %d, pic %d\n", nObjectPos, nPicturePos);
			break;
		}
		nPicturePos++;
		nRead++;
		CVideoSummaryFilePicture *pNewPicture = new CVideoSummaryFilePicture;
		*pNewPicture = *pPicture;

		sprintf(pNewPicture->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pNewPicture->m_szBkg);
		sprintf(pNewPicture->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pNewPicture->m_szFile);
		m_lstPictureGetTmp.push_back(pNewPicture);
		
	}while(nRead < nCount);
	delete pObject;

	//��ȡ�ļ�����һ��object de picture ��������ȡ����� ojbect
	pEleObject = pEleObject->NextSiblingElement();
	while (nRead < nCount && pEleObject)
	{
		nObjectPos++;
		nPicturePos = 0;
		pObject = new CVideoSummaryFileObject();
		//��ȡ����ͼƬ��Ϣ
		const char *pBkgFile = pEleObject->Attribute("bkg");
		strcpy(m_szCurBkgFile, pBkgFile);
		pEleObject->Attribute("bkg-w", &m_nW);
		pEleObject->Attribute("bkg-h", &m_nH);

		const char *pFile = pEleObject->Attribute("name");
		char szFile[256];
		sprintf(szFile, "%s\\%s\\%s", m_szPath, OBJECT_FOLDER, pFile);
		int nRet = 0 ;
		nRet = pObject->Load(szFile);
		if (nRet >= 0)
		{
			debug("load new object: %s\n", szFile);
			do
			{
				CVideoSummaryFilePicture *pPicture = 0;
				nRet = pObject->ReadPicture(&pPicture, eVSFOMC_Next);
				if (nRet < 0)
					break;
				nPicturePos++;
				nRead++;
				CVideoSummaryFilePicture *pNewPicture = new CVideoSummaryFilePicture;
				*pNewPicture = *pPicture;
				sprintf(pNewPicture->m_szFullBkgPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pNewPicture->m_szBkg);
				sprintf(pNewPicture->m_szFullPath, "%s\\%s\\%s", m_szPath, PIC_FOLDER, pNewPicture->m_szFile);
				m_lstPictureGetTmp.push_back(pNewPicture);

			}while(nRead < nCount);
		}
		delete pObject;

		pEleObject = pEleObject->NextSiblingElement();
	} 
	
	*lstPicture = &m_lstPictureGetTmp;

	return 0;
}
TiXmlElement *CVideoSummaryFile::GetChildElement(TiXmlElement *pXmlEle, int nPos)
{

	TiXmlElement *pEleChild(NULL);
	if (!pXmlEle)
	{
		return pEleChild;
	}
	pEleChild = pXmlEle->FirstChildElement();
	int nPosTmp = 0;
	while (pEleChild && nPosTmp < nPos)
	{
		pEleChild = pEleChild->NextSiblingElement();
		nPosTmp++;
	}
	if (nPosTmp != nPos)
	{//�Ƿ��ҵ�
		pEleChild = NULL;
	}

	return pEleChild;
}

int CVideoSummaryFile::SetDensity( int nDensity )
{
	m_nDensity = nDensity;

	return 0;
}
