
#ifndef DHSYSABLE_H
#define DHSYSABLE_H


//////////////////////////////////////////////////////////////////////////
//	��ѯ����
typedef enum
{
	ABILITY_WATERMARK_CFG = 17,			//ˮӡ��������
	ABILITY_WIRELESS_CFG = 18,			//wireless��������
	ABILITY_DEVALL_INFO = 26,			//�豸�������б�
	ABILITY_CARD_QUERY = 0x0100,		//���Ų�ѯ����
	ABILITY_MULTIPLAY = 0x0101,			//�໭��Ԥ������
	ABILITY_INFRARED = 0X0121,			//���߱�������
	ABILITY_TRIGGER_MODE = 0x0131,
	//2009-12-16 ���� �޸� start
	ABILITY_SAVIA_COUNT = 33,		/* SAVIA��Ŀ*/
	//2009-12-16 ���� �޸� end
	ABILITY_STR_LEN_EN = 35,		/* �ַ�������(��98�豸) */
	//2009-12-23 ���� �޸� start
	ABBI_TLV = 40,				//��½���ذ��Ƿ����TLV����
	ABBI_DECODER,				//����������
	ABBI_AUTOREGISTER,			//����ע������
	ABBI_SAVIA,					//SAVIA����
	ABBI_AUDIOIN,				//��Ƶ����
	ABBI_PTZTOUR,				//��̨��Ѳ������
	ABBI_TALK,					//�Խ�����
	ABBI_MVIEW,					//�໭��Ԥ������ָ��������
	ABBI_SNAP,					//ץ������
	//
	ABBI_DEVID,					//�豸ID
	ABBI_VERSION,				//����汾
	ABBI_AUTH_LIST,				//��ǰ��¼�û�Ȩ��
	ABBI_SYS_ATTR_EX,			//�豸����
	//
	ABBI_ISTLVPROTOCAL,			//�Ƿ�֧��TLVЭ��
	ABBI_IVIDEO,				//ƽ̨��������
	ABBI_ENCODE,				//��������
	ABBI_TIME,					//ʱ������
	ABBI_FTP,					//ftp����
	ABBI_WHITEBLACK,			//�ڰ���������			2010-5-13 luhj add
	ABBI_DEVTYPE,				//�豸����
	ABBI_RTSP,					//RTSP����
	ABBI_AUDIOVALUE,			//��Ƶ��������			2010-6-29 luhj add
	ABBI_RECORD,				//¼������
} RV_SYS_ABILITY;

//////////////////////////////////////////////////////////////////////////
//	�豸֧�ֹ����б�
enum 
{
	EN_FTP = 0,							//FTP ��λ��1������¼���ļ� 2������ץͼ�ļ�
	EN_SMTP,							//SMTP ��λ��1�����������ı��ʼ� 2����������ͼƬ
	EN_NTP,								//NTP	��λ��1������ϵͳʱ��
	EN_AUTO_MAINTAIN,					//�Զ�ά�� ��λ��1������ 2���ر� 3:ɾ���ļ�
	EN_VIDEO_COVER,						//�����ڵ� ��λ��1���������ڵ�
	EN_AUTO_REGISTER,					//����ע��	��λ��1��ע���sdk������½
	EN_DHCP,							//DHCP	��λ��1��DHCP
	EN_UPNP,							//UPNP	��λ��1��UPNP
	EN_COMM_SNIFFER,					//����ץ�� ��λ��1:CommATM
	EN_NET_SNIFFER,						//����ץ�� ��λ�� 1��NetSniffer
	EN_BURN,							//��¼���� ��λ��1����ѯ��¼״̬
	EN_VIDEO_MATRIX,					//��Ƶ���� ��λ��1���Ƿ�֧����Ƶ����
	EN_AUDIO_DETECT,					//��Ƶ��� ��λ��1���Ƿ�֧����Ƶ���
	EN_STORAGE_STATION,					//�洢λ�� ��λ��1��Ftp������(Ips) 2��U�� 3��NFS 4��DISK 5��SBM
	EN_IPSSEARCH,						//IPS�洢��ѯ ��λ��1��IPS�洢��ѯ	
	EN_SNAP,							//ץͼ  ��λ��1���ֱ���2��֡��3��ץͼ��ʽ4��ץͼ�ļ���ʽ5��ͼ������
	EN_DEFAULTNIC,						//֧��Ĭ��������ѯ ��λ 1��֧��
	EN_SHOWQUALITY,						//CBRģʽ����ʾ���������� ��λ 1:֧��
};

