#pragma once
#include "StreamIfC.h"
#include "Stream.h"

class CIfStream :
	public CStreamIfC,
	public CStream
{
public:
	CIfStream(void);
	virtual ~CIfStream(void);
	//virtual int Close();
	//����ʵ����������������ڷ������� �޷�Ϊÿ�� ���ӻỰ ���� ����ģ��
	virtual CRpcService* CreateObject(){
		CRpcService *pNewService  = new CIfStream;
		return pNewService;
	}
	virtual int OnData( buffer& bufferData );
};
