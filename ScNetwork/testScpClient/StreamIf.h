#pragma once
#include "StreamIfC.h"
#include "Stream.h"

class CStreamIf :
	public CStreamIfC,
	public CStream
{
public:
	CStreamIf(void);
	virtual ~CStreamIf(void);
	//virtual int Close();
	//����ʵ����������������ڷ������� �޷�Ϊÿ�� ���ӻỰ ���� ����ģ��
	virtual CRpcService* CreateObject(){
		CRpcService *pNewService  = new CStreamIf;
		return pNewService;
	}
	virtual int OnData( buffer& bufferData );
};