typedef struct 
{
	DWORD IsFucEnable[512];				//�����б�������,�±��Ӧ������ö��ֵ,��λ��ʾ�ӹ���
} RV_DEV_ENABLE_INFO;

//////////////////////////////////////////////////////////////////////////
//	���Ų�ѯ�����ṹ��
typedef struct 
{
	char		IsCardQueryEnable;
	char		iRev[3];
} RV_CARD_QUERY_EN;

//////////////////////////////////////////////////////////////////////////
//	wireless�����ṹ��
typedef struct 
{
	char		IsWirelessEnable;
	char		iRev[3];
} RV_WIRELESS_EN;

//////////////////////////////////////////////////////////////////////////
//	ͼ��ˮӡ�����ṹ��
typedef struct 
{
	char		isSupportWM;	//1 ֧�֣�0 ��֧��
	char		supportWhat;	//0������ˮӡ��1��ͼƬˮӡ��2��ͬʱ֧������ˮӡ��ͼƬˮӡ
	char		reserved[2];
} RV_WATERMAKE_EN;

//////////////////////////////////////////////////////////////////////////
//	�໭��Ԥ�������ṹ��
typedef struct  
{
	int			nEnable;			//1 ֧�֣�0 ��֧��
	DWORD		dwMultiPlayMask;	//����
	char		reserved[4];
} RV_MULTIPLAY_EN;

//2009-12-16 ���� �޸� start
//////////////////////////////////////////////////////////////////////////
//	SAVIA��Ŀ�����ṹ��
typedef struct 
{
	DWORD		dwCount;
} RV_SAVIA_COUNT;
//2009-12-16 ���� �޸� end

typedef struct  
{
	BOOL bSupport;//�Ƿ�֧��
	int	 nAlarmInCount;//�������
	int  nAlarmOutCount;//�������
	int  nRemoteAddrCount;//ң��������
	BYTE reserved[32];
}RV_WIRELESS_ALARM_INFO;

