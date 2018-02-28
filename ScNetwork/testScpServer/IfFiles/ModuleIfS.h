#ifndef ModuleIfS_H 
#define ModuleIfS_H  

#include "RpcService.h"
#include "Types.h"
#include "SerializeObject.h"
#include <string>
#include "DeviceInfo.h"
#ifdef IF_EXPORTS 
#define IF_API __declspec ( dllexport ) 

#else 
#define IF_API __declspec ( dllimport ) 

#endif 
using namespace std; 
using namespace Scp; 
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
typedef enum _eMessageType { 
	eMessageType_Login = 0 ,
	eMessageType_Logout ,
} eMessageType ; 
//���������ࡣ�޽ӿڵ��ࡣ�䵱�ṹ�� 
// 
// class IF_API CDeviceInfo1: public CSerializeObject 
// { 
// public: 
//  
// 	string	m_strName; 
// 	int		m_nId; 
// }; 
class IF_API CModuleIFS : public CRpcService { 
public:
	CModuleIFS();
	virtual ~CModuleIFS();

	virtual int OnLogin ( string& strUser , string& strPWD , OUT_P int& nReturn ) ;
	//user should not override this function
	virtual int OnLogin(CFunctionParams* pParam);
	virtual int OnSendData ( buffer& bufferData ) ;
	//user should not override this function
	virtual int OnSendData(CFunctionParams* pParam);
	virtual int OnGetDeviceInfo ( string& strName , OUT_P CDeviceInfo& deviceInfo ) ;
	//user should not override this function
	virtual int OnGetDeviceInfo(CFunctionParams* pParam);
	virtual int OnGetDevices ( string& strName , OUT_P vector<CDeviceInfo*>& lstDevices ) ;
	//user should not override this function
	virtual int OnGetDevices(CFunctionParams* pParam);
	virtual int OnCreateStream ( OUT_P int64& i64From , OUT_P int64& i64To ) ;
	//user should not override this function
	virtual int OnCreateStream(CFunctionParams* pParam);
	virtual int OnKeepAlive1 ( ) ;
	//user should not override this function
	virtual int OnKeepAlive1(CFunctionParams* pParam);
} ; 
#endif 
