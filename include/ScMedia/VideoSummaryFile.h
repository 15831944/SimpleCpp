#pragma once

#include <vector>
#include <list>
#include <map>
#include "MediaSdkDef.h"

using namespace std;

/*
* ���ڱ�����߶�ȡ ��ƵժҪ �ļ� ���� ��
* ��ƵժҪ�Ĵ洢��һ����ϵ��ļ��У��ɶ���ļ����ļ������
*  "video summary file"  "object [folder]"        "pic [folder]"   "video [folder]"
*                		     |                   	    |
*                		    object files         	 pictures
*/
#define OBJECT_FOLDER	"object"
#define PIC_FOLDER		"pic"
#define VIDEO_FOLDER	"video"
typedef long long int64_t;
//һ��ժҪ���� ÿ��ժҪ�ļ� �����ܶ��ժҪ���� 
//ÿ��ժҪ���� �����ܶ�� ժҪͼƬ 
namespace SimpleCpp{
	class CMutex;
}
using namespace SimpleCpp;

class TiXmlDocument;
class TiXmlNode;
class TiXmlElement;
class MEDIASDK_API CVideoSummaryFilePicture
{
	friend class  CVideoSummaryFile;
	friend class  CVideoSummaryFileObject;
public:
	CVideoSummaryFilePicture();
	~CVideoSummaryFilePicture();

	int SetData(char *pData, int nLen);
	int SetSize(int nW, int nH);
	int GetSize(int &nW, int &nH);
	int SetPos(int nX, int nY);
	int GetPos(int &nX, int &nY);
	//
	bool PointTest(int nX, int nY);
	//
	int SetBackground(char *pSzBkg);
	//ʱ���
	int64_t m_s64TimeStamp;
	int		m_nFrameIdInVideo;
	int     m_nObjectId;
	int     m_nPictureId;
	//���ֵ� ����
	int     m_nCount;

	int m_nPixFormat;
	char *GetFullPath(){return m_szFullPath;}
	char *GetFullBkgPath(){return m_szFullBkgPath;};
	char *GetBkgFile(){return m_szBkg;}

 
	//д���ʱ�������
	char *m_pData;
	int m_nDataLen;

	int m_nW;
	int m_nH;
	int m_nX;
	int m_nY;
	char m_szBkg[64];
	char m_szFile[64];
	//��ȡ��ʱ����
	char m_szFullPath[256];
	char m_szFullBkgPath[256];
	//
 
};
typedef enum  _eVideoSummaryFileObjectMoveCursor{
	eVSFOMC_Next = 0,
	eVSFOMC_Prev,
	eVSFOMC_NoMove,
}eVideoSummaryFileObjectMoveCursor;
class MEDIASDK_API CVideoSummaryFileObject
{
	friend class  CVideoSummaryFile;
public:
	CVideoSummaryFileObject();
	~CVideoSummaryFileObject();

	int Create(char *pSzFile);
	int Load(char *pSzFile);
	int Save();
	int Save(char *pSzFile);
	//˳���д�������ļ�
	int WritePicture(CVideoSummaryFilePicture *pPicture );
	int ReadPicture(CVideoSummaryFilePicture **pPicture, int nMoveFlag=eVSFOMC_Next);

	int Seek(int nPos);
	int GetPictureCount();
	int GetObjectId(){return m_nObjectId;};
	char *GetFile(){return m_szFile;};
protected:
	vector<CVideoSummaryFilePicture *> m_lstFrames;
	//
	int m_nObjectId;
	int m_nFrames;
	//�µ� һ֡�Ƿ� ������ 
	bool	m_bUpdated;
	//��Ӧ�� xml �ļ�
	TiXmlDocument *m_pXmlDoc;
	TiXmlElement *m_pElePos  ; //��ǰ node
	int			  m_nElePos;
	vector<TiXmlElement *> m_lstXmlItemPicture; //���ڶ�ȡ��ʱ��λ
	//
	char m_szFile[256];
	CVideoSummaryFile *m_pFile;
	//���ڶ�ȡ�� ����
	CVideoSummaryFilePicture *m_pPicture;
	//����ʼ��ʱ�� �ͽ�����ʱ��
	int64  m_s64BTS;
	int64  m_s64ETS;
	//��Ӧ �� vsfile�� node д���ʱ�����ڸ���ʱ��
	TiXmlElement *m_pEleInVsFile;
};
/*
* ʹ�� ���ļ� + ���� xml�ļ�
* ���ļ�ֻ�Ǵ����еĶ��� �����ļ��� �ö�����ϸ�� ֡���� 
*
*/
typedef enum _eVideoSummaryFileOpenMode{
	eVSFOM_Create = 1,
	eVSFOM_Read,
	eVSFOM_Write,
	eVSFOM_Trancate,
}eVideoSummaryFileOpenMode;
typedef enum _eVideoSummaryFileMoveCursor{
	eVSFMC_Next = 0,
	eVSFMC_Prev ,
	eVSFMC_NoMove,
}eVideoSummaryFileMoveCursor;
class MEDIASDK_API CVideoSummaryFile
{
public:
	CVideoSummaryFile(void);
	virtual ~CVideoSummaryFile(void);
	
