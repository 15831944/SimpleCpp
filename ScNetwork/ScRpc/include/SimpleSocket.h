// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SIMPLESOCKET_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SIMPLESOCKET_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef SIMPLE_SOCKET_H
#define SIMPLE_SOCKET_H
#ifdef SIMPLESOCKET_EXPORTS
#define SIMPLESOCKET_API __declspec(dllexport)
#else
#define SIMPLESOCKET_API __declspec(dllimport)
#endif

#ifdef OS_LINUX
#define SIMPLESOCKET_API
#endif

// �����Ǵ� SimpleSocket.dll ������
// class SIMPLESOCKET_API CSimpleSocket {
// public:
// 	CSimpleSocket(void);
// 	// TODO: �ڴ�������ķ�����
// };

extern SIMPLESOCKET_API int nSimpleSocket;

SIMPLESOCKET_API int fnSimpleSocket(void);

typedef enum SIMPLESOCKET_API _eCommunicationStyle
{
	eCommunicationStyle_Select = 1,
	eCommunicationStyle_MultiSelect,
	eCommunicationStyle_Iocp
}eCommunicationStyle;

#define BUF_LEN_32 32
#define BUF_LEN_64 64
#define BUF_LEN_128 128
#define BUF_LEN_256 256
#define BUF_LEN_512 512
#define BUF_LEN_1024 1024

namespace SimpleSocket{

	class CSimpleSocket
	{
		CSimpleSocket();
		~CSimpleSocket();

		static int Init();
		static int Free();
		static CSimpleSocket m_instance;
	};


}

#endif
