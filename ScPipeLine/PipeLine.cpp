// PipeLine.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "PipeLine.h"


// ���ǵ���������һ��ʾ��
PIPELINE_API int nPipeLine=0;

// ���ǵ���������һ��ʾ����
PIPELINE_API int fnPipeLine(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� PipeLine.h
CPipeLine::CPipeLine()
{
	return;
}
