#ifndef modules_H 
#define modules_H 

#include "RpcService.h"
#include "TypeDefine.h"
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
typedef enum _eMessageType { 
	eMessageType_Login = 0 ,
	eMessageType_Logout ,
} eMessageType ; 
//���������ࡣ�޽ӿڵ��ࡣ�䵱�ṹ�� 
// 
class CDeviceInfo : public CSerializeObject { 
public:
	int Write(CBuffer* pBuffer);
	int Read(CBuffer* pBuffer);
public :
	string m_strName ; 
	int m_nId ; 
} ; 
class CModuleIFS : public CRpcService { 
public:
	CModuleIFS();
	virtual ~CModuleIFS();

	virtual int OnLogin ( string& strUser , string& strPWD , OUT_P int& nReturn ) ;
	//user should not override this function
	virtual int OnLogin(CFunctionParams* pParam);
	//user should override this function
	IF_SLOT virtual int Data ( buffer & bufferData ) ;
	virtual int OnGetDeviceInfo ( string& strName , CDeviceInfo& pDeviceInfo ) ;
	//user should not override this function
	virtual int OnGetDeviceInfo(CFunctionParams* pParam);
	virtual int OnGetDevices ( string& strName , OUT_P vector<CDeviceInfo*>& arrDevices ) ;
	//user should not override this function
	virtual int OnGetDevices(CFunctionParams* pParam);
} ; 
#endif 
