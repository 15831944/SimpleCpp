#pragma once
#include "RpcService.h"
#include "ScpDefine.h"
#include "SerializeObject.h"
/*
* rpc ˫�� ˫�� ����
* ����ͬʱ ������ã��ͽ��ܵ���(�ṩ���÷���)��
*/
namespace Scp{

	class CDeviceInfo0: public CSerializeObject
	{
		
	};
class  SCP_API CRpcDuplexService :
	public CRpcService
{
public:
	CRpcDuplexService(void);
	virtual ~CRpcDuplexService(void);

	//service be called: eg.

	virtual int  OnFunction(int nCount, int& nRet);
	//client call  : eg.
	virtual	int  Function(int nCount, int& nRet);

	virtual int  GetDevices(string& strName, vector<CDeviceInfo0*>& arrDevices);
	virtual int  OnGetDevices(string& strName, vector<CDeviceInfo0*>& arrDevices);

	virtual CRpcService*	CreateObject(){
		return new CRpcDuplexService();
	}
protected:
	//��Ϊ���񱻵��õ� ��Ӧ�ͻ��˵ĺ���
	//������������þ���Ŀͻ��ӿ�
	virtual int  OnFunction(CFunctionParams* pParams);
	virtual int  OnGetDevices(CFunctionParams* pParams);
};

}