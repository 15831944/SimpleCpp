// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// VivsMediaBox.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "StdAfx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
#ifndef WIN32
#include <time.h>
long timeGetTime()
{
    unsigned int uptime = 0;
    struct timespec on;
    if (clock_gettime(CLOCK_MONOTONIC, &on)==0)
    {
        uptime = on.tv_sec*1000 + on.tv_nsec/1000000;
    }

    return  uptime;
};
#endif