//2010-2-23 ���� �޸� start
//////////////////////////////////////////////////////////////////////////
//	��̨��Ѳ�������ṹ��
typedef  struct
{
	unsigned short usPresetNums ;  //ÿ��ͨ��Ԥ�õ�������
	unsigned short usTourNums;     //ÿ��ͨ�����Ѳ���켣����
    int iRes [4]; //����
}RV_PTZ_TOUR_EN;
//////////////////////////////////////////////////////////////////////////
//	����ע�������ṹ��
typedef  struct
{
	unsigned short usRegServerNums ;	//����ע����������� ����ʵ��Ϊ1��
	unsigned short usNetMode;			//����ע��ģʽ
	// ֧�ֶ�������ģʽ ÿһλ��ʶ�Ƿ�֧�� 0��ʶ��֧�֣�1��ʶ֧��
	// ��0λ ��Ƶ���������
	// ��1λ �����ӣ�ý������ӣ�֧���豸�������ӷ�����������Ƶ��
    int iRes [4];						//����
}RV_AUTO_REGISTER_EN;
//////////////////////////////////////////////////////////////////////////
//	�����������ṹ��
typedef  struct
{
	unsigned short usDecoderNums ;  //���������·��
	unsigned short usNetMode;		//֧�ֶ�������ģʽ ÿһλ��ʶ�Ƿ�֧�� 0��ʶ��֧�֣�1��ʶ֧��
									// ��0λ ͨ������vs100��vs200��Ĭ�ϴ�Ϊ֧�� ��1
									// ��1λ ֧��rtsp Client
									//  ��2λ ֧��vs300��
	int iAbilityMask;				//ÿ·�������������� ���������16ͨ����32λÿ2λ��ʶһ��ͨ��
									// 00 ���֧��CIF��01 ���֧��D1��10�����֧��720p, 11 ����
	unsigned char ucDecoderType; 	// ��������ʽ�� �������������vs100��������ü�ҳ��
									// 0���dvr������ģ��Ҳ�������֣���1����������ֻ�����֣�
	unsigned char ucModeAblity;//// ��0λ �Ƿ�֧�ֶ�������Ѳ�ķ�ʽ
	unsigned short  usMaxChNum;//֧�ֶ����ӷ�ʽʱ,ÿ·֧�ֵ���Ѳ�б��ͨ���������Ŀ
	int iRes [3];					//����
}RV_DECODE_EN;
//////////////////////////////////////////////////////////////////////////
//	ץ�������ṹ��
typedef struct
{	
    //!��λ��ʾ 0-����ץ��, 1-��ʱץ��, 2-�澯ץ��
    unsigned long type_mask;
	unsigned long uiSnapMaxCount;/*���֧��ץ������*/
	unsigned long uiCountsPerSecond;/*!<1s����ͼƬ����λ��ʾ
									��0λ 1s1��
									��1λ 1s2��
									��2λ 1s3��
									��3λ 1s4��
									��4λ 1s5��
									*/					
	unsigned long uiMaxSeconds;/*���֧�ּ���1��*/
	unsigned long uiRes[28];
}RV_ABILITY_SNAP_T;
//////////////////////////////////////////////////////////////////////////
//	����ģ�������ṹ��
typedef struct
{
	unsigned char ucSaviaNums ;		//savia��Ŀ
	unsigned char ucSurportAl;		//֧�ֵ��㷨
	unsigned char ucRes[22];		//������
}RV_SAVIA_EN;
//////////////////////////////////////////////////////////////////////////
//	�Խ����Խ���Ƶ����+��Ƶ����������ṹ��
typedef struct
{
	unsigned char ucSurportTalkIn ;  	//�Խ���Ƶ���루�豸���ڵ�������Ƶ�ɼ��� 1:֧�֣�0����֧��
	unsigned char ucTalkInMask;     	//�豸��Ƶ��������ʽ����  ��λ��ʶ�Ƿ�֧�ֱ����ʽ 
	//��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b ��2λ g711u��
	unsigned char ucSurportTalkOut;		//�Խ���Ƶ���   1:֧�֣�0����֧��
	unsigned char ucTalkOutMask;     	//�豸��Ƶ�����ʽ����  ��λ��ʶ�Ƿ�֧�ֽ����ʽ
	//��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b  ��2λ g711u��
}RV_TALK_EN;
//////////////////////////////////////////////////////////////////////////
//	��Ƶ���������ṹ��
typedef struct
{
	unsigned long uiAudio ;				//0~31Ϊ���α�ʾͨ��1~ͨ��32����Ƶ���� 1��ʶ�У�0��ʶ
	unsigned long uiAudioMask ;  		//�豸���������ʽ����  ��λ��ʶ�Ƿ�֧�ֱ����ʽ 
	//��0λ �Ƿ�֧��g711a�� ��1λ pcm8k16b  ��2λ g711u��
}RV_AUDIO_IN_EN;
//////////////////////////////////////////////////////////////////////////
//	����ָ���������ṹ��
#define MAX_SPLIT_COMINE_NUMS 32
#define MAX_SPLITCOMBINE_NUMBER 32
typedef struct
{
	unsigned int iChMask;//ͨ�����룬��λ��ʶ����32λ4�ֽ�,���32����ʽ
						 /* ���� 4���� ��֧�� ģʽ��1��2��3��4ͨ������1��3��4��5��
						 ��Ӧ������Ϊ  0000 0000 0000 0000 0000 0000 0000 1111=0x0F
						 0000 0000 0000 0000 0000 0000 0001 1101=0x1D
						 ���9���� ֧�֣�1��2��4��5��6��7��8��9��10ͨ����
						 ��Ӧ������Ϊ0000 0000 0000 0000 0000 0011 1111 1011=0x3FB
						 �˴��������ݣ�����Ҫ���� SPLIT_MODE��uiSplitType�����������ƶ��ǰ�����ϵ�����ų���ϵ
							*/
	unsigned char ucSpecialCh;/*����ͨ����Լ��Ϊ�Զ�������ǰ���ߴ󴰿���ʾ��*/
	unsigned char ucRes[3];
}RV_SPLIT_COMBINE_CH;
typedef struct
{
	unsigned char ucSplitMode;/*�໭��Ԥ��ģʽ���ο�ö��split_combine_t*/
	unsigned char ucSplitType;    
								/*֧�ַ�����ϵ����� ��ÿ��λ��Ӧ����Ԥ��ģʽiSplitModeһλ
								0 ȫ��������ϣ� 
								���Ϊ����
								1 ������ϵ��ֻ���ٲ������������㣬����Լ�����64����
								2 �ų���ϵ�����64���ų���ϣ�
								����ǰ��������ų���ʽ��SPLIT_COMBINE�����ʾ������Ϣ
								���� ���޶��壬������չʹ��
								*/
	unsigned char ucCombinNums;	/*������ܸ������������N_SPLIT_COMINE_NUMS 32��*/
	unsigned char ucRes;
	RV_SPLIT_COMBINE_CH stCombineCh[MAX_SPLIT_COMINE_NUMS];
}RV_SPLIT_COMBINE;
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
	long lCount;		//SPLIT_COMBINE����Ŀ
	RV_SPLIT_COMBINE m_stSplitCombi[MAX_SPLITCOMBINE_NUMBER];//SPLIT_COMBINE����
}RV_SPLIT_EN;
//////////////////////////////////////////////////////////////////////////
//	��½���ص��û�Ȩ��
typedef struct
{
	unsigned long uiMonitorMask;
	unsigned long uiPlayMask;
	unsigned long uiNetPreviewMask;
	unsigned long uiControlConfigMask;
	unsigned long uiReserved[4];
}RV_USER_AUTH_LIST;
//////////////////////////////////////////////////////////////////////////
//	��½���ص��豸����
typedef struct
{
	unsigned char iVideoInCaps;     // ��Ƶ����ӿ�����
	unsigned char iVideoOutCaps;     //��Ƶ����ӿ�����
	unsigned char iAudioInCaps;     // ��Ƶ����ӿ�����
	unsigned char iAudioOutCaps;     // ��Ƶ����ӿ�����	
	unsigned char iAlarmInCaps;     // ��������ӿ��� 
	unsigned char iAlarmOutCaps;    // ��������ӿ���
	unsigned char iDiskNum;          // ʵ��ʹ��Ӳ���� sdk��byDiskNum
	unsigned char iAetherNetPortNum;// ����ӿ���sdk��iIsMutiEthIf 	
	unsigned char iUsbPortNum;          // USB�ӿ���
	unsigned char iDecodeChanNum;     // ���ؽ���(�ط�)·�� 
	unsigned char iComPortNum;      // ������
	unsigned char iParallelPortNum;   // ���ڿ���	
	unsigned char iSpeechInCaps;     // �Խ�����ӿ�����
	unsigned char iSpeechOutCaps;     // �Խ�����ӿ�����
	unsigned char bRes[2];   // ������	
}RV_SYSATTR_EX_T;
//ƽ̨���������ṹ��
typedef struct
{
	int iIVideoMask;//֧��ƽ̨������ ��0λ BELL ��1λ HXHT ��2λ VS300 .�����豸֧�ֶ��ƽ̨����
	int iRes[3];
}RV_IVIDEO_EN;
//���������ṹ��
typedef struct
{
	unsigned int	uiMaxEncodePower;				//��Ʒ֧�ֵ���߱�������
	unsigned short	usSupportChannel;				//- ÿ�� DSP ֧�����������Ƶͨ���� 
	unsigned short	usChannelSetSync;				//- DSP ÿͨ���������������Ƿ�ͬ�� 0-��ͬ��, 1-ͬ��
													//ÿһͨ��֧���������
	unsigned char	ucVideoStandardMask;			//��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ 0 PAL 1 NTSC
	unsigned char	ucEncodeModeMask;				//����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ���� ��0 VBR��1 CBR
	unsigned short	usStreamCap;					//��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
													//��һλ��ʾ֧��������
													//�ڶ�λ��ʾ֧�ָ�����1
													//����λ��ʾ֧��jpgץͼ��׽ͼ�������ⶨ�壬�ڴ˲�����
	unsigned int	uiImageSizeMask;				//�������������� ö�ٰ���capture_size_t 
	unsigned int	uiImageSizeMask_Assi[32];		//������ȡ��ͬ�ı���ʱ�򣬸�����֧�ֵı����ʽ������, 
													//uiImageSizeMask_Assi��0����ʾ��������CAPTURE_SIZE_D1ʱ��������֧�ֵı����ʽ��
													//uiImageSizeMask_Assi��1����ʾ��������CAPTURE_SIZE_HD1ʱ��������֧�ֵı����ʽ������
	unsigned char	ucSupportPolicy;				//�Ƿ�֧������������ 0 ��֧�� 1 ֧��
	unsigned char	ucRes[11];						//����
}RV_ENCODE_CAPS_NET_EN;

