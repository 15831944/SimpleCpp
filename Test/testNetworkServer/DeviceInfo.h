#pragma once
#include <string>

using namespace std;
namespace SimpleCpp{
class CBuffer;
}
using namespace SimpleCpp;
class CDeviceInfo
{
public:
	CDeviceInfo(void);
	virtual ~CDeviceInfo(void);
//ʵ������ӿھͿ��Ա����л��ķ��͵� rpc��Ϣ
	virtual int Read(CBuffer* pBuffer);
	virtual int Write(CBuffer* pBuffer);
public:

	string	m_strName;
	int		m_nId;
};
