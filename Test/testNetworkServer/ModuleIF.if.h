#ifndef __MODULE_IF_H
#define __MODULE_IF_H

#include "RpcService.h"
#include "Types.h"
#include "SerializeObject.h"
#include <string>

using namespace std;
using namespace Scp;
//�ӿں���
#define IF_FUN 
//�ӿڻص��������ۺ���
#define IF_SLOT
//���Ϊ�������
#define OUT_P
//ֻ�ǶԽӿں����ͽӿڲ� ���з��롣�����������ֲ���
//ģ��ӿڣ� ��������֮�� ���� ���� �Ϳͻ��˴��롣.cpp
//IF_FUN �ͻ����Զ����ɴ��룬����Ҫ�ֶ���д�Ĵ��롣
//       �������˻��Զ�����OnXX�ص����������޺�����
//IF_SLOT �ͻ�������������ص����û�ֱ�ӵĴ���д�����оͿ�����
//		 ���������Զ����ɷ�����Ϣ���룬
// ����ʹ�� Variant�����ͷ�ʽ��������ת����ֻ��ֱ��ʹ�����л��ķ�ʽ������
// ������ ����Ϊ class ���� struct������£������޷����ݽṹ�� �ò������ݱ�ø��Ӳ��ҵ�Ч

// ÿ����Ϊ���ݵĽṹ����� class ���ɺ��� WriteTo �� ReadFrom���� ��Ϊ���л�����
//string vector<char> ���� buffer  �ӿڲ������Ͳ�����ָ��
typedef enum _eMessageType{
	eMessageType_Login=0,
	eMessageType_Logout,
}eMessageType;
//���������ࡣ�޽ӿڵ��ࡣ�䵱�ṹ��
//
class CDeviceInfo: public CSerializeObject
{
public:

	string	m_strName;
	int		m_nId;
};


class CModuleIF:public CRpcService
{
public:
	CModuleIF(void);
	virtual ~CModuleIF(void);
	//������int �������ͱ�����int
	//�ͻ����������õ� ������ char* ֻ���� string 
	IF_FUN	virtual int Login(string& strUser, string& strPWD, OUT_P int& nReturn);
	 //�ͻ��˱������յ���Ϣ�ص��������ͻ��˲���Ҫ������ֱ�ӱ�����
	IF_SLOT virtual int OnData(buffer& bufferData);
	//���붨��һ���ͻ��� �������ڷ�����Ϣ
	IF_FUN	virtual int GetDeviceInfo(string& strName, CDeviceInfo& pDeviceInfo );
	IF_FUN	virtual int GetDevices(string& strName, OUT_P vector<CDeviceInfo*>& arrDevices );
};

#endif