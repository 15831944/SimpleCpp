// VivsMediaBox.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "StdAfx.h"
#include "MediaSdk.h"

/*#include "FilterPin.h"*/
#include "MediaFilter.h"


// ���ǵ���������һ��ʾ��
MEDIASDK_API int nVivsMediaBox=0;

// ���ǵ���������һ��ʾ����
MEDIASDK_API int fnVivsMediaBox(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� VivsMediaBox.h
CVivsMediaBox::CVivsMediaBox()
{
	return;
}
