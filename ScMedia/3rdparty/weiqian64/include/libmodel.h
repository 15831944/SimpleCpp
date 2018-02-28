
#ifndef DHNETSDK_H
#define DHNETSDK_H

//#include "HikClient.h"
#include "libclient.h"

#ifdef WIN32

#ifdef DHNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllexport) 
#else	//#ifdef DHNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllimport)   //VC ��
#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#else	//linux

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

//#define RELEASE_HEADER	//����ͷ�ļ�
#ifdef RELEASE_HEADER

#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	unsigned long
#define TRUE	0x01
#define FALSE	0x00
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#define NULL	0
typedef struct  tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
}RECT;
#else	//�ڲ�����
#include "../netsdk/osIndependent.h"
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

	/************************************************************************
	** ��������
	***********************************************************************/
#define RV_SERIALNO_LEN 		48		//�豸���к��ַ�����
#define RV_MAX_DISKNUM 			32		//���Ӳ�̸���
#define RV_MAX_SDCARDNUM		32		//���SD������
#define RV_MAX_BURNING_DEV_NUM	32		//����¼�豸����
#define RV_BURNING_DEV_NAMELEN	32		//��¼�豸������󳤶�
#define RV_MAX_LINK 			6		
#define RV_MAX_CHANNUM 			16		//���ͨ������
#define RV_MAX_ALARMIN 			128		//��󱨾��������
#define RV_MAX_ALARMOUT 		64		//��󱨾��������

#define RV_MAX_RIGHT_NUM		100		//�û�Ȩ�޸�������
#define RV_MAX_GROUP_NUM		20		//�û����������
#define RV_MAX_USER_NUM			200		//�û���������
#define RV_RIGHT_NAME_LENGTH	32		//Ȩ��������
#define RV_USER_NAME_LENGTH		8		//�û�������
#define RV_USER_PSW_LENGTH		8		//�û����볤��
#define RV_MEMO_LENGTH			32		//��ע����

#define RV_MAX_STRING_LEN		128
	//chenfeng20090520 -s
#define RV_DEF_REALPLAY_BUF_NUM (3) 
#define RV_MIN_REALPLAY_BUF_NUM (1) 
#define RV_MAX_REALPLAY_BUF_NUM (50) 
	//chenfeng20090520 -E

	//�����豸�ص�����
#define RV_DVR_SERIAL_RETURN 1   //�豸�������кŻص�
#define RV_DVR_DISCONNECT -1      //��֤�ڼ��豸���߻ص�

	//ͨ�������ַ�������س���
#define MAX_STRING_LINE_LEN	6		//�������
#define MAX_PER_STRING_LEN  20		//ÿ����󳤶�

	//2010-1-12�����޸�start
	//DDNS��Ŀ����
#define MAX_DDNS_COUNT 16
	//2010-1-12�����޸�end

	//�ص�������Ϣ���ͣ���ӦCLIENT_StartListen
#define RV_COMM_ALARM			0x1100	//���汨����Ϣ(�����ⲿ��������Ƶ��ʧ����̬���)
#define RV_SHELTER_ALARM		0x1101	//��Ƶ�ڵ�����
#define RV_DISK_FULL_ALARM		0x1102	//Ӳ��������
#define RV_DISK_ERROR_ALARM		0x1103	//Ӳ�̹��ϱ���
#define RV_SOUND_DETECT_ALARM	0x1104	//��Ƶ��ⱨ��
#define RV_ALARM_DECODER_ALARM	0x1105	//��������������

	//��չ�ص�������Ϣ���ͣ���ӦCLIENT_StartListenEx
	//������������ϸ�ֿ�
#define RV_ALARM_ALARM_EX			0x2101	//�ⲿ����
#define RV_MOTION_ALARM_EX			0x2102	//��̬��ⱨ��
#define RV_VIDEOLOST_ALARM_EX		0x2103	//��Ƶ��ʧ����
#define RV_SHELTER_ALARM_EX			0x2104	//�ڵ�����
#define RV_SOUND_DETECT_ALARM_EX	0x2105	//��Ƶ��ⱨ��
#define RV_DISKFULL_ALARM_EX		0x2106	//Ӳ��������
#define RV_DISKERROR_ALARM_EX		0x2107	//��Ӳ�̱���
#define RV_ENCODER_ALARM_EX			0x210A	//����������
#define RV_URGENCY_ALARM_EX			0x210B	//��������
#define RV_WIRELESS_ALARM_EX		0x210C	//���߱���
#define RV_NEW_SOUND_DETECT_ALARM_EX 0x210D //����Ƶ��ⱨ��������Ϣ�Ľṹ���RV_NEW_SOUND_ALARM_STATE;
#define RV_DECODER_ALARM_EX			0x210E	//����������

#define RV_SAVIA_ALARM_TRACK		0x210F	//���ܣ������㷨����
#define RV_SAVIA_ALARM_CROSSLINE	0x2110	//���ܣ�Խ���㷨����
#define RV_SAVIA_ALARM_CROSSNET		0x2111	//���ܣ������㷨����
#define RV_SAVIA_ALARM_WANDER		0x2112	//���ܣ��ǻ��㷨����
#define RV_SAVIA_ALARM_CONVERSE		0x2113	//���ܣ������㷨����
#define RV_SAVIA_ALARM_STATIC		0x2114	//���ܣ������㷨����
#define RV_SAVIA_ALARM_LOST			0x2115	//���ܣ���ʧ�㷨����
#define RV_SAVIA_ALARM_DAMAGE		0x2116	//���ܣ���Ϳ�㷨����
#define RV_INTE_ALARM_SMOKEFIRE		0x2117	//���ܣ��̻��㷨����

#define RV_INTE_ALARM_RED_LEVEL_1	0x2118	//���ܣ����ܺ�ɫ���澯1��
#define RV_INTE_ALARM_RED_LEVEL_2	0x2119	//���ܣ����ܺ�ɫ���澯2��
#define RV_INTE_ALARM_RED_LEVEL_3	0x211a	//���ܣ����ܺ�ɫ���澯3��
#define RV_INTE_ALARM_RED_LEVEL_4	0x211b	//���ܣ����ܺ�ɫ���澯4��
#define RV_INTE_ALARM_RED_LEVEL_5	0x211c	//���ܣ����ܺ�ɫ���澯5��
#define RV_INTE_ALARM_RED_LEVEL_6	0x211d	//���ܣ����ܺ�ɫ���澯6��


#define RV_CONFIG_RESULT_EVENT_EX	0X3000  //�޸����õķ����뷵�ؽṹ��DEV_SET_RESULT
#define RV_REBOOT_EVENT_EX			0x3001	//�豸�����¼�
#define RV_AUTO_TALK_START_EX		0x3002  //�豸������ʼ�����Խ�
#define RV_AUTO_TALK_STOP_EX		0x3003  //�豸����ֹͣ�����Խ�

	//��ѯ�豸״̬�ӿڲ�������ѯ���� ����CLIENT_QueryDevState����
#define RV_DEVSTATE_COMM_ALARM		0x0001	//��ѯ��ͨ����(�����ⲿ��������Ƶ��ʧ����̬���)
#define RV_DEVSTATE_SHELTER_ALARM	0x0002	//��ѯ�ڵ�����
#define RV_DEVSTATE_RECORDING		0x0003	//��ѯ¼��״̬
#define RV_DEVSTATE_DISK			0x0004	//��ѯӲ��״̬
#define RV_DEVSTATE_RESOURCE		0x0005	//ϵͳ��Դ״̬
#define RV_DEVSTATE_BITRATE			0x0006	//��ȡͨ������
#define RV_DEVSTATE_CONN			0x0007	//��ȡ�豸����״̬
#define RV_DEVSTATE_PROTOCAL_VER	0x0008	//��ȡ����Э��汾��,	pBuf = int*
#define RV_DEVSTATE_TALK_ECTYPE		0x0009	//��ȡ�豸֧�ֵ������Խ���ʽ�б����ṹ��DHDEV_TALKFORMAT_LIST
#define RV_DEVSTATE_SD_CARD			0x000A	//��ȡSD����Ϣ��IPC���Ʒ��
#define RV_DEVSTATE_BURNING_DEV			0x000B	//��ѯ��¼����Ϣ
#define RV_DEVSTATE_BURNING_PROGRESS	0x000C	//��ѯ��¼����
#define RV_DEVSTATE_PLATFORM		0x000D	//��ȡ�豸֧�ֵĽ���ƽ̨
#define RV_DEVSTATE_CAMERA			0x000E	//��ȡ����ͷ������Ϣ��pBuf = DHDEV_CAMERA_INFO *�������ж���ṹ��
#define RV_DEVSTATE_SOFTWARE		0x000F	//�豸����汾��Ϣ
#define RV_DEVSTATE_LANGUAGE        0x0010  //�豸֧�ֵ���������
#define RV_DEVSTATE_DSP				0x0011	//DSP��������
#define	RV_DEVSTATE_OEM				0x0012	//OEM
#define	RV_DEVSTATE_NET				0x0013  //��������״̬��Ϣ
#define RV_DEVSTATE_TYPE			0x0014  //�豸����
#define RV_DEVSTATE_SNAP			0x0015	 //ץͼ����������ѯ
	//ץͼ��Ƶ��������
#define CODETYPE_MPEG4   0
#define CODETYPE_H264    1
#define CODETYPE_JPG     2

	//�������ʹ��ţ�CLIENT_GetLastError�����ķ���
#define _EC(x)						(0x80000000|x)
#define NET_NOERROR 				0				//û�д���
#define NET_ERROR					-1				//δ֪����
#define NET_SYSTEM_ERROR			_EC(1)			//Windowsϵͳ����
#define NET_NETWORK_ERROR			_EC(2)			//������󣬿�������Ϊ���糬ʱ
#define NET_DEV_VER_NOMATCH			_EC(3)			//�豸Э�鲻ƥ��
#define NET_INVALID_HANDLE			_EC(4)			//�����Ч
#define NET_OPEN_CHANNEL_ERROR		_EC(5)			//��ͨ��ʧ��
#define NET_CLOSE_CHANNEL_ERROR		_EC(6)			//�ر�ͨ��ʧ��
#define NET_ILLEGAL_PARAM			_EC(7)			//�û��������Ϸ�
#define NET_SDK_INIT_ERROR			_EC(8)			//SDK��ʼ������
#define NET_SDK_UNINIT_ERROR		_EC(9)			//SDK�������
#define NET_RENDER_OPEN_ERROR		_EC(10)			//����render��Դ����
#define NET_DEC_OPEN_ERROR			_EC(11)			//�򿪽�������
#define NET_DEC_CLOSE_ERROR			_EC(12)			//�رս�������
#define NET_MULTIPLAY_NOCHANNEL		_EC(13)			//�໭��Ԥ���м�⵽ͨ����Ϊ0
#define NET_TALK_INIT_ERROR			_EC(14)			//¼�����ʼ��ʧ��
#define NET_TALK_NOT_INIT			_EC(15)			//¼����δ����ʼ��
#define	NET_TALK_SENDDATA_ERROR		_EC(16)			//������Ƶ���ݳ���
#define NET_REAL_ALREADY_SAVING		_EC(17)			//ʵʱ�����Ѿ����ڱ���״̬
#define NET_NOT_SAVING				_EC(18)			//δ����ʵʱ����
#define NET_OPEN_FILE_ERROR			_EC(19)			//���ļ�����
#define NET_PTZ_SET_TIMER_ERROR		_EC(20)			//������̨���ƶ�ʱ��ʧ��
#define NET_RETURN_DATA_ERROR		_EC(21)			//�Է������ݵ�У�����
#define NET_INSUFFICIENT_BUFFER		_EC(22)			//û���㹻�Ļ���
#define NET_NOT_SUPPORTED			_EC(23)			//��ǰSDKδ֧�ָù���
#define NET_NO_RECORD_FOUND			_EC(24)			//��ѯ����¼��
#define NET_NOT_AUTHORIZED			_EC(25)			//�޲���Ȩ��
#define NET_NOT_NOW					_EC(26)			//��ʱ�޷�ִ��
#define NET_NO_TALK_CHANNEL			_EC(27)			//δ���ֶԽ�ͨ��
#define NET_NO_AUDIO				_EC(28)			//δ������Ƶ
#define NET_NO_INIT					_EC(29)			//CLientSDKδ����ʼ��
#define NET_DOWNLOAD_END			_EC(30)			//�����ѽ���
#define NET_EMPTY_LIST				_EC(31)			//��ѯ���Ϊ��

#define NET_ERROR_GETCFG_SYSATTR	_EC(32)			//��ȡ����ʧ��λ�ã�ϵͳ����
#define NET_ERROR_GETCFG_SERIAL		_EC(33)			//��ȡ����ʧ��λ�ã����к�
#define NET_ERROR_GETCFG_GENERAL	_EC(34)			//��ȡ����ʧ��λ�ã���������
#define NET_ERROR_GETCFG_DSPCAP		_EC(35)			//��ȡ����ʧ��λ�ã�DSP��������
#define NET_ERROR_GETCFG_NETCFG		_EC(36)			//��ȡ����ʧ��λ�ã���������
#define NET_ERROR_GETCFG_CHANNAME	_EC(37)			//��ȡ����ʧ��λ�ã�ͨ������
#define NET_ERROR_GETCFG_VIDEO		_EC(38)			//��ȡ����ʧ��λ�ã���Ƶ����
#define NET_ERROR_GETCFG_RECORD		_EC(39)			//��ȡ����ʧ��λ�ã�¼��ʱ����
#define NET_ERROR_GETCFG_PRONAME	_EC(40)			//��ȡ����ʧ��λ�ã�������Э������
#define NET_ERROR_GETCFG_FUNCNAME	_EC(41)			//��ȡ����ʧ��λ�ã�232���ڹ�������
#define NET_ERROR_GETCFG_485DECODER	_EC(42)			//��ȡ����ʧ��λ�ã�����������
#define NET_ERROR_GETCFG_232COM		_EC(43)			//��ȡ����ʧ��λ�ã�232��������
#define NET_ERROR_GETCFG_ALARMIN	_EC(44)			//��ȡ����ʧ��λ�ã��ⲿ������������
#define NET_ERROR_GETCFG_ALARMDET	_EC(45)			//��ȡ����ʧ��λ�ã�ͼ���ⱨ������
#define NET_ERROR_GETCFG_SYSTIME	_EC(46)			//��ȡ����ʧ��λ�ã��豸ʱ��
#define NET_ERROR_GETCFG_PREVIEW	_EC(47)			//��ȡ����ʧ��λ�ã�Ԥ������
#define NET_ERROR_GETCFG_AUTOMT		_EC(48)			//��ȡ����ʧ��λ�ã��Զ�ά������
#define NET_ERROR_GETCFG_VIDEOMTRX	_EC(49)			//��ȡ����ʧ��λ�ã���Ƶ��������
#define NET_ERROR_GETCFG_COVER		_EC(50)			//��ȡ����ʧ��λ�ã���Ƶ�����ڵ�
#define NET_ERROR_GETCFG_WATERMAKE	_EC(51)			//��ȡ����ʧ��λ�ã�ͼ��ˮӡ����
#define NET_ERROR_GETCFG_ETHERNET	_EC(300)		//��ȡ����ʧ��λ�ã���������
#define NET_ERROR_GETCFG_WLAN		_EC(301)		//��ȡ����ʧ��λ�ã�����������Ϣ
#define NET_ERROR_GETCFG_WLANDEV	_EC(302)		//��ȡ����ʧ��λ�ã��������������豸
#define NET_ERROR_GETCFG_REGISTER	_EC(303)		//��ȡ����ʧ��λ�ã�����ע���������
#define NET_ERROR_GETCFG_CAMERA		_EC(304)		//��ȡ����ʧ��λ�ã�����ͷ��������
#define NET_ERROR_GETCFG_INFRARED	_EC(305)		//��ȡ����ʧ��λ�ã����ⱨ������
#define NET_ERROR_GETCFG_SOUNDALARM	_EC(306)		//��ȡ����ʧ��λ�ã���Ƶ��������
#define NET_ERROR_GETCFG_STORAGE    _EC(307)		//��ȡ����ʧ��λ�ã��洢λ������
#define NET_ERROR_GETCFG_MAIL		_EC(308)		//��ȡ�ʼ�����ʧ��


#define NET_ERROR_SETCFG_GENERAL	_EC(55)			//��������ʧ��λ�ã���������
#define NET_ERROR_SETCFG_NETCFG		_EC(56)			//��������ʧ��λ�ã���������
#define NET_ERROR_SETCFG_CHANNAME	_EC(57)			//��������ʧ��λ�ã�ͨ������
#define NET_ERROR_SETCFG_VIDEO		_EC(58)			//��������ʧ��λ�ã���Ƶ����
#define NET_ERROR_SETCFG_RECORD		_EC(59)			//��������ʧ��λ�ã�¼��ʱ����
#define NET_ERROR_SETCFG_485DECODER	_EC(60)			//��������ʧ��λ�ã�����������
#define NET_ERROR_SETCFG_232COM		_EC(61)			//��������ʧ��λ�ã�232��������
#define NET_ERROR_SETCFG_ALARMIN	_EC(62)			//��������ʧ��λ�ã��ⲿ������������
#define NET_ERROR_SETCFG_ALARMDET	_EC(63)			//��������ʧ��λ�ã�ͼ���ⱨ������
#define NET_ERROR_SETCFG_SYSTIME	_EC(64)			//��������ʧ��λ�ã��豸ʱ��
#define NET_ERROR_SETCFG_PREVIEW	_EC(65)			//��������ʧ��λ�ã�Ԥ������
#define NET_ERROR_SETCFG_AUTOMT		_EC(66)			//��������ʧ��λ�ã��Զ�ά������
#define NET_ERROR_SETCFG_VIDEOMTRX	_EC(67)			//��������ʧ��λ�ã���Ƶ��������
#define NET_ERROR_SETCFG_COVER		_EC(69)			//��������ʧ��λ�ã���Ƶ�����ڵ�
#define NET_ERROR_SETCFG_WATERMAKE	_EC(60)			//��������ʧ��λ�ã�ͼ��ˮӡ����
#define NET_ERROR_SETCFG_WLAN		_EC(61)			//��������ʧ��λ�ã�����������Ϣ
#define NET_ERROR_SETCFG_WLANDEV	_EC(62)			//��������ʧ��λ�ã�ѡ�����������豸
#define NET_ERROR_SETCFG_REGISTER	_EC(63)			//��������ʧ��λ�ã�����ע���������
#define NET_ERROR_SETCFG_CAMERA		_EC(64)			//��������ʧ��λ�ã�����ͷ��������
#define NET_ERROR_SETCFG_INFRARED	_EC(65)			//��������ʧ��λ�ã����ⱨ������
#define NET_ERROR_SETCFG_SOUNDALARM	_EC(66)			//��������ʧ��λ�ã���Ƶ��������
#define NET_ERROR_SETCFG_STORAGE    _EC(67)			//��������ʧ��λ�ã��洢λ������

#define NET_AUDIOENCODE_NOTINIT		_EC(70)			//��Ƶ����ӿ�û�гɹ���ʼ��
#define NET_DATA_TOOLONGH			_EC(71)			//���ݹ���

#define NET_UNSUPPORTED				_EC(72)			//�豸��֧�ָò���
#define NET_DEVICE_BUSY				_EC(73)			//�豸��Դ����
#define NET_SERVER_STARTED			_EC(74)			//�������Ѿ�����
#define NET_SERVER_STOPPED			_EC(75)			//��������δ�ɹ�����

#define NET_LISTER_INCORRECT_SERIAL	_EC(80)			//�������к�����
#define NET_QUERY_DISKINFO_FAILED	_EC(81)			//��ȡӲ����Ϣʧ��

#define NET_LOGIN_ERROR_PASSWORD	_EC(100)		//���벻��ȷ
#define NET_LOGIN_ERROR_USER		_EC(101)		//�ʻ�������
#define NET_LOGIN_ERROR_TIMEOUT		_EC(102)		//�ȴ���¼���س�ʱ
#define NET_LOGIN_ERROR_RELOGGIN	_EC(103)		//�ʺ��ѵ�¼
#define NET_LOGIN_ERROR_LOCKED		_EC(104)		//�ʺ��ѱ�����
#define NET_LOGIN_ERROR_BLACKLIST	_EC(105)		//�ʺ��ѱ���Ϊ������
#define NET_LOGIN_ERROR_BUSY		_EC(106)		//��Դ���㣬ϵͳæ
#define NET_LOGIN_ERROR_CONNECT		_EC(107)		//��������ʧ��"
#define NET_LOGIN_ERROR_NETWORK		_EC(108)		//��������ʧ��"

#define NET_RENDER_SOUND_ON_ERROR	_EC(120)		//Render�����Ƶ����
#define NET_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render��ر���Ƶ����
#define NET_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render�������������
#define NET_RENDER_ADJUST_ERROR		_EC(123)		//Render�����û����������
#define NET_RENDER_PAUSE_ERROR		_EC(124)		//Render����ͣ���ų���
#define NET_RENDER_SNAP_ERROR		_EC(125)		//Render��ץͼ����
#define NET_RENDER_STEP_ERROR		_EC(126)		//Render�ⲽ������
#define NET_RENDER_FRAMERATE_ERROR	_EC(127)		//Render������֡�ʳ���

#define NET_GROUP_EXIST				_EC(140)		//�����Ѵ���
#define	NET_GROUP_NOEXIST			_EC(141)		//����������
#define NET_GROUP_RIGHTOVER			_EC(142)		//���Ȩ�޳���Ȩ���б�Χ
#define NET_GROUP_HAVEUSER			_EC(143)		//�������û�������ɾ��
#define NET_GROUP_RIGHTUSE			_EC(144)		//���ĳ��Ȩ�ޱ��û�ʹ�ã����ܳ���
#define NET_GROUP_SAMENAME			_EC(145)		//������ͬ���������ظ�
#define	NET_USER_EXIST				_EC(146)		//�û��Ѵ���
#define NET_USER_NOEXIST			_EC(147)		//�û�������
#define NET_USER_RIGHTOVER			_EC(148)		//�û�Ȩ�޳�����Ȩ��
#define NET_USER_PWD				_EC(149)		//�����ʺţ��������޸�����
#define NET_USER_FLASEPWD			_EC(150)		//���벻��ȷ
#define NET_USER_NOMATCHING			_EC(151)		//���벻ƥ��


#define NET_CONFIG_DEVBUSY			_EC(999)		//��ʱ�޷�����
#define NET_CONFIG_DATAILLEGAL		_EC(1000)		//�������ݲ��Ϸ�

	//Զ�����ýӿ�CLIENT_GetDEVConfig,CLIENT_GetDEVConfig�����������
#define RV_DEV_DEVICECFG			1		//��ȡ�豸����
#define RV_DEV_NETCFG				2		//��ȡ�������
#define RV_DEV_CHANNELCFG			3		//��ȡͨ�����ã�ͼ��ѹ��������
#define RV_DEV_PREVIEWCFG 			4		//��ȡԤ������
#define RV_DEV_RECORDCFG			5		//��ȡ¼��ʱ�����
#define RV_DEV_COMMCFG				6		//��ȡ���ڲ���
#define RV_DEV_ALARMCFG 			7		//��ȡ��������
#define RV_DEV_TIMECFG 				8		//��ȡDVRʱ��
#define RV_DEV_TALKCFG				9		//�Խ�����
#define RV_DEV_AUTOMTCFG			10		//�Զ�ά������		
#define	RV_DEV_VEDIO_MARTIX			11		//����������Ʋ�������	
#define RV_DEV_MULTI_DDNS			12		//��ddns����������
#define RV_DEV_SNAP_CFG				13		//ץͼ�������
#define RV_DEV_WEB_URL_CFG			14		//HTTP·������
#define RV_DEV_FTP_PROTO_CFG		15		//FTP�ϴ�����
#define RV_DEV_INTERVIDEO_CFG		16		//ƽ̨�������ã���ʱchannel��������ƽ̨���ͣ�
	//channel=4  ��������������
	//channel=10	 ����������ά
	//channel=11 ����U��ͨ
#define RV_DEV_VIDEO_COVER			17		//�����ڵ�����
#define RV_DEV_TRANS_STRATEGY		18		//����������ã���������\����������
#define RV_DEV_DOWNLOAD_STRATEGY	19		//¼�����ز������ã���������\��ͨ����
#define RV_DEV_WATERMAKE_CFG		20		//ͼ��ˮӡ����
#define RV_DEV_WLAN_CFG				21		//������������
#define RV_DEV_WLAN_DEVICE_CFG		22		//���������豸����
#define RV_DEV_REGISTER_CFG			23		//����ע���������
#define RV_DEV_CAMERA_CFG			24		//����ͷ��������
#define RV_DEV_INFRARED_CFG 		25		//��ȡ���ⱨ������
#define RV_DEV_SNIFFER_CFG			26		//Snifferץ������
#define RV_DEV_MAIL_CFG				27		//�ʼ�����,�����Ժ���ô���������
#define RV_DEV_DNS_CFG				28		//DNS����������
#define RV_DEV_NTP_CFG				29		//NTP����
#define RV_DEV_AUDIO_DETECT_CFG		30		//��Ƶ�������
#define RV_DEV_STORAGE_STATION_CFG  31      //�洢λ������
#define RV_DEV_PTZ_OPT_CFG			32		//��̨��������
	//add by HY 2009-11-2 begin
#define RV_DEV_DDNS_CFG				33		//DDNS����
	//add by HY 2009-11-2 end
	//add by HY 2009-11-16 begin
#define RV_DEV_UPNP_CFG				34		//UPNP����
	//add by HY 2009-11-16 end
	//add by ���� 2009-12-14 begin
#define RV_DEV_SAVIA_ALARM_CFG		35		//SAVIA������������
#define RV_DEV_SAVIA_COUNT_CFG		36		//SAVIA��Ŀ
	//add by ���� 2009-12-14 end
	//add by ���� 2009-12-28 start
#define RV_DEV_BLACKWHITE_CFG		37		//�ڰ���������
	//add by ���� 2009-12-28 end
	//add by ���� 2010-1-12 begin
#define RV_DEV_DDNS_CFG_EX			38		//DDNS����
	//add by ���� 2010-1-12 end
	//add by ���� 2010-1-21 begin
#define RV_DEV_DECODER_CFG			39		//����������
	//add by ���� 2010-1-21 end
	//add by ���� 2010-2-10 begin
#define RV_DEV_REG_SERVER_CFG		40		//����ע������
	//add by ���� 2010-2-10 end
	//add by ���� 2010-3-1 begin
#define RV_DEV_DISPLAY_SPLIT		41		//����ָ�ͨ���������
#define RV_DEV_DISPLAY_TOUR			42		//��Ѳ����
#define RV_DEV_DISPLAY_SPLITTOUR	43		//����ָ�ͨ�������Ѳ����
#define RV_DEV_SNAP_CFG_NEW			44		//ץͼ�������
	//add by ���� 2010-3-1 end
#define RV_DEV_DECODER_ALARM_CFG	45		//�������澯����
#define RV_DEV_MARGIN_CFG			46		//TV��������
//2010-3-18 luhj-0007
#define RV_DEV_IPCONFLICT_CFG		47		//IP��ͻ����
#define RV_DEV_MAIL_CFG_EX			48		//����������		luhj add
#define RV_DEV_DEV_CFG				49		//�豸��Ϣ(ʹ��TLVЭ��)
#define RV_DEV_CHANNEL_ENC_CFG		50		//�豸ͨ��������Ϣ(ʹ��TLVЭ��)
#define RV_DEV_NET_BASE_CFG			51		//������������(ʹ��TLVЭ��)
#define RV_DEV_NET_APP_CFG			52		//Ӧ����������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_CFG			53		//��ȡ���б�������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_IN_CFG			54		//���ñ������뱨������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_MOTION_CFG		55		//������Ƶ���챨������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_LOSS_CFG		56		//������Ƶ��Ƶ��ʧ��������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_BIND_CFG		57		//������Ƶ��Ƶ�ڵ���������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_NODISK_CFG		58		//������Ӳ�̱�������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_ERRDISK_CFG	59		//����Ӳ�̴��󱨾�����(ʹ��TLVЭ��)
#define RV_DEV_ALARM_FULLDISK_CFG	60		//����Ӳ������������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_NETBROKEN_CFG	61		//���ö�����������(ʹ��TLVЭ��)
#define RV_DEV_ALARM_IPCONFLICT_CFG	62		//����IP��ͻ��������(ʹ��TLVЭ��)

#define RV_DEV_INTERVIDEO_BELL_CFG	64		//bellƽ̨��������
#define RV_DEV_INTERVIDEO_MEGA_CFG	65		//���Ż�ͨƽ̨��������
#define RV_DEV_INTERVIDEO_VS300_CFG	66		//VS300ƽ̨��������
#define RV_DEV_INTERVIDEO_ZXSHENYAN_CFG	67		//����ƽ̨��������


#define RV_DEV_DISK_CFG				80		//��������(ʹ��TLVЭ��)
#define RV_DEV_NET_COMM_CFG			81		//����ͨ������(ʹ��TLVЭ��)
#define RV_DEV_EMAIL_CFG			82		//EMAIL����(ʹ��TLVЭ��)
#define RV_DEV_DNS_CFG_TLV			83		//dns����(ʹ��TLVЭ��)
#define RV_DEV_UPNP_CFG_TLV			84		//upnp����(ʹ��TLVЭ��)
#define RV_DEV_PPPOE_CFG			85		//pppoe����(ʹ��TLVЭ��)
#define RV_DEV_MDDNS_CFG			86		//DDNS����(ʹ��TLVЭ��)
#define RV_DEV_CODE_CFG				87		//��������(ʹ��TLVЭ��)
#define RV_DEV_NTP_CFG_TLV			88		//NTP����(ʹ��TLVЭ��)
#define RV_DEV_OUT_MODE_CFG			89		//���ģʽ����(ʹ��TLVЭ��)

//2010-3-31 luhj-0016
#define	RV_DEV_PRESET_CFG			90//81		//��̨Ԥ�õ�����
#define RV_DEV_TOUR_CFG				91//82		//��̨���Ѳ������
#define RV_DEV_ADDPRESET_CFG		92//83		//����Ԥ�õ����
#define RV_DEV_DELETEPRESET_CFG		93//84		//ɾ��Ԥ�õ����
#define	RV_DEV_ADDTOURPRESET_CFG	94//85		//����Ѳ��Ԥ�õ����
#define RV_DEV_DELTOURPRESET_CFG	95//86		//ɾ��Ѳ��Ԥ�õ����
#define	RV_DEV_CLEARTOUR_CFG		96//87		//ɾ��Ѳ����·
//luhj-0016

#define	RV_DEV_FTP_CFG				97			//FTP����
#define	RV_DEV_RTSP_CFG				98			//RTSP����

#define	RV_DEV_INTERED_CFG			99			//���ܺ�ɫ��ⱨ������

#define RV_DEV_NETCFG_RHEX			100			//��ȡ�������(��98�豸remotehost����64�ֽ�)
#define	RV_DEV_RECCTL_CFG			101			//¼����Ʋ���(ʹ��TLVЭ��)
#define RV_DEV_COMMCFG_EX			102			//��ȡ���ڲ���(����16ͨ��)
#define RV_DEV_CHANNEL_NAME			103			//��ȡͨ����(ʹ��TLVЭ��)
#define RV_DEV_AUDIO_T				104			//��Ƶ����(ʹ��TLVЭ��)
#define RV_DEV_DIGICHAN_TOUR		105			//����ͨ����ѵ����(ʹ��TLVЭ��)

#define RV_DEV_USER_END_CFG			1000

	/////////////////////Զ�����ýṹ����س���///////////////////////
#define RV_MAX_MAIL_ADDR_LEN		128	//�ʼ���(��)�˵�ַ��󳤶�
#define RV_MAX_MAIL_SUBJECT_LEN		64	//�ʼ�������󳤶�
#define RV_MAX_IPADDR_LEN			16	//IP��ַ�ַ�������
#define RV_MACADDR_LEN				40	//MAC��ַ�ַ�������
#define RV_MAX_URL_LEN				128	//URL�ַ�������
#define RV_MAX_DEV_ID_LEN			48	//���������󳤶�
#define	RV_MAX_HOST_NAMELEN			64  //32	//�������ַ������ȣ�
#define RV_MAX_HOST_PSWLEN			32	//����
#define RV_MAX_HOST_PSWLEN_EX		64	//����
#define RV_MAX_NAME_LEN				16	//ͨ�������ַ�������
#define RV_MAX_NAME_LEN_EX			32	//�����û����ַ�������	luhj-0015	
#define RV_MAX_ETHERNET_NUM			2	//��̫����������
#define	RV_DEV_SERIALNO_LEN			48	//���к��ַ�������
#define RV_DEV_TYPE_LEN				32	//�豸�����ַ�������
#define RV_N_WEEKS					7	//һ�ܵ�����	
#define RV_N_TSECT					6	//ͨ��ʱ��θ���
#define RV_N_REC_TSECT				6	//¼��ʱ��θ���
#define RV_N_COL_TSECT				2	//��ɫʱ��θ���	
#define RV_CHAN_NAME_LEN			32	//ͨ��������,dvr DSP�������ƣ����32�ֽ�		
#define RV_N_ENCODE_AUX				3	//��չ��������	
#define RV_N_TALK					1	//���Խ�ͨ������
#define RV_N_COVERS					1	//�ڵ��������	
#define RV_N_CHANNEL				16	//���ͨ������	
#define RV_N_ALARM_TSECT			2	//������ʾʱ��θ���
#define RV_MAX_ALARMOUT_NUM			16	//��������ڸ�������
#define RV_MAX_VIDEO_IN_NUM			16	//��Ƶ����ڸ�������
#define RV_MAX_ALARM_IN_NUM			16	//��������ڸ�������
#define RV_MAX_DISK_NUM				16	//Ӳ�̸������ޣ��ݶ�Ϊ16
#define RV_MAX_DECODER_NUM			16	//��������485����������	
#define RV_MAX_DECODER_NUM_EX		32	//��������������	
#define RV_MAX_232FUNCS				10	//232���ڹ��ܸ�������
#define RV_MAX_232_NUM				2	//232���ڸ�������
#define RV_MAX_DECPRO_LIST_SIZE		100	//������Э���б��������
#define RV_FTP_MAXDIRLEN			240	//FTP�ļ�Ŀ¼��󳤶�
#define RV_MATRIX_MAXOUT			16	//���������������
#define RV_TOUR_GROUP_NUM			6	//���������������
#define RV_MAX_DDNS_NUM				10	//�豸֧�ֵ�ddns������������
#define RV_MAX_SERVER_TYPE_LEN		32	//ddns���������� ����ַ�������
#define RV_MAX_DOMAIN_NAME_LEN		256	//ddns���� ����ַ�������
#define RV_MAX_DDNS_ALIAS_LEN		32	//ddns���������� ����ַ�������
#define RV_MOTION_ROW				32	//��̬������������
#define RV_MOTION_COL				32	//��̬������������
#define	RV_FTP_USERNAME_LEN			64  //FTP���ã��û�����󳤶�
#define	RV_FTP_PASSWORD_LEN			64  //FTP���ã�������󳤶�
#define	RV_TIME_SECTION				2	//FTP���ã�ÿ��ʱ��θ���
#define RV_FTP_MAX_PATH				240	//FTP���ã��ļ�·������󳤶�
#define RV_INTERVIDEO_UCOM_CHANID	32	//ƽ̨�������ã�U��ͨͨ��ID
#define RV_INTERVIDEO_UCOM_DEVID	32	//ƽ̨�������ã�U��ͨ�豸ID
#define RV_INTERVIDEO_UCOM_REGPSW	16	//ƽ̨�������ã�U��ͨע������
#define RV_INTERVIDEO_UCOM_USERNAME	32	//ƽ̨�������ã�U��ͨ�û���
#define RV_INTERVIDEO_UCOM_USERPSW	32	//ƽ̨�������ã�U��ͨ����
#define RV_INTERVIDEO_NSS_IP		32	//ƽ̨�������ã�������άIP
#define RV_INTERVIDEO_NSS_SERIAL	32	//ƽ̨�������ã�������άserial
#define RV_INTERVIDEO_NSS_USER		32	//ƽ̨�������ã�������άuser
#define RV_INTERVIDEO_NSS_PWD		50	//ƽ̨�������ã�������άpassword

#define RV_MAX_VIDEO_COVER_NUM		16	//�ڵ�����������
#define RV_MAX_WATERMAKE_DATA		4096	//ˮӡͼƬ������󳤶�
#define RV_MAX_WATERMAKE_LETTER		128	//ˮӡ������󳤶�
#define RV_MAX_WLANDEVICE_NUM		10	//����������������豸����
#define RV_MAX_ALARM_NAME			64	//��ַ����
#define RV_MAX_REGISTER_SERVER_NUM	10	//����ע�����������
#define RV_SNIFFER_FRAMEID_NUM		6   //6��FRAME ID ѡ��
#define RV_SNIFFER_CONTENT_NUM		4   //ÿ��FRAME��Ӧ��4��ץ������
#define RV_MAX_PROTOCOL_NAME_LENGTH 20
#define RV_SNIFFER_GROUP_NUM		4   //4��ץ������
#define MAX_PATH_STOR              240  //Զ��Ŀ¼�ĳ���
#define MAX_HHCHANNELNAME_LEN		32	//����ͨ�����Ƴ���
	//2009-12-15 ���� �޸� start
#define RV_MAX_SAVIA_NUM			16	//savia��Ŀ���ֵ
	//2009-12-15 ���� �޸� end
	//2009-12-28 ���� �޸� start
#define RV_MAX_BLACK_IP_NUM			128	//��������Ŀ���ֵ
#define RV_MAX_WHITE_IP_NUM			128	//��������Ŀ���ֵ
	//2009-12-28 ���� �޸� end
	//2010-1-21 ���� �޸� start
#define RV_MAX_DECODER_CHAN_NUM			32	//������ͨ����Ŀ���ֵ
	//2010-1-21 ���� �޸� end


	//�ֱ����б�������ֱ�����������롢�����
#define	RV_CAPTURE_SIZE_D1			0x00000001
#define RV_CAPTURE_SIZE_HD1			0x00000002
#define RV_CAPTURE_SIZE_BCIF		0x00000004
#define RV_CAPTURE_SIZE_CIF			0x00000008
#define RV_CAPTURE_SIZE_QCIF		0x00000010	
#define RV_CAPTURE_SIZE_VGA			0x00000020	
#define RV_CAPTURE_SIZE_QVGA		0x00000040
#define RV_CAPTURE_SIZE_SVCD		0x00000080
#define RV_CAPTURE_SIZE_QQVGA		0x00000100
#define RV_CAPTURE_SIZE_SVGA		0x00000200
#define RV_CAPTURE_SIZE_XVGA		0x00000400
#define RV_CAPTURE_SIZE_WXGA		0x00000800
#define RV_CAPTURE_SIZE_SXGA		0x00001000
#define RV_CAPTURE_SIZE_WSXGA		0x00002000   
#define RV_CAPTURE_SIZE_UXGA		0x00004000
#define RV_CAPTURE_SIZE_WUXGA       0x00008000

	//��̨�����б�������ֱ�����������롢�����
	//lowMask
#define PTZ_DIRECTION				0x00000001				/*!< ���� */
#define PTZ_ZOOM					0x00000002	   			/*!< �䱶 */
#define PTZ_FOCUS					0x00000004				/*!< �۽� */
#define PTZ_IRIS					0x00000008				/*!< ��Ȧ */
#define PTZ_ALARM					0x00000010				/*!< �������� */
#define PTZ_LIGHT					0x00000020				/*!< �ƹ� */
#define PTZ_SETPRESET				0x00000040				/*!< ����Ԥ�õ� */
#define PTZ_CLEARPRESET				0x00000080				/*!< ���Ԥ�õ� */
#define PTZ_GOTOPRESET				0x00000100				/*!< ת��Ԥ�õ� */
#define PTZ_AUTOPANON				0x00000200				/*!< ˮƽ��ʼ */
#define PTZ_AUTOPANOFF				0x00000400				/*!< ˮƽ���� */
#define PTZ_SETLIMIT				0x00000800				/*!< ���ñ߽� */
#define PTZ_AUTOSCANON				0x00001000				/*!< �Զ�ɨ�迪ʼ */
#define PTZ_AUTOSCANOFF				0x00002000				/*!< �Զ�ɨ�迪ֹͣ */
#define PTZ_ADDTOUR					0x00004000				/*!< ����Ѳ���� */
#define PTZ_DELETETOUR				0x00008000				/*!< ɾ��Ѳ���� */
#define PTZ_STARTTOUR				0x00010000				/*!< ��ʼѲ�� */
#define PTZ_STOPTOUR				0x00020000				/*!< ����Ѳ�� */
#define PTZ_CLEARTOUR				0x00040000				/*!< ɾ��Ѳ�� */
#define PTZ_SETPATTERN				0x00080000				/*!< ����ģʽ */
#define PTZ_STARTPATTERN			0x00100000				/*!< ��ʼģʽ */
#define PTZ_STOPPATTERN				0x00200000				/*!< ֹͣģʽ */
#define PTZ_CLEARPATTERN			0x00400000				/*!< ���ģʽ */
#define PTZ_POSITION				0x00800000				/*!< ���ٶ�λ */
#define PTZ_AUX						0x01000000				/*!< �������� */
#define PTZ_MENU					0x02000000				/*!< ����˵� */
#define PTZ_EXIT					0x04000000				/*!< �˳�����˵� */
#define PTZ_ENTER					0x08000000				/*!< ȷ�� */
#define PTZ_ESC						0x10000000				/*!< ȡ�� */
#define PTZ_MENUUPDOWN				0x20000000				/*!< �˵����²��� */
#define PTZ_MENULEFTRIGHT			0x40000000				/*!< �˵����Ҳ��� */
#define PTZ_OPT_NUM					0x80000000				//*< �����ĸ��� */

	//hiMask
#define PTZ_DEV						0x00000001				/*!< ��̨���� */
#define PTZ_MATRIX					0x00000002				/*!< ������� */

	//����ģʽ�б����������ģʽ��������롢�����
#define RV_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define RV_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define RV_CAPTURE_COMP_MPEG2		0x00000004
#define RV_CAPTURE_COMP_MPEG1		0x00000008
#define RV_CAPTURE_COMP_H263		0x00000010
#define RV_CAPTURE_COMP_MJPG		0x00000020
#define RV_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define RV_CAPTURE_COMP_H264		0x00000080

	//���������б�
#define RV_CAPTURE_BRC_CBR			0
#define RV_CAPTURE_BRC_VBR			1
	//#define RV_CAPTURE_BRC_MBR			2

	//�������������������뱨������������������롢�����
#define RV_ALARM_UPLOAD		0x00000001
#define RV_ALARM_RECORD		0x00000002
#define RV_ALARM_PTZ		0x00000004
#define RV_ALARM_MAIL		0x00000008
#define RV_ALARM_TOUR		0x00000010
#define RV_ALARM_TIP		0x00000020
#define RV_ALARM_OUT		0x00000040
#define RV_ALARM_FTP_UL		0x00000080
#define RV_ALARM_BEEP		0x00000100
#define RV_ALARM_VOICE		0x00000200
#define RV_ALARM_SNAP		0x00000400

	//"�ָ�Ĭ������"���룬������ÿ��û����
#define RV_RESTORE_COMMON			0x00000001	//��ͨ����
#define RV_RESTORE_CODING			0x00000002	//��������
#define RV_RESTORE_VIDEO			0x00000004	//¼������
#define RV_RESTORE_COMM				0x00000008	//��������
#define RV_RESTORE_NETWORK			0x00000010	//��������
#define RV_RESTORE_ALARM			0x00000020	//��������
#define RV_RESTORE_VIDEODETECT		0x00000040	//��Ƶ���
#define RV_RESTORE_PTZ				0x00000080	//��̨����
#define RV_RESTORE_OUTPUTMODE		0x00000100	//���ģʽ
#define RV_RESTORE_CHANNELNAME		0x00000200	//ͨ������
#define RV_RESTORE_ALL				0x80000000	//ȫ������


	////////////////end ofԶ�����ýṹ����س���///////////////////////


	/************************************************************************
	** ö�ٶ���
	***********************************************************************/
	//�豸����
	enum NET_DEVICE_TYPE 
	{
		NET_PRODUCT_NONE = 0,
		NET_DVR_NONREALTIME_MACE, /*!< ��ʵʱMACE */
		NET_DVR_NONREALTIME, /*!< ��ʵʱ */
		NET_NVS_MPEG1, /*!< ������Ƶ������ */
		NET_DVR_MPEG1_2, /*!< MPEG1��·¼��� */
		NET_DVR_MPEG1_8, /*!< MPEG1��·¼��� */
		NET_DVR_MPEG4_8, /*!< MPEG4��·¼��� */
		NET_DVR_MPEG4_16, /*!< MPEG4ʮ��·¼��� */
		NET_DVR_MPEG4_SX2, /*!< LBϵ��¼��� */
		NET_DVR_MEPG4_ST2, /*!< GBϵ��¼��� */
		NET_DVR_MEPG4_SH2, /*!< HBϵ��¼��� */
		NET_DVR_MPEG4_GBE, /*!< GBEϵ��¼��� */
		NET_DVR_MPEG4_NVSII, /*!< II��������Ƶ������ */
		NET_DVR_STD_NEW, /*!< �±�׼����Э�� */
		NET_DVR_DDNS, /*DDNS������*/
		NET_DVR_ATM,  /* ATM�� */
		NET_NB_SERIAL, /* ������ʵʱNBϵ�л��� */
		NET_LN_SERIAL, /* LNϵ�в�Ʒ */
		NET_BAV_SERIAL, /* BAVϵ�в�Ʒ */
		NET_SDIP_SERIAL, /* SDIPϵ�в�Ʒ */
		NET_IPC_SERIAL, /* IPCϵ�в�Ʒ */
		NET_NVS_B,		/* NVS Bϵ�� */
		NET_NVS_C,		/* NVS Hϵ�� */
		NET_NVS_S,		/* NVS Sϵ�� */
		NET_NVS_E,		/* NVS Eϵ�� */
		NET_DVR_NEW_PROTOCOL /*��QueryDevState�в�ѯ�豸����,���ַ�����ʽ*/
	};

	//add by HY 2009-5-22 begin