//2010-2-23 ���� �޸� end
//ʱ�������ṹ��
typedef struct
{
	unsigned char ucSupTimeAdjust;  //�Ƿ�֧��Уʱ����
									//��λ����
									//��0λ Dst ֧������ʱ
									//��һλ SNTP��udp ��123���� ����Ĭ���Ǵ�ntp
									//�ڶ�λ NTP��udp��37��tcp��37��
	unsigned char ucRes[11];   //������
}RV_TIME_EN;

//////////////////////////////////////////////////////////////////////////
//	ftp�����ṹ��
typedef struct
{
	//��λ����
    //��0λ ֧��ftp¼���ϴ�
    //��1λ ֧��ftpͼƬ�ϴ�
	unsigned char ucSupFtp;
	//������ 
	unsigned char ucRes[15];
}RV_FTP_EN;

//2010-5-13 luhj add
//�ڰ����������ṹ��
typedef struct  
{
	unsigned short	usMaxBlackNums;	//����������Ŀ
	unsigned short	usMaxWhiteNums;	//����������Ŀ
	unsigned long	res[12];		//����
}RV_WHITEBLACK_EN;
// 
// //   ���������ṹ��
// typedef struct
// {	
// 	unsigned long uiAudioVolumn;    //0~31Ϊ���α�ʾͨ��~ͨ����Ƶ����֧����������,��Ƶ����"����"�������ο�RV_AUDIO_IN_EN	
// 	unsigned char ucTalk;           //��λ��ʾ�Խ�������Ƶ֧����������,�Խ���Ƶ����"����"�������ο�RV_TALK_EN	
// 	unsigned char ucRes[3];	
// 	unsigned long uiRes[14];	
// }RV_AUDIOVALUE_EN;

