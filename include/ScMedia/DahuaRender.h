#pragma once
#include "render.h"

class CDahuaRender :
	public CRender
{
public:
	CDahuaRender(void);
	virtual ~CDahuaRender(void);

	virtual int Open(HWND hWnd, int nPlayBuffer );
	//filter��ִ�� ���� 
	virtual int DoFilter();

protected:
	int m_nDhStreamHandle;
};