#define DH_MAX_IPADDR_LEN			16			// IP��ַ�ַ�������
#define DH_MACADDR_LEN				40			// MAC��ַ�ַ�������
#define DH_DEV_TYPE_LEN				32			// �豸�����ַ�������
	// �����ļ����ͣ���CLIENT_ExportConfigFile�ӿ�ʹ��
	typedef enum __DH_CONFIG_FILE_TYPE
	{
		DH_CONFIGFILE_ALL = 0,						// ȫ�������ļ�
		DH_CONFIGFILE_LOCAL,						// ���������ļ�
		DH_CONFIGFILE_NETWORK,						// ���������ļ�
		DH_CONFIGFILE_USER,							// �û������ļ�
	} DH_CONFIG_FILE_TYPE;

	// ��ӦCLIENT_SearchDevices�ӿ�
	typedef struct 
	{
		char				szIP[DH_MAX_IPADDR_LEN];		// IP
		int					nPort;							// �˿�
		char				szSubmask[DH_MAX_IPADDR_LEN];	// ��������
		char				szGateway[DH_MAX_IPADDR_LEN];	// ����
		char				szMac[DH_MACADDR_LEN];			// MAC��ַ
		char				szDeviceType[DH_DEV_TYPE_LEN];	// �豸����
		BYTE				bReserved[32];					// �����ֽ�
	} DEVICE_NET_INFO;

	// ���õ���ʱ����ز���
	typedef struct  
	{
		int					nWaittime;				// �ȴ���ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��5000ms
		int					nConnectTime;			// ���ӳ�ʱʱ��(����Ϊ��λ)��Ϊ0Ĭ��1500ms
		int					nConnectTryNum;			// ���ӳ��Դ�����Ϊ0Ĭ��1��
		int					nSubConnectSpaceTime;	// ������֮��ĵȴ�ʱ��(����Ϊ��λ),Ϊ0Ĭ��10ms
		int					nGetDevInfoTime;		// ��ȡ�豸��Ϣ��ʱʱ�䣬Ϊ0Ĭ��500ms.
		int					nConnectBufSize;		// ÿ�����ӽ������ݻ����С(�ֽ�Ϊ��λ)��Ϊ0Ĭ��250*1024
		BYTE				bReserved[28];			// �����ֶ�
	} NET_PARAM;
	//add by HY 2009-5-22 end

	//ͨ����̨��������
	typedef enum _PTZ_ControlType
	{
		RV_PTZ_UP_CONTROL = 0,			//��
		RV_PTZ_DOWN_CONTROL,			//��
		RV_PTZ_LEFT_CONTROL,			//��
		RV_PTZ_RIGHT_CONTROL,			//��
		RV_PTZ_ZOOM_ADD_CONTROL,		//�䱶+
		RV_PTZ_ZOOM_DEC_CONTROL,		//�䱶-
		RV_PTZ_FOCUS_ADD_CONTROL,		//����+
		RV_PTZ_FOCUS_DEC_CONTROL,		//����-
		RV_PTZ_APERTURE_ADD_CONTROL,	//��Ȧ+
		RV_PTZ_APERTURE_DEC_CONTROL,   //��Ȧ-
		RV_PTZ_POINT_MOVE_CONTROL,     //ת��Ԥ�õ�
		RV_PTZ_POINT_SET_CONTROL,      //����
		RV_PTZ_POINT_DEL_CONTROL,      //ɾ��
		RV_PTZ_POINT_LOOP_CONTROL,     //���Ѳ��
		RV_PTZ_LAMP_CONTROL            //�ƹ���ˢ
	}RV_PTZ_ControlType;

	//��̨������չ����
	typedef enum _EXTPTZ_ControlType
	{
		RV_EXTPTZ_LEFTTOP = 0X20,		//����
		RV_EXTPTZ_RIGHTTOP ,			//����
		RV_EXTPTZ_LEFTDOWN ,			//����
		RV_EXTPTZ_RIGHTDOWN,			//����
		RV_EXTPTZ_ADDTOLOOP,			//����Ԥ�õ㵽Ѳ��	Ѳ����·	Ԥ�õ�ֵ	
		RV_EXTPTZ_DELFROMLOOP,			//ɾ��Ѳ����Ԥ�õ�	Ѳ����·	Ԥ�õ�ֵ	
		RV_EXTPTZ_CLOSELOOP,			//���Ѳ��	Ѳ����·		
		RV_EXTPTZ_STARTPANCRUISE,		//��ʼˮƽ��ת			
		RV_EXTPTZ_STOPPANCRUISE,		//ֹͣˮƽ��ת			
		RV_EXTPTZ_SETLEFTBORDER,		//������߽�			
		RV_EXTPTZ_SETRIGHTBORDER,		//�����ұ߽�			
		RV_EXTPTZ_STARTLINESCAN,		//��ʼ��ɨ			
		RV_EXTPTZ_CLOSELINESCAN,		//ֹͣ��ɨ			
		RV_EXTPTZ_SETMODESTART,		//����ģʽ��ʼ	ģʽ��·		
		RV_EXTPTZ_SETMODESTOP,			//����ģʽ����	ģʽ��·		
		RV_EXTPTZ_RUNMODE,				//����ģʽ	ģʽ��·		
		RV_EXTPTZ_STOPMODE,			//ֹͣģʽ	ģʽ��·		
		RV_EXTPTZ_DELETEMODE,			//���ģʽ	ģʽ��·		
		RV_EXTPTZ_REVERSECOMM,			//��ת����			
		RV_EXTPTZ_FASTGOTO,			//���ٶ�λ	ˮƽ����(8192)	��ֱ����(8192)	�䱶(4)
		RV_EXTPTZ_AUXIOPEN,			//x34	�������ؿ�	������		
		RV_EXTPTZ_AUXICLOSE,			//0x35	�������ع�	������
		RV_EXTPTZ_OPENMENU = 0X36,		//������˵�
		RV_EXTPTZ_CLOSEMENU ,			//�رղ˵�
		RV_EXTPTZ_MENUOK,				//�˵�ȷ��
		RV_EXTPTZ_MENUCANCEL,			//�˵�ȡ��
		RV_EXTPTZ_MENUUP,				//�˵���
		RV_EXTPTZ_MENUDOWN,			//�˵���
		RV_EXTPTZ_MENULEFT,			//�˵���
		RV_EXTPTZ_MENURIGHT,			//�˵���
		RV_EXTPTZ_ALARMHANDLE = 0x40,	//����������̨ parm1:��������ͨ�� parm2:������������1-Ԥ�õ�2-��ɨ3-Ѳ�� parm3:����ֵ����Ԥ�õ��
		RV_EXTPTZ_MATRIXSWITCH = 0x41,	//�����л� parm1:��������(��Ƶ�����) parm2:(��Ƶ�����) parm3:�����
		RV_EXTPTZ_LIGHTCONTROL,			//�ƹ������
		RV_EXTPTZ_UP_TELE = 0x70,		//�� + TELE��param1=�ٶȣ�1-8������ͬ
		RV_EXTPTZ_DOWN_TELE,			//�� + TELE
		RV_EXTPTZ_LEFT_TELE,			//�� + TELE
		RV_EXTPTZ_RIGHT_TELE,			//�� + TELE
		RV_EXTPTZ_LEFTUP_TELE,			//���� + TELE
		RV_EXTPTZ_LEFTDOWN_TELE,		//���� + TELE
		RV_EXTPTZ_TIGHTUP_TELE,			//���� + TELE
		RV_EXTPTZ_RIGHTDOWN_TELE,		//���� + TELE
		RV_EXTPTZ_UP_WIDE,				//�� + WIDE��param1=�ٶȣ�1-8������ͬ
		RV_EXTPTZ_DOWN_WIDE,			//�� + WIDE
		RV_EXTPTZ_LEFT_WIDE,			//�� + WIDE
		RV_EXTPTZ_RIGHT_WIDE,			//�� + WIDE
		RV_EXTPTZ_LEFTUP_WIDE,			//���� + WIDE
		RV_EXTPTZ_LEFTDOWN_WIDE,		//���� + WIDE
		RV_EXTPTZ_TIGHTUP_WIDE,			//���� + WIDE
		RV_EXTPTZ_RIGHTDOWN_WIDE,		//���� + WIDE
		RV_EXTPTZ_TOTAL,				//�������ֵ
		//add by HY 2009-8-14 begin
		RV_EXTPTZ_RESET,				//��λ
		//add by HY 2009-8-14 end
	}RV_EXTPTZ_ControlType;

	//IO��������
	typedef enum _IOTYPE
	{
		RV_ALARMINPUT = 1,				//��������
		RV_ALARMOUTPUT = 2,			//�������

		RV_DECODER_ALARMOUT = 3,	//�������������
		RV_WIRELESS_ALARMOUT =5,    //���߱������
		RV_ALARM_TRIGGER_MODE = 7,
	}RV_IOTYPE;

	//��ѯ��־��չ�ӿڲ������豸��־����
	typedef enum _RV_LOG_QUERY_TYPE
	{
		DHLOG_ALL = 0,		//������־
		DHLOG_SYSTEM,		//ϵͳ��־
		DHLOG_CONFIG,		//������־
		DHLOG_STORAGE,		//�洢���
		DHLOG_ALARM,		//������־
		DHLOG_RECORD,		//¼�����
		DHLOG_ACCOUNT,		//�ʺ����
		DHLOG_CLEAR,		//�����־
		DHLOG_PLAYBACK		//�ط����
	}RV_LOG_QUERY_TYPE;

	//���ص���־��Ϣ�ṹ�壭��־����
	typedef enum _RV_LOG_TYPE
	{
		//system logs
		RV_LOG_REBOOT = 0x0000,
		RV_LOG_SHUT,
		//config logs
		RV_LOG_CONFSAVE = 0x0100,
		RV_LOG_CONFLOAD,
		//fs logs
		RV_LOG_FSERROR = 0x0200,   //�ļ�ϵͳ����
		RV_LOG_HDD_WERR,           //Ӳ��д����
		RV_LOG_HDD_RERR,           //Ӳ�̶�����
		RV_LOG_HDD_TYPE,           //����Ӳ������
		RV_LOG_HDD_FORMAT,         //��ʽ��Ӳ��
		//alarm logs
		RV_LOG_ALM_IN = 0x0300,
		RV_LOG_ALM_END = 0x0302,
		RV_LOG_INFRAREDALM_IN = 0x03a0, //���߱�������
		RV_LOG_INFRAREDALM_END,       //���߱�������
		//record
		RV_LOG_MANUAL_RECORD = 0x0401,
		RV_LOG_CLOSED_RECORD,
		//user manager
		RV_LOG_LOGIN = 0x0500,
		RV_LOG_LOGOUT,
		RV_LOG_ADD_USER,
		RV_LOG_DELETE_USER,
		RV_LOG_MODIFY_USER,
		RV_LOG_ADD_GROUP,
		RV_LOG_DELETE_GROUP,
		RV_LOG_MODIFY_GROUP,
		//clear
		RV_LOG_CLEAR = 0x0600,
		RV_LOG_TYPE_NR = 7,
	}RV_LOG_TYPE;

	//add by HY 2009-7-14 begin
	typedef enum _RV_RESET_TYPE
	{	
		DEFAULT_CFG_GENERAL = 0,		
		DEFAULT_CFG_ENCODE,
		DEFAULT_CFG_RECORD,		
		DEFAULT_CFG_COMM,		
		DEFAULT_CFG_NET,		
		DEFAULT_CFG_ALARM = 5,		
		DEFAULT_CFG_DETECT,		
		DEFAULT_CFG_PTZ,		
		DEFAULT_CFG_AUT,		
		DEFAULT_CFG_CHANTITLE = 9,		
		DEFAULT_CFG_EXCEP,		
		DEFAULT_CFG_ALL = 31,		
		DEFAULT_CFG_END,		
	}_RV_RESET_TYPE;
	//add by HY 2009-7-14 end

	//�ӿ�CLIENT_QueryLogEx���ص���־��Ϣ�ṹ�壭��־����
	//������int nType = 1;����reserved = &nType.
	typedef enum _RV_NEWLOG_TYPE
	{
		//system logs
		RV_NEWLOG_REBOOT	 = 0x0000,		//ϵͳ����
		RV_NEWLOG_SHUT,						//ϵͳ�ػ�

		//config logs
		RV_NEWLOG_CONFSAVE = 0x0100,
		RV_NEWLOG_CONFLOAD,

		//fs logs
		RV_NEWLOG_FSERROR	 = 0x0200,		//�ļ�ϵͳ����
		RV_NEWLOG_HDD_WERR,					//Ӳ��д����
		RV_NEWLOG_HDD_RERR,					//Ӳ�̶�����
		RV_NEWLOG_HDD_TYPE,					//����Ӳ������
		RV_NEWLOG_HDD_FORMAT,				//��ʽ��Ӳ��
		RV_NEWLOG_HDD_NOSPACE,				//��ǰ�����̿ռ䲻��

		//alarm logs
		RV_NEWLOG_ALM_IN	 = 0x0300,
		RV_NEWLOG_NETALM_IN,
		RV_NEWLOG_ALM_END,
		RV_NEWLOG_LOSS_IN,
		RV_NEWLOG_LOSS_END,

		//record
		RV_NEWLOG_AUTOMATIC_RECORD = 0x0400,
		RV_NEWLOG_MANUAL_RECORD,
		RV_NEWLOG_CLOSED_RECORD,

		//user manager
		RV_NEWLOG_LOGIN    = 0x0500,
		RV_NEWLOG_LOGOUT,
		RV_NEWLOG_ADD_USER,
		RV_NEWLOG_DELETE_USER,
		RV_NEWLOG_MODIFY_USER,
		RV_NEWLOG_ADD_GROUP,
		RV_NEWLOG_DELETE_GROUP,
		RV_NEWLOG_MODIFY_GROUP,

		//clear
		RV_NEWLOG_CLEAR    = 0x0600,
		RV_NEWLOG_SEARCHLOG,				//��ѯ��־

		//record operation
		RV_NEWLOG_SEARCH	 = 0x0700,		//¼���ѯ
		RV_NEWLOG_DOWNLOAD,					//¼������
		RV_NEWLOG_PLAYBACK,					//¼��ط�
		RV_NEWLOG_BACKUP,					/*!< ����¼���ļ� */
		RV_NEWLOG_BACKUPERROR,				/*!< ����¼���ļ�ʧ�� */

		RV_NEWLOG_TYPE_NR = 8,		
	}RV_NEWLOG_TYPE;


	//ʵʱԤ����չ�ӿ����ӵĲ�����Ԥ������
	typedef enum _RealPlayType
	{
		RV_RType_Realplay = 0,	//ʵʱԤ��
		RV_RType_Multiplay,	//�໭��Ԥ��

		RV_RType_Realplay_0,	//ʵʱ����-����������ͬ��RV_RType_Realplay
		RV_RType_Realplay_1,	//ʵʱ����-������1
		RV_RType_Realplay_2,	//ʵʱ����-������2
		RV_RType_Realplay_3,	//ʵʱ����-������3

		RV_RType_Multiplay_1,	//�໭��Ԥ����1����
		RV_RType_Multiplay_4,	//�໭��Ԥ����4����
		RV_RType_Multiplay_8,	//�໭��Ԥ����8����
		RV_RType_Multiplay_9,	//�໭��Ԥ����9����
		RV_RType_Multiplay_16,	//�໭��Ԥ����16����

		RV_RType_Multiplay_6,	//�໭��Ԥ����6����
		RV_RType_Multiplay_12,	//�໭��Ԥ����12����
	} RV_RealPlayType;

	//�豸���ƽӿڲ������������Ͷ���
	typedef enum _CtrlType
	{
		RV_CTRL_REBOOT = 0,	//�����豸	
		RV_CTRL_SHUTDOWN,	//�ر��豸
		RV_CTRL_DISK,		//Ӳ�̹���
		//�������
		RV_KEYBOARD_POWER = 3,
		RV_KEYBOARD_ENTER,
		RV_KEYBOARD_ESC,
		RV_KEYBOARD_UP,
		RV_KEYBOARD_DOWN,
		RV_KEYBOARD_LEFT,
		RV_KEYBOARD_RIGHT,
		RV_KEYBOARD_BTN0,
		RV_KEYBOARD_BTN1,
		RV_KEYBOARD_BTN2,
		RV_KEYBOARD_BTN3,
		RV_KEYBOARD_BTN4,
		RV_KEYBOARD_BTN5,
		RV_KEYBOARD_BTN6,
		RV_KEYBOARD_BTN7,
		RV_KEYBOARD_BTN8,
		RV_KEYBOARD_BTN9,
		RV_KEYBOARD_BTN10,
		RV_KEYBOARD_BTN11,
		RV_KEYBOARD_BTN12,
		RV_KEYBOARD_BTN13,
		RV_KEYBOARD_BTN14,
		RV_KEYBOARD_BTN15,
		RV_KEYBOARD_BTN16,
		RV_KEYBOARD_SPLIT,
		RV_KEYBOARD_ONE,
		RV_KEYBOARD_NINE,
		RV_KEYBOARD_ADDR,
		RV_KEYBOARD_INFO,
		RV_KEYBOARD_REC,
		RV_KEYBOARD_FN1,
		RV_KEYBOARD_FN2,
		RV_KEYBOARD_PLAY,
		RV_KEYBOARD_STOP,
		RV_KEYBOARD_SLOW,
		RV_KEYBOARD_FAST,
		RV_KEYBOARD_PREW,
		RV_KEYBOARD_NEXT,
		RV_KEYBOARD_JMPDOWN,
		RV_KEYBOARD_JMPUP,
		//��������
		RV_TRIGGER_ALARM_IN = 100,
		RV_TRIGGER_ALARM_OUT,
		//�������
		RV_CTRL_MATRIX,
		//SD�����ƣ�ipc��Ʒ������ͬӲ�̿���
		RV_CTRL_SDCARD,
		//��¼������
		RV_BURNING_START,		//��ʼ��¼
		RV_BURNING_STOP,		//������¼

		RV_BURNING_ADDPWD,	//��������(��0Ϊ��β���ַ���,��󳤶�8λ)
		RV_BURNING_ADDHEAD,	//����Ƭͷ(��0Ϊ��β���ַ���,��󳤶�1024�ֽ�,֧�ַ���,�зָ���'\n')��
		RV_BURNING_ADDSIGN,	//���Ӵ�㵽��¼��Ϣ(������)
		RV_BURNING_ADDCURSTOMINFO,	//�Զ������(��0Ϊ��β���ַ���,��󳤶�1024�ֽ�,֧�ַ���,�зָ���'\n')

		//�ָ��豸��Ĭ������
		RV_CTRL_RESTOREDEFAULT,

		//�豸����DSPץͼ
		RV_CTRL_CAPTURE_START,		//�����豸ץͼ

		//�����־
		RV_CTRL_CLEARLOG,
		//���߱���
		RV_TRIGGER_ALARM_WIRELESS = 200,
	}CtrlType;

	//�������ͣ�Ŀǰʹ�ø�ö�ٵĽӿ�����̭���벻Ҫʹ��
	typedef enum _CFG_INDEX
	{
		CFG_GENERAL =  0,		// ��ͨ
		CFG_COMM   		,		// ����
		CFG_NET    		,		// ����
		CFG_RECORD 		,		// ¼��
		CFG_CAPTURE		,		// ͼ������
		CFG_PTZ    		,		// ��̨
		CFG_DETECT 		,		// ��̬���
		CFG_ALARM  		,		// ����
		CFG_DISPLAY		,		// ��ʾ
		CFG_RESERVED	,		// ������ʹ��������
		CFG_TITLE  		=10,	// ͨ������
		CFG_MAIL  		=11,	// �ʼ�����
		CFG_EXCAPTURE	=12,	// Ԥ��ͼ������
		CFG_PPPOE		=13,	// pppoe����
		CFG_DDNS		=14,	// DDNS����
		CFG_SNIFFER		=15,	// ������Ӳ�������
		CFG_DSPINFO		=16,	// ����������Ϣ
		CFG_COLOR		=126,  //��ɫ������Ϣ
		CFG_ALL,				// ����
	} CFG_INDEX;

	typedef enum _SNAP_TYPE
	{
		SNAP_TYP_TIMING = 0,
		SNAP_TYP_ALARM,
		SNAP_TYP_NUM,
	} SNAP_TYPE;

	//�ֱ���ö�٣���RV_DSP_ENCODECAPʹ��
	typedef enum _CAPTURE_SIZE
	{
		CAPTURE_SIZE_D1,				// <  720*576(PAL)  720*480(NTSC)
		CAPTURE_SIZE_HD1,				// <  352*576(PAL)  352*480(NTSC)
		CAPTURE_SIZE_BCIF,				// <  720*288(PAL)  720*240(NTSC)
		CAPTURE_SIZE_CIF,				// <  352*288(PAL)  352*240(NTSC)
		CAPTURE_SIZE_QCIF,				// <  176*144(PAL)  176*120(NTSC)
		CAPTURE_SIZE_VGA,				// <  640*480
		CAPTURE_SIZE_QVGA,				// <  320*240
		CAPTURE_SIZE_SVCD,				// <  480*480
		CAPTURE_SIZE_QQVGA,				// <  160*128
		//2010-6-29 luhj add
		CAPTURE_SIZE_720P	= 9,		//	1280*720	720P
		CAPTURE_SIZE_1080P	= 10,		//	1920*1080	1080P
		//add end
		CAPTURE_SIZE_SVGA,				// <  800*592
		CAPTURE_SIZE_XVGA,				// <  1024*768	VGA������룬2800��Ҫ
		CAPTURE_SIZE_WXGA,				// <  1280*800
		CAPTURE_SIZE_SXGA,				// <  1280*1024  
		CAPTURE_SIZE_WSXGA,				// <  1600*1024  
		CAPTURE_SIZE_UXGA,				// <  1600*1200
		CAPTURE_SIZE_WUXGA,				// <  1920*1200
		CAPTURE_SIZE_NR  
	} CAPTURE_SIZE;

	typedef enum __EM_USEDEV_MODE
	{
		RV_TALK_CLIENT_MODE,		//���ÿͻ��˷�ʽ���������Խ�
		RV_TALK_SERVER_MODE,		//���÷�������ʽ���������Խ�
		RV_TALK_ENCODE_TYPE,		//���������Խ������ʽ
		RV_ALARM_LISTEN_MODE        //���ñ������ķ�ʽ

	} EM_USEDEV_MODE;

	typedef enum __EM_UPGRADE_TYPE
	{
		RV_UPGRADE_BIOS_TYPE=1,		//BIOS����
		RV_UPGRADE_WEB_TYPE,		//WEB����
		RV_UPGRADE_BOOT_YPE,		//BOOT����
		RV_UPGRADE_CHARACTER_TYPE,	//���ֿ�
		RV_UPGRADE_LOGO_TYPE,		//LOGO
		RV_UPGRADE_EXE_TYPE,		//EXE ���粥������
	} EM_UPGRADE_TYPE;

	//��������
	typedef enum __LANGUAGE_TYPE
	{
		RV_LANGUAGE_ENGLISH,				//Ӣ��	
		RV_LANGUAGE_CHINESE_SIMPLIFIED,		//��������	
		RV_LANGUAGE_CHINESE_TRADITIONAL,	//��������	
		RV_LANGUAGE_ITALIAN,				//�������	
		RV_LANGUAGE_SPANISH,				//��������
		RV_LANGUAGE_JAPANESE,				//���İ�	
		RV_LANGUAGE_RUSSIAN,				//���İ�		
		RV_LANGUAGE_FRENCH,					//���İ�		
		RV_LANGUAGE_GERMAN, 				//���İ�		
		RV_LANGUAGE_PORTUGUESE,				//��������	
		RV_LANGUAGE_TURKEY,					//��������	
		RV_LANGUAGE_POLISH,					//������	
		RV_LANGUAGE_ROMANIAN,				//��������	
		RV_LANGUAGE_HUNGARIAN,              //��������	
		RV_LANGUAGE_FINNISH,				//������	
		RV_LANGUAGE_ESTONIAN,				//��ɳ������	
		RV_LANGUAGE_KOREAN,					//����	
		RV_LANGUAGE_FARSI,					//��˹�� 	
		RV_LANGUAGE_DANSK,					//������
		RV_LANGUAGE_CZECHISH,				//�ݿ���
		RV_LANGUAGE_BULGARIA,				//����������
	} RV_LANGUAGE_TYPE;

	//�����Խ���ʽ
	typedef enum __TALK_CODING_TYPE
	{
		RV_TALK_DEFAULT = 0,
		RV_TALK_PCM = 1,					//PCM
		RV_TALK_G711a,						//G711a
		RV_TALK_AMR,						//AMR
		RV_TALK_G711u,						//G711u
		RV_TALK_G726,						//G726
	}RV_TALK_CODING_TYPE;

	/************************************************************************
	** �ṹ�嶨��
	***********************************************************************/
	//add by HY 2009-11-16 begin
	typedef struct
	{	
		BOOL	bEnable;
		int		dwWebPort;
		int		dwTCPPort;
		DWORD	dwReserved;	
	}NET_UPNP;
	//add by HY 2009-11-16 begin

	//ʱ��
	typedef struct 
	{
		DWORD dwYear;		//��
		DWORD dwMonth;		//��
		DWORD dwDay;		//��
		DWORD dwHour;		//ʱ
		DWORD dwMinute;		//��
		DWORD dwSecond;		//��
	} NET_TIME,*LPNET_TIME;

	//�豸��Ϣ
	typedef struct {
		BYTE sSerialNumber[RV_SERIALNO_LEN];	//���к�
		BYTE byAlarmInPortNum;				//DVR�����������
		BYTE byAlarmOutPortNum;				//DVR�����������
		BYTE byDiskNum;						//DVR Ӳ�̸���
		BYTE byDVRType;						//DVR����, ��ö��DHDEV_DEVICE_TYPE
		BYTE byChanNum;						//DVR ͨ������
	} NET_DEVICEINFO, *LPNET_DEVICEINFO;

	//��ͨ������Ϣ
	typedef struct {
		int channelcount;
		int alarminputcount;
		unsigned char alarm[16];			//�ⲿ����
		unsigned char motiondection[16];	//��̬���
		unsigned char videolost[16];		//��Ƶ��ʧ
	} NET_CLIENT_STATE;

	//��ѯ�豸����״̬Ӳ����Ϣ
	typedef struct {
		DWORD		dwVolume;		//Ӳ�̵�����
		DWORD		dwFreeSpace;	//Ӳ�̵�ʣ��ռ�
		BYTE		dwStatus;		//Ӳ�̵�״̬,0-����,1-�,2-���ϵȣ���DWORD����ĸ�BYTE
		BYTE		bDiskNum;		//Ӳ�̺�
		BYTE		bSubareaNum;	//������
		BYTE		bSignal;		//��ʶ��0Ϊ���� 1ΪԶ��
	}NET_DEV_DISKSTATE,*LPNET_DEV_DISKSTATE;

	//add by HY 2009-9-24 begin
	//��ѯ�豸Ӳ������
	typedef struct {
		int Type[32];
	}NET_DEV_DISKTYPE;
	//add by HY 2009-9-24 end

	//¼���ļ���Ϣ
	typedef struct {
		unsigned int     ch;              //ͨ����
		char             filename[128];   //�ļ���
		unsigned int     size;            //�ļ�����
		NET_TIME         starttime;       //��ʼʱ��
		NET_TIME         endtime;         //����ʱ��
		unsigned int     driveno;         //���̺�
		unsigned int     startcluster;    //��ʼ�غ�
		int				 nRecordFileType; //¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��
	} NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;

	//¼���ļ���Ϣ
	typedef struct {
		unsigned int     ch;              //ͨ����
		char             filename[128];   //�ļ���
		unsigned int     size;            //�ļ�����
		NET_TIME         starttime;       //��ʼʱ��
		NET_TIME         endtime;         //����ʱ��
		unsigned int     driveno;         //���̺�
		unsigned int     startcluster;    //��ʼ�غ�
		int				 nRecordFileType; //¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��
		unsigned int	 partno;		  //������
		unsigned int	 hint;			  
	} NET_RECORDFILE_INFO_EX, *LPNET_RECORDFILE_INFO_EX;

	//����IO����
	typedef struct 
	{
		unsigned short index;	//�˿����
		unsigned short state;	//�˿�״̬
	}ALARM_CONTROL;


	typedef struct
	{
		unsigned short		index;					//???��D��o?
		unsigned short		mode;					//�䣤���顤?��?(01?��?1��??��2��??��);2?����??��?�����̨���?sdk??��???����3??-�����?����???��
		BYTE				bReserved[28];			
	} TRIGGER_MODE_CONTROL;

	typedef struct 
	{
		int	decoderNo;	//������������,��0��ʼ
		unsigned short  alarmChn; //���������,��0��ʼ
		unsigned short  alarmState; //�������״̬,1-�򿪡�0-�ر�
	}DECODER_ALARM_CONTROL;

	///////////////////�û��ʺŹ�����ؽṹ��/////////////////////////////////
	typedef struct _OPR_RIGHT
	{
		DWORD		dwID;
		char		name[RV_RIGHT_NAME_LENGTH];
		char		memo[RV_MEMO_LENGTH];
	}OPR_RIGHT;

	typedef struct _USER_INFO
	{
		DWORD		dwID;
		DWORD		dwGroupID;
		char		name[RV_USER_NAME_LENGTH];
		char		passWord[RV_USER_PSW_LENGTH];
		DWORD		dwRightNum;
		DWORD		rights[RV_MAX_RIGHT_NUM];
		char		memo[RV_MEMO_LENGTH];
		DWORD		dwReusable;		//���û��Ƿ������� 1-���ã�0-������

	}USER_INFO;

	typedef struct _USER_GROUP_INFO
	{
		DWORD		dwID;
		char		name[RV_USER_NAME_LENGTH];
		DWORD		dwRightNum;
		DWORD		rights[RV_MAX_RIGHT_NUM];
		char		memo[RV_MEMO_LENGTH];
	}USER_GROUP_INFO;

	//�û���Ϣ���ýṹ
	typedef struct _USER_MANAGE_INFO
	{
		DWORD				dwRightNum;
		OPR_RIGHT			rightList[RV_MAX_RIGHT_NUM];
		DWORD				dwGroupNum;
		USER_GROUP_INFO		groupList[RV_MAX_GROUP_NUM];
		DWORD				dwUserNum;
		USER_INFO			userList[RV_MAX_USER_NUM];
		DWORD				dwSpecial; //������Ϣ�� 1-֧���û����ã���0-��֧���û�����
	}USER_MANAGE_INFO;

	//////////////////////////////////////////////////////////////////////////////
	///////////////////�û��ʺŹ�����չ��ؽṹ��/////////////////////////////////