//   ���������ṹ��

typedef struct
{	
    //0~31Ϊ���α�ʾͨ��~ͨ����Ƶ����֧����������,��Ƶ����"����"�������ο�AUDIO_IN_ABILITY
    unsigned long uiAudioVolumn ;    
    //��0λ��ʾ�Խ�������Ƶ֧����������,�Խ���Ƶ����"����"�������ο�TALK_ABILITY
    //��1λ��ʾ�Խ������Ƶ֧���������ƺ;���,�Խ���Ƶ���"����"�������ο�TALK_ABILITY
    //��2λ��ʾ�Խ�������Ƶ֧��MIC����
    //��3λ��ʾ�Խ�������Ƶ֧��Liner����
    unsigned char ucTalk;          
    //��Ƶ�����������1����������2��˫����
    unsigned char ucAudioChannel;    
    unsigned char ucRes;
    //��Ƶ���(�Խ����)��������1����������2��˫����
    unsigned char ucAudioOutChannel; 
    unsigned long uiRes[14];	
}RV_AUDIOVALUE_EN;


//add end

/////////////////////////////////////////////////////////////////////////
//	rtsp�����ṹ��
typedef struct  
{
	unsigned char ucAbilty;//��1λ��ʾ�Ƿ�֧��rtspʵʱ���ӣ���2λ��ʾ�Ƿ�֧��rtsp¼��ط�
	unsigned char Res[31] ;//����
}RV_RTSP_EN;

/////////////////////////////////////////////////////////////////////////
//	��98�豸�ַ������������ṹ��
typedef struct  
{
	unsigned short usPPPoeNameLen;//pppoe�û������ȣ�����null�ַ���
	unsigned short usPPPoePwdLen;//pppoe���볤�ȣ�����null�ַ���
	unsigned short usRes[30] ;//����
}RV_STR_LEN_EN;

//////////////////////////////////////////////////////////////////////////
//      ¼����������ṹ��
typedef struct
{
	unsigned long dwFlag;//��0λ��ʾ֧���µ�"¼�����"Э��
	unsigned char ucRes[16];
}RV_RECORD_EN;

#endif // DHSYSABLE_H

