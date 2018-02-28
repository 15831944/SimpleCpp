#include "StdAfx.h"
#include "PackageParser.h"
#include "Buffer.h"
#include "FilterManager.h"

CPackageParser g_parser;
CPackageParser::CPackageParser(void)
:CMediaFilter()
{
	strcpy(m_szKind, "parser");
	strcpy(m_szName, "parser");
	strcpy(m_szType, "parser");

	CFilterManager::RegistFilter(&g_parser);
}

CPackageParser::~CPackageParser(void)
{

}

int CPackageParser::Open(int nBufferCount)
{
	CMediaFilter::Open();

	CFilterPin *pInOut = m_lstPinOut.at(0);
	if (pInOut)
	{
		pInOut->Clear();
		pInOut->CreateBuffer<CFilterPinBuffer>(nBufferCount);
	}
	return 0;
}
/*
//
*FTMV ... FTMV avdata end FTMV ... FTMV
*�������� ��1024 �ֽ� һ�� FTMV 
*��Ҫ ���� 264 �� ��ʽ�ְ�  
* ������һ�� avdataend ���� avdatastream �� ���� 
*/
int CPackageParser::InputData(char *pData, int nLen)
{

	//
	return 0;
}

CMediaFilter * CPackageParser::CreateObject()
{
	return new CPackageParser();
}
