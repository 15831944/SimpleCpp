
#include "ScpResult.h"

CScpResult::CScpResult()
{
	m_mapError2String[eScpResult_Error] = "����";
	m_mapError2String[eScpResult_Min] = "��Сֵ";
}

CScpResult::~CScpResult()
{
	m_mapError2String.clear();
}

string& CScpResult::ErrorString(int nError)
{
	map<int, string> ::iterator item;
	item = m_mapError2String.find(nError);
	if (item == m_mapError2String.end())
	{
		return m_strEmpty;
	}
	return item->second;
}