	int Open(char *pSzFile, int nOpenMode = eVSFOM_Write);
	int Save();
	int Close();

	int WriteVideoInfo(int nW, int nH, int nTimeBaseNum, int nTimeBaseDen, int64 s64StartTimestamp=0);

	int WriteBackground(CVideoSummaryFilePicture *pPicture);
	//���� д���ʱ�� ����
	int BeginFrame();
	int WritePicture(CVideoSummaryFilePicture *pPicture);
	int EndFrame( );
	//��ȡ�ļ� ��Ҫ�����������ݣ� һ���� xml��node һ���� ��ȡ������ ���� �Ľṹ��
	//ʹ�� ָ�� ��Ϊ�˷�ֹ  vector ���ڴ� �ڿ�������䣬���ڿ������ͷţ����������
	int ReadFrame(vector<CVideoSummaryFilePicture*> **lstPicture, int nMoveCursor);
	//���ö�ȡ�ܶ�, 1-20 
	int SetDensity(int nDensity);
	char *GetFilePath(){return m_szPath;};
	//���ѡȡ �ӵ�ǰ֡�ܣ������ĵ� ѡȡ ͼƬ��
	int GetFramePicture(vector<CVideoSummaryFilePicture*> **lstPicture, int nX, int nY);
	//��ȡ��ǰ֡ͼƬ
	int GetFramePicture(vector<CVideoSummaryFilePicture*> **lstPicture);
	//���� ʱ�� ��ȡͼƬ 
	int GetPicture(vector<CVideoSummaryFilePicture*> **lstPicture, int64 s64TimeB, int64 s64TimeE);
	int GetPicture(vector<CVideoSummaryFilePicture*> **lstPicture, int &nObjectPos, int &nPicturePos , int nCount);
	//
	void GetBkgSize(int &nW, int  &nH){ nW = m_nW; nH = m_nH; };


	int GetPictureCount();
	//���� picture �� ����λ�ã� ��λ��
	int Seek(int nAbsPos);
	int Pos();
	//��ȡһ��ͼƬ��λ���Զ�����ƶ�
	int ReadPicture(CVideoSummaryFilePicture **pPicture);
	//���ն����ȡ
	int GetObjectCount();
	//����object id
	int GetObjectPictureCount(int nObjectIndex);
	//���� object ��� ��ȡ picture, Ч�ʺܵ͡������� ��ȡ��һ������ 
	int ReadObjectPicture(int nObjectIndex, int nPicIndex, CVideoSummaryFilePicture *pPicture);

	CVideoSummaryFileObject *GetVsObject(int nObjectIndex);
	void FreeVsObject(CVideoSummaryFileObject *pObject);

	void FreeObjectPicture(vector<CVideoSummaryFilePicture*> *lstPicture);
	//

	void GetTimeBase(int &nNum, int &nDen);
	int64 GetCurrTime();
	int64 GetTotalTime();
	int64 GetStartTimestamp();
	char *GetPath(){return m_szPath;};
protected:
	//
	TiXmlElement *GetChildElement(TiXmlElement *pXmlEle, int nPos);
	//�ĵ�����
	TiXmlDocument  *m_pXmlDoc;

	//TiXmlElement   *m_pEleRoot;
	//�����ļ���������
	char m_szFile[256]; //�����ļ�
	//�����ļ�����·��
	char m_szPath[256];
	//��ǰ ����ͼƬ����
	char m_szCurBkgFile[64];
	//��Ƶ������ ��� �߶�
	int m_nW;
	int m_nH;
	//���е� ���� [д��]
	vector<CVideoSummaryFileObject *> m_lstObject;
	//���� һ֡�Ķ���  �� ���� ��һ�� �ĶԱ�ʹ�� 
	list<CVideoSummaryFileObject *> m_lstLastFrameObject;
	//list<CVideoSummaryObject *> m_lstCurrFrameObject;
	map<int, CVideoSummaryFileObject *> m_mapId2Object;
	//for read 
	//��ǰ�� nodes�� ���ڶ�ȡ�� ����ͬʱ�� ��� node д��ֻ��һ�� 
	list<TiXmlElement *> m_lstCurEle;
	TiXmlElement      *m_pEleCursor;
	CVideoSummaryFileObject *m_pSummaryObject;
	int				   m_nElePos;
	int				   m_nAbsPos;//pic�ľ���λ��
	int					m_nTotalPicture;
	vector<TiXmlElement *> m_lstXmlItemObject; //���е� xml�ڵ㣬����ֱ�� �±�λ
	int m_nDensity; //��ȡ�ܶ�
	//���ڶ�ȡ��һ֡�� ͼƬ
	vector<CVideoSummaryFilePicture*> m_lstFramePicture;
	//ѡȡ ͼƬ�� ���棬
	//
	vector<CVideoSummaryFilePicture*> m_lstPictureGetTmp;
	//��ǰʱ���
	int64 m_s64TimeStamp;
	//��ǰ items ����Ľ���ʱ�䡣���� �ж� �Ƿ��� ʱ���Ͻ����� object
	int64 m_s64CurItemsEndTimeStamp;
	//
	int64 m_s64StartTimestamp;
	int64 m_s64EndTimestamp;
	//
	//��д��
	CMutex  *m_pMutextReadWrite;
};
