#pragma once

#include <string>
#include <map>

using namespace std;

class CFileTags;
class CTag;
//ת���ṹ�� Դ����
//
class CTrans2Source
{
public:
	CTrans2Source(void);
	virtual ~CTrans2Source(void);
	//
	void	SetFileTags(CFileTags* pFileTags){ m_pFileTags = pFileTags;};
	void	SetClientFileName(string& strName){ m_strClientFileName = strName;};
	void	SetServerFileName(string& strName){m_strServerFileName = strName;};
	void	SetModuleIfFileName(string& strName){m_strModuleIfFileName = strName;}

	int		Open();
	void	Close();
	//

	//��ʼת��
	int		Trans();	
	//
	//
	void	Trans2Server( );
	void	Trans2Client();
	//ת�� tag ��Դ����
//	int		TransTag2Source(CFileTags* pFileTags, FILE* pFileH, FILE* pFileCPP, string& strHeaderFile);
	//
	void	SetPragmaOnce(CFileTags* pFileTags, string& strText);

	CTag* GetMembers(CTag* pTopTag, CTag* pTagMembers);

	//���캯��
//	int TransConstructor2Client(CTag* pTopTag, FILE* pFileH, FILE* pFileCPP);
//	//��������
//	int TransDestructor2Client(CTag* pTopTag, FILE* pFileH, FILE* pFileCPP);
	//
	void	ModifyClassName(CTag* pTagClass, string& strName);

	void	ModifyFunctionName(CTag* pTagMember, string& strName);
	//��ת�ӿ� function -> slot, slot->function
	void    ReverseIf(CTag* pTagIf);
	//
//	int		TransTag2Header(CTag* pTag, FILE* pFileH);

	std::string GetClientSuffix() const { return m_strClientSuffix; }
	void SetClientSuffix(std::string& val) { m_strClientSuffix = val; }
	std::string GetServerSuffix() const { return m_strServerSuffix; }
	void SetServerSuffix(std::string& val) { m_strServerSuffix = val; }

	std::string GetOutPath() const { return m_strOutPath; }
	void SetOutPath(std::string val) { m_strOutPath = val; }

	std::string GetIfFilePath() const { return m_strIfFilePath; }
	void SetIfFilePath(std::string val) { m_strIfFilePath = val; }
protected:
	//
	
	//client C.cpp
// 	void TransIfFunction(CTag* pTagClassFunction, FILE * pFileH, FILE * pFileCPP);
// 	//server S.h S.cpp
// 	void TransIfFunction2Server(CTag* pTagClassMember, FILE * pFileH, FILE * pFileCPP);
// 	void TransFunction(CTag* pTagClassFunction, FILE * pFileH, FILE * pFileCPP);
// 
// 	int  TransParams(CTag* pTagParams,  string &strParams);
// 
// 	////slot of client
// 	void TransSlot(CTag* pTagClassMember, FILE * pFileH, FILE * pFileCPP);
// 	//slot of server;
// 	void TransSlot2Server(CTag* pTagClassMember, FILE * pFileH, FILE * pFileCPP);
	//
	//

protected:
	CFileTags*	m_pFileTags;
	//
	string	m_strModuleIfFileName;
	//�ͻ��� ������ ��Դ���� �ļ�����
	string	m_strClientFileName;
	string	m_strServerFileName;
	map<CTag*, string> m_mapClassNameOld;
	//	�����Ƶĺ�׺
	string  m_strClientSuffix;

	string	m_strServerSuffix;
	//
	string	m_strIfName;
	//if �ļ���path
	string	m_strIfFilePath;

	//����·��
	string  m_strOutPath;

	//
	//�ͻ���ͷ�ļ����������Ǳ���if�ļ����䣬����ֱ��ʹ��
	FILE*	m_pFileClientH;
	//�ͻ��˵�ʵ���ļ���nameC.cpp
	FILE*	m_pFileClientCPP;
	//nameS.h
	FILE*	m_pFileServerH;
	//nameS.cpp
	FILE*	m_pFileServerCPP;
};
