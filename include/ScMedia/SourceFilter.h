#pragma once
#include "MediaFilter.h"
#include "MediaSdkDef.h"

#undef  GetCurrTime

#define AvFormat_Unknown "AvFormat_Unknown"
class MEDIASDK_API CSourceFilter :
	public CMediaFilter
{
public:
	CSourceFilter(void);
	virtual ~CSourceFilter(void);


	virtual int Seek(int64_t s64Time, int nFlag=0);
	//���� ������ֻ�Ǹ��� ���� ��֮���ӵ� ���� ��һ��  Filter �� DoFilter 
	//������� �� stream �� thread ѭ��ִ�С�����
	//virtual int DoFilter();

	virtual int Close();
	virtual int64 GetTotalTime();
	virtual int64 GetCurrTime();
	virtual void GetTimeBase(int &nNum, int nDen);
	virtual int64 TimestampToTime(int64 s64Timestamp);
	virtual int64 TimeToTimestamp(int64 s64Time);

	virtual int GetWidth();
	virtual int GetHeight();
	virtual int GetPixelFormat();
	//��� ���� stream���߳� ���� ���ߵ�ʱ��
	virtual int GetPumperSleepTime();
	virtual bool IsStreamEnd();

	virtual char *GetFormatName();
	virtual char *GetFormatSubName() ;
	virtual void  SetSegment(int64_t s64TimeBegin, int64_t s64TimeEnd);
	virtual bool  IsNeedFix();
	virtual int   DoFixFile(int64 &s64Total, int64 &s64Pos);

	virtual int  ProbMediaInfo(char *pSzFile);
protected:
	virtual CMediaFilter *CreateObject();
	virtual int CheckFormat(char *pSzFile);

	bool	m_bSeek;
	int64_t m_s64SeekTime;
	int64_t m_s64TimeStamp;
	int64_t m_s64TotalTime;
	int64_t m_s64CurrTime;

	int     m_nW;
	int		m_nH;
	int     m_nPixelFormat;
	//
	int64_t  m_s64SegmentTimeBegin;
	int64_t  m_s64SegmentTimeEnd;
	//�޸��ļ�
	bool    m_bNeedFix;

	//0 �ܸߵ� cpuѭ���� �����ֵ �Ǳ��ⲿ�����߳�ʹ�� 
	int		m_nNeedSleep;
	bool	m_bIsStreamEnd;
	char	m_szFormatName[32];
	char    m_szFormatSubName[32];
};
//extern CSourceFilter g_sourceFilter;