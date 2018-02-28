#pragma once

#include <list>

using namespace std;
//
//�ļ�ģ��
//
class CTemplateNode{
public:
	CTemplateNode();
	~CTemplateNode();
	//����һ����ǩ���ı�
	virtual int SetText(string& strText);
	//
	string	m_strName;
	//
	string  m_strText;
};
//
class CFileTemplate
{
public:
	CFileTemplate(void);
	virtual ~CFileTemplate(void);
	//
	virtual int Open(string &strFile);
	virtual void Close();//

	list<CTemplateNode*>& GetTopNodes(){return m_lstTopNode;};
	list<CTemplateNode*>  GetTopNodes(string& strName);
	//���뵽����
	virtual int ToText(string& strText);
	//
protected:
	//
	virtual int From(FILE* pFile);
	virtual int From(string& strText);

	//
	string	m_strFileName;
	FILE*	m_pFile;
	//���еĽڵ�
	list<CTemplateNode*> m_lstTopNode;
	//
};
