// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#pragma once
#ifndef STDAFX_H
#define STDAFX_H

#ifdef WIN32

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>


#define debug(format, ...)	do{ \
	char szMsg[255];\
	memset(szMsg, 0, sizeof(szMsg));\
	sprintf(szMsg, format, __VA_ARGS__);\
	OutputDebugStringA(szMsg);  \
}while (0);


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#ifdef MEDIASDK_EXPORTS
#define MEDIASDK_API __declspec(dllexport)
#else
#define MEDIASDK_API __declspec(dllimport)
#endif

#endif //WIN32

#endif
