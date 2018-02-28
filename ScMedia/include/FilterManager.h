#pragma once
//������
//
#include <vector>

using namespace std;

class CMediaFilter;
class CSourceFilter;
class MEDIASDK_API CFilterManager
{
public:
	CFilterManager(void);
	virtual ~CFilterManager(void);

	static CFilterManager *GetManager();
	//ϵͳ�������ͷţ����ʹ�� ȫ�ֱ�������ע��
	static int RegistFilter(CMediaFilter* pFilter);
	//���������ʹ�õ� ����
	static int CreateFilter(char *pName, CMediaFilter **pFilter);
	static void FreeFilter(CMediaFilter *pFilter);
	//��������filter, ����һ��������͵ڶ�����������������
	static int Connect(CMediaFilter *pFilterFirst, int nPinOutIndex, CMediaFilter *pFilterSecond, int nPinInIndex);
	static int Disconnect(CMediaFilter *pFilterFirst, CMediaFilter *pFilterSecond);
	static int GetSourceFilter(vector<CSourceFilter*> &lstSourceFilter);
protected:
	void RegistFilterImp(CMediaFilter* pFilter);
	int  CreateFilterImp(char *pName, CMediaFilter **pFilter);

protected:
	vector<CMediaFilter *> m_lstFilter;
};
//extern VIVSMEDIABOX_API CFilterManager *g_pFilterManager;

