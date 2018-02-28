#ifndef __MODULE_IF_H
#define __MODULE_IF_H

#include "RpcService.h"
#include "Types.h"
#include "SerializeObject.h"
#include <string>
#include "DeviceInfo.h"
#include "ScBuffer.h"


#ifdef IF_EXPORTS
#define IF_API __declspec(dllexport)
#else
#define IF_API __declspec(dllimport)
#endif

using namespace std;
using namespace SimpleCpp;
//�ӿں���
#define IF_FUN 
//�ӿڻص��������ۺ���
#define IF_SLOT
//���Ϊ�������
#define OUT_P
#define ONE_WAY
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
// class IF_API CDeviceInfo1: public CSerializeObject
// {
// public:
// 
// 	string	m_strName;
// 	int		m_nId;
// };


class IF_API CModuleIF:public CRpcService
{
public:
	CModuleIF(void);
	virtual ~CModuleIF(void);
	//������int �������ͱ�����int
	//�ͻ����������õ� ������ char* ֻ���� string 
	IF_FUN	virtual int Login(string& strUser, string& strPWD, OUT_P int& nReturn);
	 //�ͻ��˱������յ���Ϣ�ص��������ͻ��˲���Ҫ������ֱ�ӱ�����
	IF_FUN virtual int SendData(buffer& bufferData);
	//���붨��һ���ͻ��� �������ڷ�����Ϣ
	IF_FUN	virtual int GetDeviceInfo(string& strName, OUT_P CDeviceInfo& deviceInfo );
	IF_FUN	virtual int GetDevices(string& strName, OUT_P vector<CDeviceInfo*>& lstDevices );

	IF_FUN	virtual int CreateStream(OUT_P int64& i64From, OUT_P int64& i64To);
	ONE_WAY IF_FUN virtual int KeepAlive1();
};

#endif