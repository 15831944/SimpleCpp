#include "StdAfx.h"
#include "Dwt1.h"

CDwt1::CDwt1(void)
{
}

CDwt1::~CDwt1(void)
{
}
void CDwt1::Dwt53(unsigned char *pSrc, int nW, int nH, int nLevels, int nTh, int nQ, char *pDwtCof)
{

}
void CDwt1::IDwt53(unsigned char *pDwtCof, int nW, int nH, int nLevels, int nTh, int nQ, char *pSrc)
{

}
//ʹ��С��������Сͼ��
void CDwt1::DwtZoomIn53(unsigned char *pSrc, int nW, int nH, int nLevels, unsigned char *pDes)
{
	int nWLL(0), nHLL(0);
	for (int i=0; i<nLevels; i++)
	{
		
		nWLL = nW>>i;
		nHLL = nH>>i;
		for (int y = 0; y<nHLL; y++)
		{
			for (int x=0; x<nWLL; x++)
			{
				
			}
		}
	}
}
//һά 53С�� 1�α任, ���������� , ���ұ߽�ֱ� Ԥ�� 2 �����ݡ�
void CDwt1::Dwt1D53(char *pSrc, int nCount, char *pDwtCof)
{

}