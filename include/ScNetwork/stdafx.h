// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#ifdef WIN32
#include <windows.h>
#include <stdio.h>

#define debug(format, ...)	do{ \
	char szMsg[255];\
	memset(szMsg, 0, sizeof(szMsg));\
	sprintf(szMsg, format, __VA_ARGS__);\
	OutputDebugStringA(szMsg);  \
}while (0);

#endif

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
