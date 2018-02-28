// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SIMPLESOCKET_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SCNETWORK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef SIMPLE_SOCKET_H
#define SIMPLE_SOCKET_H
#ifdef SIMPLESOCKET_EXPORTS
#define SCNETWORK_API __declspec(dllexport)
#else
#define SCNETWORK_API __declspec(dllimport)
#endif

#ifdef OS_LINUX
#define SCNETWORK_API
#endif

// �����Ǵ� SimpleSocket.dll ������
// class SCNETWORK_API CSimpleSocket {
// public:
// 	CSimpleSocket(void);
// 	// TODO: �ڴ�������ķ�����
// };

extern SCNETWORK_API int nSimpleSocket;

SCNETWORK_API int fnSimpleSocket(void);

typedef enum SCNETWORK_API _eCommunicationStyle
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

namespace SimpleCpp{

	class CScNetwork
	{
		CScNetwork();
		~CScNetwork();

		static int Init();
		static int Free();
		static CScNetwork m_instance;
	};


}

#endif
