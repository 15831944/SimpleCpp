#pragma once

#ifndef SEMAPHOREENCAP_H
#define SEMAPHOREENCAP_H

#ifdef WIN32
#include "Windows.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Kernel32.lib")

#ifdef STHREAD_EXPORTS
#define SCCORE_API __declspec(dllexport)
#else
#define SCCORE_API __declspec(dllimport)
#endif

#else
#include <semaphore.h>
#include <time.h>
#include <errno.h>

#define SCCORE_API

#endif

namespace SimpleCpp
{
	class CSemaphoreData;
	class SCCORE_API CSemaphore
	{
		public:
			CSemaphore();
			virtual ~CSemaphore();

			//lValue:windows�´�ֵ��ʾ�ź�����ʼ�����ֵ��linux�´�ֵ��ʾ�Ƿ��ڽ��̼䣨0������һ�����̵��̼߳乲����0��
			long Init(long lInitCount, long lValue = 10000);
			bool Wait();
			bool TryWait(long lTimeOut);
			long Post();

			long Destory();

		protected:
			CSemaphoreData *m_pSemaphoreData;
	};
}

#endif