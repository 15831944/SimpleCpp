#pragma once

class CDwt1
{
public:
	CDwt1(void);
	~CDwt1(void);
	
	//���� char���ݣ�һ��Ϊͼ�� ��� ���з��ŵ� dwt ϵ�������� LLͼ��Ҳ�� �����ŵ�ϵ��
	void Dwt53(unsigned char *pSrc, int nW, int nH, int nLevels, int nTh, int nQ, char *pDwtCof);
	void IDwt53(unsigned char *pDwtCof, int nW, int nH, int nLevels, int nTh, int nQ, char *pSrc);
	//ʹ��С��������Сͼ��
	void DwtZoomIn53(unsigned char *pSrc, int nW, int nH, int nLevels, unsigned char *pDes);
	//һά 53С�� 1�α任, ���������� , ���ұ߽�ֱ� Ԥ�� 2 �����ݡ�
	void Dwt1D53(char *pSrc, int nCount, char *pDwtCof);
protected:
	
};
