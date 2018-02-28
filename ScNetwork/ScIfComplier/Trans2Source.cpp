#include "StdAfx.h"
#include "Trans2Source.h"
#include "Tag.h"
#include "FileTags.h"
#include "RpcService.h"
#include "TransInterfaceTags.h"

using namespace SimpleCpp;

CTrans2Source::CTrans2Source(void)
: m_pFileServerH(NULL)
, m_pFileServerCPP(NULL)
, m_pFileClientH(NULL)
, m_pFileClientCPP(NULL)
{
	//�ͻ�������ʹ�ã�
	m_strClientSuffix = "";
	m_strServerSuffix = "";
	m_strOutPath = "./";
}

CTrans2Source::~CTrans2Source(void)
{
	Close();
}

int CTrans2Source::Open()
{
	if (m_pFileClientH 
		|| m_pFileClientCPP
		|| m_pFileServerH
		|| m_pFileServerCPP)
	{
		return -1;
	}
	//
	string strFileName;
	//���ɿͻ���ͷ�ļ�
	strFileName = m_strOutPath + m_strClientFileName + ".h";
	m_pFileClientH = fopen(strFileName.c_str(), "w+b");
	if (!m_pFileClientH)
	{
		return -2;
	}
	strFileName = m_strOutPath + m_strClientFileName +  ".cpp";
	m_pFileClientCPP = fopen(strFileName.c_str(), "w+b");
	if (!m_pFileClientCPP)
	{
		return -3;
	}
	//
	strFileName = m_strOutPath + m_strServerFileName +  ".h";
	m_pFileServerH = fopen(strFileName.c_str(), "w+b");
	if (!m_pFileServerH)
	{
		return -4;
	}
	strFileName = m_strOutPath + m_strServerFileName + ".cpp";
	m_pFileServerCPP = fopen(strFileName.c_str(), "w+b");
	if (!m_pFileServerCPP)
	{
		return -5;
	}


	//
	return 0;
}

void CTrans2Source::Close()
{
	if (m_pFileClientH)
	{
		fflush(m_pFileClientH);
		fclose(m_pFileClientH);
		m_pFileClientH = NULL;
	}
	if (m_pFileClientCPP)
	{
		fflush(m_pFileClientCPP);
		fclose(m_pFileClientCPP);
		m_pFileClientCPP = NULL;
	}
	if (m_pFileServerH)
	{
		fflush(m_pFileServerH);
		fclose(m_pFileServerH);
		m_pFileServerH = NULL;
	}
	if (m_pFileServerCPP)
	{
		fflush(m_pFileServerCPP);
		fclose(m_pFileServerCPP);
		m_pFileServerCPP = NULL;
	}
	return ;
}

int CTrans2Source::Trans()
{
	int nRet = 0;
	//
	if (!m_pFileTags)
	{
		return -1;
	}
	if (//!m_pFileClientH 
		 !m_pFileClientCPP
		|| !m_pFileServerH
		|| !m_pFileServerCPP)
	{
		return -2;
	}
	CTag* pTagIfClass = m_pFileTags->GetIfTag();
	if (!pTagIfClass)
	{
		debug("%s: no if class\n", __FUNCTION__);
		
	}
	else{//string strClassNameNew = pTagIfClass->m_strName + m_strClientSuffix;
		m_strIfName = pTagIfClass->m_strName;
	}
	//clientC.h .cpp
	
	Trans2Client();
	//serviceS.h .cpp
	Trans2Server();

	//
	return nRet;
}