#define RV_USER_NAME_LENGTH_EX  16  //�û�������
#define RV_USER_PSW_LENGTH_EX   16  //����
	typedef struct _OPR_RIGHT_EX
	{
		DWORD  dwID;
		char  name[RV_RIGHT_NAME_LENGTH];
		char  memo[RV_MEMO_LENGTH];
	}OPR_RIGHT_EX;

	typedef struct _USER_INFO_EX
	{
		DWORD  dwID;
		DWORD  dwGroupID;
		char  name[RV_USER_NAME_LENGTH_EX];
		char  passWord[RV_USER_PSW_LENGTH_EX];
		DWORD  dwRightNum;
		DWORD  rights[RV_MAX_RIGHT_NUM];
		char  memo[RV_MEMO_LENGTH];
		DWORD   dwFouctionMask;//����

		/* ����,����
		* 0x00000001 - ֧���û�����
		*/

		BYTE  byReserve[32];

	}USER_INFO_EX;

	typedef struct _USER_GROUP_INFO_EX
	{
		DWORD  dwID;
		char  name[RV_USER_NAME_LENGTH_EX];
		DWORD  dwRightNum;
		DWORD  rights[RV_MAX_RIGHT_NUM];
		char  memo[RV_MEMO_LENGTH];
	}USER_GROUP_INFO_EX;

	//�û���Ϣ���ýṹ
	typedef struct _USER_MANAGE_INFO_EX
	{

		DWORD				dwRightNum;
		OPR_RIGHT_EX		rightList[RV_MAX_RIGHT_NUM];
		DWORD				dwGroupNum;
		USER_GROUP_INFO_EX  groupList[RV_MAX_GROUP_NUM];
		DWORD				dwUserNum;
		USER_INFO_EX		userList[RV_MAX_USER_NUM];
		DWORD				dwFouctionMask;//����    
		/* ����,����
		* 0x00000001 - ֧���û�����
		* 0x00000002 - �����޸���ҪУ��
		*/
		BYTE  byNameMaxLength;       //֧���û�������󳤶�
		BYTE  byPSWMaxLength;       //֧�ֵ�������󳤶�
		BYTE  byReserve[254];
	}USER_MANAGE_INFO_EX;
	///////////////////end of �û��ʺŹ�����չ��ؽṹ��////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	////////////////////��־�ṹ�����///////////////////////////
	//��־ʱ��ṹ
	typedef struct _DHDEVTIME
	{
		DWORD second		:6;					//	��	1-60		
		DWORD minute		:6;					//	��	1-60		
		DWORD hour			:5;					//	ʱ	1-24		
		DWORD day			:5;					//	��	1-31		
		DWORD month			:4;					//	��	1-12		
		DWORD year			:6;					//	��	2000-2063	
	}DHDEVTIME, *LPDHDEVTIME;

	typedef struct _RV_LOG_ITEM
	{
		DHDEVTIME time;					//����
		unsigned short type;			//����
		unsigned char reserved;			//����
		unsigned char data;				//����
		unsigned char context[8];		//����
	}RV_LOG_ITEM, *LPRV_LOG_ITEM;

	//�ӿ�CLIENT_QueryLogEx���ص���־��Ϣ�ṹ��
	//������int nType = 1;����reserved = &nType.
	typedef struct _RV_NEWLOG_ITEM
	{
		DHDEVTIME	time; 				//����
		WORD	type;					//����
		WORD	data;					//����
		char  	szOperator[8]; 			//�û���
		BYTE	context[16];		    //����	
	}RV_NEWLOG_ITEM, *LPRV_NEWLOG_ITEM;

	typedef struct _LOG_ITEM_RECORD
	{
		DHDEVTIME	time;		//ʱ��
		BYTE	channel;		//ͨ��
		BYTE	type;		//¼������
		BYTE	reserved[2];
	}LOG_ITEM_RECORD, *LPLOG_ITEM_RECORD;
	////////////////////end of ��־�ṹ�����///////////////////////////

	//�ص���Ƶ����֡��֡�����ṹ��
	typedef struct _tagVideoFrameParam
	{
		BYTE encode;		//��������
		BYTE frametype;		//I = 0, P = 1, B = 2...
		BYTE format;		//PAL - 0, NTSC - 1
		BYTE size;			//CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
		//SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15,
		DWORD fourcc;		//�����H264��������Ϊ0��MPEG4����������дFOURCC('X','V','I','D');
		DWORD reserved;		//����
		NET_TIME struTime;	//ʱ����Ϣ
	}tagVideoFrameParam;

	//�ص���Ƶ����֡��֡�����ṹ��
	typedef struct _tagCBPCMDataParam
	{
		BYTE channels;		// ������
		BYTE samples;			// ���� 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000
		BYTE depth;			// ������� ȡֵ8����16�ȡ�ֱ�ӱ�ʾ
		BYTE param1;			// 0 - ָʾ�޷��ţ�1-ָʾ�з���
		DWORD reserved;		// ����
	}tagCBPCMDataParam;

	//ͨ��������Ļ���ӵ����ݽṹ
	typedef struct _RV_CHANNEL_OSDSTRING
	{
		BOOL bEnable;	//ʹ��
		DWORD dwPosition[MAX_STRING_LINE_LEN];	//�����ַ���λ�á���1-9������ʾ����С����λ�ö�Ӧ
		//		7����	8��		9����
		//		4��		5��		6��
		//		1����	2��		3����
		char szStrings[MAX_STRING_LINE_LEN][MAX_PER_STRING_LEN]; //��������ַ���ÿ�����20���ֽ�
	}RV_CHANNEL_OSDSTRING;

	////////////////////�豸���ƽӿڵĿ��Ʋ�������//////////////////////
	typedef struct _DISKCTRL_PARAM
	{
		DWORD dwSize;		//size of this structure, for version control
		int nIndex;			//ΪӲ����Ϣ�ṹ��RV_HARDDISK_STATE�������stDisks�±꣬��0��ʼ
		int ctrlType;		//control type.
		// 0 - �������, 1 - ��Ϊ��д��, 2 - ��Ϊֻ����
		// 3 - ��Ϊ������, 4 - �ָ�����, 5 - ��Ϊ������
	}DISKCTRL_PARAM;

	typedef struct _ALARMCTRL_PARAM
	{
		DWORD dwSize;
		int nAlarmNo;		//����ͨ���ţ���0��ʼ
		int nAction;		//0-����������1-ֹͣ����
	}ALARMCTRL_PARAM;

	typedef struct _MATRIXCTRL_PARAM
	{
		DWORD dwSize;
		int nChannelNo;		//��Ƶ����ţ���0��ʼ
		int nMatrixNo;		//��������ţ���0��ʼ
	}MATRIXCTRL_PARAM;

	typedef struct _BURNING_PARM
	{
		int channelMask;	//ͨ�������룬ÿλ��ʾһ��ͨ��
		int	devMask;		//�豸���룬ÿλ��ʾһ̨�豸
	}BURNNG_PARM;


	////////////////////end of�豸���ƽӿڵĿ��Ʋ�������//////////////////////

	////////////////////��ѯ�豸״̬�Ĳ�������////////////////////////////////
	typedef struct _RV_HARDDISK_STATE
	{
		DWORD	dwDiskNum;		//����
		NET_DEV_DISKSTATE	stDisks[RV_MAX_DISKNUM]; //��Ӳ�̻������Ϣ
	}RV_HARDDISK_STATE,*LPRV_HARDDISK_STATE;

	typedef RV_HARDDISK_STATE  RV_SDCARD_STATE;	//SD�������ݽṹͬӲ����Ϣ

	typedef struct _NET_DEV_BURNING
	{
		DWORD dwDriverType;	//��¼���������� 0 -	DHFS, 1 - DISK, 2- CDRW
		DWORD dwBusType;	//�������͡�0- USB, 1-1394, 2-IDE
		DWORD dwTotalSpace;	//������(KB)
		DWORD dwRemainSpace;	//ʣ������(KB)
		BYTE  dwDriverName[RV_BURNING_DEV_NAMELEN]; //��¼����������
	}NET_DEV_BURNING,*LPNET_DEV_BURNING;

	typedef struct _RV_BURNING_DEVINFO
	{
		DWORD	dwDevNum;		//��¼�豸����
		NET_DEV_BURNING	stDevs[RV_MAX_BURNING_DEV_NUM]; //����¼�豸��Ϣ
	}RV_BURNING_DEVINFO, *LPRV_BURNING_DEVINFO;

	typedef struct _RV_BURNING_PROGRESS
	{
		BYTE	bBurning;		//�ɿ�¼����ʾ�Ƿ����ڿ�¼
		/*
		* �¿�¼����ֵ��
		*0;   ���Կ�¼
		*1;   �ǹ����豸,�豸���Ͳ���ȷ
		*2;   û����Ч���豸,��ʣ��ռ�Ϊ0
		*3;   �����������ڿ�¼
		*4;   �豸Ϊ�ǿ���״̬,���ڱ��ݡ���¼��ط���
		*/
		BYTE	bRomType;		//������Ƭ����(�¿�¼���������ֵ)(0:RV�ļ�ϵͳ��1���ƶ�Ӳ�̻�u�̣�2������)
		BYTE	bOperateType;   //��������(�¿�¼���������ֵ)(0�����У�1�����ڱ����У�2�����ڿ�¼�У�3�����ڽ��й��̻ط�)
		BYTE	bType;			//���ݻ��¼�ù���״̬(�¿�¼���������ֵ)(0��ֹͣ����� ��1����ʼ��2������3����;4�����ڳ�ʼ��)	
		//**************************
		NET_TIME stTimeStart;	//��ʼʱ�䡡
		DWORD	dwTimeElapse;	//�ѿ�¼ʱ��(��)
		DWORD	dwTotalSpace;	//����������
		DWORD	dwRemainSpace;	//����ʣ������
		DWORD	dwBurned;		//�ѿ�¼����
		DWORD	dwStatus;		/*
								Ϊ�˼������豸�����������ģ��¿�¼��û��ʵ���ô�
								-1����ʾ�¿�¼���������Ϊ-1����ʾ�ɿ�¼��
								���������豸�Ŀ�¼״̬�����豸�õģ������Ϊ-1����ʾ�ɿ�¼����
								0-���ڳ�ʼ����
								1-���ڿ�¼�����ϸ�������Ч
								2-��¼����
								3-����ֹͣ
								*/
	}RV_BURNING_PROGRESS, *LPRV_BURNING_PROGRESS;

	//�豸֧�����Խṹ��
	typedef struct _RV_LANGUAGE_DEVINFO
	{
		DWORD	dwLanguageNum;		    //֧�����Ը���
		BYTE    byLanguageType[252];    //ö��ֵ,���RV_LANGUAGE_TYPE
	}RV_DEV_LANGUAGE_INFO, *LPRV_DEV_LANGUAGE_INFO;


	typedef struct  
	{
		RV_TALK_CODING_TYPE		encodeType;		//��������
		int						nAudioBit;		//��ʵ�ʵ�ֵ��ʾ����8λ ����ֵΪ8
		DWORD					dwSampleRate;	//�����ʣ���16k ����ֵΪ16000
		char					reserved[64];
	}DHDEV_TALKDECODE_INFO;

	//�豸֧�ֵ������Խ���ʽ
	typedef struct 
	{
		int						nSupportNum;	//����
		DHDEV_TALKDECODE_INFO	type[64];		//�����ʽ
		char					reserved[64];
	}DHDEV_TALKFORMAT_LIST;

	////////////////////end of ��ѯ�豸״̬�Ĳ�������////////////////////////////////


	//add by HY 2009-11-2 begin
	//DDNS ����
	typedef struct 
	{
		BOOL	enable;
		int		DDNSKey;
		char	ServerName[64];
		int		ip;
		int		Port;
		char	UserName[64];
		char	Password[64];
		BOOL	Anonymity;
	}DDNS;

	typedef struct
	{
		DDNS Ddns[2];
	}NET_DEV_DDNS;

	typedef struct
	{
		int	 Count;
		DDNS Ddns[MAX_DDNS_COUNT];
	}NET_DEV_DDNS_EX;
	//add by HY 2009-11-2 end

	//GPS��Ϣ�ṹ��
	typedef struct _GPS_Info
	{
		NET_TIME revTime;        //��λʱ��
		char DvrSerial[50];      //�豸���к�
		double longitude;        //����
		double latidude;         //γ��
		double height;           //�߶ȣ��ף�
		double angle;            //����ǣ���������Ϊԭ�㣬˳ʱ��Ϊ����
		double speed;            //�ٶȣ�����/Сʱ��
		WORD starCount;          //��λ����
		BOOL antennaState;       //����״̬(true �ã�false ��)
		BOOL orientationState;    //��λ״̬��true ��λ��false ����λ��
	}GPS_Info,*LPGPS_Info;

	//ץͼ�����ṹ��
	typedef struct _snap_param
	{
		UINT Channel;				//ץͼ��ͨ��
		UINT Quality;				//����1~6, �˲���ֻ��Գ���DVR�豸��Ч
		UINT ImageSize;				//�����С 0:QCIF,1:CIF,2:D1, �˲���ֻ��Գ���DVR�豸��Ч
		UINT mode;					//ץͼģʽ 0����ʾ����һ֡; 1����ʾ��ʱ��������; 2����ʾ��������,����DVR�豸��Ч��
		UINT InterSnap;				//ʱ�䵥λ�� ��mode=1��ʾ��ʱ��������ʱ����ʱ����Ч������ֻ�г���DVR��Ч��
		UINT CmdSerial;				//�������к�
		UINT Reserved[4];
	}SNAP_PARAMS,*LPSNAP_PARAMS;

	//���紥���豸ץͼ�ṹ��
	typedef struct __NET_SNAP_COMMANDINFO 
	{
		char			szCardInfo[16];		//������Ϣ
		char			reserved[64];		//����
	} NET_SNAP_COMMANDINFO, LPNET_SNAP_COMMANDINFO;

	//Э����Ϣ
	typedef struct 
	{
		char            protocolname[12]; //Э����
		unsigned int	baudbase;	      //������
		unsigned char	databits; 	      //����λ
		unsigned char	stopbits;	      //ֹͣλ
		unsigned char	parity;		      //У��λ
		unsigned char   reserve;
	} PROTOCOL_INFO, *LPPROTOCOL_INFO;

	//��Ƶ��ʽ��Ϣ
	typedef struct {
		BYTE	byFormatTag;				//�������ͣ���0-PCM
		WORD	nChannels;				//������
		WORD	wBitsPerSample;			//�������			
		DWORD	nSamplesPerSec;			//������
	} RV_AUDIO_FORMAT, *LPRV_AUDIO_FORMAT;

	//��ѯ�豸����״̬ͨ����Ϣ:��ؽӿ�����̭���벻Ҫʹ��
	typedef struct {
		BYTE byRecordStatic;		//ͨ���Ƿ���¼��,0-��¼��,1-�ֶ�¼��2-�Զ�¼��
		BYTE bySignalStatic;		//���ӵ��ź�״̬,0-����,1-�źŶ�ʧ
		BYTE byHardwareStatic;		//ͨ��Ӳ��״̬,0-����,1-�쳣,����DSP����
		char reserve;
		DWORD dwBitRate;			//ʵ������
		DWORD dwLinkNum;			//�ͻ������ӵĸ���
		DWORD dwClientIP[RV_MAX_LINK];	//�ͻ��˵�IP��ַ
	}NET_DEV_CHANNELSTATE,*LPNET_DEV_CHANNELSTATE;

	//��ѯ�豸����״̬:��ؽӿ�����̭���벻Ҫʹ��
	typedef struct{
		DWORD dwDeviceStatic; 	//�豸��״̬,0x00 ����,0x01 CPUռ�ù���,0x02 Ӳ������
		NET_DEV_DISKSTATE  stHardDiskStatic[RV_MAX_DISKNUM]; 
		NET_DEV_CHANNELSTATE stChanStatic[RV_MAX_CHANNUM];//ͨ����״̬
		BYTE  byAlarmInStatic[RV_MAX_ALARMIN]; //�����˿ڵ�״̬,0-û�б���,1-�б���
		BYTE  byAlarmOutStatic[RV_MAX_ALARMOUT]; //��������˿ڵ�״̬,0-û�����,1-�б������
		DWORD  dwLocalDisplay;//������ʾ״̬,0-����,1-������
	} NET_DEV_WORKSTATE,*LPNET_DEV_WORKSTATE;


	/************************************************************************
	** �����������ص�ԭ��
	***********************************************************************/
	typedef int (CALLBACK *fServiceCallBack)(LONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);

	/************************************************************************
	** �������Ͽ��ص�ԭ��
	***********************************************************************/
	typedef void (CALLBACK *fDisConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

	//	���������ɹ��ص�����
	typedef void (CALLBACK *fHaveReConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

	/************************************************************************
	** ʵʱԤ���ص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *fRealDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

	/************************************************************************
	** ԭʼ���ݻص�ԭ��
	***********************************************************************/
	typedef int(CALLBACK *fDataCallBack) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

	/************************************************************************
	** ��Ϣ���������ص�ԭ��
	***********************************************************************/
	typedef BOOL (CALLBACK *fMessCallBack)(LONG lCommand, LONG lLoginID, char *pBuf,
		DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

	/************************************************************************
	** ��Ļ���ӻص�ԭ��
	***********************************************************************/
	typedef void (CALLBACK *fDrawCallBack)(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);

	/************************************************************************
	** ʵʱԤ���ص�ԭ��-��չ
	***********************************************************************/
	typedef void(CALLBACK *fRealDataCallBackEx) (LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, DWORD dwUser);

	/************************************************************************
	** �ط�¼����Ȼص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *fDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

	/************************************************************************
	** ͨ��ʱ������¼����Ȼص�ԭ��
	���ڰ�ʱ������û��ʹ������ص�������ʹ�õ��ǻط�¼����Ȼص�ԭ��. //by linjianyan
	***********************************************************************/
	typedef void(CALLBACK *fTimeDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);

	/************************************************************************
	** ͨ��ʱ������¼����Ȼص�ԭ��
	���ڰ�ʱ������û��ʹ������ص�������ʹ�õ��ǻط�¼����Ȼص�ԭ��. //by linjianyan
	***********************************************************************/
	typedef void(CALLBACK *fTimeDownLoadPosCallBackNew) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO_EX recordfileinfo, DWORD dwUser);

	/************************************************************************
	** ��ѯ�豸��־���ݻص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *fLogDataCallBack) (LONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, DWORD dwUser);

	/************************************************************************
	** ͸�����ڻص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *fTransComCallBack) (LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser);

	/************************************************************************
	** �����豸����ص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *fUpgradeCallBack) (LONG lLoginID, LONG lUpgradechannel, int nTotalSize, int nSendSize, DWORD dwUser);

	/************************************************************************
	** �����Խ�����Ƶ���ݻص�ԭ��
	***********************************************************************/
	typedef void(CALLBACK *pfAudioDataCallBack) (LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

	/***********************************************************************
	** ץͼ�ص�ԭ��
	***********************************************************************/
	typedef void( CALLBACK *fSnapRev)(LONG lLoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, DWORD dwUser);

	/************************************************************************
	** SDK��ʼ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_Init(fDisConnect cbDisConnect, DWORD dwUser);

	/************************************************************************
	** SDK�˳�����
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_Cleanup();

	/************************************************************************
	** ���ö��������ɹ��ص����������ú�SDK�ڲ������Զ�����
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_SetAutoReconnect(fHaveReConnect cbAutoConnect, DWORD dwUser);

	/************************************************************************
	** ���غ���ִ��ʧ�ܴ���
	***********************************************************************/
	CLIENT_API DWORD CALL_METHOD CLIENT_GetLastError(void);

	/************************************************************************
	** �������ӷ�������ʱʱ��ͳ��Դ���
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);


	/************************************************************************
	** ��ȡSDK�İ汾��Ϣ
	***********************************************************************/
	CLIENT_API DWORD CALL_METHOD CLIENT_GetSDKVersion();


	/************************************************************************
	** ���豸ע��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

	//	nSpecCap = 0ΪTCP��ʽ�µĵ��룻nSpecCap = 2Ϊ����ע��ĵ��룻nSpecCap = 3Ϊ�鲥��ʽ�µĵ��룻nSpecCap = 4ΪUDP��ʽ�µĵ���
	CLIENT_API LONG CALL_METHOD CLIENT_LoginEx(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

	/************************************************************************
	** ���豸ע��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_Logout(LONG lLoginID);

	/************************************************************************
	** 
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage,DWORD dwUser);


	/************************************************************************
	** ���������Խ�ģʽ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetDeviceMode(LONG lLoginID, EM_USEDEV_MODE emType, void* pValue);


	/************************************************************************
	** ��ʼ֡���豸
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StartListen(LONG lLoginID);

	//��ӦLB�豸����汾
	CLIENT_API BOOL CALL_METHOD CLIENT_StartListenEx(LONG lLoginID);

	/************************************************************************
	** ֹͣ֡���豸
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopListen(LONG lLoginID);

	/************************************************************************
	** ��ʼ�����������������ƶ�DVR����
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_ListenServer(char* ip, WORD port, int nTimeout, fServiceCallBack cbListen, DWORD dwUserData);

	/************************************************************************
	** ֹͣ������������ֹͣ�����ƶ�DVR����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopListenServer(LONG lServerHandle);

	/************************************************************************
	** ��Ӧ�豸��ע������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

	/************************************************************************
	** ��������˿�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_StartService(WORD wPort, char *pIp = NULL, fServiceCallBack pfscb = NULL, 
		DWORD dwTimeOut = 0xffffffff, DWORD dwUserData = 0);

	/************************************************************************
	** ֹͣ����˿�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopService(LONG lHandle);

	/************************************************************************
	** ������Ļ���ӻص�
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, DWORD dwUser);


	/************************************************************************
	** ��ʼʵʱԤ��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_RealPlay(LONG lLoginID, int nChannelID, HWND hWnd);
	CLIENT_API LONG CALL_METHOD CLIENT_RealPlayEx(LONG lLoginID, int nChannelID, HWND hWnd, RV_RealPlayType rType = RV_RType_Realplay);

	CLIENT_API BOOL	CALL_METHOD CLIENT_AdjustFluency(LONG lRealHandle, int nLevel);

	/************************************************************************
	** ֹͣʵʱԤ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlay(LONG lRealHandle);

	/************************************************************************
	** ֹͣʵʱԤ��_��չ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlayEx(LONG lRealHandle);

	/************************************************************************
	** ��������Ϊ�ļ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SaveRealData(LONG lRealHandle, const char *pchFileName);


	/************************************************************************
	** ������������Ϊ�ļ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopSaveRealData(LONG lRealHandle);


	/************************************************************************
	** ����ͼ������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffect(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

	/************************************************************************
	** ����ͼ������()
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffectNew(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

	/************************************************************************
	** ��ȡͼ������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffect(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

	/************************************************************************
	** ��ȡͼ������()
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffectNew(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

	/************************************************************************
	** ������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_OpenSound(LONG hPlayHandle);

	/************************************************************************
	** ������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_OpenSoundNew(LONG hPlayHandle);

	/************************************************************************
	** �ر�����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_CloseSound();

	/************************************************************************
	** �ر�����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_CloseSoundNew();
	
	/************************************************************************
	** �������Խ�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_StartTalkEx(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser);

	/************************************************************************
	** ���������Խ�������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetAudioClientVolume(LONG lTalkHandle, WORD wVolume);

	/************************************************************************
	** �����������ݵ��豸
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

	/************************************************************************
	** ��ʼPC��¼��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_RecordStart();

	/************************************************************************
	** ����PC��¼��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_RecordStop();

	/************************************************************************
	** ������Ƶ����
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

	/************************************************************************
	** ֹͣ�����Խ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopTalkEx(LONG lTalkHandle);

	/************************************************************************
	** ����豸���㲥��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastAddDev(LONG lLoginID);

	/************************************************************************
	** �ӹ㲥����ɾ���豸
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastDelDev(LONG lLoginID);

	/************************************************************************
	** ��������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetVolume(LONG lPlayHandle, int nVolume);

	/************************************************************************
	** ��Ƶ����--��ʼ��(�ض���׼��ʽ->RV��ʽ)
	***********************************************************************/
	CLIENT_API int  CALL_METHOD CLIENT_InitAudioEncode(RV_AUDIO_FORMAT aft);

	/************************************************************************
	** ��Ƶ����--���ݱ���
	***********************************************************************/
	CLIENT_API int	CALL_METHOD	CLIENT_AudioEncode(LONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

	/************************************************************************
	** ��Ƶ����--����˳�
	***********************************************************************/
	CLIENT_API int	CALL_METHOD	CLIENT_ReleaseAudioEncode();

	/************************************************************************
	** ����ʵʱԤ���ص�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealData, DWORD dwUser);

	/************************************************************************
	** ����ʵʱԤ���ص�-��չ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBackEx(LONG lRealHandle, fRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);

	/************************************************************************
	** ץͼ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_CapturePicture(LONG hPlayHandle, const char *pchPicFileName);

	/************************************************************************
	** ץͼ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_CapturePictureNew(LONG hPlayHandle, const char *pchPicFileName);

	/************************************************************************
	** ��ѯĳ��ʱ�����Ƿ���¼��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);

	/************************************************************************
	** ͨ��ʱ���ѯ¼���ļ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

	/************************************************************************
	** �ط�¼���ļ�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** �ط�¼���ļ���չ_���������ݻص�����
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileEx(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

	/************************************************************************
	** �ط�¼���ļ�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileNew(LONG lLoginID, LPNET_RECORDFILE_INFO_EX lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** ��ͣ¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBack(LONG lPlayHandle, BOOL bPause);

	/************************************************************************
	** ��ͣ¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBackNew(LONG lPlayHandle, BOOL bPause);

	/************************************************************************
	** ��λ¼��ط���ʼ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

	/************************************************************************
	** ��λ¼��ط���ʼ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBackNew(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

	/************************************************************************
	** ֹͣ¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBack(LONG lPlayHandle);

	/************************************************************************
	** ֹͣ¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBackNew(LONG lPlayHandle);

	/************************************************************************
	** ����¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBack(LONG lPlayHandle, BOOL bStop);

	/************************************************************************
	** ����¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBackNew(LONG lPlayHandle, BOOL bStop);

	/************************************************************************
	** ���¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBack(LONG lPlayHandle);

	/************************************************************************
	** ���¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBackNew(LONG lPlayHandle);

	/************************************************************************
	** ����¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBack(LONG lPlayHandle);

	/************************************************************************
	** ����¼��ط�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBackNew(LONG lPlayHandle);

	/************************************************************************
	** �ָ������ط��ٶ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBack(LONG lPlayHandle);

	/************************************************************************
	** �ָ������ط��ٶ�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBackNew(LONG lPlayHandle);

	/************************************************************************
	** ���ûط�֡��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetFramePlayBack(LONG lPlayHandle, int framerate);

	/************************************************************************
	** ��ȡ�ط�֡��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

	/************************************************************************
	** ��ȡ�ط�OSDʱ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetPlayBackOsdTime(LONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

	/************************************************************************
	** ����¼���ļ�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFile(LONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** ����¼���ļ�
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFileNew(LONG lLoginID,LPNET_RECORDFILE_INFO_EX lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** ͨ��ʱ������¼��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** ͨ��ʱ������¼��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTimeNew(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBackNew cbTimeDownLoadPos, DWORD dwUserData);

	/************************************************************************
	** ֹͣ¼������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopDownload(LONG lFileHandle);

	/************************************************************************
	** ֹͣ¼������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopDownloadNew(LONG lFileHandle);

	/************************************************************************
	** ��ѯ¼�����ؽ���
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

	/************************************************************************
	** ��ѯ¼�����ؽ���
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPosNew(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

	/************************************************************************
	** �໭��ʵʱԤ��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_MultiPlay(LONG lLoginID, HWND hWnd);

	/************************************************************************
	** ֹͣ�໭��ʵʱԤ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopMultiPlay(LONG lMultiHandle);

	/************************************************************************
	** ��ѯϵͳ���������� ���ýӿ�����̭����ʹ��CLIENT_GetDevConfig
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int maxlen, int *nConfigbuflen, int waittime=1000);

	/************************************************************************
	** ����ϵͳ���������� ���ýӿ�����̭����ʹ��CLIENT_SetDevConfig
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetupConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int nConfigbuflen, int waittime=1000);

	/************************************************************************
	** ��ѯ�豸ͨ������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryChannelName(LONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime=1000);

	/************************************************************************
	** �����豸ͨ������
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

	/************************************************************************
	** �����豸ͨ���ַ�����
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelOsdString(LONG lLoginID, int nChannelNo, RV_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

	/************************************************************************
	** ͨ����̨����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

	/************************************************************************
	** RV��̨����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
		unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);

	/************************************************************************
	** RV��̨������չ�ӿڣ�֧����ά���ٶ�λ
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, 
		LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);

	/************************************************************************
	** �첽��ѯ�豸��־
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogCallback(LONG lLoginID, fLogDataCallBack cbLogData, DWORD dwUser);

	/************************************************************************
	** ͬ����ѯ�豸��־
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryLog(LONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, int waittime=3000);

	CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogEx(LONG lLoginID, RV_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime=3000);

	/************************************************************************
	** ����͸������ͨ��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_CreateTransComChannel(LONG lLoginID, int TransComType, 
		unsigned int baudrate, unsigned int databits,
		unsigned int stopbits, unsigned int parity,
		fTransComCallBack cbTransCom, DWORD dwUser);

	/************************************************************************
	** ͸�����ڷ�������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

	/************************************************************************
	** �ͷ�ͨ������ͨ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_DestroyTransComChannel(LONG lTransComChannel);

	/************************************************************************
	** �ýӿ�����̭���벻Ҫʹ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_Reset(LONG lLoginID, BOOL bReset);

	//add by HY 2009-5-22 begin
	// ���õ�½���绷��
	CLIENT_API void CALL_METHOD CLIENT_SetNetworkParam(NET_PARAM *pNetParam);

	// ���������ļ�
	CLIENT_API LONG CALL_METHOD CLIENT_ImportConfigFile(LONG lLoginID, char *szFileName, fDownLoadPosCallBack cbUploadPos, DWORD dwUserData, DWORD param=0);

	// ֹͣ���������ļ�
	CLIENT_API BOOL CALL_METHOD CLIENT_StopImportCfgFile(LONG lImportHandle);

	// ���������ļ�
	CLIENT_API LONG CALL_METHOD CLIENT_ExportConfigFile(LONG lLoginID, DH_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	// ֹͣ���������ļ�
	CLIENT_API BOOL CALL_METHOD CLIENT_StopExportCfgFile(LONG lExportHandle);

	// ������������IPC��NVS���豸
	CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime);
	//add by HY 2009-5-22 end

	//add by HY 2009-9-24 begin
	CLIENT_API BOOL CALL_METHOD CLIENT_GetDiskType(LONG lLoginID, NET_DEV_DISKTYPE* Type, DWORD dwSearchTime = 2000);
	//add by HY 2009-9-24 end

	/************************************************************************
	** ��ʼ�����豸����
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

	CLIENT_API LONG CALL_METHOD CLIENT_StartUpgradeEx(LONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);


	/************************************************************************
	** ��������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SendUpgrade(LONG lUpgradeID);

	/************************************************************************
	** ���������豸����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopUpgrade(LONG lUpgradeID);

	/************************************************************************
	** ���ͨ��¼��״̬
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime=1000);

	/************************************************************************
	** ����ͨ��¼��״̬
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);

	/************************************************************************
	** ��ѯ�豸��ǰʱ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime, int waittime=1000);

	/************************************************************************
	** �����豸��ǰʱ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetupDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime);

	/************************************************************************
	** ��ѯ����Э�� �� �ýӿ�����̭����ʹ��CLIENT_GetDevConfig
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryComProtocol(LONG lLoginID, int nProtocolType, char *pProtocolBuffer, int maxlen, int *nProtocollen, int waittime=1000);

	/************************************************************************
	** ��ѯϵͳ��Ϣ �� �ýӿ�����̭����ʹ��CLIENT_GetDevConfig
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QuerySystemInfo(LONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime=1000);

	//add by HY 2009-8-12 begin
	/************************************************************************
	��ѯ�û�����״̬
	*************************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetUserLockState(LONG lLoginID, char* UserName, bool *bstate);

	/************************************************************************
	����û�����״̬
	*************************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_UnlockUserLockState(LONG lLoginID, char* UserName);
	//add by HY 2009-8-12 end

	/************************************************************************
	�����Ժ�����չ�ӿ�(��Щ�豸�û�����󳤶���16���ֽڵ�)
	*************************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoEx(LONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime=1000);

	/************************************************************************
	** ��ѯ�豸�û�(�Ͻӿڡ�֧��8λ�û������ȡ�)
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfo(LONG lLoginID, USER_MANAGE_INFO *info, int waittime=1000);

	/************************************************************************
	** �����豸�û�
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);
	/************************************************************************
	** �����豸�û����½ӿڣ�֧��8λ��16λ���û������볤�ȣ���
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

	/************************************************************************
	** ��ʼ�Խ� �� �ýӿ�����̭����ʹ��CLIENT_StartTalkEx
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StartTalk(LONG lRealHandle, BOOL bCustomSend=false);

	/************************************************************************
	** �����Խ� �� �ýӿ�����̭����ʹ��CLIENT_StopTalkEx
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_StopTalk(LONG lRealHandle);

	/************************************************************************
	** �����Զ���Խ����� �� �ýӿ�����̭����ʹ��CLIENT_TalkSendData
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SendTalkData_Custom(LONG lRealHandle, char *pBuffer, DWORD dwBufSize);

	/************************************************************************
	** ��ȡͨ������
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

	/************************************************************************
	** ��ѯIO״̬
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryIOControlState(LONG lLoginID, RV_IOTYPE emType, 
		void *pState, int maxlen, int *nIOCount, int waittime=1000);

	/************************************************************************
	** IO����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_IOControl(LONG lLoginID, RV_IOTYPE emType, void *pState, int maxlen);

	/************************************************************************
	** ��ѯ�豸����״̬ �ýӿ�����̭����ʹ��CLIENT_QueryDevState
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetDEVWorkState(LONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime=1000);

	/************************************************************************
	** ǿ��I֡
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_MakeKeyFrame(LONG lLoginID, int nChannelID, int nSubChannel=0);

	/************************************************************************
	** �����豸��������
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetMaxFlux(LONG lLoginID, WORD wFlux);

	/************************************************************************
	** ͨ���豸���ֻ����豸���к���DDNS��������ѯ�豸IP
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, 
		BYTE *sDVRName, WORD wDVRNameLen, 
		BYTE *sDVRSerialNumber, WORD wDVRSerialLen, 
		char* sGetIP);

	/************************************************************************
	** ͨ��ʱ��ط�¼��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTime(LONG lLoginID, int nChannelID, 
		LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

	/************************************************************************
	** ͨ��ʱ��ط�¼��
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeNew(LONG lLoginID, int nChannelID, 
		LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

	/************************************************************************
	** ͨ��ʱ��ط�¼����չ_���������ݻص�����
	***********************************************************************/
	CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeEx(LONG lLoginID, int nChannelID, 
		LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser,
		fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

	/************************************************************************
	** ��ʼ����¼���ļ�
	***********************************************************************/
	CLIENT_API LONG	CALL_METHOD CLIENT_FindFile(LONG lLoginID,
		int nChannelId,
		int nRecordFileType, 
		char* cardid, 
		LPNET_TIME time_start,
		LPNET_TIME time_end,
		BOOL bTime, 
		int waittime);

	/************************************************************************
	** ����¼���ļ�
	***********************************************************************/
	CLIENT_API int	CALL_METHOD CLIENT_FindNextFile(LONG lFindHandle,LPNET_RECORDFILE_INFO lpFindData);

	/************************************************************************
	** ����¼���ļ�����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_FindClose(LONG lFindHandle);

	/************************************************************************
	** ��ʼ����¼���ļ�
	***********************************************************************/
	CLIENT_API LONG	CALL_METHOD CLIENT_FindFileNew(LONG lLoginID,
		int nChannelId,
		int nRecordFileType, 
		char* cardid, 
		LPNET_TIME time_start,
		LPNET_TIME time_end,
		BOOL bTime, 
		int waittime);

	/************************************************************************
	** ����¼���ļ�
	***********************************************************************/
	CLIENT_API int	CALL_METHOD CLIENT_FindNextFileNew(LONG lFindHandle,LPNET_RECORDFILE_INFO_EX lpFindData);

	/************************************************************************
	** ����¼���ļ�����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_FindCloseNew(LONG lFindHandle);

	/************************************************************************
	** �����豸������ֵ TRUE �ɹ��� FALSE ʧ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_RebootDev(LONG lLoginID);

	/************************************************************************
	** �ָ��������ã�����ֵ TRUE �ɹ��� FALSE ʧ��
	***********************************************************************/
	//add by HY 2009-7-14 begin
	CLIENT_API BOOL CALL_METHOD CLIENT_ResetDeafault(LONG lLoginID, unsigned long type);
	//add by HY 2009-7-14 end

	/************************************************************************
	** �ر��豸������ֵ TRUE �ɹ��� FALSE ʧ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ShutDownDev(LONG lLoginID);

	/************************************************************************
	** �豸���ƣ�����ֵ TRUE �ɹ��� FALSE ʧ��
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_ControlDevice(LONG lLoginID, CtrlType type, void *param, int waittime = 1000);

	/************************************************************************
	** ������ѯ�豸״̬������������Ӳ�̡�¼��״̬�ȡ�
	***********************************************************************/
	//	�� nType  = RV_DEVSTATE_BURNING_PROGRESS ʱ,*pRetLen��ʾ��ѯ�豸��id��.��������ԭ����û����������ʹ�õ���ڲ�����
	CLIENT_API BOOL CALL_METHOD CLIENT_QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

	///////////////�����ǳ���dvr��صĹ��ܽӿ� /////////////////////////
	/************************************************************************
	** ����ץͼ�ص�����
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, DWORD dwUser);

	/************************************************************************
	** ץͼ����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SnapPicture(LONG lLoginID, SNAP_PARAMS par);

	/************************************************************************
	** GPS��Ϣ���Ļص�
	***********************************************************************/
	typedef void( CALLBACK *fGPSRev)(LONG lLoginID,           //�豸���
		GPS_Info  GpsInfo,       //GPS��Ϣ
		DWORD dwUserData);       //�û�����

	/************************************************************************
	** ����GPS���Ļص�����
	***********************************************************************/
	CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBack(fGPSRev OnGPSMessage, DWORD dwUser);

	/************************************************************************
	** GPS��Ϣ����
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPS (
		LONG lLoginID,        //�豸���
		BOOL bStart,		  //�Ƿ�����
		LONG KeepTime,        //���ĳ���ʱ�䣨��λ�룩
		LONG InterTime);      //����ʱ����GPS����Ƶ�ʣ���λ�룩  

	/////////////////////////end of ����dvr��صĹ��� ///////////////////////////////


	/////////////////////////δʵ��//////////////////////////
	/************************************************************************
	** ����ʵʱԤ�������С
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_SetPlayerBufNumber(LONG lRealHandle, DWORD dwBufNum);

	/************************************************************************
	** ͨ��ʱ�������ļ���CLIENT_DownloadByTime��ʵ�ָù���
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_GetFileByTime(LONG lLoginID, int nChannelID, 
		LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, char *sSavedFileName);

	/************************************************************************
	** ����طſ��ƣ���ϸ��Ϊ�����ƽӿ���
	***********************************************************************/
	CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControl(LONG lPlayHandle, 
		DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

	//////////////////////////end of δʵ��//////////////////////


	/************************************************************************
	** Զ�������豸�ӿ� �������ͼ�RV_DEV_DEVICECFG ����
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_GetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
	CLIENT_API BOOL  CALL_METHOD CLIENT_SetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);


	/************************************************************************
	** ƽ̨����ӿ�
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
	CLIENT_API BOOL  CALL_METHOD CLIENT_SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

	/************************************************************************
	**  ��ȡ��̨��Ϣ	
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_GetPtzOptAttr(LONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime=500);

	//chenfeng20090304 -s
	/************************************************************************
	**  ��ȡԶ�̻طŽ�����
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_GetPlayBackPlayerIndex(LONG lPlayHandle);

	/************************************************************************
	**  ��ȡԤ��������
	***********************************************************************/
	CLIENT_API BOOL  CALL_METHOD CLIENT_GetRealPlayerIndex(LONG lPlayHandle);

	//chenfeng20090304 -e
	/******************************************************************************
	** �����Ǹ��������ýṹ��
	*****************************************************************************/

	/************************************************************************
	*	ϵͳ��Ϣ
	************************************************************************/

	/*�汾��Ϣ:��16λ��ʾ���汾�ţ���16λ��ʾ�ΰ汾��
	*����ʱ���������֯�ǣ�yyyymmdd */
	typedef struct 
	{
		DWORD	dwSoftwareVersion;
		DWORD	dwSoftwareBuildDate;
		DWORD	dwDspSoftwareVersion;
		DWORD	dwDspSoftwareBuildDate;
		DWORD	dwPanelVersion;
		DWORD	dwPanelSoftwareBuildDate;
		DWORD	dwHardwareVersion;
		DWORD	dwHardwareDate;
		DWORD	dwWebVersion;
		DWORD	dwWebBuildDate;
	} RV_VERSION_INFO, *LPRV_VERSION_INFO;

	/* DSP��������(CLIENT_GetDevConfig���)���Ժ�����CLIENT_QueryDevState�ӿ� */
	typedef struct 
	{
		DWORD	dwVideoStandardMask;	//��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ
		DWORD	dwImageSizeMask;		//�ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ�������
		DWORD	dwEncodeModeMask;		//����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ����	

		DWORD	dwStreamCap;			//��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
		//��һλ��ʾ֧��������
		//�ڶ�λ��ʾ֧�ָ�����1
		//����λ��ʾ֧�ָ�����2
		//����λ��ʾ֧��jpgץͼ
		DWORD	dwImageSizeMask_Assi[8];//��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣

		DWORD	dwMaxEncodePower;		//- DSP ֧�ֵ���߱������� 
		WORD	wMaxSupportChannel;		//- ÿ�� DSP ֧�����������Ƶͨ���� 
		WORD	wChannelMaxSetSync;		//- DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��
	} RV_DSP_ENCODECAP, *LPRV_DSP_ENCODECAP;

	/* �豸��Ϣ���ýṹ */
	typedef struct 
	{
		DWORD dwSize;
		/*�������豸��ֻ������*/
		RV_VERSION_INFO			stVersion;
		RV_DSP_ENCODECAP		stDspEncodeCap;		//DSP��������
		BYTE	szDevSerialNo[RV_DEV_SERIALNO_LEN];	//���к�
		BYTE	byDevType;							//�豸���ͣ���ö��DHDEV_DEVICE_TYPE
		BYTE	szDevType[RV_DEV_TYPE_LEN];			//�豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��
		BYTE	byVideoCaptureNum;					//��Ƶ������
		BYTE	byAudioCaptureNum;					//��Ƶ������
		BYTE	byTalkInChanNum;					//NSP
		BYTE	byTalkOutChanNum;					//NSP
		BYTE	byDecodeChanNum;					//NSP
		BYTE	byAlarmInNum;						//�����������
		BYTE	byAlarmOutNum;						//�����������
		BYTE	byNetIONum;							//�������
		BYTE	byUsbIONum;							//USB������
		BYTE	byIdeIONum;							//IDE����
		BYTE	byComIONum;							//��������
		BYTE	byLPTIONum;							//��������
		BYTE	byVgaIONum;							//NSP
		BYTE	byIdeControlNum;					//NSP
		BYTE	byIdeControlType;					//NSP
		BYTE	byCapability;						//NSP����չ����
		BYTE	byMatrixOutNum;						//��Ƶ�����������

		/*�������豸�Ŀ�д����*/
		BYTE	byOverWrite;						//Ӳ��������ʽ�����ǡ�ֹͣ��
		BYTE	byRecordLen;						//¼��������
		BYTE	byStartChanNo;						//NSP
		WORD	wDevNo;								//�豸��ţ�����ң��
		BYTE	byVideoStandard;					//��Ƶ��ʽ
		BYTE	byDateFormat;						//���ڸ�ʽ
		BYTE	byDateSprtr;						//���ڷָ��(0-"."�� 1-"-"�� 2-"/")
		BYTE	byTimeFmt;							//ʱ���ʽ (0-24Сʱ��1��12Сʱ)
		BYTE	byLanguage;						    //ö��ֵ���RV_LANGUAGE_TYPE
	} DHDEV_SYSTEM_ATTR_CFG, *LPDHDEV_SYSTEM_ATTR_CFG;

	/************************************************************************
	*	ͼ��ͨ��
	************************************************************************/

	/* ¼�����ͣ���ʱ����̬��⡢���� */
	typedef enum _REC_TYPE
	{
		RV_REC_TYPE_TIM = 0,
		RV_REC_TYPE_MTD,
		RV_REC_TYPE_ALM,
		RV_REC_TYPE_NUM,
	}REC_TYPE;

	/* ʱ��νṹ */															    
	typedef struct 
	{
		BOOL	bEnable;	//����ʾ¼��ʱ���ʱ����λ��ʾ����ʹ�ܣ��ӵ�λ����λ�ֱ��ʾ����¼�󡢱���¼����ͨ¼��
		int		iBeginHour;
		int		iBeginMin;
		int		iBeginSec;
		int		iEndHour;
		int		iEndMin;
		int		iEndSec;
	} RV_TSECT, *LPRV_TSECT;

	/* ����:���߾ఴ����8192�ı��� */
	typedef struct {
		long		left;
		long		top;
		long		right;
		long		bottom;
	} RV_RECT,*LPRV_RECT;

	/* OSD���Խṹ */
	typedef struct  tagENCODE_WIDGET
	{
		DWORD		rgbaFrontground;		/*!< �����ǰ��RGB����͸���� */
		DWORD		rgbaBackground;			/*!< ����ĺ�RGB����͸����*/
		RV_RECT		rcRect;					/*!< λ�� */
		BYTE		bShow;					/*!< �����ʾ */
		BYTE		byReserved[3];
	} RV_ENCODE_WIDGET, *LPRV_ENCODE_WIDGET;

	/* ͨ������Ƶ���� */
	typedef struct 
	{
		//��Ƶ����
		BYTE	byVideoEnable;				/* ��Ƶʹ��:1���򿪣�0���ر� */
		BYTE	byBitRateControl;			/* ��������,���ճ������� */
		BYTE	byFramesPerSec;				/* ֡�� */
		BYTE	byEncodeMode;				/* ����ģʽ,���ճ������� */
		BYTE	byImageSize;				/* �ֱ��ʲ�,���ճ������� */
		BYTE	byImageQlty;				/* ����1-6 */
		WORD	wLimitStream;				/* ����������, ��Χ��50~4*1024 (k) */

		//��Ƶ����
		BYTE	byAudioEnable;				/* ��Ƶʹ��:1���򿪣�0���ر� */
		BYTE	wFormatTag;					/* �������ͣ���PCM */
		WORD	nChannels;					/* ������ */
		WORD	wBitsPerSample;				/* ������� */		
		DWORD	nSamplesPerSec;				/* ������ */

		BYTE	bIFrameInterval;			/* I֡���֡��������������I֮֡���P֡������0-149*/
		char	reserved;
	} RV_VIDEOENC_OPT, *LPRV_VIDEOENC_OPT;

	/* ������ɫ���� */
	typedef struct 
	{
		RV_TSECT	stSect;
		BYTE		byBrightness;			/*! ����	0-100*/
		BYTE		byContrast;				/*! �Աȶ�	0-100*/
		BYTE		bySaturation;			/*!	���Ͷ�	0-100*/
		BYTE		byHue;					/*!	ɫ��	0-100*/
		BYTE		byGainEn;				/*! ����ʹ��	 */ 
		BYTE		byGain;					/*! ����	0-100*/
		BYTE		byReserved[2];
	} RV_COLOR_CFG, *LPRV_COLOR_CFG;

	/* ͼ��ͨ�����Խṹ�� */
	typedef struct 
	{
		DWORD				dwSize;
		char				szChannelName[RV_CHAN_NAME_LEN];
		RV_VIDEOENC_OPT		stMainVideoEncOpt[RV_REC_TYPE_NUM];
		RV_VIDEOENC_OPT		stAssiVideoEncOpt[RV_N_ENCODE_AUX];		
		RV_COLOR_CFG		stColorCfg[RV_N_COL_TSECT];
		RV_ENCODE_WIDGET	stTimeOSD;
		RV_ENCODE_WIDGET	stChannelOSD;
		RV_ENCODE_WIDGET	stBlindCover[RV_N_COVERS];
		BYTE				byBlindEnable;			/*! �����ڸǿ��ء�0x00��ʹ���ڸǣ�0x01���ڸ��豸����Ԥ����0x10���ڸ�¼�񣨼�����Ԥ������0x11���ڸ�	*/
		BYTE				byBlindMask;			/*! �����ڸ�����  ��һλ���豸����Ԥ�����ڶ�λ��¼��(������Ԥ��) */
		BYTE				byReserved[2];
	} DHDEV_CHANNEL_CFG, *LPDHDEV_CHANNEL_CFG;


	/************************************************************************
	*	�����ڵ�����
	************************************************************************/
	typedef struct __VIDEO_COVER_ATTR
	{
		RV_RECT				rcBlock;			// ���ǵ���������
		int					nColor;				// ���ǵ���ɫ
		BYTE				bBlockType;			// ���Ƿ�ʽ��0-�ڿ飬1-������
		BYTE				bEncode;			// ���뼶�ڵ�, 1����Ч, 0��������
		BYTE				bPriview;           // Ԥ���ڵ�, 1����Ч, 0������Ч
		char				reserved[29];		// ����
	}VIDEO_COVER_ATTR;

	typedef struct __DHDEV_VIDEOCOVER_CFG 
	{
		DWORD				dwSize;
		char				szChannelName[RV_CHAN_NAME_LEN];	// ֻ��
		BYTE				bTotalBlocks;		// ֧�ֵ��ڵ�����
		BYTE				bCoverCount;		// �����õ��ڵ�����
		VIDEO_COVER_ATTR	CoverBlock[RV_MAX_VIDEO_COVER_NUM];		// ���ǵ�����	
		char				reserved[30];		// ����
	}DHDEV_VIDEOCOVER_CFG;


	/************************************************************************
	*	Ԥ��ͼ�����
	************************************************************************/

	/* Ԥ��ͼ����� */
	typedef struct 
	{
		DWORD dwSize;
		RV_VIDEOENC_OPT	stPreView;
		RV_COLOR_CFG  stColorCfg[RV_N_COL_TSECT];
	}DHDEV_PREVIEW_CFG;

	/************************************************************************
	* �����Խ���Ƶ���Խṹ�壭δʵ�֣�����չ *
	************************************************************************/

	typedef struct 
	{
		//��Ƶ�������
		BYTE	byInFormatTag;					//�������ͣ���PCM
		BYTE	byInChannels;					//������
		WORD	wInBitsPerSample;				//�������					
		DWORD	dwInSamplesPerSec;				//������

		//��Ƶ�������
		BYTE	byOutFormatTag;					//�������ͣ���PCM
		BYTE	byOutChannels;					//������
		WORD	wOutBitsPerSample;				//�������				
		DWORD	dwOutSamplesPerSec;				//������
	} DHDEV_TALK_CFG, *LPDHDEV_TALK_CFG;

	/************************************************************************
	*	��ʱ¼��
	************************************************************************/

	typedef struct 
	{
		DWORD		dwSize;
		RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];
		BYTE		byPreRecordLen;					/*! Ԥ¼ʱ��,��λ��s,0��ʾ��Ԥ¼*/
		BYTE		byRedundancyEn;					/*! ¼�����࿪��*/
		BYTE		byReserved[2];
	} DHDEV_RECORD_CFG, *LPRV_RECORD_CFG;

	/************************************************************************
	*	��������
	************************************************************************/

	typedef struct 
	{
		int iType;
		int iValue;
	} RV_PTZ_LINK, LPRV_PTZ_LINK;

	typedef struct 
	{
		/******************************************************************************
		** ��Ϣ��������
		**
		** ���豸������Ϣ,Ʃ�����һ�����뱨��,������Ƶ��ʧʱ,��Ҫ����Ӧ�Ĵ���.
		** �˴�������δ���һ����Ϣ
		*****************************************************************************/

		/* ��Ϣ����ʽ,����ͬʱ���ִ���ʽ,����
		* 0x00000001 - ����:�ϴ����������
		* 0x00000002 - ¼��:����
		* 0x00000004 - ��̨����
		* 0x00000008 - �����ʼ�
		* 0x00000010 - �豸���ر�����Ѳ
		* 0x00000020 - �豸��ʾʹ��
		* 0x00000040 - �豸�������ʹ��
		* 0x00000080 - Ftp�ϴ�ʹ��
		* 0x00000100 - ����
		* 0x00000200 - ������ʾ
		* 0x00000400 - ץͼʹ��*/

		/*��ǰ������֧�ֵĴ���ʽ����λ�����ʾ*/
		DWORD		dwActionMask;

		/* ������������λ�����ʾ�����嶯������Ҫ�Ĳ����ڸ��Ե�����������*/
		DWORD		dwActionFlag;

		/* �������������ͨ��,�������������,Ϊ 1 ��ʾ���������  */ 
		BYTE		byRelAlarmOut[RV_MAX_ALARMOUT_NUM];
		DWORD		dwDuration;		/* ��������ʱ�� */

		/*����¼��*/
		BYTE		byRecordChannel[RV_MAX_VIDEO_IN_NUM];		/* ����������¼��ͨ��,Ϊ1��ʾ������ͨ�� */
		DWORD		dwRecLatch;		/* ¼�����ʱ�� */

		/*ץͼͨ��*/
		BYTE		bySnap[RV_MAX_VIDEO_IN_NUM];
		/*��Ѳͨ��*/
		BYTE		byTour[RV_MAX_VIDEO_IN_NUM];

		/*  ��̨����: */
		RV_PTZ_LINK	struPtzLink[RV_MAX_VIDEO_IN_NUM];
		DWORD		dwEventLatch;   /*!< ������ʼ��ʱʱ�䣬sΪ��λ ��Χ��0����15 Ĭ��ֵ��0*/
		/* �����������������ͨ��,�������������,Ϊ 1 ��ʾ���������  */ 
		BYTE		byRelWIAlarmOut[RV_MAX_ALARMOUT_NUM];
		BYTE		bMessageToNet;	//��Ϣ�ϴ�������ʹ��
		BYTE		byReserved[111];       
	} RV_MSG_HANDLE;

	/* �ⲿ���� */
	typedef struct
	{
		BYTE		byAlarmType;						/* ����������,0������,1������  */
		BYTE		byAlarmEn;							/*����ʹ��*/
		BYTE		byReserved[2];						
		RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE	struHandle;	/* ����ʽ  */
	} RV_ALARMIN_CFG,*LPDHDEV_ALARMIN_CFG; 

	/* ��̬��ⱨ�� */
	typedef struct 
	{
		BYTE			byMotionEn;							/* ��̬��ⱨ��ʹ��*/
		BYTE			byReserved;
		WORD			wSenseLevel;						/*������*/
		WORD			wMotionRow;							/* ��̬������������ */
		WORD			wMotionCol;							/* ��̬������������ */
		BYTE			byDetected[RV_MOTION_ROW][RV_MOTION_COL];	/*����������32*32������*/
		RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE	struHandle;	/*����ʽ*/
	}RV_MOTION_DETECT_CFG;

	/* ��Ƶ��ʧ���� */
	typedef struct
	{
		BYTE			byAlarmEn;							/*��Ƶ��ʧ����ʹ��*/
		BYTE			byReserved[3];
		RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE	struHandle;	/* ����ʽ  */
	} RV_VIDEO_LOST_CFG;

	/* ͼ���ڵ����� */
	typedef struct
	{
		BYTE			byBlindEnable;						/* ʹ�� */
		BYTE			byBlindLevel;						/* ������1-6 */
		BYTE			byReserved[2];
		RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE	struHandle;	/* ����ʽ  */
	} RV_BLIND_CFG;

	/* Ӳ����Ϣ(�ڲ�����) */
	typedef struct 
	{
		BYTE				byNoDiskEn;				/* ��Ӳ��ʱ���� */
		BYTE				byReserved_1[3];
		RV_TSECT			stNDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE		struNDHandle;				/* ����ʽ  */

		BYTE				byLowCapEn;				/* Ӳ�̵�����ʱ����*/
		BYTE				byLowerLimit;			/* ������ֵ 0-99*/
		BYTE				byReserved_2[2];
		RV_TSECT			stLCSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE		struLCHandle;			/* ����ʽ  */

		BYTE				byDiskErrEn;			/* Ӳ�̹��ϱ���*/
		BYTE				byReserved_3[3];
		RV_TSECT			stEDSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE		struEDHandle;	/* ����ʽ  */

	} RV_DISK_ALARM_CFG;

	typedef struct
	{
		BYTE				byEnable;
		BYTE				byReserved[3];
		RV_MSG_HANDLE		struHandle;
	} RV_NETBROKEN_ALARM_CFG;

	//2010-3-18 luhj-0002 ����IP��ͻ�����ṹ��
	typedef struct  
	{
		BYTE				byEnable;
		BYTE				byReserved[3];
		RV_MSG_HANDLE		struHandle;
	}RV_IPCONFLICT_ALARM_CFG;
	//luhj-0002 end

	///*��Ƶ����*/
	//typedef struct 
	//{
	//	BYTE		bySoundAlarmEn;			/*��Ƶ����ʹ��*/
	//	BYTE		byVol;					/*����������ֵ*/
	//	BYTE		byReserved[2];			/*�����ֽ�*/
	//	RV_TSECT	stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
	//	RV_MSG_HANDLE	struHandle;	/* ����ʽ  */
	//}RV_SOUND_ALARM_CFG;


	/* �������� */
	typedef struct
	{
		DWORD dwSize;

		RV_ALARMIN_CFG 		struLocalAlmIn[RV_MAX_ALARM_IN_NUM];
		RV_ALARMIN_CFG		struNetAlmIn[RV_MAX_ALARM_IN_NUM];
		RV_MOTION_DETECT_CFG struMotion[RV_MAX_VIDEO_IN_NUM];
		RV_VIDEO_LOST_CFG	struVideoLost[RV_MAX_VIDEO_IN_NUM];
		RV_BLIND_CFG		struBlind[RV_MAX_VIDEO_IN_NUM];
		RV_DISK_ALARM_CFG	struDiskAlarm;
		RV_NETBROKEN_ALARM_CFG	struNetBrokenAlarm;
		//	RV_SOUND_ALARM_CFG	struSoundAlarm[RV_MAX_VIDEO_IN_NUM];
		//���ܻ����豸�쳣
	} DHDEV_ALARM_SCHEDULE;
	
	//2010-3-18 luhj-008
	typedef struct  
	{
		DWORD dwSize;
		RV_IPCONFLICT_ALARM_CFG	struIPConflict;
	} DHDEV_ALARM_IPCONFLICT;
	//luhj-0008 end

	//2009-12-14 ���� �޸� start
	/* ����DVR SAVIA���� */
	typedef struct
	{
		long			iIntelEnable;						/* ʹ�� */
		unsigned long	iIntelIPaddr;					/* ip��ַ */
		BYTE			byReserved[4];
		RV_TSECT		stSect[RV_N_WEEKS][RV_N_REC_TSECT];		//NSP
		RV_MSG_HANDLE	struHandle;	/* ����ʽ  */
	} RV_SAVIA_ALARM;
	typedef struct
	{
		long			iSaviaNum;							//Savia��Ŀ
		RV_SAVIA_ALARM	stSaviaAlarm[RV_MAX_SAVIA_NUM];		//Savia��������
	} RV_SAVIA_ALARM_SCHEDULE;
	//2009-12-14 ���� �޸� end

	//2009-12-28 ���� �޸� start
	/* �ڰ����� */
	typedef struct
	{
		DWORD			dwSize;								//�ṹ���С
		BOOL			bEnable;							//IPȨ������ʹ��
		LONG			iBlackCount;						//��������Ŀ
		DWORD			dwBlackIP[RV_MAX_BLACK_IP_NUM];		//������IP
		LONG			iWhiteCount;						//��������Ŀ
		DWORD			dwWhiteIP[RV_MAX_WHITE_IP_NUM];		//������IP
	} RV_BLACKWHITE_CFG;
	//2009-12-28 ���� �޸� end

	//2010-1-21 ���� �޸� start
	/* ���������� */
	typedef struct
	{
		int				channel;		//!���ؽ���ͨ����, ��0��ʼ
		unsigned short	device_type;	//!�豸����, 0-��Ǭ�豸 ,4-VS300����,3-RTSP
		unsigned short	device_port;	//����ǰ���豸�˿�
		unsigned int	device_ip;		//�����ֽ��򴢴�, ���ӵ�ǰ���豸ip
		unsigned int	device_channel;	//!Զ��ͨ����
		unsigned int	enable;			//!ʹ�ܿ���
		unsigned int	stream_type;	//!������������,0-������
		char			username[128];	//!����ǰ���û���
		char			password[128];	//!��������
		//
		unsigned char	ucAVEnable;       //0,ֻ����Ƶ 1��ֻ����Ƶ ��2 ������Ƶ ��������ʲô������
		unsigned char	ucRemotePtzPreset;//Զ��Ԥ�õ�
		unsigned char	ucRemotePtzPresetEnable;//�Ƿ�һ�����Ͼ�����Զ��Ԥ�õ�   
		unsigned char	ucRes;
		unsigned char	ucUrl[256];       //rtspģʽ�´�������Ч,��ʽ�磺rtsp://ip:port/user=xxx&password=xxx&id=xx&type=xx
		int				iDecodePolicy;    //������� 	(-2, ��ʵʱ -1 ʵʱ 0 Ĭ����� 1 ���� 2,	������ ) �Ժ������չ���Զ���������ʱʱ��
		unsigned char	ucRes1[124];
	}RV_CFG_DECODE_T;
	typedef struct
	{
		DWORD			dwSize;
		long			iDecoderNumber;
		RV_CFG_DECODE_T	struDecoder[RV_MAX_DECODER_CHAN_NUM];
	}RV_DECODER_CFG;
	//2010-1-21 ���� �޸� end

	/************************************************************************
	*	��������
	************************************************************************/
	/*                                                                      */
	/*��̫������*/
	typedef struct 
	{
		char	sDevIPAddr[RV_MAX_IPADDR_LEN];			/* DVR IP ��ַ  */ 
		char	sDevIPMask[RV_MAX_IPADDR_LEN];			/* DVR IP ��ַ����  */ 
		char	sGatewayIP[RV_MAX_IPADDR_LEN];			/* ���ص�ַ  */ 

		/* 10M/100M  ����Ӧ,���� 
		* 1-10MBase - T
		* 2-10MBase-T ȫ˫�� 
		* 3-100MBase - TX
		* 4-100M ȫ˫��
		* 5-10M/100M  ����Ӧ 
		*/
		//Ϊ����չ��DWORD����ĸ�
		BYTE	dwNetInterface;							/* NSP */
		BYTE	bTranMedia;								/* 0������ 1������ */
		BYTE	bValid;									/* ��λ��ʾ����һλ��1����Ч 0����Ч���ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�����λ��0����֧��DHCP 1��֧��DHCP */
		BYTE	bDefaultEth;							/* �Ƿ���ΪĬ�ϵ����� 1��Ĭ�� 0����Ĭ�� */
		char	byMACAddr[RV_MACADDR_LEN];				/* MAC��ַ��ֻ�� */
	} RV_ETHERNET; 

	/* Զ���������� */
	typedef struct 
	{
		BYTE	byEnable;								/* ����ʹ��  */
		BYTE	byReserved;
		WORD	wHostPort;								/* Զ������ �˿�  */
		char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* Զ������ IP ��ַ  */ 		
		char	sHostUser[RV_MAX_HOST_NAMELEN];			/* Զ������ �û��� */ 
		char	sHostPassword[RV_MAX_HOST_PSWLEN];		/* Զ������ ���� */ 
	}RV_REMOTE_HOST;

	/* Զ����������(����64�ֽ�) */
	typedef struct 
	{
		BYTE	byEnable;								/* ����ʹ��  */
		BYTE	byReserved;
		WORD	wHostPort;								/* Զ������ �˿�  */
		char	sHostIPAddr[RV_MAX_IPADDR_LEN];			/* Զ������ IP ��ַ  */ 		
		char	sHostUser[RV_MAX_HOST_NAMELEN];			/* Զ������ �û��� */ 
		char	sHostPassword[RV_MAX_HOST_PSWLEN_EX];		/* Զ������ ���� */ 
	}RV_REMOTE_HOST_EX;

	/* �ʼ����� */
	typedef struct 
	{
		char	sMailIPAddr[RV_MAX_IPADDR_LEN];			/*�ʼ�������IP��ַ*/
		WORD	wMailPort;								/*�ʼ��������˿�*/
		WORD	wReserved;								/* ���� */
		char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*���͵�ַ*/
		char	sUserName[RV_MAX_NAME_LEN];			/* �û��� */
		char	sUserPsw[RV_MAX_NAME_LEN];				/* �û����� */
		char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];			/*Ŀ�ĵ�ַ*/
		char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*���͵�ַ*/
		char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*������ַ*/
		char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*����*/
	}RV_MAIL_CFG;

	/*�������ýṹ��*/
	typedef struct
	{ 
		DWORD				dwSize; 

		char				sDevName[RV_MAX_NAME_LEN];				/* �豸������ */

		WORD				wTcpMaxConnectNum;						/* TCP���������(һ��ָ��Ƶ����������) */
		WORD				wTcpPort;								/* TCP֡���˿� */
		WORD				wUdpPort;								/* UDP�����˿� */
		WORD				wHttpPort;								/* HTTP�˿ں� */
		WORD				wHttpsPort;							/* HTTPS�˿ں� */
		WORD				wSslPort;								/* SSL�˿ں�*/
		RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];/* ��̫����  */ 

		RV_REMOTE_HOST		struAlarmHost;		/* ���������� */
		RV_REMOTE_HOST		struLogHost;		/* ��־������ */
		RV_REMOTE_HOST		struSmtpHost;		/* SMTP������ */
		RV_REMOTE_HOST		struMultiCast;		/* �ಥ�� */
		RV_REMOTE_HOST		struNfs;			/* NFS������ */
		RV_REMOTE_HOST		struPppoe;			/* PPPoE������ */
		char				sPppoeIP[RV_MAX_IPADDR_LEN]; /* PPPoEע�᷵�ص�IP */
		RV_REMOTE_HOST		struDdns;			/* DDNS������ */
		char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS������*/
		RV_REMOTE_HOST		struDns;			/* DNS������*/
		RV_MAIL_CFG			struMail;			/* �ʼ����� */
	} DHDEV_NET_CFG;

	/*�������ýṹ��*/
	typedef struct
	{ 
		DWORD				dwSize; 
		
		char				sDevName[RV_MAX_NAME_LEN];				/* �豸������ */
		
		WORD				wTcpMaxConnectNum;						/* TCP���������(һ��ָ��Ƶ����������) */
		WORD				wTcpPort;								/* TCP֡���˿� */
		WORD				wUdpPort;								/* UDP�����˿� */
		WORD				wHttpPort;								/* HTTP�˿ں� */
		WORD				wHttpsPort;							/* HTTPS�˿ں� */
		WORD				wSslPort;								/* SSL�˿ں�*/
		RV_ETHERNET			stEtherNet[RV_MAX_ETHERNET_NUM];/* ��̫����  */ 
		
		RV_REMOTE_HOST_EX		struAlarmHost;		/* ���������� */
		RV_REMOTE_HOST_EX		struLogHost;		/* ��־������ */
		RV_REMOTE_HOST_EX		struSmtpHost;		/* SMTP������ */
		RV_REMOTE_HOST_EX		struMultiCast;		/* �ಥ�� */
		RV_REMOTE_HOST_EX		struNfs;			/* NFS������ */
		RV_REMOTE_HOST_EX		struPppoe;			/* PPPoE������ */
		char				sPppoeIP[RV_MAX_IPADDR_LEN]; /* PPPoEע�᷵�ص�IP */
		RV_REMOTE_HOST_EX		struDdns;			/* DDNS������ */
		char				sDdnsHostName[RV_MAX_HOST_NAMELEN];		/* DDNS������*/
		RV_REMOTE_HOST_EX		struDns;			/* DNS������*/
		RV_MAIL_CFG			struMail;			/* �ʼ����� */
	} DHDEV_NET_CFG_RHEX;

	/************************************************************************
	*	��������
	************************************************************************/

	/* ���ڻ������� */
	typedef struct
	{
		BYTE	byDataBit;		//����λ 0-5,1-6,2-7,3-8
		BYTE	byStopBit;		//ֹͣλ 0-1λ, 1-1.5λ, 2-2λ 
		BYTE	byParity;		//У��λ 0-no, 1-odd, 2-even 
		BYTE	byBaudRate;	//{0-300,1-600,2-1200,3-2400,4-4800
		// 5-9600,6-19200,7-38400,8-57600,9-115200} 
	} RV_COMM_PROP;

	/* 485���������� */
	typedef struct
	{ 
		RV_COMM_PROP	struComm;

		BYTE			wProtocol;			/*!< Э������ ����Э����±꣬��̬�仯 */
		BYTE			byReserved;			/*!����  */	
		BYTE			wDecoderAddress;	/*��������ַ:0 - 255*/ 
		BYTE 			byMartixID;			/*�����*/
	} RV_485_CFG; 

	/* 232�������� */
	typedef struct
	{
		RV_COMM_PROP	struComm;
		BYTE			byFunction;/*!< ���ڹ��ܣ���Ӧ��������ȡ���Ĺ������б� */
		BYTE			byReserved[3];
	} RV_RS232_CFG;

	/* �������ýṹ�� */
	typedef struct
	{
		DWORD			dwSize;
		//������Э��
		DWORD			dwDecProListNum;				//Э�����
		char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN]; //Э�����б�
		RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM];		//����������ǰ����

		DWORD			dw232FuncNameNum;				//232���ܸ���
		char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];	//�������б�
		RV_RS232_CFG	st232[RV_MAX_232_NUM];		//��232���ڵ�ǰ����
	} DHDEV_COMM_CFG;


	/************************************************************************
	*	�Զ�ά������
	***********************************************************************/
	/* �Զ�ά������ */
	typedef struct
	{
		DWORD dwSize;

		//�Զ�����
		BYTE byAutoRebootDay; // 0-�Ӳ�, 1-ÿ��, 2-ÿ������, 3-ÿ����һ,.....
		BYTE byAutoRebootTime;  // 0-0:00 1-1:00,........23-:23:00 */
		//�Զ�ɾ���ļ�
		BYTE byAutoDeleteFilesTime; /*! 0-�Ӳ�, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH */

		BYTE reserved[13]; // ����λ
	} DHDEV_AUTOMT_CFG;

	/************************************************************************
	* ����������Ʋ�������
	************************************************************************/

	typedef struct
	{
		BOOL		bTourEnable;			//	��Ѳʹ��
		int			nTourPeriod;			//	��Ѳ�������λ��, 5-300 
		DWORD		dwChannelMask;			//	��Ѳ��ͨ����������ʽ��ʾ
		char		reserved[64];
	}RV_VIDEOGROUP_CFG;

	typedef struct
	{
		DWORD	dwSize;
		int		nMatrixNum;			//	�������(ע���������޸�)
		RV_VIDEOGROUP_CFG struVideoGroup[RV_MATRIX_MAXOUT];
		char	reserved[32];
	}DHDEV_VIDEO_MATRIX_CFG;   

	/************************************************************************
	*	��ddns���ýṹ��
	************************************************************************/

	typedef struct
	{
		DWORD	dwId;				//ddns������id��
		BOOL	bEnable;			//ʹ�ܣ�ͬһʱ��ֻ����һ��ddns����������ʹ��״̬
		char	szServerType[RV_MAX_SERVER_TYPE_LEN];	//���������ͣ�ϣ��..
		char	szServerIp[RV_MAX_DOMAIN_NAME_LEN];		//������ip��������
		DWORD	dwServerPort;						//�������˿�
		char	szDomainName[RV_MAX_DOMAIN_NAME_LEN];	//dvr��������jeckean.3322.org
		char	szUserName[RV_MAX_HOST_NAMELEN];	//�û���
		char	szUserPsw[RV_MAX_HOST_PSWLEN];		//����
		char	szAlias[RV_MAX_DDNS_ALIAS_LEN];		//��������������"RV inter ddns"
		DWORD	dwAlivePeriod;						//DDNS ����ʱ��
		char	reserved[256];
	}RV_DDNS_SERVER_CFG;

	typedef struct
	{
		DWORD	dwSize;
		DWORD	dwDdnsServerNum;	
		RV_DDNS_SERVER_CFG struDdnsServer[RV_MAX_DDNS_NUM];	
	}DHDEV_MULTI_DDNS_CFG;


	/************************************************************************
	*   �ʼ����ýṹ��
	************************************************************************/
	typedef struct 
	{
		char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*�ʼ���������ַ(IP��������)*/
		char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
		WORD	wMailPort;								/*�ʼ��������˿�*/
		WORD	wSubMailPort;
		WORD	wReserved;								/*����*/
		char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*���͵�ַ*/
		char	sUserName[RV_MAX_NAME_LEN];				/*�û���*/
		char	sUserPsw[RV_MAX_NAME_LEN];				/*�û�����*/
		char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*Ŀ�ĵ�ַ*/
		char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*���͵�ַ*/
		char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*������ַ*/
		char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*����*/
		BYTE	bEnable;//ʹ��0:false,	1:true
		char	reserved[255];
	} DHDEV_MAIL_CFG;

	/************************************************************************
	*   �ʼ����ýṹ����չ
	************************************************************************/
	typedef struct 
	{
		char	sMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];	/*�ʼ���������ַ(IP��������)*/
		char	sSubMailIPAddr[RV_MAX_DOMAIN_NAME_LEN];
		WORD	wMailPort;								/*�ʼ��������˿�*/
		WORD	wSubMailPort;
		WORD	wReserved;								/*����*/
		char	sSenderAddr[RV_MAX_MAIL_ADDR_LEN];		/*���͵�ַ*/
		char	sUserName[RV_MAX_NAME_LEN_EX];			/*�û���	luhj-0015 ��16�޸���32*/
		char	sUserPsw[RV_MAX_NAME_LEN];				/*�û�����*/
		char	sDestAddr[RV_MAX_MAIL_ADDR_LEN];		/*Ŀ�ĵ�ַ*/
		char	sCcAddr[RV_MAX_MAIL_ADDR_LEN];			/*���͵�ַ*/
		char	sBccAddr[RV_MAX_MAIL_ADDR_LEN];			/*������ַ*/
		char	sSubject[RV_MAX_MAIL_SUBJECT_LEN];		/*����*/
		BYTE	bEnable;//ʹ��0:false,	1:true
		char	reserved[255];
	} DHDEV_MAIL_CFG_EX;

	/************************************************************************
	*   �豸����汾��Ϣ
	************************************************************************/
	typedef struct  
	{
		char	szDevSerialNo[RV_DEV_SERIALNO_LEN];		//���к�
		char	byDevType;								//�豸���ͣ���ö��DHDEV_DEVICE_TYPE
		char	szDevType[RV_DEV_TYPE_LEN];				//�豸��ϸ�ͺţ��ַ�����ʽ������Ϊ��
		int		nProtocalVer;							//Э��汾��
		char	szSoftWareVersion[RV_MAX_URL_LEN];
		DWORD	dwSoftwareBuildDate;
		char	szDspSoftwareVersion[RV_MAX_URL_LEN];
		DWORD	dwDspSoftwareBuildDate;
		char	szPanelVersion[RV_MAX_URL_LEN];
		DWORD	dwPanelSoftwareBuildDate;
		char	szHardwareVersion[RV_MAX_URL_LEN];
		DWORD	dwHardwareDate;
		char	szWebVersion[RV_MAX_URL_LEN];
		DWORD	dwWebBuildDate;
		char	reserved[256];
	} DHDEV_VERSION_INFO;


	/************************************************************************
	*   DSP��������
	************************************************************************/
	typedef struct 
	{
		DWORD	dwVideoStandardMask;	//��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ
		DWORD	dwImageSizeMask;		//�ֱ������룬��λ��ʾ�豸�ܹ�֧�ֵķֱ�������
		DWORD	dwEncodeModeMask;		//����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ����	

		DWORD	dwStreamCap;			//��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
		//��һλ��ʾ֧��������
		//�ڶ�λ��ʾ֧�ָ�����1
		//����λ��ʾ֧�ָ�����2
		//����λ��ʾ֧��jpgץͼ
		DWORD	dwImageSizeMask_Assi[32];//��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣

		DWORD	dwMaxEncodePower;		//- DSP ֧�ֵ���߱������� 
		WORD	wMaxSupportChannel;		//- ÿ�� DSP ֧�����������Ƶͨ���� 
		WORD	wChannelMaxSetSync;		//- DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��

		BYTE	bMaxFrameOfImageSize[32];//��ͬ�ֱ����µ����ɼ�֡�ʣ���dwVideoStandardMask��λ��Ӧ
		BYTE	bEncodeCap;				//0���������ı�������+�������ı������� <= �豸�ı���������
		//1���������ı�������+�������ı������� <= �豸�ı���������
		//�������ı������� <= �������ı���������
		//�������ķֱ��� <= �������ķֱ��ʣ�
		//�������͸�������֡�� <= ǰ����Ƶ�ɼ�֡��

		char	reserved[95];
	} DHDEV_DSP_ENCODECAP, *LPDHDEV_DSP_ENCODECAP;


	/************************************************************************
	*   ץͼ��������
	************************************************************************/
	typedef struct 
	{
		DWORD	dwSize;
		BOOL	bTimingEnable;		//��ʱץͼ���أ�����ץͼ�����ڸ������������������֣�
		RV_VIDEOENC_OPT struSnapEnc[SNAP_TYP_NUM];	//ץͼ�������ã���֧�����еķֱ��ʡ����ʡ�֡�����ã�֡���������Ǹ�������ʾһ��ץͼ�Ĵ�����
	}DHDEV_SNAP_CFG;

	/************************************************************************
	*   web·������
	************************************************************************/
	typedef struct 
	{
		DWORD	dwSize;
		BOOL	bSnapEnable;	//�Ƿ�ץͼ
		int		iSnapInterval;	//ץͼ����
		char	szHostIp[RV_MAX_IPADDR_LEN]; /* HTTP����IP */
		WORD	wHostPort;
		int		iMsgInterval;	//״̬��Ϣ���ͼ��
		char	szUrlState[RV_MAX_URL_LEN];		//״̬��Ϣ�ϴ�URL
		char	szUrlImage[RV_MAX_URL_LEN];		//ͼƬ�ϴ�Url
		char	szDevId[RV_MAX_DEV_ID_LEN];		//������web���
		BYTE	byReserved[2];
	}DHDEV_URL_CFG;

	/************************************************************************
	*   ͼ��ˮӡ����
	************************************************************************/
	typedef struct __DHDEV_WATERMAKE_CFG 
	{
		DWORD				dwSize;
		int					nEnable;			//	ʹ��
		int					nStream;			//	������1��n��0-��������
		int					nKey;				//	��������(1-���֣�2-ͼƬ)
		char				szLetterData[RV_MAX_WATERMAKE_LETTER];	//	����
		char				szData[RV_MAX_WATERMAKE_DATA];		//	ͼƬ����
		BYTE				bReserved[512];		//	����
	} DHDEV_WATERMAKE_CFG;

	/************************************************************************
	*   FTP�ϴ�����
	************************************************************************/
	typedef struct
	{
		struct
		{
			RV_TSECT	struSect;	//��ʱ����ڵġ�ʹ�ܡ���Ч���ɺ���
			BOOL		bMdEn;		//�ϴ���̬���¼��
			BOOL		bAlarmEn;	//�ϴ��ⲿ����¼��
			BOOL		bTimerEn;	//�ϴ���ͨ��ʱ¼��
			DWORD		dwRev[4];
		} struPeriod[RV_TIME_SECTION];
	}RV_FTP_UPLOAD_CFG;

	typedef struct
	{
		DWORD				dwSize;
		BOOL				bEnable;							//�Ƿ�����
		char				szHostIp[RV_MAX_IPADDR_LEN];		//����IP
		WORD				wHostPort;							//�����˿�
		char				szDirName[RV_FTP_MAX_PATH];			//FTPĿ¼·��
		char				szUserName[RV_FTP_USERNAME_LEN];	//�û���
		char				szPassword[RV_FTP_PASSWORD_LEN];	//����
		int					iFileLen;							//�ļ�����
		int					iInterval;							//�����ļ�ʱ����
		RV_FTP_UPLOAD_CFG	struUploadCfg[RV_MAX_CHANNUM][RV_N_WEEKS];
		char 				protocol;							//0-FTP 1-SMB
		char				NASVer;								//����洢�������汾0=�ϵ�FTP����������ʾʱ��Σ�,1=NAS�洢������������ʱ��Σ�
		BYTE 				reserved[128];
	}DHDEV_FTP_PROTO_CFG;

	// DNS����������
	typedef struct  
	{
		char				szPrimaryIp[RV_MAX_IPADDR_LEN];
		char				szSecondaryIp[RV_MAX_IPADDR_LEN];
		char				reserved[256];
	}DHDEV_DNS_CFG;


	/************************************************************************
	*   ¼�����ز�������
	************************************************************************/
	typedef struct
	{
		DWORD dwSize;

		BOOL bEnable;	//TRUE���������أ�FALSE-��ͨ����
	}DHDEV_DOWNLOAD_STRATEGY_CFG;

	/************************************************************************
	*   ���紫���������
	************************************************************************/
	typedef struct
	{
		DWORD dwSize;

		BOOL bEnable;
		int  iStrategy;	//0-�������ȣ� 1-���������ȣ� 2-�Զ���
	}DHDEV_TRANSFER_STRATEGY_CFG;


	/************************************************************************
	*	IPC��һЩ����
	************************************************************************/
	//	��������������Ϣ
	typedef struct 
	{
		int					nEnable;			// ����ʹ��
		char				szSSID[36];			// SSID
		int					nLinkMode;			// ����ģʽ 0:auto 1:adhoc 2:Infrastructure
		int					nEncryption;		// ���� 0: off 2:WEP64bit 3: WEP128bit
		int					nKeyType;			// 0:Hex 1:ASCII
		int					nKeyID;				// ���
		char				szKeys[4][32];		// ��������
		int					nKeyFlag;
		char				reserved[12];
	} DHDEV_WLAN_INFO;

	//	ѡ��ʹ��ĳ�������豸
	typedef struct  
	{
		char				szSSID[36];
		int					nLinkMode;			// ����ģʽ 0:adhoc 1:Infrastructure
		int 				nEncryption;		// ���� 0: off  2:WEP64bit 3: WEP128bit
		char				reserved[48];
	} DHDEV_WLAN_DEVICE;

	//	�������������豸�б�
	typedef struct  
	{
		DWORD				dwSize;
		BYTE				bWlanDevCount;		// �������������豸����
		DHDEV_WLAN_DEVICE	lstWlanDev[RV_MAX_WLANDEVICE_NUM];
		char				reserved[255];
	} DHDEV_WLAN_DEVICE_LIST;

	//	����ע���������
	typedef struct  
	{
		char				szServerIp[32];		//ע�������IP
		int					nServerPort;		//�˿ں�
		char				reserved[64];
	} DHDEV_SERVER_INFO;

	typedef struct  
	{
		DWORD				dwSize;
		BYTE				bServerNum;         //֧�ֵ����ip��
		DHDEV_SERVER_INFO	lstServer[RV_MAX_REGISTER_SERVER_NUM];
		BYTE				bEnable;			//ʹ��
		char				szDeviceID[32];		//�豸id��
		char				reserved[94];
	} DHDEV_REGISTER_SERVER;

	//	����ͷ����
	typedef struct __DHDEV_CAMERA_INFO
	{
		BYTE				bBrightnessEn;		// ���ȿɵ� 1���ɣ�0������
		BYTE				bContrastEn;		// �Աȶȿɵ�
		BYTE				bColorEn;			// ɫ�ȿɵ�
		BYTE				bGainEn;			// ����ɵ�
		BYTE				bSaturationEn;		// ���Ͷȿɵ�
		BYTE				bBacklightEn;		// ���ⲹ���ɵ�
		BYTE				bExposureEn;		// �ع�ѡ��ɵ�
		BYTE				bColorConvEn;		// �Զ��ʺ�ת���ɵ�
		BYTE				bAttrEn;			// ����ѡ�� 1���ɣ�0������
		BYTE				bMirrorEn;			// ���� 1��֧�֣�0����֧��
		BYTE				bFlipEn;			// ��ת 1��֧�֣�0����֧��
		BYTE				bRev[125];			// ����
	} DHDEV_CAMERA_INFO;

	//	����ͷ��������
	typedef struct __DHDEV_CAMERA_CFG 
	{
		DWORD				dwSize;
		BYTE				bExposure;			//�ع�ģʽ 1-9:�ֶ��ع�ȼ�; 0:�Զ��ع�
		BYTE				bBacklight;			//���ⲹ�� 3:ǿ��2���У�1������ 0:��
		BYTE				bAutoColor2BW;		//��/ҹģʽ 2:����1���Զ�; 0:��
		BYTE				bMirror;			//����  1 ���� 0��
		BYTE				bFlip;				//��ת  1 ���� 0��
		char				bRev[123];			//����
	} DHDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
	//(����)���ⱨ������
	typedef struct
	{
		BOOL				bEnable;							//��������ʹ��
		char				szAlarmName[RV_MAX_ALARM_NAME];		//������������
		int					nAlarmInPattern;					//���������벨��
		int					nAlarmOutPattern;					//�����������
		char				szAlarmInAddress[RV_MAX_ALARM_NAME];//���������ַ
		int					nSensorType;						//�ⲿ�豸���������ͳ��� or ����
		int					nDefendEfectTime;					//��������ʱʱ�䣬�ڴ�ʱ���ñ���������Ч
		int					nDefendAreaType;					//�������� 
		int					nAlarmSmoothTime;					//����ƽ��ʱ�䣬���ڴ�ʱ�������ֻ��һ��������������������������Ե�����һ��
		char				reserved[128];

		RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];
		RV_MSG_HANDLE		struHandle;	/* ����ʽ  */
	} RV_INFRARED_INFO;

	//����ң��������
	typedef struct 
	{
		BYTE  address[ALARM_MAX_NAME];							// ң������ַ
		BYTE  name[ALARM_MAX_NAME];								// ң��������
		BYTE  reserved[32];										// �����ֶ�
	}RV_WI_CONFIG_ROBOT;

	//���߱����������
	typedef struct 
	{
		BYTE  address[ALARM_MAX_NAME];							//���������ַ
		BYTE  name[ALARM_MAX_NAME];								//�����������
		BYTE  reserved[32];										//�����ֶ�
	}RV_WI_CONFIG_ALARM_OUT;

	typedef struct  
	{
		DWORD				dwSize;
		BYTE				bAlarmInNum;						//���߱���������
		BYTE				bAlarmOutNum;						//���߱��������
		RV_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];				//���������ַ
		BYTE				bRobotNum;							//ң��������
		RV_WI_CONFIG_ROBOT RobotAddr[16];						//ң������ַ
		RV_INFRARED_INFO	InfraredAlarm[16];
		char				reserved[256];
	} RV_INFRARED_CFG;

	//����Ƶ��ⱨ����Ϣ
	typedef struct {
		int channel;						//����ͨ����
		int alarmType;						//��������0--��Ƶֵ���� 1---��Ƶֵ����
		unsigned int volume;				//����ֵ
		char 	reserved[256];
	} NET_NEW_SOUND_ALARM_STATE;

	typedef struct  
	{
		int channelcount;                   //������ͨ������
		NET_NEW_SOUND_ALARM_STATE  SoundAlarmInfo[RV_MAX_ALARM_IN_NUM];
	}RV_NEW_SOUND_ALARM_STATE;

	//����Ƶ��ⱨ������
	typedef struct
	{
		BOOL				bEnable;							//��������ʹ��
		int					Volume_min;							//��������Сֵ
		int					Volume_max;							//���������ֵ
		char				reserved[128];	
		RV_TSECT			stSect[RV_N_WEEKS][RV_N_REC_TSECT];	
		RV_MSG_HANDLE		struHandle;	/* ����ʽ  */
	} RV_AUDIO_DETECT_INFO;

	typedef struct  
	{
		DWORD					dwSize;
		int						AlarmNum;
		RV_AUDIO_DETECT_INFO	AudioDetectAlarm[RV_MAX_ALARM_IN_NUM];
		char					reserved[256];
	} RV_AUDIO_DETECT_CFG;

	//�洢λ�����ýṹ�壬ÿͨ����������,ÿͨ������ѡ����ִ洢����, Ŀǰ��������, ���ƶ�, Զ�̴洢.
	typedef struct 
	{
		DWORD 	dwSize;
		DWORD 	dwLocalMask;      //���ش洢����  ��λ��ʾ��
		//��һλ	ϵͳԤ¼
		//�ڶ�λ	��ʱ¼��
		//����λ	����¼��
		//����λ	����¼��
		//����λ	����¼��
		//����λ	�ֶ�¼��

		DWORD 	dwMobileMask;				//���ƶ��洢���� �洢�����籾�ش洢����
		int  	RemoteType;					//Զ�̴洢���� 0: Ftp  1: Smb 
		DWORD 	dwRemoteMask;				//Զ�̴洢���� �洢�����籾�ش洢����
		DWORD 	dwRemoteSecondSelLocal;		//Զ���쳣ʱ���ش洢����
		DWORD 	dwRemoteSecondSelMobile;	//Զ���쳣ʱ���ƶ��洢����
		char 	SubRemotePath[MAX_PATH_STOR];  //Զ��Ŀ¼, ���г���Ϊ260
		char	reserved[128];
	}RV_STORAGE_STATION_CFG;

	/************************************************************************
	*   ����ץ������
	************************************************************************/
	typedef struct
	{
		int					Offset;			//��־λ��λƫ��
		int					Length;			//��־λ�ĳ���
		char				Key[16];		//��־λ��ֵ
	} RV_SNIFFER_FRAMEID;

	typedef struct 
	{
		int					Offset;			//��־λ��λƫ��
		int					Offset2;		//Ŀǰû��Ӧ��
		int					Length;			//��־λ�ĳ���
		int					Length2;		//Ŀǰû��Ӧ��
		char				KeyTitle[24];	//�����ֵ
	} RV_SNIFFER_CONTENT;

	typedef struct 
	{
		RV_SNIFFER_FRAMEID	snifferFrameId;								//ÿ��FRAME ID ѡ��
		RV_SNIFFER_CONTENT	snifferContent[RV_SNIFFER_CONTENT_NUM];		//ÿ��FRAME��Ӧ��4��ץ������
	} RV_SNIFFER_FRAME;

	//ÿ��ץ����Ӧ�����ýṹ
	typedef struct
	{
		char				SnifferSrcIP[RV_MAX_IPADDR_LEN];			//ץ��Դ��ַ		
		int					SnifferSrcPort;								//ץ��Դ�˿�
		char				SnifferDestIP[RV_MAX_IPADDR_LEN]; 			//ץ��Ŀ���ַ
		int					SnifferDestPort;							//ץ��Ŀ��˿�
		char				reserved[28];								//�����ֶ�
		RV_SNIFFER_FRAME	snifferFrame[RV_SNIFFER_FRAMEID_NUM];		//6��FRAME ѡ��
		int					displayPosition;							//��ʾλ��
		int					recdChannelMask;							//ͨ������
	} RV_ATM_SNIFFER_CFG;

	typedef struct  
	{
		DWORD dwSize;
		RV_ATM_SNIFFER_CFG SnifferConfig[4];
		char	reserved[256];								//�����ֶ�
	}DHDEV_SNIFFER_CFG;


	/************************************************************************
	*   OEM��ѯ
	************************************************************************/
	typedef struct  
	{
		char				szVendor[RV_MAX_STRING_LEN];
		char				szType[RV_MAX_STRING_LEN];
		char				reserved[128];
	}DHDEV_OEM_INFO;


	/************************************************************************
	*   NTP����
	************************************************************************/

	typedef enum __RV_TIME_ZONE_TYPE
	{
		RV_TIME_ZONE_0,				// {0, 0*3600,"GMT+00:00"}
		RV_TIME_ZONE_1,				// {1, 1*3600,"GMT+01:00"}
		RV_TIME_ZONE_2,				// {2, 2*3600,"GMT+02:00"}
		RV_TIME_ZONE_3,				// {3, 3*3600,"GMT+03:00"}
		RV_TIME_ZONE_4,				// {4, 3*3600+1800,"GMT+03:30"}
		RV_TIME_ZONE_5,				// {5, 4*3600,"GMT+04:00"}
		RV_TIME_ZONE_6,				// {6, 4*3600+1800,"GMT+04:30"}
		RV_TIME_ZONE_7,				// {7, 5*3600,"GMT+05:00"}
		RV_TIME_ZONE_8,				// {8, 5*3600+1800,"GMT+05:30"}
		RV_TIME_ZONE_9,				// {9, 5*3600+1800+900,"GMT+05:45"}
		RV_TIME_ZONE_10,			// {10, 6*3600,"GMT+06:00"}
		RV_TIME_ZONE_11,			// {11, 6*3600+1800,"GMT+06:30"}
		RV_TIME_ZONE_12,			// {12, 7*3600,"GMT+07:00"}
		RV_TIME_ZONE_13,			// {13, 8*3600,"GMT+08:00"}
		RV_TIME_ZONE_14,			// {14, 9*3600,"GMT+09:00"}
		RV_TIME_ZONE_15,			// {15, 9*3600+1800,"GMT+09:30"}
		RV_TIME_ZONE_16,			// {16, 10*3600,"GMT+10:00"}
		RV_TIME_ZONE_17,			// {17, 11*3600,"GMT+11:00"}
		RV_TIME_ZONE_18,			// {18, 12*3600,"GMT+12:00"}
		RV_TIME_ZONE_19,			// {19, 13*3600,"GMT+13:00"}
		RV_TIME_ZONE_20,			// {20, -1*3600,"GMT-01:00"}
		RV_TIME_ZONE_21,			// {21, -2*3600,"GMT-02:00"}
		RV_TIME_ZONE_22,			// {22, -3*3600,"GMT-03:00"}
		RV_TIME_ZONE_23,			// {23, -3*3600-1800,"GMT-03:30"}
		RV_TIME_ZONE_24,			// {24, -4*3600,"GMT-04:00"}
		RV_TIME_ZONE_25,			// {25, -5*3600,"GMT-05:00"}
		RV_TIME_ZONE_26,			// {26, -6*3600,"GMT-06:00"}
		RV_TIME_ZONE_27,			// {27, -7*3600,"GMT-07:00"}
		RV_TIME_ZONE_28,			// {28, -8*3600,"GMT-08:00"}
		RV_TIME_ZONE_29,			// {29, -9*3600,"GMT-09:00"}
		RV_TIME_ZONE_30,			// {30, -10*3600,"GMT-10:00"}
		RV_TIME_ZONE_31,			// {31, -11*3600,"GMT-11:00"}
		RV_TIME_ZONE_32,			// {32, -12*3600,"GMT-12:00"}
	}RV_TIME_ZONE_TYPE;

	typedef struct  
	{
		BOOL				bEnable;			//	�Ƿ�����
		int					nHostPort;			//	NTP������Ĭ�϶˿�Ϊ123
		char				szHostIp[32];		//	����IP
		char				szDomainName[128];	//	����
		int					nType;				//	�������� 0����ʾIP��1����ʾ������2����ʾIP������
		int					nUpdateInterval;	//	����ʱ��(����)
		int					nTimeZone;			//	��RV_TIME_ZONE_TYPE
		char				reserved[128];
	}DHDEV_NTP_CFG;


	/************************************************************************
	*   ƽ̨�������� �� U��ͨ
	************************************************************************/
	typedef struct
	{
		BOOL bChnEn;
		char szChnId[RV_INTERVIDEO_UCOM_CHANID];
	}RV_INTERVIDEO_UCOM_CHN_CFG;

	typedef struct
	{
		DWORD dwSize;
		BOOL bFuncEnable;		// ���빦��ʹ����� 0 - ʹ��
		BOOL bAliveEnable;		// ����ʹ�����
		DWORD dwAlivePeriod;	// �������ڣ���λ�룬0-3600
		char szServerIp[RV_MAX_IPADDR_LEN];		// CMS��IP
		WORD wServerPort;						// CMS��Port
		char szRegPwd[RV_INTERVIDEO_UCOM_REGPSW]; //ע������
		char szDeviceId[RV_INTERVIDEO_UCOM_DEVID];	//�豸id
		char szUserName[RV_INTERVIDEO_UCOM_USERNAME];
		char szPassWord[RV_INTERVIDEO_UCOM_USERPSW];
		RV_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[RV_MAX_CHANNUM];//ͨ��id,en
	}DHDEV_INTERVIDEO_UCOM_CFG;

	/************************************************************************
	*   ƽ̨�������� �� ��������
	************************************************************************/
	typedef struct
	{
		DWORD dwSize;
		unsigned short usCompanyID[2];  /* ��˾ID,��ֵ,��ͬ�ĵ���������˾,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szDeviceNO[32];  /* ǰ���豸���кţ��ַ���, ����'\0'��������32byte */
		char szVSName[32];  /* ǰ���豸���ƣ��ַ���, ����'\0'��������16byte */
		char szVapPath[32];  /* VAP·�� */
		unsigned short usTcpPort;  /* TCP �˿�,��ֵ: ��ֵ 1~65535 */    
		unsigned short usUdpPort;  /* UDP �˿�,��ֵ: ��ֵ 1~65535 */    
		bool bCsEnable[4];  /* ���ķ�����ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szCsIP[16];  /* ���ķ�����IP��ַ, �ַ���, ����'\0'��������16byte */
		unsigned short usCsPort[2];  /* ���ķ������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */    
		bool bHsEnable[4];  /* ����������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szHsIP[16];  /* ����������IP��ַ, �ַ���, ����'\0'��������16byte */
		unsigned short usHsPort[2];  /* �����������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */ 
		int iHsIntervalTime;  /* �����������������,��ֵ(��λ:��) */ 
		bool bRsEnable[4];  /* ע�������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szRsIP[16];  /* ע�������IP��ַ, �ַ���, ����'\0'��������16byte */
		unsigned short usRsPort[2];  /* ע��������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		int iRsAgedTime;  /* ע���������Чʱ��,��ֵ(��λ:Сʱ) */
		char szAuthorizeServerIp[16];  /* ��Ȩ������IP */
		unsigned short usAuthorizePort[2];  /* ��Ȩ�������˿�,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szAuthorizeUsername[32];  /* ��Ȩ�������ʺ� */
		char szAuthorizePassword[36];  /* ��Ȩ���������� */

		char szIpACS[16];  /* ACS(�Զ�ע�������) IP */
		unsigned short usPortACS[2];  /* ACS Port,����4�ֽڶ���,Ŀǰֻ�������һ�� */
		char szUsernameACS[32];  /* ACS�û��� */
		char szPasswordACS[36];  /* ACS���� */
		bool bVideoMonitorEnabled[4];  /* DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ, ��ֵ: trueʹ��, false��ʹ�� */
		int iVideoMonitorInterval;  /* �ϱ����ڣ����ӣ� */

		char szCoordinateGPS[64];  /* GPS���� */
		char szPosition[32];  /* �豸λ�� */
		char szConnPass[36];  /* �豸������ */
	}DHDEV_INTERVIDEO_BELL_CFG;

	/************************************************************************
	*   ƽ̨�������� �� ������ά
	************************************************************************/
	typedef struct  
	{
		DWORD dwSize;
		unsigned short		nSevPort;							//�������˿�, ��ֵ, ��ֵ1~65535
		char				szSevIp[RV_INTERVIDEO_NSS_IP];		//������IP��ַ, �ַ���, ����'\0'��������32byte
		char				szDevSerial[RV_INTERVIDEO_NSS_SERIAL];	//ǰ���豸���кţ��ַ���,����'\0'��������32byte
		char				szUserName[RV_INTERVIDEO_NSS_USER];
		char				szPwd[RV_INTERVIDEO_NSS_PWD];
	}DHDEV_INTERVIDEO_NSS_CFG;

	/************************************************************************
	*   ��������״̬��Ϣ
	************************************************************************/

	typedef struct
	{
		int					nChannelNum;//ͨ����
		char				szUseType[32];//ͨ����;
		DWORD				dwStreamSize;//������С(��λ:kb/s)
		char				reserved[32];//����
	}DHDEV_USE_CHANNEL_STATE;

	typedef struct 
	{
		char						szUserName[32];//�û���
		char						szUserGroup[32];//�û���
		NET_TIME					time;//����ʱ��
		int							nOpenedChannelNum;//������ͨ������
		DHDEV_USE_CHANNEL_STATE		channelInfo[RV_MAX_CHANNUM];
		char						reserved[64];
	}DHDEV_USER_NET_INFO;

	typedef	struct 
	{
		int							nUserCount;//�û�����
		DHDEV_USER_NET_INFO			stuUserInfo[32];
		char						reserved[256];
	}DHDEV_TOTAL_NET_STATE;
	/************************************************************************
	*   ��̨������Ϣ
	************************************************************************/
