#pragma once

#ifndef BUFFER_H
#define BUFFER_H

#ifndef MEDIASDK_API
#define MEDIASDK_API
#endif

class MEDIASDK_API CBuffer
{
public:
	CBuffer(int nInitSize = 1024, int nMaxSize=1024*1024);
	virtual ~CBuffer(void);
	
	int CopyFrom(CBuffer *pBufferFrom);
	int Append(unsigned char *pData, int nLen);
	int Append(CBuffer *pBuffer);

	int Resize(int nSize);
	int SetUsed(int nUsedSize);
	int SetMaxSize(int nMaxSize);
	int SetAllocSize(int nAllocSize);
	int GetAllocSize();
	int GetUsedSize();
	//�ӿ�ʼ����һ�����ȣ� ѡ���ͷŶ��ڵ��ڴ�, ==0 ����ԭ���ڴ�
	void Clear(int nReversedMemoryLen=0);
	//��� ֮��  nLen��������
	void Clear(int nPos, int nLen);
	//�ӿ�ʼ����һ�����ȣ� ѡ���ͷŶ��ڵ��ڴ�
	//void Clear(int nReversedMemoryLen);

    inline unsigned char* GetData()
    {
        return m_pMemory;
    }
    inline int GetLength(){
        return m_nUsedSize;
    }
	inline  int GetMaxSize()
	{
		return m_nMaxSize;
	}
	
protected:
	unsigned char *m_pMemory;
	int m_nUsedSize;
	int m_nAllocSize;
	int m_nMaxSize;
};

#endif