//
// void CTrans2Source::TransIfFunction(CTag* pTagClassFunction, FILE * pFileH, FILE * pFileCPP)
// {
// 	string strTmp;
// 	string strField;
// 
// 
// 	int nMaxFiledSize = 2550;
// 	strField.resize(nMaxFiledSize);
// 	
// 	char *pField = (char*)strField.c_str();
// 	//д������дʵ��
// 	strTmp = "\t\/\/user should override this function\r\n"
// 		"\t";
// 	CTag* pTagParams(NULL);
// 	list<CTag*>::iterator item, itemTmp;
// 	for (item = pTagClassFunction->m_lstProperty.begin();
// 		item != pTagClassFunction->m_lstProperty.end();
// 		item++)
// 	{
// 		CTag *pTagProperty = *item;
// 		strTmp += pTagProperty->ToString();
// 		if (pTagProperty->m_nType == eTagType_Params)
// 		{
// 			pTagParams = pTagProperty;
// 		}
// 	}
// 	strTmp += ";\r\n";
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 	strTmp.clear();
// 	//дʵ�� 
// 	for (item = pTagClassFunction->m_lstProperty.begin();
// 		item != pTagClassFunction->m_lstProperty.end();
// 		item++)
// 	{
// 		CTag *pTagProperty = *item;
// 		if (pTagProperty->m_nType == eTagType_Virtual
// 			|| pTagProperty->m_nType == eTagType_TokenIfFun
// 			)
// 		{// 
// 			 continue;
// 		}
// 		if (pTagProperty->m_nType == eTagType_FunctionName)
// 		{
// 			sprintf(pField, "%s::%s ", pTagClassFunction->m_pParent->m_pParent->m_strName.c_str(),  pTagProperty->m_strBody.c_str());
// 			strTmp += pField;
// 		}
// 		else if (pTagProperty->m_nType == eTagType_Params)
// 		{//д�����в���
// 			pTagParams = pTagProperty;
// 			string strParams;
// 
// 			TransParams(pTagParams,  strParams);
// 
// 
// 			strTmp += strParams;
// 		}
// 		else
// 		{
// 			sprintf(pField, "%s ", pTagProperty->m_strBody.c_str());
// 			strTmp += pField;
// 		}
// 	}
// 	//
// 	sprintf(pField, "%s", "\r\n{\r\n");
// 	strTmp += pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	//��д���벿�� ���������Ϣ����
// 	//��д������ʼ
// 	strTmp = 
// 	"\tif (!m_pProcessor)\r\n"
// 	"\t	  return -1;\r\n"
// 	"\tif (!m_pSession) \r\n"
// 	"\t{\r\n"
// 	"\t	  m_pSession = m_pProcessor->GetSession();\r\n"
// 	"\t	  if (!m_pSession)\r\n"
// 	"\t	  {\r\n"
// 	"\t			return -2;\r\n"
// 	"\t	  }\r\n"
// 	"\t}\r\n"
// 	"\tint nRet = 0;\r\n"
// 	"\tCRpcMessage rpcCall;\r\n";
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	//	
// 	string strBuildMessage;
// 	//strBuildMessage.resize(nMaxFiledSize);
// 	//char *pBuildMesage= &strBuildMessage.at(0);
// 	sprintf(pField, 
// 	"\trpcCall.SetService(m_strName);\r\n"    //m_strName���� ���캯����������
// 	"\trpcCall.SetFunction(string(\"%s\"));\r\n", 
// 	pTagClassFunction->m_strName.c_str()
// 	);
// 	strBuildMessage += pField;
// 	//��䷵��ֵ
// 	sprintf(pField,
// 	"\tCFunctionParams *pParams = rpcCall.GetFunctionParams();\r\n"
// 	"\tCVariant* pVar(NULL) ;\r\n"
// 	"\tCParam*	pParam(NULL);\r\n"
// 	"\t\/\/����ֵ\r\n"
// 	"\tpVar = new CVariant(eVariantType_int32);\r\n"
// 	"\tpParams->SetReturn(pVar);\r\n"
// 	"\t\/\/����\r\n"
// 	);
// 	strBuildMessage += pField;
// 	
// 	//������������Ϣ
// 	string strParams;
// 	list<CTag*>::iterator itemParam;
// 	for (itemParam = pTagParams->m_lstChild.begin();
// 		itemParam != pTagParams->m_lstChild.end();
// 		itemParam++)
// 	{
// 		CTag *pTagParam = *itemParam;
// 		eParamInOut paramInOut(eParamInOut_In);
// 		string strInOutP = "eParamInOut_In";
// 		if (pTagParam->m_lstProperty.front()->m_strName == "OUT_P")
// 		{
// 			paramInOut = eParamInOut_Out;
// 			strInOutP = "eParamInOut_Out";
// 		}
// 
// 		sprintf(pField,
// 		"\tpParam = new CParam();\r\n"
// 		"\tpVar = pParam->m_pVariant;\r\n"
// 		"\t*pVar = CVariant(%s);\r\n"
// 		"\tpParam->m_nInOut = %s;\r\n"
// 		"\tpParams->Append(pParam);\r\n"
// 		"\t\r\n"
// 		, 
// 		pTagParam->m_strName.c_str(),
// 		strInOutP.c_str()
// 		);
// 		strParams += pField;
// 	}
// 	strBuildMessage += strParams;
// 	strBuildMessage += "\r\n";
// 
// 	fwrite(strBuildMessage.c_str(), strBuildMessage.size(), 1, pFileCPP);
// 
// 	//������Ϣ���Ҵ�����ֵ
// 	strTmp = 
// 
// 	"\tCRpcMessage *pRpcRet(NULL);\r\n"
// 	"\tnRet = m_pSession->Send(&rpcCall,(CMessage**) &pRpcRet, 20*1000);\r\n"
// 	"\tif (nRet < 0)\r\n"
// 	"\t{\r\n"
// 	"\t		\/\/debug(\"%s: false\\n\", __FUNCTION__);\r\n"
// 	"\t		return -1;\r\n"
// 	"\t}\r\n"
// 	"\telse\r\n"
// 	"\t{\r\n"
// 	"\t//��������"
// 	"\t	int nRetValue;\r\n"
// 	"\t	if (pRpcRet)\r\n"
// 	"\t	{\r\n"
// 	"\t		nRet = pRpcRet->GetFunctionParams()->GetReturn()->Value<int>();\r\n"
// 	"\t		\/\/debug(\"%s: ok: ret [%d]\\n\", __FUNCTION__, nRetValue);\r\n"
// 	"\t	}\r\n"
// 	"\t}\r\n"
// 	"\treturn nRet;\r\n";
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	 
// 	strTmp.clear();
// 	sprintf(pField, "%s", "}\r\n");
// 	strTmp += pField;
// 	//
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// }
// 
// void CTrans2Source::TransSlot(CTag* pTagClassMember, FILE * pFileH, FILE * pFileCPP)
// {
// 	string strTmp;
// 	string strField;
// 	strField.resize(1024);
// 	char* pField = &strField.at(0);
// 	
// 	list<CTag*>::iterator item, itemTmp;
// 	CTag* pTagParams(NULL);
// 	//д������дʵ��
// 	/*strTmp = "\t\/\/user should override this function\r\n"
// 		"\t";
// 	
// 	
// 	for (item = pTagClassMember->m_lstProperty.begin();
// 		item != pTagClassMember->m_lstProperty.end();
// 		item++)
// 	{
// 		CTag *pTagProperty = *item;
// 		strTmp += pTagProperty->ToString();
// 		if (pTagProperty->m_nType == eTagType_Params)
// 		{
// 			pTagParams = pTagProperty;
// 		}
// 	}
// 	strTmp += ";\r\n";
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);*/
// 	//
// 	TransFunction(pTagClassMember, pFileH, pFileCPP);
// 
// 	pTagParams = pTagClassMember->GetProperty(eTagType_Params);
// 	//���һ�� ͬ����������дʵ��
// 	strTmp = "\t\/\/user should not override this function\r\n";
// 	sprintf(pField, "\tvirtual int %s(CFunctionParams* pParam);\r\n",
// 			pTagClassMember->m_strName.c_str()
// 			);
// 	strTmp += pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 
// 
// 	sprintf(pField, "int %s::%s(CFunctionParams* pFunctionParam)\r\n"
// 		"{\r\n"
// 		,
// 		pTagClassMember->m_pParent->m_pParent->m_strName.c_str(),
// 		pTagClassMember->m_strName.c_str()
// 		);
// 	strTmp = pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	//д�뺯������ʵ�ֲ���
// 	//ʵ�ʵ��ûص����� OnXXX
// 	sprintf(pField, 
// 		"\tCVariant *pVarRet = pFunctionParam->GetReturn();\r\n"
// 		"\tvector<CParam*>& arrParams = pFunctionParam->GetParam();\r\n"
// 		"\tif(arrParams.size() != %d)\r\n"
// 		"\t{\r\n"
// 		"\t\treturn -1;\r\n"
// 		"\t}\r\n"
// 		, pTagParams->m_lstChild.size()
// 		);
// 	strTmp = pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	
// 	string strParams;
// 	//��������
// 	int i=0;
// 	for (item = pTagParams->m_lstChild.begin();
// 		item != pTagParams->m_lstChild.end();
// 		item++, i++)
// 	{
// 		CTag* pTagParam = *item;
// 		CTagType* pTagParamType = dynamic_cast<CTagType*>(pTagParam->GetProperty(eTagType_VarType));
// 
// 		if (i == 0)
// 		{	//��һ������
// 		}
// 		else
// 		{
// 			strParams += "\t";
// 		}
// 		if (pTagParamType->IsRef())
// 		{
// 			sprintf(pField, "\t(%s)arrParams[%d]->m_pVariant->RefValue<%s>() "
// 				, pTagParamType->m_strName.c_str()
// 				, i
// 				, pTagParamType->GetBaseType().c_str()
// 				);
// 		}
// 		else{
// 			sprintf(pField, "\t(%s)arrParams[%d]->m_pVariant->Value<%s>() "
// 			, pTagParamType->m_strName.c_str()
// 			, i
// 			, pTagParamType->m_strName.c_str()
// 			);
// 		}
// 
// 
// 		strParams += pField;
// 		itemTmp = item;
// 		itemTmp++;
// 		if (itemTmp != pTagParams->m_lstChild.end() )
// 		{
// 			strParams += ", \r\n";
// 		}
// 		else
// 		{
// 			strParams += "\r\n";
// 		}
// 		
// 	}
// 	//������
// 	sprintf(pField, "\tint nLen;\r\n"
// 		"\t\/\/call OnXXX function\r\n"
// 		"\t%s(%s"
// 		"\t);\r\n"
// 		, pTagClassMember->m_strName.c_str()
// 		, strParams.c_str()
// 		);
// 	strTmp = pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	//
// 	sprintf(pField, "\treturn 0;\r\n"
// 		"}\r\n"
// 		);
// 	strTmp = pField;
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 
// 	//
// 
// }
// 
// void CTrans2Source::TransIfFunction2Server(CTag* pTagClassMember, FILE * pFileH, FILE * pFileCPP)
// {
// 	//
// 
// 	//
// }
//client ֻ����д cpp����
void CTrans2Source::Trans2Client()
{
	SetPragmaOnce(m_pFileTags, m_strClientFileName + "_H");

// 	CTag* pTagIfClass = m_pFileTags->GetIfTag();
// 	string strClassNameNew = m_strIfName + m_strClientSuffix;
// 	ModifyClassName( pTagIfClass , strClassNameNew );
	//
	list<CTag*>& lstTopTags = m_pFileTags->GetTopTags();
	list<CTag*>::iterator item;
	for (item = lstTopTags.begin();
		item != lstTopTags.end();
		item++)
	{
		CTag* pTagTmp = *item;
		if (pTagTmp->m_nType == eTagType_Class
			&& pTagTmp->m_bHasInterface)
		{
			m_mapClassNameOld[pTagTmp] = pTagTmp->m_strName;
			//string strClassNameNew = m_strIfName + m_strClientSuffix;
			string strClassNameNew = pTagTmp->m_strName + m_strClientSuffix;
			ModifyClassName( pTagTmp , strClassNameNew );
		}
	}
	//

	//TransTag2Source(m_pFileTags, m_pFileClientH, m_pFileClientCPP, m_strClientFileName);
	CTransInterfaceTags *pTransIf = new CTransInterfaceTags();
	pTransIf->SetFileH(m_pFileClientH);
	pTransIf->SetFileCPP(m_pFileClientCPP);

	//�������Ҫ����Ϊֱ��ʹ���˽ӿڵ�����
//	string strLocalName = strClassNameNew;
//	pTransIf->SetLocalName(strLocalName);

//	string strRemoteName = m_strIfName + m_strServerSuffix;
//	pTransIf->SetRemoteName(strRemoteName);
	pTransIf->SetClientSuffix(m_strClientSuffix);
	pTransIf->SetServerSuffix(m_strServerSuffix);

	pTransIf->SetFileName(m_strClientFileName);

	pTransIf->Trans(m_pFileTags);

	delete pTransIf;

	//�ָ�����
//	list<CTag*>::iterator item;
	for (item = lstTopTags.begin();
		item != lstTopTags.end();
		item++)
	{
		CTag* pTagTmp = *item;
		if (pTagTmp->m_nType == eTagType_Class
			&& pTagTmp->m_bHasInterface)
		{
			string strClassNameOld = m_mapClassNameOld[pTagTmp];// = pTagTmp->m_strName;
			//string strClassNameNew = m_strIfName + m_strClientSuffix;
			//string strClassNameNew = pTagTmp->m_strName;// + m_strClientSuffix;
			ModifyClassName( pTagTmp , strClassNameOld );
		}
	}

	return ;

}
 

