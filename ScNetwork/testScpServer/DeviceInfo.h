#pragma once
#include <string>

using namespace std;

class CBuffer;
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
