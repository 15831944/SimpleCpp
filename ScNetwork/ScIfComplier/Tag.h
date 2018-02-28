
#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;
#define debug printf

//�ӿں���
#define IF_FUN 
//�ӿڻص��������ۺ���
#define IF_SLOT
//�����Ĳ���
#define OUT_P
//ֻ�ǶԽӿں����ͽӿڲ� ���з��롣�����������ֲ���
//
class CTag;
//����Ϊ CTag���� flex bison ����ſ���ʹ��
#define YYSTYPE CTag*
//���� flex bison�ڲ������ token ö��ֵ 
#include "ScpIfParserY.h"
//#define YYSTYPE CTag*

typedef enum _eTagType{
	eTagType_Unknown = -1,
	eTagType_Token = 0, //�����Ƿָ����� ����������
	
	eTagType_TokenBrancesLeft  = TK_BRANCES_LEFT,    //{  
	eTagType_TokenBrancesRight = TK_BRANCES_RIGHT ,   //}
	eTagType_TokenParenthesesLeft = TK_PARENTHESES_LEFT, //PARENTHESES_LEFT ()
	eTagType_TokenParenthesesRight = TK_PARENTHESES_RIGHT, //(

	eTagType_TokenComma = TK_COMMA,  //,
	eTagType_TokenQuotation = TK_QUOTATION, //"
	eTagType_TokenBracketLeft = TK_ANGLE_BRACKET_LEFT, //[
	eTagType_TokenBracketRight =  TK_ANGLE_BRACKET_RIGHT, //]
	eTagType_TokenInverse = TK_INVERSE, //~
	eTagType_TokenAnd = TK_AND,   //&
	eTagType_TokenStar = TK_STAR, //*


	eTagType_TokenInclude = TK_KW_INCLUDE, 
	eTagType_TokenIfndef = TK_KW_IFNDEF,
	eTagType_TokenEndif	= TK_KW_ENDIF,

	eTagType_TokenIfFun = TK_KW_IF_FUN,
	eTagType_TokenIfSlot= TK_KW_IF_SLOT,
	eTagType_TokenInt  = TK_KW_INT,
	eTagType_TokenInt8 = TK_KW_INT8, 
	eTagType_TokenUInt8 = TK_KW_UINT8, 
	eTagType_TokenInt16 = TK_KW_INT16, 
	eTagType_TokenUInt16 = TK_KW_UINT16, 
	eTagType_TokenInt32 = TK_KW_INT32, 
	eTagType_TokenUInt32 = TK_KW_UINT32, 
	eTagType_TokenInt64 = TK_KW_INT64, 
	eTagType_TokenUInt64 = TK_KW_UINT64, 
	eTagType_TokenFloat = TK_KW_FLOAT, 
	eTagType_TokenDouble = TK_KW_DOUBLE, 


	
	//����
	eTagType_Type = 10000,
	eTagType_Class,
	eTagType_BaseClasses, //�̳еĻ����
	eTagType_BaseClass,   //����

	eTagType_Struct,
	eTagType_Members, //��Ա�б��ֶ�
	eTagType_Union,
	
	eTagType_TypeName, //�������֣�����class �� struct��

	eTagType_Function, //����
	eTagType_Constructor, //���캯��
	eTagType_Destructor, //��������

	eTagType_Virtual, //virtual 
	
	eTagType_Return,  //����ֵ
	eTagType_FunctionName, //������
	eTagType_Params,   //������
	eTagType_Param,   //����
	eTagType_OutParam,   //��������

	eTagType_Variant,  //����
	eTagType_Keyword,  //�ؼ���


	eTagType_CommentLine,
	eTagType_CommentBlock,
	
	eTagType_VarType,  //��������
	eTagType_VarTypePointer,	
	
	eTagType_VarName,  //��������
	
	eTagType_Enum,
	eTagType_EnumMembers, //��Ա��
	eTagType_EnumMember,

	eTagType_Define,
	eTagType_DefineContents,
	eTagType_Ifdef,
	eTagType_Ifndef,
	eTagType_Ifelse,
	eTagType_Endif,
	eTagType_Include,	//include #include "" #include<> 
	eTagType_Typedef, //typedef ..
	eTagType_Pragma, //#pragma
	eTagType_Access, //public, protected private,

	eTagType_UsingNamespace,

	eTagType_Interface = 20000,
	eTagType_IfFunction, //�ӿں���
	eTagType_IfSlot,  //�ӿڲۺ���
	eTagType_InterfaceEnd,
}eTagType;
class CTag
{
public:
	CTag(void);
	virtual ~CTag(void);

	//
	void AppendProperty(CTag* pTag);;
	void AppendChild(CTag* pTag);;
	//void Login(char* pUser, char* pPWD);
	//
	virtual void	CopyChild(CTag* pOther);
	virtual void	CopyFrom(CTag* pOther);
	//
	CTag*	GetProperty(eTagType type);
	CTag*	GetProperty(int nPos);

	//
	//bool	IsRef();
	//

	virtual string  ToString();
	//ת�������Ե�xxλ�ý���
	virtual string  ToString(eTagType typeEnd);
	virtual string  ToString(eTagType typeStart, eTagType typeEnd);
	//
	//	
	//�ⲿʹ�õ�
	int		m_nType;

	string  m_strName;
	string  m_strType;
	string  m_strBody;
	void*	m_pUserData;
	// class struct enum union ʹ��
	//����������ϣ�class members, struct members, enum members, union members��
	list<CTag*>	m_lstChild;
	//���Ա���������δ���, ������ ���� ���Ƶȶ�������
	list<CTag*>	m_lstProperty;
	//
	CTag*		m_pParent;
	//flex bison �ڲ�ʹ�õ�����
	int			m_nTokenType;
	//��׺��ͨ���ǽ�β֮��� �ָ��ַ�������ո� ; \r\n�� ������ʵ�����ݣ�ֻ��tostring��ʱ����Ҫ����
	string		m_strSuffix;
	string		m_strPrefix;
	//�Ƿ��нӿڡ���� class
	bool		m_bHasInterface;
	bool		m_bIsOneWay;
};
class CTagEnum: public CTag
{
public:
	CTagEnum();
	virtual ~CTagEnum();

	virtual string  ToString();
}; 
class CTagBaseClasses: public CTag
{
public:
	CTagBaseClasses();
	virtual ~CTagBaseClasses();
	virtual string  ToString();
};
class CTagParams: public CTag
{
public:
	CTagParams();
	virtual ~CTagParams();

	virtual string ToString();
};
class CTagInclude: public CTag{
public:
	CTagInclude();
	virtual ~CTagInclude();

	virtual string ToString();
};
//���� ���� int int* CTag �� ����������
class CTagType: public CTag{
public:
	CTagType();
	~CTagType();

	bool IsRef();
	bool IsPointer();
	//�Ƿ���ԭ�����ͣ����� int �Ȼ������ͣ� ���� class struct���� ?
	bool IsAtom();
	bool IsType(string &strName);
	//
	string GetBaseType();
	//
};
//���� �� header to string
class CTagClass: public CTag{
public:
	CTagClass();
	~CTagClass();

	virtual string ToString();
};