#pragma once
#ifndef int64_t
typedef long long int64_t; 
#endif

namespace CX{
class CTime
{
public:
	CTime(void);
	~CTime(void);
	inline int GetYear();
	inline int GetMonth();
	inline int GetDay();
	inline int GetHour();
	inline int GetMinute();
	inline int GetSecond();
	inline int GetMiniSecond();
	//��1970 �����ڵ�����
	inline int64_t ToSeconds();

	static void GetCurrentTime(CTime &time);
protected:
	//���е�ʱ�䣬��������
	int64_t m_s64Time;
	short	m_s16Year;
	char	m_s8Month;
	char	m_s8Day;
	char	m_s8WeekDay;
	char	m_s8Hour;
	char	m_s8Minute;
	char	m_s8Second;
	short	m_s16MiniSecond;
};
}