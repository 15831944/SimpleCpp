#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;
/*
*����
*/
namespace Scp{
	//����
	class CVariant{
	public:
		CVariant();
		~CVariant();

	protected:
		int m_nType;
	};
	class CFunctionParam{
	public:
		CFunctionParam();
		~CFunctionParam();
	protected:
		vector<CVariant>	m_arrParams;
		CVariant			m_varReturn;
	};
class CService;
	typedef void (CService::*FunctionType)(CFunctionParam* );
class CService
{
public:
	CService(void);
	virtual ~CService(void);
	//eg.���Ա����õķ�����
	virtual void Function(CFunctionParam& param);
	//
	virtual int  OnFunction(string &strFunction, CFunctionParam* pParams);
	//
	string& GetName(){return m_strName;}
protected:
	string		m_strName;
	map<string, FunctionType>	m_mapName2Function;
};

}