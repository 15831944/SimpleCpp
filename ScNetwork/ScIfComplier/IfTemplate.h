#pragma once
#include "filetemplate.h"
//interface ģ����룬�����Զ����ɴ���ʱ�����д
//
class CIfTemplate :
	public CFileTemplate
{
public:
	CIfTemplate(void);
	virtual ~CIfTemplate(void);
	
	virtual int Open(string &strFile);

	virtual int ToText(string& strText);
protected:
	virtual int From(FILE* pFile);
	
};
