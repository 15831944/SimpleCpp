// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� VIVSMEDIABOX_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// VIVSMEDIABOX_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef MEDIA_SDK_H
#define MEDIA_SDK_H

#ifdef WIN32
#ifdef VIVSMEDIABOX_EXPORTS
#define MEDIASDK_API __declspec(dllexport)
#else
#define MEDIASDK_API __declspec(dllimport)
#endif
#else
#define MEDIASDK_API
#define __stdcall
#endif


#ifndef WIN32
#define debug printf
unsigned long timeGetTime();
#endif
//#define OS_WIN

// �����Ǵ� VivsMediaBox.dll ������
class MEDIASDK_API CVivsMediaBox {
public:
	CVivsMediaBox(void);
	// TODO: �ڴ�������ķ�����
};

extern MEDIASDK_API int nVivsMediaBox;

MEDIASDK_API int fnVivsMediaBox(void);
MEDIASDK_API int Vmb_Ret2Err(int nRet);
MEDIASDK_API int Vmb_Err2Ret(int nErr);

#endif
