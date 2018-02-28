
#ifndef AUDIO_IN_H
#define AUDIO_IN_H

#pragma once

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*#include "devicein.h"*/
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

typedef  void (__stdcall *Cb_OnAudioIn)(char *pData, int nLength, void *pParam, void *pReversed);

class CAudioIn/*:public CDeviceIn*/
{
public:
	CAudioIn(int nChannels=2, int nBitPerSample=16, int nSampleRate=44100);
	virtual ~CAudioIn(void);
	virtual int		Open();
	virtual int		Close();
	virtual int     Start();
	virtual int		Stop();

	bool	IsOpen();
	
	void	SetOnDataCB(Cb_OnAudioIn onData, void * pParam);
	//
protected:
	static DWORD WINAPI AudioInThreadProc(LPVOID lpParam);
	//
	int		AllocBuffer();
	int		FreeBuffer();
protected:
	//¼���̵߳� ���
	::HANDLE			m_hThread;
	//�߳� id
	DWORD			m_dwThreadId;
	// ������ʽ
	WAVEFORMATEX	m_WF;
	//���ݻ���
	WAVEHDR			*m_pWHdr;	
	int				m_nBufferSize;
	//
	Cb_OnAudioIn	m_cbOnData;
	::HANDLE		m_hDevice;
	//
	void		*m_pCBParam;
};
#endif