void CTrans2Source::Trans2Server( )
{
	string strTmp;

	strTmp = "\/\/server cpp \r\n" \
		"#include \""  \
		+   m_strServerFileName + ".h" \
		"\" \r\n\r\n";
	fwrite(strTmp.c_str(), strTmp.size(), 1, m_pFileServerCPP);
	//
	SetPragmaOnce(m_pFileTags, m_strServerFileName + "_H");
	
	list<CTag*>& lstTopTags = m_pFileTags->GetTopTags();
	list<CTag*>::iterator item;
	for (item = lstTopTags.begin();
		item != lstTopTags.end();
		item++)
	{
		CTag* pTagTmp = *item;
		if (pTagTmp->m_nType == eTagType_Class
			&& pTagTmp->m_bHasInterface)
		{
			m_mapClassNameOld[pTagTmp] = pTagTmp->m_strName;
			string strClassNameNew = pTagTmp->m_strName + m_strServerSuffix;
			ModifyClassName( pTagTmp , strClassNameNew );
			ReverseIf(pTagTmp);
		}
	}

	//
	//TransTag2Source(m_pFileTags, m_pFileServerH, m_pFileServerCPP, m_strServerFileName);
	CTransInterfaceTags *pTransIf = new CTransInterfaceTags();
	pTransIf->SetFileH(m_pFileServerH);
	pTransIf->SetFileCPP(m_pFileServerCPP);

	//�������Ҫ����Ϊֱ��ʹ���˽ӿڵ�����
	//string strLocalName = strClassNameNew;
	//pTransIf->SetLocalName(strLocalName);

	//string strRemoteName = m_strIfName + m_strClientSuffix;
	//pTransIf->SetRemoteName(strRemoteName);
	//������ת������������ ���Ժ�׺ Ӧ�öԵ�
	pTransIf->SetClientSuffix( m_strServerSuffix );
	pTransIf->SetServerSuffix( m_strClientSuffix );
	pTransIf->SetFileName(m_strServerFileName);

	pTransIf->Trans(m_pFileTags);

	delete pTransIf;
	//�ָ�����
//	list<CTag*>::iterator item;
	for (item = lstTopTags.begin();
		item != lstTopTags.end();
		item++)
	{
		CTag* pTagTmp = *item;
		if (pTagTmp->m_nType == eTagType_Class
			&& pTagTmp->m_bHasInterface)
		{
			string strClassNameOld = m_mapClassNameOld[pTagTmp];// = pTagTmp->m_strName;
			//string strClassNameNew = pTagTmp->m_strName + m_strServerSuffix;
			ModifyClassName( pTagTmp , strClassNameOld );
			//ReverseIf(pTagTmp);
		}
	}

	return ;

}
// 
// void CTrans2Source::TransFunction(CTag* pTagClassFunction, FILE * pFileH, FILE * pFileCPP)
// {
// 	string strDeclare;
// 	string strDefinition;
// 	string strField;
// 
// 	strDeclare = "\t";
// 	strDefinition = "";
// 
// 	int nMaxFiledSize = 255;
// 	strField.resize(nMaxFiledSize);
// 
// 	char *pField = (char*)strField.c_str();
// 	CTag* pTagParams;
// 	list<CTag*>::iterator item;
// 	for (item = pTagClassFunction->m_lstProperty.begin();
// 		item != pTagClassFunction->m_lstProperty.end();
// 		item++)
// 	{
// 		CTag *pTagProperty = *item;
// 		if (pTagProperty->m_nType == eTagType_TokenIfFun
// 			)
// 		{// 
// 			//continue;
// 		}
// 		else if(pTagProperty->m_nType == eTagType_Virtual)
// 		{
// 			//ͷ�ļ���Ҫ
// 			sprintf(pField, "%s ", pTagProperty->m_strBody.c_str());
// 			strDeclare += pField;
// 			//ʵ�ֲ���Ҫ
// 		}
// 		else if (pTagProperty->m_nType == eTagType_FunctionName)
// 		{
// 			sprintf(pField, "%s ",  pTagProperty->m_strBody.c_str());
// 			strDeclare += pField;
// 
// 			sprintf(pField, "%s::%s ", pTagClassFunction->m_pParent->m_pParent->m_strName.c_str(),  pTagProperty->m_strBody.c_str());
// 			strDefinition += pField;
// 
// 		}
// 		else if (pTagProperty->m_nType == eTagType_Params)
// 		{//д�����в���
// 			string strParams;
// 			pTagParams = pTagProperty;
// 			TransParams(pTagParams,  strParams);
// 
// 			strDeclare += strParams;
// 			strDefinition += strParams;
// 		}
// 		else
// 		{
// 			sprintf(pField, "%s ", pTagProperty->m_strBody.c_str());
// 			strDeclare += pField;
// 			strDefinition += pField;
// 		}
// 	}
// 	//declare
// 	sprintf(pField, ";\r\n");
// 	strDeclare += pField;
// 	//
// 	sprintf(pField, "%s", "\r\n{\r\n");
// 	strDefinition += pField;
// 	//��д���벿�� ���������Ϣ����
// 
// 	//
// 	//if (pTagClassFunction->m_nType == eTagType_Function)
// 	{//���� �����������ʱ��
// 		sprintf(pField, "\t int nRet=0;\r\n\r\n" \
// 		"\t return nRet;\r\n");
// 		strDefinition += pField;
// 	}
// 
// 	sprintf(pField, "%s", "}\r\n");
// 	strDefinition += pField;
// 	//
// 	fwrite(strDeclare.c_str(), strDeclare.size(), 1, pFileH);	
// 	fwrite(strDefinition.c_str(), strDefinition.size(), 1, pFileCPP);	
// }
// int CTrans2Source::TransConstructor2Client(CTag* pTagClass, FILE* pFileH, FILE* pFileCPP)
// {
// 	string strContent;
// 	string strField;
// 
// 	int nMaxFiledSize = 255;
// 	strField.resize(nMaxFiledSize);
// 	char *pField = (char*)strField.c_str();
// 	//
// 	sprintf(pField, "public:\r\n"
// 		);
// 	strContent = pField;
// 	fwrite(strContent.c_str(), strContent.size(), 1, pFileH);
// 	//д���캯���������� ͷ�ļ�
// 	sprintf(pField, "\t%s();\r\n"
// 		,
// 		pTagClass->m_strName.c_str()
// 		);
// 	strContent = pField;
// 	fwrite(strContent.c_str(), strContent.size(), 1, pFileH);
// // 	sprintf(pField, "\tvirtual ~%s();\r\n"
// // 		,
// // 		pTagClass->m_strName.c_str()
// // 		);
// // 	strContent = pField;
// // 	fwrite(strContent.c_str(), strContent.size(), 1, pFileH);
// 	//
// 	//ͳ�� �ж��� ���ӿ�slot��Ҫ����ע��
// 
// 	//дcpp
// 	sprintf(pField, "%s::%s()\r\n"
// 		"{\r\n"
// 		"\tm_strName = \"%s\";\r\n"
// 		,
// 		pTagClass->m_strName.c_str(),
// 		pTagClass->m_strName.c_str(),
// 		pTagClass->m_strName.c_str()
// 		);
// 	strContent = pField;
// 	//"\tRegisterFunction(string("Function"), (ServiceFunctionHandle)&CRpcDuplexService::OnFunction);"
// 	//ע�� ���ֽӿں���
// 	CTag* pTagMembers = pTagClass->GetProperty(eTagType_Members);
// 
// 	list<CTag*>::iterator itemClassMember;
// 	for(itemClassMember = pTagMembers->m_lstChild.begin();
// 		itemClassMember != pTagMembers->m_lstChild.end();
// 		itemClassMember++)
// 	{
// 		CTag* pTagMember = *itemClassMember;
// 		if (pTagMember->m_nType != eTagType_IfSlot
// 			)
// 		{//���ǽӿ�
// 			continue;;
// 		}
// 		//ȥ��OnXXX ��On;
// 		string strFunctionName = pTagMember->m_strName;
// 
// 		int nTrimSize = strlen("On");
// 		strFunctionName = pTagMember->m_strName.substr(nTrimSize, pTagMember->m_strName.size()-nTrimSize+1);
// 		//ע��ص�����
// 		sprintf(pField, "\tRegisterFunction(string(\"%s\"), (ServiceFunctionHandle)&%s::%s);\r\n",
// 				strFunctionName.c_str(),
// 				pTagClass->m_strName.c_str(),
// 				pTagMember->m_strName.c_str()
// 			);
// 		strContent += pField;
// 	}
// 
// 	//
// 
// 	sprintf(pField, "}\r\n"
// 		);
// 	strContent += pField;
// 	
// 	fwrite(strContent.c_str(), strContent.size(), 1, pFileCPP);
// 
// 	return 0;
// }
// 
// int CTrans2Source::TransDestructor2Client(CTag* pTagClass, FILE* pFileH, FILE* pFileCPP)
// {
// 	string strContent;
// 	string strField;
// 
// 	int nMaxFiledSize = 255;
// 	strField.resize(nMaxFiledSize);
// 	char *pField = (char*)strField.c_str();
// 	//
// 
// 	sprintf(pField, "\tvirtual ~%s();\r\n\r\n"
// 		,
// 		pTagClass->m_strName.c_str()
// 		);
// 	strContent = pField;
// 	fwrite(strContent.c_str(), strContent.size(), 1, pFileH);
// 	//
// 	//ͳ�� �ж��� ���ӿ�slot��Ҫ����ע��
// 
// 	sprintf(pField, "%s::~%s()\r\n"
// 		"{\r\n"
// 		"\t\r\n"
// 		,
// 		pTagClass->m_strName.c_str(),
// 		pTagClass->m_strName.c_str()
// 		);
// 	strContent = pField;
//  
// 	sprintf(pField, "}\r\n"
// 			);
// 	strContent += pField;
// 
// 	fwrite(strContent.c_str(), strContent.size(), 1, pFileCPP);
// 
// 	return 0;
// }
// 
// int CTrans2Source::TransParams(CTag* pTagParams,   string &strParams)
// {
// 	int nRet = 0;
// 	list<CTag*>::iterator itemParam;
// 	strParams = "";
// 	string strField;
// 	int nMaxFieldLen(255);
// 	strField.resize(nMaxFieldLen);
// 	char * pField = (char*)strField.c_str();
// 	for (itemParam = pTagParams->m_lstChild.begin();
// 		itemParam != pTagParams->m_lstChild.end();
// 		itemParam++)
// 	{//���еĲ���ѭ��
// 		CTag* pTagParam = *itemParam;
// 
// 		//���������е���
// 		list<CTag*>::iterator itemParamField;
// 		for (itemParamField = pTagParam->m_lstProperty.begin();
// 			itemParamField != pTagParam->m_lstProperty.end();
// 			itemParamField++)
// 		{
// 			CTag* pTagParamField = *itemParamField;
// 			sprintf(pField, "%s ", pTagParamField->m_strName.c_str());
// 			strParams += pField;
// 		}
// 		//
// 		list<CTag*>::iterator itemParamTmp = itemParam;
// 		itemParamTmp++;
// 		if (itemParamTmp != pTagParams->m_lstChild.end())
// 		{//, 
// 			sprintf(pField, "%s", ", ");
// 			strParams += pField;
// 		}
// 		//����
// 		//
// 	}
// 
// 	return nRet;
// }
//�޸�������
void CTrans2Source::ModifyClassName(CTag* pTagClass, string& strName)
{
	//
	pTagClass->m_strName = strName;
	pTagClass->m_strBody = strName;
	//
	list<CTag*>::iterator item;
	for (item = pTagClass->m_lstProperty.begin();
		item != pTagClass->m_lstProperty.end();
		item++)
	{
		CTag* pTagProperty = *item;
		if (pTagProperty->m_nType == eTagType_TypeName)
		{
			pTagProperty->m_strName = strName;
			pTagProperty->m_strBody = strName;
		}
		else if (pTagProperty->m_nType == eTagType_Members)
		{
			//��Ա
			list<CTag*>::iterator itemMember;
			for (itemMember = pTagProperty->m_lstChild.begin();
				itemMember != pTagProperty->m_lstChild.end();
				itemMember++)
			{//���캯��
				CTag* pTagMember = *itemMember;
				if (pTagMember->m_nType == eTagType_Constructor)
				{
					ModifyFunctionName(pTagMember, strName);
				}//
				else if (pTagMember->m_nType == eTagType_Destructor)
				{//��������
					string strDestructor = "~" + strName;
				 
					ModifyFunctionName(pTagMember, strDestructor);
				}
			}
			//
		}
	}
}

