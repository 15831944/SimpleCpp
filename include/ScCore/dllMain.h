// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� STHREAD_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// STHREAD_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef STHREAD_EXPORTS
#define SCCORE_API __declspec(dllexport)
#else
#define SCCORE_API __declspec(dllimport)
#endif

// �����Ǵ� SThread.dll ������
class SCCORE_API CSThreadLib {
public:
	CSThreadLib(void);
	// TODO: �ڴ�������ķ�����
};

extern SCCORE_API int nSThread;

SCCORE_API int fnSThread(void);
