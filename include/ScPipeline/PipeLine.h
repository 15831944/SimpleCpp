// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PIPELINE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PIPELINE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
/*
* ��ˮ�� �࣬����ͨ�����ݴ�����ˮ�ߡ�
* ����һ���Ͷ�� filter�� filter֮������ź����������ӣ��Ӷ��γ���������
*/
#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

// �����Ǵ� PipeLine.dll ������
class PIPELINE_API CPipeLine {
public:
	CPipeLine(void);
	// TODO: �ڴ�������ķ�����
};

extern PIPELINE_API int nPipeLine;

PIPELINE_API int fnPipeLine(void);
