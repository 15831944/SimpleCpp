#pragma once
//�ڲ�ʹ�õ���־��

//
class CLog
{
public:
	CLog(void);
	~CLog(void);

	long Open(char* pSzPath);
	long Close();

	long Write(int nLevel, char*pFormat, ...);
	
protected:
};