#define  NAME_MAX_LEN 16
	typedef struct 
	{
		DWORD		dwHighMask; /*!< �����������λ */
		DWORD		dwLowMask; /*!< �����������λ */
		char		szName[NAME_MAX_LEN]; /*!< ������Э����NAME_MAX_LEN=16 */
		WORD		wCamAddrMin; /*!< ͨ����ַ����Сֵ */
		WORD		wCamAddrMax; /*!< ͨ����ַ�����ֵ */
		WORD		wMonAddrMin; /*!< ���ӵ�ַ����Сֵ */
		WORD		wMonAddrMax; /*!< ���ӵ�ַ�����ֵ */
		BYTE		bPresetMin; /*!< Ԥ�õ����Сֵ */
		BYTE		bPresetMax; /*!< Ԥ�õ�����ֵ */
		BYTE		bTourMin; /*!< �Զ�Ѳ����·����Сֵ */
		BYTE		bTourMax; /*!< �Զ�Ѳ����·�����ֵ */
		BYTE		bPatternMin; /*!< �켣��·����Сֵ */
		BYTE		bPatternMax; /*!< �켣��·�����ֵ */
		BYTE		bTileSpeedMin; /*!< ��ֱ�ٶȵ���Сֵ */
		BYTE		bTileSpeedMax; /*!< ��ֱ�ٶȵ����ֵ */
		BYTE		bPanSpeedMin; /*!< ˮƽ�ٶȵ���Сֵ */
		BYTE		bPanSpeedMax; /*!< ˮƽ�ٶȵ����ֵ */
		BYTE		bAuxMin; /*!< �������ܵ���Сֵ */
		BYTE		bAuxMax; /*!< �������ܵ����ֵ */
		int			nInternal; /*!< ���������ʱ���� */
		char		cType; /*!< Э������� */
		char		Reserved[7];
	}PTZ_OPT_ATTR;
	/************************************************************************
	*   �����豸����Ϣ
	************************************************************************/
	typedef struct
	{
		DWORD		dwType;	 //����(��GetDevConfig SetDevConfig������)
		WORD		wResultCode;//�����룺
		/*		0:�ɹ� 
		*		1:ʧ��
		*		2:���ݲ��Ϸ�
		*		3:��ʱ�޷�����	
		*		4:û��Ȩ��
		*/

		WORD   		wRebootSign;//������־��
		/*
		*	0:����Ҫ���� 1:��Ҫ��������Ч
		*/
		DWORD		dwReserved[2];//����	
	}DEV_SET_RESULT;

	/******************************************************************************
	* ץͼ�������Խṹ��
	*****************************************************************************/

	typedef struct 
	{
		int			nChannelNum;//ͨ����

		DWORD		dwVideoStandardMask	;//�ֱ���(��λ) ����鿴ö�� CAPTURE_SIZE						
		int			nFramesCount;//Frequence[128]�������Ч����
		char 		Frames[128];	//֡�ʣ�����ֵ��
		//-25:25��1֡
		//-24:24��1֡
		//-23:23��1֡
		//-22:22��1֡
		//����
		//0:��Ч
		//1��1��1֡
		//2��1��2֡
		//3��1��3֡
		//4��1��4֡
		//5��1��5֡
		//17��1��17֡
		//18��1��18֡
		//19��1��19֡
		//20��1��20֡
		//����
		//25: 1��25֡
		int			nSnapModeCount;//SnapMode[16]�������Ч����
		char		SnapMode[16];//������ֵ�� 0����ʱ����ץͼ 1���ֶ�����ץͼ
		int			nPicFormatCount;//Format[16]�������Ч����
		char 		PictureFormat[16];//������ֵ��0:BMP��ʽ 1:JPG��ʽ
		int			nPicQualityCount;//Quality[32]�������Ч����
		char 		PictureQuality[32];//������ֵ��	
		//100:ͼ������100%
		//80:ͼ������80%
		//60:ͼ������60%
		//50:ͼ������50%
		//30:ͼ������30%
		//10:ͼ������10%
		char 		nReserved[128];//����
	} RV_QUERY_SNAP_INFO;

	typedef struct 
	{
		int			nChannelCount; //ͨ������
		RV_QUERY_SNAP_INFO  stuSnap[RV_MAX_CHANNUM];
	}RV_SNAP_ATTR_EN;

	/******************************************************************************
	* ����ע�Ṧ�����Խṹ��
	*****************************************************************************/

	typedef struct
	{
		DWORD	 dwSize;
		LONG     iEnable;   //ʹ��
		LONG     iConnectType; //���ӷ�ʽ��0�������ӣ�ʹ��ԭ�е�����ý�嵥һ����ģʽ�� 1�������� ����ȡ����Ϊ����ע�����ӣ�ý����Ҫ�������������Ƶ��������½����µĶ�̬���ӷ�ʽ��
		char	 strServerIp[16]; //ע�������ip		
		LONG     iServerPort;   //ע��������˿�
		char     strUsr[64];    //�û���
		char     strPwd[64];   //����
		char     strPuId[32];   //�豸ͳһ��ʶ��32λ��ʶ����ƽ̨������Լ��
		/*
		�豸ͳһ��ʶ���� 
		����ʹ����32�ֽڣ�������Ϣ���ţ���ƽ̨������Լ������
		Xx          yy          zz                    a      				b     
		2�ֽ�		2�ֽ�       2�ֽ�					1�ֽ�     			1�ֽ�
		ʡ�����    �м����     �м������ű�����     ǰ�� 0���ͻ���1		�豸����
		cccccccc cccccccc ccccccccc
		24�ֽ� �豸���

		�����豸���� 01�� DVR�� 02 ��IPC ��03��NVS �� 04 ����������05������DVR
		*/
	}RV_CONFIG_REG_SERVER;

	/******************************************************************************
	* ��Ѳ�������Խṹ��
	*****************************************************************************/