void CTrans2Source::ModifyFunctionName(CTag* pTagMember, string& strName)
{
	pTagMember->m_strName = strName;
	pTagMember->m_strBody = strName;

	list<CTag*>::iterator itemFunction;
	for (itemFunction = pTagMember->m_lstProperty.begin();
		itemFunction != pTagMember->m_lstProperty.end();
		itemFunction++)
	{
		CTag* pFunProperty = *itemFunction;
		if (pFunProperty->m_nType == eTagType_FunctionName)
		{
			pFunProperty->m_strName = strName;
			pFunProperty->m_strBody = strName;
		}
	}
}

// int CTrans2Source::TransTag2Header(CTag* pTag, FILE* pFileH)
// {
// 	string strTmp;
// 	strTmp = pTag->ToString() + "\r\n";
// 	//strTmp += "\r\n";
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 	
// 	return 0;
// }
//��ȫͨ�� file tag ת����Դ��
// int CTrans2Source::TransTag2Source(CFileTags* pFileTags, FILE* pFileH, FILE* pFileCPP, string& strHeaderFile)
// {
// 	//
// 	int nRet = 0;
// 	string strTmp;
// 	//дincludeͷ�ļ�
// 	strTmp = "\/\/cpp file, user can not modify this file \r\n" \
// 		"#include \"" + strHeaderFile + ".h"  + "\" \r\n";
// 	strTmp = strTmp + 
// 		"#include \"" + "RpcMessage.h" + "\" \r\n";
// 	strTmp = strTmp + 
// 		"#include \"" + "Variant.h" + "\" \r\n";
// 	strTmp = strTmp + 
// 		"#include \"" + "Session.h" + "\" \r\n";
// 	strTmp = strTmp + 
// 		"#include \"" + "RpcDispatcher.h" + "\" \r\n";
// 
// 	strTmp = strTmp + "\r\n";
// 
// 	fwrite(strTmp.c_str(), strTmp.size(), 1, pFileCPP);
// 	//���еĶ���Ҫдͷ�ļ��� cpp
// 	list<CTag*>& lstTopTags = m_pFileTags->GetTopTags();
// 	list<CTag*>::iterator item;
// 	for (item = lstTopTags.begin();
// 		item != lstTopTags.end();
// 		item++)
// 	{
// 		CTag* pTopTag = *item;
// 		//ֻ��clas��If ��ת��
// 
// 		if (pTopTag->m_nType == eTagType_Class
// 			&& pTopTag->m_bHasInterface == true )
// 		{
// 			//дclass������ͷ�ļ�
// 			strTmp = pTopTag->ToString(eTagType_TokenBrancesLeft) + "\r\n";
// 			fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 			//д���캯�� ����������
// 			TransConstructor2Client(pTopTag, pFileH, pFileCPP);
// 			TransDestructor2Client(pTopTag, pFileH, pFileCPP);
// 			//ת�� �ӿ�
// 
// 			//class д���캯���ȣ�	
// 			CTag* pTagMembers(NULL);
// 			pTagMembers = pTopTag->GetProperty(eTagType_Members);
// 
// 
// 			//д�� ���ֽӿں���
// 			list<CTag*>::iterator itemClassMember;
// 			for(itemClassMember = pTagMembers->m_lstChild.begin();
// 				itemClassMember != pTagMembers->m_lstChild.end();
// 				itemClassMember++)
// 			{
// 				CTag* pTagClassMember = *itemClassMember;
// 				if (pTagClassMember->m_nType < eTagType_Interface
// 					|| pTagClassMember->m_nType > eTagType_InterfaceEnd)
// 				{//���ǽӿ�
// 					continue;;
// 				}
// 				//ת���ӿں���
// 				if (pTagClassMember->m_nType == eTagType_IfFunction)
// 				{//д�뵽 Ŀ���ļ�
// 					//1�ͻ���ʵ�ַ��ͱ���
// 					TransIfFunction(pTagClassMember, pFileH, pFileCPP);
// 
// 					printf("%s: if function\n", __FUNCTION__);
// 				}
// 				//ת���ص�����
// 				else if  (pTagClassMember->m_nType == eTagType_IfSlot)
// 				{//
// 					//�ͻ���ʵ��On �ص�
// 					printf("%s: if slot\n", __FUNCTION__);
// 					//��Ҫд��ͷ�ļ� ��cpp ���һ������ Onxx(CFunctionParam* pParams);
// 					//��д�ú����塣�����е��� ������ifslot
// 					TransSlot(pTagClassMember, pFileH, pFileCPP);
// 				}
// 			}
// 			//д class ��β
// 			strTmp = pTopTag->ToString(eTagType_TokenBrancesRight, eTagType_Unknown) + "\r\n";
// 			fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 		}
// 		else
// 		{
// 			eTagType tagType = (eTagType)pTopTag->m_nType;
// 			TransTag2Header(pTopTag, pFileH);
// 			
// 			if (pTopTag->m_nType == eTagType_Define)
// 			{
// 				strTmp = "\r\n";
// 				fwrite(strTmp.c_str(), strTmp.size(), 1, pFileH);
// 			}
// 		}
// 		//
// 	}
// 
// 
// 	return nRet;
// }

