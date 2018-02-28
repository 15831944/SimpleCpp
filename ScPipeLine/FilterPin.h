
#ifndef FILTER_PIN_H
#define FILTER_PIN_H

#include <string>
#include "PipeLineDef.h"
#include <sigc++/trackable.h>
#include <sigc++/signal.h>
#include <sigc++/connection.h>
#include <sigc++/functors/ptr_fun.h>
#include <sigc++/functors/mem_fun.h>
#include <string>
#include <vector>

namespace SimpleCpp{
	class CFilterPinBuffer;
}
namespace SimpleCpp
{
	class CThread;
	class CMutex;
}
using namespace SimpleCpp;
using namespace std;
using namespace SimpleCpp;

typedef enum _eFilterPinIOType{
	eFPT_In = 0,
	eFPT_Out,
}eFilterPinIOType;
//����״̬
/*
typedef enum _eFilterState{
	eFilterState_Run = 0,
	eFilterState_ToStop,
	eFilterState_Stop,
	eFilterState_Pause,
}eFilterState;*/
//����ģʽ
typedef enum _eFilterPlayMode{
	eFPM_None=0,
	eFPM_Play,
	eFPM_PlayBackward,
	eFPM_PlayNextFrame,
	eFPM_PlayPrevFrame ,
	
}eFilterPlayMode;

 

typedef enum _eFilterPinName{
	eFPN_Video = 0,
	eFPN_Audio,
	
}eFilterPinName;

namespace SimpleCpp{
//��Ϊ out pin ��in pin 
class PIPELINE_API CFilterPin{
 
	friend class CBaseFilter;
public:
	CFilterPin(CBaseFilter *pFilter);
	~CFilterPin();

	int Init(eFilterPinIOType ioType, int nBufferCount);
	int SetAutoFreeMemory(int nReversedMemorySize=0);
	//
	//
	vector<CFilterPin*> &GetNextPins(){return m_lstNextPinIn;};
	int GetConnectedPinCount();
	//�ⲿ���õ� filter ֮����� 
	int GetBuffer(CFilterPinBuffer **pBuffer);
	int PutBuffer(CFilterPinBuffer *pBuffer);
	int GetPreparedBufferConut(){return m_lstBusyBuffer.size();};
	//
	int ResizeBuffers(int nBufferCount);

	//fliter �ڲ����á�
	int GetFreeBuffer(CFilterPinBuffer **pBuffer);
	int GetFreeBufferCount(){return m_lstFreeBuffer.size();};
	//��� ��������Ĵ�С���Ƿ� ɾ�������·���һ����С���ڴ�
	int PutFreeBuffer(CFilterPinBuffer *pBuffer, int nReverseMemory=0);
	//��ͷ����ȡ
	int PutPreparedBuffer(CFilterPinBuffer *pBuffer,  bool bToTail = true  );
	int GetPreparedBuffer(CFilterPinBuffer **pBuffer, bool bFromHead = true);
	// ��ȡ prepare ���ݵ� ��һ���汾����β����ȡ
// 	int PutPreparedBufferToHead();
	//�ͷ����� busy �� free
	void FreeAllBuffer();
	//
	int Clear();
	//����� ������������˸ú�����Ӧ���ڳ����˳���ʱ���ڸ�����ģ�� �ֶ��ͷ�
	template <class T> int CreateBuffer(int nCount=1){
		//m_pMutexFreeBuffer->Lock();
		for (int i=0; i<nCount; i++)
		{
			//��� new ��δ��� ��  �����˳���ʱ����������� 
			CFilterPinBuffer *pBuffer = new T;
			//m_lstFreeBuffer.push_back(pBuffer);
			//��Ҫֱ�ӵ��� m_lstFreeBuffer ��Ϊ��ģ�壬�� dll ��Ӧ�� ���� ֮��ύ�� new delete �����ڴ棬���쳣
			PutFreeBuffer(pBuffer);
		}
		//m_pMutexFreeBuffer->Unlock();
		return 0;
	}
	template <class T> int ResizeBuffer(int nBufferCount=1){
		if (nBufferCount <= m_nBufferCount)
			return m_nBufferCount;
		int nNeedMore = nBufferCount - m_nBufferCount ;

		//m_pMutexFreeBuffer->Lock();
		for (int i=0; i<nNeedMore; i++)
		{
			//��� new ��δ��� ��  �����˳���ʱ����������� 
			CFilterPinBuffer *pBuffer = new T;
			//m_lstFreeBuffer.push_back(pBuffer);
			//��Ҫֱ�ӵ��� m_lstFreeBuffer ��Ϊ��ģ�壬�� dll ��Ӧ�� ���� ֮��ύ�� new delete �����ڴ棬���쳣
			PutFreeBuffer(pBuffer);
		}
		//m_pMutexFreeBuffer->Unlock();
		return m_nBufferCount;
	}
	virtual int Flush();
	const char *GetType();
	eFilterPinIOType GetIoType();
	//�ź������� ����ֵ��  ���pin
	//sigc::signal<int, CFilterPin*, CFilterPinBuffer*>		m_sigPinOut;
	sigc::signal<int, CFilterPin*, CFilterPinBuffer*>*		m_pSigPinOut;
	//��������֪ͨ��
	virtual int OnPinIn(CFilterPin* pPinPrevOut, CFilterPinBuffer* pPinBuffer);
	//void AppendBuffer(CFilterPinBuffer *pBuffer);
	virtual int Connect(CFilterPin*	pNextPinIn);
	//
	virtual int Emit(CFilterPinBuffer *pPinBuffer);
	//
protected:
	//
	bool FindNextPinIn(CFilterPin *pPin/*, int &nIndex*/);
	
	list<CFilterPinBuffer *> m_lstFreeBuffer;
	CMutex *m_pMutexFreeBuffer;
	list<CFilterPinBuffer *> m_lstBusyBuffer;
	CMutex *m_pMutexBusyBuffer;

	//CMutex *m_pMutextFlush;
	int m_nBufferCount;
	eFilterPinIOType m_nIOType;
	//filter���� 
	CBaseFilter *m_pFilter;
	//�Զ� �ͷ� ����� �ڴ档
	int m_nReversePinBufferMemorySize;
	//���ӵ� in pin��һ�� out pin �������ӵ���� in pin 
	vector<CFilterPin *>	m_lstNextPinIn;
	//����� in pin ���ָ�� ��һ�� �������ӵ� out pin
	vector<CFilterPin *>	m_lstPrevPinOut;
	//CFilterPin  *			m_pPrevPinOut;
	//
	int    m_nPinName;
	string m_strPinName;
	string m_strType;
};
}
#endif