#define V_TOUR_COMBINE_NUM 10
	typedef struct
	{
		unsigned int iSplitMode;  
		//֧�ֶ��ֻ���Ԥ��ģʽ����λ��ʶ���ο�ö��split_combine_t
		// ��0λ SPLIT1 ��Ĭ�϶�֧�֣���Ϊ�����棬ȫ��
		// ��1λ SPLIT2 
		//  ��2λ SPLIT4
		// ��3λ SPLIT8 
		//  ��4λ SPLIT9
		// ��5λ SPLIT16 
		//  ��6λ SPLITIP
		// ��7λ SPLIT6 
		//  ��8λ SPLIT12
	}RV_SPLIT_MODE;
	typedef struct
	{
		unsigned char bTourEnable;//ʹ��
		unsigned char ucRes;	//
		unsigned short usIntervalTime;//��Ѳʱ����
	}RV_DISPLAY_TOUR_CFG;
	typedef struct
	{
		DWORD	 dwSize;
		RV_DISPLAY_TOUR_CFG stDisplayTour;
		RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
	}RV_DISPLAY_TOUR;

	/******************************************************************************
	* ����ָ�����Խṹ��
	*****************************************************************************/
	typedef struct
	{
		RV_SPLIT_MODE stSplitMode;//ģʽ
		RV_SPLIT_COMBINE_CH stCombineCH;//ͨ�����
	}RV_DISPLAY_SPLIT_CFG;

	/******************************************************************************
	* �������������ͨ������Լ���ѯ�ṹ��
	*****************************************************************************/
	typedef struct
	{
		DWORD	 dwSize;
		RV_DISPLAY_SPLIT_CFG stSplitCfg;
		RV_DISPLAY_TOUR_CFG stTourCfg;
		LONG iCombineNum;
		RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
	}RV_WSCC;

	/******************************************************************************
	* ץͼ���ýṹ��
	*****************************************************************************/