void CTrans2Source::SetPragmaOnce(CFileTags* pFileTags, string& strText)
{
	CTag *pTag(NULL);
	pTag = pFileTags->GetTags(eTagType_Ifndef);
	if (pTag)
	{
		pTag->GetProperty(1)->m_strName = strText;
		pTag->GetProperty(1)->m_strBody = strText;
	}
	pTag = pFileTags->GetTags(eTagType_Define);
	if (pTag)
	{
		pTag->GetProperty(1)->m_strName = strText;
		pTag->GetProperty(1)->m_strBody = strText;
	}
}
//���ӿڵĺ����� slot�Ե�
void CTrans2Source::ReverseIf(CTag* pTagIf)
{
	CTag* pTagClassMembers(NULL);
	pTagClassMembers = pTagIf->GetProperty(eTagType_Members);
	list<CTag*>::iterator itemClassMember;
	for(itemClassMember = pTagClassMembers->m_lstChild.begin();
		itemClassMember != pTagClassMembers->m_lstChild.end();
		itemClassMember++)
	{
		CTag* pTagClassMember = *itemClassMember;
		if (pTagClassMember->m_nType == eTagType_IfFunction)
		{//�ӿں���->��� slot
			pTagClassMember->m_nType = eTagType_IfSlot;
			pTagClassMember->m_strName = "On" + pTagClassMember->m_strName;

			CTag* pTagName = pTagClassMember->GetProperty(eTagType_FunctionName);
			pTagName->m_strName = pTagClassMember->m_strName;
			pTagName->m_strBody = pTagClassMember->m_strName;
		}
		else if (pTagClassMember->m_nType == eTagType_IfSlot)
		{//�Ƴ�"On" ��ɺ���
			pTagClassMember->m_nType = eTagType_IfFunction;
			int nPrefixLen = strlen("On");
			pTagClassMember->m_strName = pTagClassMember->m_strName.substr(nPrefixLen, pTagClassMember->m_strName.size() - nPrefixLen);

			CTag* pTagName = pTagClassMember->GetProperty(eTagType_FunctionName);
			pTagName->m_strName = pTagClassMember->m_strName;
			pTagName->m_strBody = pTagClassMember->m_strName;
		}

	}
}



