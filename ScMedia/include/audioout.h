
#ifndef AUDIO_OUT_H
#define AUDIO_OUT_H


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#pragma once
/*#include "deviceout.h"*/
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
typedef void (__stdcall * OnDataWrite)(void *pParam) ;

#include <queue>

using namespace std;
class CAudioOut/*:public CDeviceOut*/
{
	friend static DWORD WINAPI ThreadAudioOutProc(LPVOID lpParam);
public:
	CAudioOut(int nChannels=2, int nBitPerSample=16, int nSampleRate=44100);
	virtual ~CAudioOut(void);
	//
	virtual int		Open(int nChannels=2, int nBitPerSample=16, int nSampleRate=44100);
	virtual int		Close();
	virtual int		Start();
	virtual int     Stop();
	int		FillData(char *pData, int nLength);
	void	SetOnWriteCB(OnDataWrite cbWrite, void *pParam){
		m_cbOnDataWrite = cbWrite;
		m_pCBParam = pParam;
	};
protected:
	//�̺߳���
	static DWORD WINAPI ThreadAudioOutProc(LPVOID lpParam);
protected:
	//¼���̵߳� ���
	::HANDLE			m_hThread;
	//�߳� id
	DWORD			m_dwThreadId;
	// ������ʽ
	WAVEFORMATEX	m_WF;
	//����
	std::queue<WAVEHDR *> m_lstBuffer;
	int				m_nMaxBuffers;
	//
	OnDataWrite		m_cbOnDataWrite;
	void			*m_pCBParam;
	//
	::HANDLE			m_hDevice;
	//
	CRITICAL_SECTION m_hMutex;
	//
};
#endif