#define MAX_SNAP_COUNT 32
	typedef struct
	{   	    	
		int iChannel;
	    int Enable;/*��ʱץ��ʹ��*/
		int SnapQuality;/*ץ��ͼ��������������6���� 1 �� 2 һ�� 3��ͨ�� 4�ã� 5�ܺã� 6���*/
							/*!<ץͼ����
							 usSnapMode ץ��ģʽ�� 0 ��ʾ1�뼸��ģʽ
												   1 ��ʾ����1��ģʽ
												   2 ��ʾ������1��ģʽ
							 usCounts   ��Ӧץ��ģʽ�µ���ֵ
							 */
		unsigned short usSnapMode;
		unsigned short usCounts;/*ץ��������1�뼸��ģʽ������ץ��ʱ�䣨����1��ģʽ��*/
	    int SnapCount;
	}RV_CONFIG_SNAP;
	typedef struct
	{
		DWORD dwSize;
		DWORD dwCount;								//����ʱ��==ͨ����Ϊ���У�>=0&&<ͨ����Ϊ�ĸ�ͨ������
													//��ȡʱ�����ظ���
		RV_CONFIG_SNAP stSnapCfg[MAX_SNAP_COUNT];
	}RV_SNAP;

	typedef struct
	{
		unsigned short usTotal;  //��ͨ����Ŀ
		unsigned short usIndex;  //�ڼ���ͨ����Ϣ
	}RV_DEV_CHANNEL;

	/******************************************************************************
	* �������������ýṹ��
	*****************************************************************************/
	#define RV_N_UI_TSECT					6
	#define RV_N_WEEKS						7
	typedef struct
	{
		int				enable;		     //!ʹ��		
		unsigned char	startHour; 			//!��ʼʱ��:Сʱ		
		unsigned char	startMinute;		//!��ʼʱ��:����		
		unsigned char	startSecond; 		//!��ʼʱ��:����		
		unsigned char	endHour;			 //!����ʱ��:Сʱ		
		unsigned char	endMinute; 		//!����ʱ��:����		
		unsigned char	endSecond; 		//!����ʱ��:����		
		unsigned char   ucReserved[2];    //����
	}RV_NETSECTION;		
	typedef struct
	{
		int				iName;
		RV_NETSECTION	tsSchedule[RV_N_WEEKS][RV_N_UI_TSECT];	/*!< ʱ��� */
	}RV_NET_WORKSHEET;
	#define RV_N_SYS_CH 16
	typedef struct
	{		
		unsigned int		dwRecord;				/*!< ¼������ */
		int					iRecordLatch;				/*!< ¼����ʱ��10��300 sec */ 	
		unsigned int		dwTour;					/*!< ��Ѳ���� */	
		unsigned int		dwSnapShot;				/*!< ץͼ���� */
		unsigned int		dwAlarmOut;				/*!< �������ͨ������ */
		int					iAOLatch;				/*!< ���������ʱ��10��300 sec */ 
		RV_PTZ_LINK			PtzLink[RV_N_SYS_CH];		/*!< ��̨������ */		
		int					bRecordEn;					/*!< ¼��ʹ�� */
		int					bTourEn;						/*!< ��Ѳʹ�� */
		int					bSnapEn;						/*!< ץͼʹ�� */	
		int					bAlarmOutEn;					/*!< ����ʹ�� */
		int					bPtzEn;						/*!< ��̨����ʹ�� */
		int					bTip;						/*!< ��Ļ��ʾʹ�� */	
		int					bMail;						/*!< �����ʼ� */	
		int					bMessage;					/*!< ������Ϣ���������� */	
		int					bBeep;						/*!< ���� */	
		int					bVoice;						/*!< ������ʾ */		
		int					bFTP;						/*!< ����FTP���� */		
		int					iWsName;				/*!< ʱ����ѡ������ʱ�����ʹ���������������Ҳ������ */
		unsigned int		dwMatrix;					/*!< �������� */
		int					bMatrixEn;					/*!< ����ʹ�� */
		int					bLog;						/*!< ��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ�� */
		int					iEventLatch;				/*!< ������ʼ��ʱʱ�䣬sΪ��λ */
		int					bMessagetoNet;				/*!< ��Ϣ�ϴ�������ʹ�� */
		unsigned int		dwReserved[7]; 				/*!< �����ֽ� */
	}RV_EVENT_HANDLER;
	typedef struct
	{
		int iEnable;  //�澯�������� 0������1����
		int iReserved; ////ͨ��������Ϣ�����嶨������
						//�澯�����ʶ���������ͳ��� or ���գ�0������1����
						//��Ƶ��ʧ�Ͷ���Ϊ�����ȣ�0~6���Σ�6����Ϊ������
						//����ΪӲ��ʣ����������, �ٷ���
						//���ܺ�ɫ����Ϊ�����ȣ�0~6���Σ�6����Ϊ������
 	}RV_ALARM_GUARD;
	typedef struct
	{
		RV_ALARM_GUARD			stGuard;
		RV_NET_WORKSHEET		stWorkSheet;
		RV_EVENT_HANDLER		struHandle;	/* ����ʽ  */
	} RV_DECODER_ALARM,*LPRV_DECODER_ALARM; 
	typedef struct
	{
		DWORD dwSize;		
		RV_DECODER_ALARM 		struDecoderAlarm[RV_MAX_CHANNUM];
	}RV_DECODER_ALARM_SCHEDULE;

	//////////////////////////////////////////////////////////////////////
	//	���������ṹ
	//////////////////////////////////////////////////////////////////////
	typedef struct
	{
		RV_ALARM_GUARD			stGuard;
		RV_NET_WORKSHEET		stWorkSheet;
		RV_EVENT_HANDLER		struHandle;	/* ����ʽ  */
	} RV_GEN_ALARM; 
	#define RV_MD_REGION_ROW	32
	typedef struct
	{
		int iRowNum;
		int iColNum;
		BYTE byRegion[32][32];
	}RV_REGION;
	typedef struct
	{
		RV_ALARM_GUARD			stGuard;
		RV_REGION				stRegion;
		RV_NET_WORKSHEET		stWorkSheet;
		RV_EVENT_HANDLER		struHandle;	/* ����ʽ  */
	} RV_MOTION_ALARM; 
	typedef struct
	{
		DWORD dwSize;		
		RV_GEN_ALARM 		struLocalAlarmIn[RV_MAX_CHANNUM];
		//RV_GEN_ALARM 		struNetAlarmIn[RV_MAX_CHANNUM];
		RV_MOTION_ALARM		struMotionAlarm[RV_MAX_CHANNUM];
		RV_GEN_ALARM 		struVideoLossAlarm[RV_MAX_CHANNUM];
		RV_GEN_ALARM 		struVideoBindAlarm[RV_MAX_CHANNUM];
		RV_GEN_ALARM 		struNoDiskAlarm;
		RV_GEN_ALARM 		struDiskErrAlarm;
		RV_GEN_ALARM 		struDiskFullAlarm;
		RV_GEN_ALARM 		struNetBrokenAlarm;
		RV_GEN_ALARM 		struIPConflictAlarm;
	}RV_ALARM_SCHEDULE;

	//////////////////////////////////////////////////////////////////////
	//	TV���ڽṹ
	//////////////////////////////////////////////////////////////////////
	typedef struct 
	{
		int left;//[0,100]
		int top;//[0,100]
		int right;//[0,100]
		int bottom;//[0,100]
	}RV_VD_RECT;
	//!TV��������
	typedef struct
	{
		DWORD dwSize;
		//!TV��С���ʣ�������ȡֵ��ͬ   [0,100]
		RV_VD_RECT rctMargin;		//!����   [0,100]	
		int iBrightness;		//!�Աȶ�[0,100]	
		int iContrast;		//!ȥ����[0,100]	
		int iAntiDither;	
	}RV_TVADJUST;

	//////////////////////////////////////////////////////////////////////
	//	��ͨ����
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//	����ʱ�ṹ��
	typedef struct
	{
		int Hour;
		int Minute;
	}RV_DSTTIMES;
	typedef struct
	{
		int iYear;		//!year [2000,2037]
		int iMonth;		//!month from January=1 [1,12]
		int iWeek;		//!��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]
		union
		{
			int iWeekDay;	//!weekday from sunday=0 [0, 6]
			int iDays;		//!day from one=1[0, 31]
		};	
		RV_DSTTIMES time;
	}RV_DST_POINT;
	//��ģʽѡ��
	//iMonth��iWeek(-1,1,2,3,4)�� iWeekDay��Hour��Min
	//��ģʽѡ�� iWeek=0
	//iYear ,iMonth,iDays��Hour��Min
	typedef struct
	{
		RV_DST_POINT iDST[2];
		unsigned char ucEnable;//0,��ʹ�ܣ�1ʹ��
		unsigned char ucRes[3];//���� 
	}RV_DST_TIME;
	typedef struct
	{ 		
		int  iCtrlMask;/*!< ��λ������ʽ
						0 Ӳ����ʱ���� 1����"OverWrite", 0ֹͣ"StopRecord" 
						1 �Ƿ���
						2 LCD��Ļ�Զ��ر�
						3 �Ƿ�TV���
						4 �Ƿ�VGA���
						5 �Ƿ�HDMI���
						*/		
		int iLocalNo;/*!<?�������:[0,?998]?*/ 
		unsigned short usScreenSaveTime;	//!����ʱ��(����) [0, 120]	
		unsigned short usAutoLogout;//!���ز˵��Զ�ע��(����) [0, 120]
		unsigned char ucDateFormat;//���ڸ�ʽ/*!< ���ڸ�ʽ:��YYMMDD��, ��MMDDYY��, ��DDMMYY�� */
		unsigned char ucDateSprtr;//���ڷָ���/*!< ���ڷָ��:��.��, ��-��, ��/�� */
		unsigned char ucTimeFmt;//ʱ���ʽ/*!< ʱ���ʽ:1����12��, 0����24�� */
		unsigned char ucRes;
		unsigned char ucSupportVideoFmt;/*�豸����֧�ֵ���ʽ �� ��0λ PAL ����1λ NTSC�� ��2λ SECAM*/
		unsigned char ucCurVideoFmt;/*�豸ʹ�õ���ʽ ��0 PAL ��1 NTSC�� 2 SECAM*/
		unsigned char ucRes1[2];
		unsigned int uiSupportLanguage;/*�豸����֧�ֵ����� �� 
								��0λ English����1λ SimpChinese�� ��2λ TradChinese��
								��3λ ��Italian��,4 ��Spanish��, 5��Japanese��, 6��Russian��, 7��French��, 8��German�� 
								*/						
		unsigned int uiCurLanguage;/*�豸ʹ�õ����� ��
								0 English��1 SimpChinese��2 TradChinese��3��Italian��,4 ��Spanish��, 
								5��Japanese��, 6��Russian��, 7��French��, 8��German�� */
		unsigned int uiRes[3];//�����ֽ�						
	}RV_NET_GENERAL;
	/// ϵͳʱ��ṹ
	typedef struct
	{
		int  year;///< �ꡣ[2000,2037]   
		int  month;///< �£�January = 1, February = 2, and so on.   
		int  day;///< �ա�   
		int  wday;///< ���ڣ�Sunday = 0, Monday = 1, and so on   
		int  hour;///< ʱ��   
		int  minute;///< �֡�   
		int  second;///< �롣   
		int  isdst;///< ����ʱ��ʶ��   
	}RV_SYSTEM_TIME;
	#define RV_MAX_DRIVERINFO 64
	typedef  struct
	{
		DWORD dwSize;
		RV_NET_GENERAL stGeneral;
		RV_SYSTEM_TIME stCurTime;
		RV_DST_TIME stDst;
	}RV_COMM_CFG;
//////////////////////////////////////////////////////////////////////
//	ƽ̨��������
//////////////////////////////////////////////////////////////////////
//���Ż�ͨƽ̨��������
typedef struct
{
	DWORD dwSize;
	BOOL			Enable;   //ʹ��
	int				MaxConn;  //��Ƶ���������	
	char			ServerIp[40]; //������IP	
	unsigned short	ServerPort; //�������˿�
	unsigned short	MegaPort; //�����˿�	
	char			DeviceId[32];//�豸ID	
	char			UserName[32];  //�û���
	char			PassWords[32]; //����	
	unsigned short	DownLoadMode; //¼�����ط�ʽ��λ0 TCP 1 HTXT
	unsigned short	FunMask;	/*�������룬��λ����
								��0λ�Ƿ�֧��Ԥ��
								��1λ�Ƿ�֧������
								��2λ�Ƿ�֧��Ԥ¼
								��3λ�Ƿ�֧��NAT
								*/	
	unsigned short	AlarmInterVal; /*�������*/
	unsigned short	Reserve;
}RV_CONFIG_NET_MEGA;
/************************************************************************
*   ƽ̨�������� �� ��������
************************************************************************/
typedef struct
{
	DWORD dwSize;
	unsigned short usCompanyID[2];  /* ��˾ID,��ֵ,��ͬ�ĵ���������˾,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szDeviceNO[32];  /* ǰ���豸���кţ��ַ���, ����'\0'��������32byte */
	char szVSName[32];  /* ǰ���豸���ƣ��ַ���, ����'\0'��������16byte */
	char szVapPath[32];  /* VAP·�� */
	unsigned short usTcpPort;  /* TCP �˿�,��ֵ: ��ֵ 1~65535 */    
	unsigned short usUdpPort;  /* UDP �˿�,��ֵ: ��ֵ 1~65535 */    
	bool bCsEnable[4];  /* ���ķ�����ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szCsIP[64];  /* ���ķ�����IP��ַ, �ַ���, ����'\0'��������16byte */
	unsigned short usCsPort[2];  /* ���ķ������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */    
	bool bHsEnable[4];  /* ����������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szHsIP[64];  /* ����������IP��ַ, �ַ���, ����'\0'��������16byte */
	unsigned short usHsPort[2];  /* �����������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */ 
	int iHsIntervalTime;  /* �����������������,��ֵ(��λ:��) */ 
	bool bRsEnable[4];  /* ע�������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szRsIP[64];  /* ע�������IP��ַ, �ַ���, ����'\0'��������16byte */
	unsigned short usRsPort[2];  /* ע��������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	int iRsAgedTime;  /* ע���������Чʱ��,��ֵ(��λ:Сʱ) */
	char szAuthorizeServerIp[64];  /* ��Ȩ������IP */
	unsigned short usAuthorizePort[2];  /* ��Ȩ�������˿�,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szAuthorizeUsername[32];  /* ��Ȩ�������ʺ� */
	char szAuthorizePassword[36];  /* ��Ȩ���������� */

	char szIpACS[64];  /* ACS(�Զ�ע�������) IP */
	unsigned short usPortACS[2];  /* ACS Port,����4�ֽڶ���,Ŀǰֻ�������һ�� */
	char szUsernameACS[32];  /* ACS�û��� */
	char szPasswordACS[36];  /* ACS���� */
	bool bVideoMonitorEnabled[4];  /* DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ, ��ֵ: trueʹ��, false��ʹ�� */
	int iVideoMonitorInterval;  /* �ϱ����ڣ����ӣ� */

	char szCoordinateGPS[64];  /* GPS���� */
	char szPosition[32];  /* �豸λ�� */
	char szConnPass[36];  /* �豸������ */
}RV_INTERVIDEO_BELL_CFG;
//VS300ƽ̨����
typedef struct
{
	DWORD dwSize;
	BOOL    BEnalbe;//ʹ�� 4�ֽ� 0 ��ʹ�� 1 ʹ��
	char    acServerIp[32];//������ip
	long	iServerPort;//�����������˿�
    char    acUserName[32];//�û���
    char    acPassWords[32];//����
	long	iType;//Э������ 0 tcp 1 udp
    char    acReserve[80];//����λ
}RV_CONFIG_VS300_NET;
//����ƽ̨��������
typedef struct
{ 	
	DWORD dwSize;
	BOOL Enable;//!�Ƿ���
	char ServerIp[64];//���۷�����IP
	int ServerPort;//!���۷������˿ں�
	char PUId[32];//!�豸ID
	int  usTcpPort;  /* �����TCP �˿�,��ֵ: ��ֵ 1~65535 */    
	int  usUdpPort;  /* �����UDP �˿�,��ֵ: ��ֵ 1~65535 */    
	char Reserved[64];//!����
}RV_CONFIG_ZXSHENYAN_NET;
//////////////////////////////////////////////////////////////////////
//	��������
//////////////////////////////////////////////////////////////////////
typedef struct
{	
	unsigned char ucUse;			//�˷����Ƿ���Ч	
	unsigned char ucPartion;		//�����ţ�	
	unsigned char ucFSType;			//����֧�ֵ��ļ�ϵͳ	
									// 0 WFS�ļ�ϵͳ  �������֧��2�������ҷ�����Լ���������ַ�ʽ	
									// WFS2�����Ļ���Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼�����	
									//  �����WFS 1�����Ļ�������ucPartType����	
									//  ucPartType==0��¼�������ucPartType==1���շ���	
									//  ��ʱ���գ��洢ͼƬ������¼���豸ֻ�ܽ���һ��ý��Ĵ洢	
									//  WFS�ļ�ϵͳԼ��ֻ���ٷֱ�2����ģʽ	
									// 1 FAT32	
									// 2 EXT3	
	unsigned char ucPartType;		//WFS�ļ�ϵͳ����ר�� 0 ¼�����  1���շ�������׼�ļ�ϵͳ������Ҫ��������	
	unsigned int uiTotalSpace;		//< ���������䵥λ�ο�ucSpaceType˵��	
	unsigned int uiRemainSpace;		//< ʣ���������䵥λ�ο�ucSpaceType˵��	
	unsigned char ucSpaceType;		//��ʶӲ��������λ������Ƚ�׼ȷ��ͳ��	
									//  ��4λ��7  6 5 4 �� �ܴ�С��λ  0 KB��1MB��2GB��3TB								
									//  ǰ4λ��3 2 1 0�� ʣ���С��λ  0 KB��1MB��2GB��3TB
	unsigned char ucReserve[3];
}RV_DISK_PARTION_INFO;
typedef struct
{
	unsigned char ucDiskNo;				//�̷�,�ڼ���Ӳ�� ���255��
	unsigned char ucCurrentUse;			//�Ƿ�ǰʹ�ù�����
	unsigned char ucLocalStorage;		//���ش洢����Զ�̴洢���� 0���� 1Զ��
	unsigned char ucDiskType;			//Ӳ�̽������� 0 sataӲ�� 1��U�̣�3 sd����4���ƶ�Ӳ�̣�5��dvd����
	unsigned char ucErrorFlag;			//�����̴����־
	unsigned char ucPartMethod;			//֧�ַ���ģʽ 
										// ��0λ��ʾ�Ƿ�֧�ַ��� 0 ��֧�� 1֧��
										//  ����λ ��λ��ʶ֧�ַ�����ʽ 
										//  ��1λ ���հٷֱȷ��� 0 ��֧�� 1֧��
										//   ��2λ ������������ MB  0 ��֧�� 1֧��
										//   ��3λ ������������ GB  0 ��֧�� 1֧��
										//   ��4λ ������������ TB 0 ��֧�� 1֧��
	unsigned char ucSupportPartionMax;  //֧��Ӳ������������
	unsigned char ucSupportFileSystem;  //֧�ֵ��ļ�ϵͳ0 WFS 1 FAT32 2 EXT3
	unsigned int uiTotalSpace;			//< ���������䵥λ�ο�ucSpaceType˵��
	unsigned int uiRemainSpace;			//< ʣ���������䵥λ�ο�ucSpaceType˵��
	unsigned char ucSpaceType;			//��ʶӲ��������λ������Ƚ�׼ȷ��ͳ��
										//  ��4λ��7  6 5 4 �� �ܴ�С��λ  0 KB��1MB��2GB��3TB
										//  ǰ4λ��3 2 1 0�� ʣ���С��λ  0 KB��1MB��2GB��3TB
	unsigned char ucAttr;       //0 �ɶ�д ��Ĭ�ϣ���1ֻ���� 2 ���౸��
	unsigned char ucRes1[2];				//����
	RV_DISK_PARTION_INFO szPartion[4];
	unsigned char ucRes2[64];			//����
}RV_DISK_INFO;
#define RV_MAX_DISK_NUM	16
typedef struct
{
	DWORD dwSize;
	DWORD dwCount;
	RV_DISK_INFO stDiskInfo[RV_MAX_DISK_NUM];
}RV_DISKS;
//Ӳ�̲���
typedef struct
{
	unsigned char ucDiskNo;         //�̷�,�ڼ���Ӳ�� ���255��
	unsigned char ucCtrlType;       //0 �ɶ�д ��Ĭ�ϣ���1ֻ���� 2 ���౸�� ��3 ��ʽ�� 
									//4 ����������ָ�
									// 5���·��������·����������ݲ���Ч
	unsigned char ucRes[2];  

	/////���·�����Ч����----------------------
	unsigned char ucFSType;	// 0 WFS�ļ�ϵͳ  �������֧��2�������ҷ�����Լ���������ַ�ʽ
							// WFS2�����Ļ���Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼�����
							//  �����WFS 1�����Ļ���ucPartType��ʾ¼������Ϳ��գ��洢ͼƬ��
							//  ��ʱ����¼���豸ֻ�ܽ���һ��ý��Ĵ洢
							//  WFS�ļ�ϵͳԼ��ֻ���ٷֱ�2����ģʽ
							// 1 FAT32
							// 2 EXT3
	unsigned char ucPartType;			//WFS�ļ�ϵͳ����ר�� ֻ��һ��������ʱ���ʹ�� 0 ¼�����  1���շ���
										//WFS  ������ʱ��Ĭ�ϵ�1����Ϊ���շ�������2����Ϊ¼���������ֵ��Ч
	unsigned char ucPartNum; //��������
	unsigned char ucPartMethod;	//Ӳ�̷�����ʽ�� 0 �ٷֱȣ�1 KB 2MB 3 GB 4 TB
	unsigned int uiPartSpace[4];	// ���շ�����ʽ�����η�����ʹ�õ�����
									//������հٷֱȣ����� 50%-50% 2������ 
									//�ڲ����50��50, 0, 0��ucPartCtrlType== 2 ��ucPartNo ==2
									//�����������MB������ʽ������1G��Ӳ�̣�200MB-300MB-100MB-400MB��
									//��ô������� 200��300��100��400��ucPartCtrlType== 2 ��ucPartNo ==4
	unsigned int uiRes[6];  
}RV_CTRL_DISK_INFO;
//Ӳ�̷������и�ʽ���Լ��޸�����
typedef struct
{
	unsigned char ucDiskNo;          //�̷�,�ڼ���Ӳ�� ���255��
	unsigned char ucPartCtrlType;   //0 ��ʽ����1������������޸�
	unsigned char ucPartNo;       //ucPartCtrlType==0��1���Ե�ucPartNo���������и�ʽ������������޸���
	unsigned char ucRes;	
	unsigned int uiRes[7];       //����
}RV_CTRL_DISK_PARTION_INFO;
typedef struct
{
	DWORD dwSize;
	RV_CTRL_DISK_INFO stDiskInfo;
}RV_CTRL_DISK_OP;
typedef struct
{
	DWORD dwSize;
	RV_CTRL_DISK_PARTION_INFO stDiskPartionInfo;
}RV_CTRL_DISK_PARTION_OP;
//////////////////////////////////////////////////////////////////////
//	ͨ������
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int enable;//!ʹ��
	int startHour;//!��ʼʱ��:Сʱ
	int	startMinute;//!��ʼʱ��:����
	int	startSecond;//!��ʼʱ��:����
	int	endHour;//!����ʱ��:Сʱ
	int	endMinute;//!����ʱ��:����
	int	endSecond;//!����ʱ��:����
}RV_TIMESECTION;
//////////////////////////////////////////////////////////////////////
//	��������
//////////////////////////////////////////////////////////////////////
#define RV_NAME_PASSWORD_LEN		64	
#define RV_EMAIL_ADDR_LEN  32
#define RV_N_MIN_TSECT 2
typedef struct
{
	char HostName[RV_NAME_PASSWORD_LEN]; //!�豸��	
	int HttpPort; //!HTTP����˿�	
	int TCPPort; //!TCP�����˿�		
	int SSLPort; //!SSL�����˿�	
	int UDPPort; //!UDP�����˿�	
	int MaxConn; //!���������	
	unsigned char ucMonMode; //!����Э�� {"TCP","UDP","MCAST",��}  0|1|2	
	unsigned char ucUseTransPlan; //!�Ƿ��������紫�����
	unsigned char ucTransPlan; //!������� 2�Զ� 1���������� 0�������ȣ�Ĭ��1
	unsigned char ucHighSpeedDownload; //!�Ƿ����ø���¼�����ز���
    int iRes[3];
}RV_CONFIG_NET_APP;
typedef struct
{
	char strEthName[16]; //��ͬ�������ƣ����ַ�����ʾ"eth0"; �˲����Ը�
	char strMacAddr[32];//xx.xx.xx.xx.xx.xx(�ַ�����ʽ)
	char HostIP[20]; //!����IP	
	char Submask[20]; //!��������
	char Gateway[20]; //!����IP
	unsigned char  ucTranMedia;   // 0�����ߣ�1������
	unsigned char  ucDefaultEth; //�Ƿ���ΪĬ�ϵ�����, 1��Ĭ�� 0����Ĭ��
	unsigned char  ucValid;	// ��λ��ʾ����һλ��1����Ч 0����Ч��
							//�ڶ�λ��0��DHCP�ر� 1��DHCPʹ�ܣ�
							//����λ��0����֧��DHCP 1��֧��DHCP
	unsigned char  ucReserve;	
	unsigned char  ucRes[16]; //������
}RV_CONFIG_NET_ETH;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NET_APP stNetApp;
	RV_CONFIG_NET_ETH stNetEth;
}RV_CONFIG_NET_COMM;
//!�������ṹ����
typedef struct
{	
	char ServerName[RV_NAME_PASSWORD_LEN];//!������,ip������ʽ������xxx.xxx.xxx.xxx��ʽ���64�ֽ�
	int iReserved;//!ԭʼΪIP��ַ��Ϊ����չ�������ֶΣ�	
	int Port;//!�˿ں�
	char UserName[RV_NAME_PASSWORD_LEN];//!�û���	
	char Password[RV_NAME_PASSWORD_LEN];	//!����	
	int  Anonymity;//!�Ƿ�������¼
}RV_REMOTE_SERVER;
typedef struct
{
	int Enable;	//!�Ƿ��� 0 ��������1����	
	int iKey;//!�������ƣ������ddns����Ӧddnskey;������չ��������ʹ��
	RV_REMOTE_SERVER Server;		//!������ ��Ϣ
}RV_IPADDR_SERVER;
#define  RV_MAX_EMAIL_TITLE_LEN 64
#define  RV_MAX_EMAIL_RECIEVERS  5
//!EMAIL����
typedef struct
{
	//!������ip,Ҳ����������
	RV_IPADDR_SERVER Server;
	int bUseSSL;		
	char SendAddr[RV_EMAIL_ADDR_LEN];//!���͵�ַ		
	char Recievers[RV_MAX_EMAIL_RECIEVERS][RV_EMAIL_ADDR_LEN];//!�����˵�ַ		
	char Title[RV_MAX_EMAIL_TITLE_LEN];//!�ʼ�����	
	RV_TIMESECTION Schedule[RV_N_MIN_TSECT];//!email��Чʱ��	
}RV_CONFIG_EMAIL;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_EMAIL stEmail;
}RV_EMAIL;
//DNS
typedef struct
{
	char strPrimaryIp[16]; //xxx. xxx. xxx. xxx (�ַ�����ʽ)
	char strSecondIp[16];
}RV_DNS_IP_LIST;
typedef struct
{
	DWORD dwSize;
	RV_DNS_IP_LIST stDNSIpList;
}RV_DNS;
//UPNP
typedef struct
{	
	int Enable; //�Ƿ���	
	int WebPort;// web�˿�	
	int TCPPort; // tcp�˿�	
	int iRervered;
}RV_CONFIG_UPNP;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_UPNP stUpnp;
}RV_UPNP;
//PPPOE
typedef struct 
{
	int iEnable; //0 ��ʹ�ܣ�1 ʹ��
	char strip[32];
	char strUser[64];
	char strPwd[64];
}RV_PPPOE_IP_SRV;	//ע�������У����Ż�ȡ���õ�ʱ��ֻ��ʹ�ܣ�ip������ip�����û���������Ч��
				//���õ�ʱ��ֻ��ʹ�ܣ��û���������Ч��
typedef struct
{
	DWORD dwSize;
	RV_PPPOE_IP_SRV stPppoe;
}RV_PPPOE;
//DDNS
#define RV_MAX_DDNS_SERVER_NUM 16
typedef struct
{
	DWORD dwSize;
	int iCount;
	RV_IPADDR_SERVER stDDNSServer[RV_MAX_DDNS_SERVER_NUM];
}RV_MDDNS;
//////////////////////////////////////////////////////////////////////
//	��������
//////////////////////////////////////////////////////////////////////
typedef struct
{
	int		iCompression;			/*!< ѹ��ģʽ */	
	int		iResolution;			/*!< �ֱ��� ����ö��capture_size_t(DVRAPI.H) */	
	int		iBitRateControl;		/*!< �������� ����ö��capture_brc_t(DVRAPI.H) */	
	int		iQuality;				/*!< �����Ļ��� ����1-6����Ӧ�������һ�㣬�ã��ܺã����*/	
	int		nFPS;					/*!< ֡��ֵ��0~30����-n~0��������ʾ����һ֡��NTSC/PAL������ */	
	int		nBitRate;				/*!< 0-4096k */
	int		iGOP;					/*!< ��������I֮֡��ļ��ʱ��s��2-12 */
}RV_VIDEO_FORMAT;
typedef struct
{
	int		nBitRate;				/*!< ����kbps*/	
	int		nFrequency;				/*!< ����Ƶ��*/	
	//int		nMaxVolume;				/*!< ���������ֵ*/
	unsigned char	ucLAudioVolumn;	//����������
	unsigned char	ucRAudioVolumn;	//����������
	unsigned char	ucRes[2];		//����
}RV_AUDIO_FORMAT_T;
//!ý���ʽ
typedef struct
{
	RV_VIDEO_FORMAT vfFormat;			/*!< ��Ƶ��ʽ���� */			
	RV_AUDIO_FORMAT_T afFormat;			/*!< ��Ƶ��ʽ���� */
	int	bVideoEnable;				/*!< ������Ƶ���� */
	int	bAudioEnable;				/*!< ������Ƶ���� */	
}RV_MEDIA_FORMAT;
//!��������
typedef struct
{
	int iSteamIndex;				/*!<������ʽ 
										������ �ο�ö�ٲο�ENCODE_TYPE_BY_RECORD �����в�ƷĬ��ֻ��һ�������������Ϊ0��
										������ �ο� ENCODE_TYPE_BY_SUBSTREAM�����4�������������ڲ�Ʒ���֧��һ�ָ����������Ϊ0��
										׽ͼ���� �ο� ENCODE_TYPE_BY_SUBSTREAM������4�������н���׽ͼ����
									*/	
	RV_MEDIA_FORMAT dstFmt;			/*!<������ʽ */	
}RV_NET_ENCODE;
//
#define RV_N_COLOR_SECTION 2
//! ��Ƶ��ɫ�ṹ
typedef struct
{
	int	nBrightness;				/*!< ����	0-100 */
	int	nContrast;					/*!< �Աȶ�	0-100 */
	int	nSaturation;				/*!< ���Ͷ�	0-100 */
	int	nHue;						/*!< ɫ��	0-100 */
	int	mGain;						/*!< ����	0-100 �ڣ�λ��1��ʾ�Զ����桡*/		
	int	mWhitebalance;				/*!<�Զ��׵�ƽ���ƣ�bit7��λ��ʾ�����Զ�����.0x0,0x1,0x2�ֱ�����,��,�ߵȼ�*/
}RV_VIDEOCOLOR_PARAM; 
typedef struct
{
	RV_TIMESECTION		TimeSection;		/*!< ʱ��� */
	RV_VIDEOCOLOR_PARAM	dstColor;			/*!< ��ɫ���� */
	int					iEnable;             /*!< ʹ�ܶ��� */ /* ����sdk��ʱû�д˲��֣�Ĭ��ʹ��*/
}RV_VIDEOCOLOR;
typedef struct
{
	RV_VIDEOCOLOR dstVideoColor[RV_N_COLOR_SECTION];
}RV_CONFIG_VIDEOCOLOR;
//! ��ѯ��Ƶ�����ڵ�������Ϣ
typedef void *						VD_HANDLE;
typedef int							VD_BOOL;
typedef unsigned int				VD_COLORREF;//0x00bbggrr
typedef unsigned int				VD_COLORDEV;//0x????????
//!��Ƶ����ṹ
typedef struct
{
	VD_COLORREF rgbaFrontground;		/*!< �����ǰ��RGB����͸���� */	
	VD_COLORREF rgbaBackground;			/*!< ����ĺ�RGB����͸����*/	
	RV_VD_RECT	rcRelativePos;				/*!< ����߾��������ı���*8191 */	
	VD_BOOL	bPreviewBlend;				/*!< Ԥ������ */	
	VD_BOOL	bEncodeBlend;				/*!< ������� */
}RV_VIDEO_WIDGET;
//�����ڵ�
#define RV_COVERNUM 8
typedef struct
{
	unsigned int	uiCoverNum;			/*!< ��ǰ��ͨ���м������ӵ����� */
	RV_VIDEO_WIDGET	dstCovers[RV_COVERNUM];
}RV_NET_VIDEO_COVER;
//
#define RV_CHANNEL_NAME_SIZE 32
typedef struct
{
	DWORD dwSize;	
	char cName[RV_MAX_CHANNUM][RV_CHANNEL_NAME_SIZE];
	RV_NET_ENCODE stEncodeMain[RV_MAX_CHANNUM];
	RV_NET_ENCODE stEncodeAssist[RV_MAX_CHANNUM];
	RV_CONFIG_VIDEOCOLOR stColorCfg[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTimeOSD[RV_MAX_CHANNUM];
	RV_VIDEO_WIDGET stTitleOSD[RV_MAX_CHANNUM];
	RV_NET_VIDEO_COVER stCovor[RV_MAX_CHANNUM];
	RV_NET_GENERAL stGeneral;
}RV_CODE_CFG;

//2010-7-20 luhj add
// typedef struct  
// {
// 	DWORD dwSize;
// 	NET_CHANNEL_NAME stChannelName[32];
// }RV_CHANNEL_NAME;
//add end
//2010-3-29 luhj-0016
typedef struct
{
	unsigned short 	iChannel;		//ͨ�� ��0��ʼ
	unsigned short	iIndex;			//Ԥ�õ���߹켣�±�� ��1��ʼ
}RV_PTZ_CHANNEL;

#define NAME_LEN			32		
#define PTZ_PRESETNUM		64
#define PTZ_CHANNELS		8

typedef struct 
{
	unsigned char 	ucChannel;					//ͨ��
	unsigned char 	ucPresetID;					//Ԥ�õ��
	unsigned char	iSpeed;						//Ԥ�õ��ٶ� �ٶ�1~15�ȼ�
	unsigned char	iDWellTime;					//Ԥ�õ�ͣ��ʱ�� 1~255s
	unsigned char	szPresetName[NAME_LEN];		//Ԥ�õ�����
}RV_PRESET_INFO;

typedef struct
{
	unsigned char 	ucChannel;					//ͨ��
	unsigned char	ucTourIndex;				//Ѳ����
	unsigned char	ucPresetCnt;				//һ��Ѳ�����е�Ԥ�õ��� 0~128
	unsigned char	uRes;						//����
	unsigned char	uiPresetNum[PTZ_PRESETNUM];	//Ѳ�����е�Ԥ�õ��
}RV_TOUR_INFO;

typedef struct  
{
	DWORD dwSize;
	DWORD dwCount;
	RV_PRESET_INFO	struPreset[PTZ_PRESETNUM];
}RV_PTZ_PRESET_SCHEDULE;

typedef struct  
{
	DWORD dwsize;
	DWORD dwCount;
	RV_TOUR_INFO	struTour[PTZ_CHANNELS];
}RV_PTZ_TOUR_SCHEDULE;

typedef struct  
{
	RV_PTZ_CHANNEL struChannel;
	RV_PRESET_INFO	struPreset;
}RV_PTZ_TOUR_PRESET;
//luhj-0016 end
//NTP�ṹ��
typedef struct
{	
	RV_IPADDR_SERVER szNtpServer;//!������	
	int UpdatePeriod;//!��������	
	int TimeZone;//!ʱ��
}RV_CONFIG_NTP;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_NTP stNtp;
}RV_NTP;

//////////////////////////////////////////////////////////////////////////
//	���ģʽ�ṹ��
typedef struct
{
    unsigned char ucOSDShow;//0λ �Ƿ���ʾʱ�� 1λ �Ƿ���ʾͨ����
    unsigned char ucRes[15];//����
}RV_OUT_MODE_OSD_CFG;
typedef struct
{
	DWORD dwSize;
    RV_OUT_MODE_OSD_CFG stOSD;
}RV_OUT_MODE_CFG;

//////////////////////////////////////////////////////////////////////////
//	ftp�ṹ��
typedef struct
{
	RV_IPADDR_SERVER	stServer;						//ftp������
	char            cDirName[RV_FTP_MAX_PATH];            //FTPĿ¼·�� 240
    int             iReserved;                   
    int             iFileLen;                    //�ļ�����               MΪ��λ
    int             iInterval;                    //�����ļ�ʱ����    ��Ϊ��λ  //����ȱ����������
    char            cRev[128];
}RV_CONFIG_FTP_SERVER_SET;
typedef struct
{
    RV_TSECT				stSect[RV_N_WEEKS][RV_TIME_SECTION];
}RV_FTP_APP_TIME_SET;
typedef struct
{
	RV_CONFIG_FTP_SERVER_SET	stFtpServerSet;	
	RV_FTP_APP_TIME_SET			stFtpAppTimeSet[RV_MAX_CHANNUM];
}RV_FTP_SERVER;
typedef struct
{
	DWORD dwSize;
	RV_FTP_SERVER stFtpRecord;//¼��
	RV_FTP_SERVER stFtpPicture;//ͼƬ
}RV_FTP;

/////////////////////////////////////////////////////////////////////////
//	rtsp�ṹ��
typedef struct
{
    unsigned short    usEnable;           //ʹ�� 
    unsigned short    usListernPort;     //RTSP�����˿�
    unsigned short    usUdpStartPort;  //UDP��ʼ�˿�
    unsigned short    usUdpPortNum;   //UDP�˿�����
    unsigned short    usReserve[36];   //����
}RV_CONFIG_RTSP_SET;
typedef struct
{
	DWORD dwSize;
	RV_CONFIG_RTSP_SET stRTSP;
}RV_RTSP;

//////////////////////////////////////////////////////////////////////
//	�ܺ�ɫ�����ṹ
//////////////////////////////////////////////////////////////////////
//�����ڵ�
#define RV_REDREGIONNUM 8
typedef struct
{
	long lX;
	long lY;
}RV_POINT;
typedef struct
{
	int				iRectNum;	/*!< ��ǰ��ͨ���м������� */
	RV_POINT		szPointArray[RV_REDREGIONNUM][4];
}RV_REDON_RECT;
typedef struct
{
	RV_ALARM_GUARD			stGuard;
	RV_NET_WORKSHEET		stWorkSheet;
	RV_EVENT_HANDLER		struHandle;	/* ����ʽ  */
	RV_REDON_RECT			stRedonRect;
} RV_INTERED_ALARM; 
typedef struct
{
	DWORD dwSize;		
	RV_INTERED_ALARM		struInteRedAlarm[RV_MAX_CHANNUM];
}RV_INTERED_ALARM_SCHEDULE;

//////////////////////////////////////////////////////////////////////
//¼�����
typedef struct
{
	unsigned char ucChannelCount;//ͨ����Ŀ
	unsigned char ucRes[3];
	unsigned char ucState[128];//��0������127������Ϊ��1����128ͨ����0: Ϊ��¼��;1: �ֶ�¼��;2: Ϊ�Զ�¼��
}RV_RECCTL; 
typedef struct
{
	DWORD dwSize;  
	RV_RECCTL struRecCtl;
}RV_RECCTL_CFG;

/* �������ýṹ�� ����16ͨ�� */
typedef struct
{
	DWORD			dwSize;
	//������Э��
	DWORD			dwDecProListNum;				//Э�����
	char			DecProName[RV_MAX_DECPRO_LIST_SIZE][RV_MAX_NAME_LEN]; //Э�����б�
	RV_485_CFG		stDecoder[RV_MAX_DECODER_NUM_EX];		//����������ǰ����
	
	DWORD			dw232FuncNameNum;				//232���ܸ���
	char			s232FuncName[RV_MAX_232FUNCS][RV_MAX_NAME_LEN];	//�������б�
	RV_RS232_CFG	st232[RV_MAX_232_NUM];		//��232���ڵ�ǰ����
} DHDEV_COMM_CFG_EX;

//2010-7-20 luhj add
typedef struct  
{
    int iChannel;
    char strChannelName[MAX_HHCHANNELNAME_LEN]; 
}RV_CHANNEL_NAME;

typedef struct  
{
	DWORD dwSize;
	RV_CHANNEL_NAME stChannelName[RV_MAX_DECODER_NUM_EX];		
}RV_CHANNELNAME_CFG;
//add end

//////////////////////////////////////////////////////////////////////////
//��Ƶ����
typedef struct
{
  unsigned int uiTalkAudioSourceType;    //!< ����Դ��ʽ��0Ϊ�������룬1Ϊmic
  unsigned int uiOutSilence;        ///< ���� 0--�Ǿ��� 1--����
  unsigned int uiOutLAudioVolumn;   //����������
  unsigned int uiOutRAudioVolumn;   //���������������������豸����ֵһ��
  unsigned int uiReserverd[32];//����
}RV_DEV_AUDIO;
typedef struct  
{
	DWORD			dwSize;
	RV_DEV_AUDIO	stDevAudio;		
}RV_DEV_AUDIO_CFG;

//////////////////////////////////////////////////////////////////////////
// ����ͨ����ѵ����
typedef struct
{
	BOOL			BEnable;                  //ʹ�ܿ���
    char			cChName[32];                         /* ����������,����ʶ��*/
    char			cDeviceIP[64];                            ///< �������豸��ip��ַ
    LONG			iDevicePort;                        ///< �������豸�Ķ˿ں�
    char			cDeviceUserName[32]; ///< �û���
    char			cDevicePassword[32]; ///< ����    
    LONG			iDevType;                            ///< �豸���ͣ���ö�ٱ�ʾ����Э������,0��ʾtcpֱ����3 rtsp+udp 4 vs300.
    LONG			iRemoteChannelNo;                    ///< Զ��ͨ����,��0��ʼ����  
    LONG			iStreamType;                         ///< Ҫ���ӵ���������?0:�������� 1:������
    LONG			iRemotePtzPreset;//Զ��Ԥ�õ�
    LONG			iRemotePtzPresetEnable;//�Ƿ�һ�����Ͼ�����Զ��Ԥ�õ�   
    LONG			reserverd[5];                        ///< �����ֽ�	
}RV_REMOTE_CH_CFG;
typedef struct
{
    BOOL			BEnable;//ʹ�ܿ���
    LONG			iDeviceChannelType;                    ///< ͨ�����ͣ�0��ʾ����ͨ����1��ʾģ��ͨ����Ĭ��Ϊ����ͨ��,��ʱ�������л�
    LONG			iMode;//0 ������ 1 ������
    unsigned long   uiTourTime;/* ��������Ѳʱ�� */
    unsigned long   uiNotTourCfgIndex; /* ������ʱ�Ĳ��õ�ͨ������,����Ѳ�б��е�λ��*/
    LONG			iDecodePolicy;   // //�������     (-2, ��ʵʱ -1 ʵʱ 0 Ĭ����� 1 ���� 2,    ������ ) �Ժ������չ���Զ���������ʱʱ��
    LONG			iAVEnable;       //0,ֻ����Ƶ 1��ֻ����Ƶ ��2 ������Ƶ 
    LONG			iReserverd[5];          ///< �����ֽ�
}RV_LOCAL_CH_CFG;
typedef struct
{
	RV_LOCAL_CH_CFG		stLocalChCfg;		//ͨ������
	DWORD				dwRemoteChanCount;	//Զ��ͨ����Ŀ
	RV_REMOTE_CH_CFG	stRemoteChanCfg[64]; //Զ��ͨ������
}RV_LOCAL_CH;
typedef struct
{
	DWORD dwSize;
	RV_LOCAL_CH stLocalChan[64];
}RV_DIGI_CH_TOUR_CFG;

	/******************************************************************************
	* end of ���ýṹ��
	*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // DHNETSDK_H










































