#ifndef	_SVACDECLIB_H_
#define _SVACDECLIB_H_

#define MAX_CUSTOM_EXT_COUNT          8
#define MAX_CUSTOM_EXT_SIZE          1024 // 256
#define MAX_DIVA_INIT_SIZE           1024
#define MAX_DIVA_INFOR_SIZE          32768 //8192 // 512

typedef enum /*seek_status*/
{
    SVAC_SEEK_ERROR = -1,
    SVAC_SEEK_SUCCESS,
	SVAC_SEEK_NOTFOUND,
    SVAC_SEEK_NEED_MORE_BITS
}SVAC_SEEK_STATUS;

typedef enum /*auth_status*/
{
    SVAC_AUTH_DEC_ERROR =	-1,
	SVAC_AUTH_END,
    SVAC_AUTH_NEED_MORE_BITS,
	SVAC_AUTH_NEED_PASSWORD,
	SVAC_AUTH_SUCCESS,
	SVAC_AUTH_CONTINUE,
	SVAC_AUTH_ERROR,
	SVAC_AUTH_BL_ERROR,
	SVAC_AUTH_EL_ERROR,
	SVAC_AUTH_NODATA,
	SVAC_AUTH_BL_NODATA,
	SVAC_AUTH_EL_NODATA
}SVAC_AUTH_STATUS;

typedef enum /*dec_status*/
{
    
    SVAC_DEC_ERROR =	-1,
    SVAC_DEC_SUCCESS	,
    SVAC_DEC_NEED_MORE_BITS,
    SVAC_DEC_NO_PICTURE,
    SVAC_DEC_BUF_OVERFLOW,
	SVAC_DEC_PASSWORD_ERROR
/*	SVAC_DEC_AUTH_ERROR,
	SVAC_DEC_BL_AUTH_ERROR,
	SVAC_DEC_EL_AUTH_ERROR,
	SVAC_DEC_NO_AUTH_DATA,
	SVAC_DEC_BL_NO_AUTH_DATA,
	SVAC_DEC_EL_NO_AUTH_DATA,
	SVAC_DEC_AUTH_SUCCESS*/
}SVAC_DEC_STATUS;

typedef struct
{
    unsigned char type;
    unsigned short length;
    unsigned char *pbuf;
	unsigned char reserved[2];
}SVAC_EXT_INFO_CUSTOM;

typedef struct 
{
	unsigned int    roi_infor_en;						//ROI ������Ϣ�����λΪ0�������roi������
	unsigned short	top;								//ROI �������� [y_min]	
	unsigned short	left;								//ROI ������� [x_min]
	unsigned short	bot;								//ROI �ױ����� [y_max]
	unsigned short	right;								//ROI �ұ����� [x_max]
}SVAC_ROI;

typedef struct
{
	unsigned short  len;		// val���ֽ���
	unsigned char	*DIVA_init_extension_val;
} DIVA_init_extension;

typedef struct
{
	unsigned short  len;		// val���ֽ���
	unsigned char	*DIVA_info_extension_val;
} DIVA_info_extension;

typedef struct
{
	unsigned char  TsEnable;							//�Ƿ����ʱ����Ϣ
    unsigned char  Ts_time_stamp_flag;					//
    unsigned char  Ts_ref_date_flag;
    unsigned short Ts_time_year;						//��
    unsigned char  Ts_time_month;						//��
    unsigned char  Ts_time_day;							//��
    unsigned char  Ts_time_hour;						//ʱ	
    unsigned char  Ts_time_minute;						//��	
    unsigned char  Ts_time_second;						//��
    unsigned short Ts_time_sec_fractional;				
	unsigned char  SeEnable;							//�Ƿ���������Ϣ
    unsigned char  Se_roi_extension_flag;				//�Ƿ����ROI��չ��Ϣ
    unsigned char  Se_event_extension_flag;				//�Ƿ�����¼���չ��Ϣ
    unsigned char  Se_event_num[4+1];					//�¼���Ϣ
    unsigned char  Se_alert_extension_flag;				//�Ƿ����������Ϣ
    unsigned char  Se_vm_alert_extension_flag;			//�Ƿ����vimico������Ϣ
    unsigned char  Se_alert_num;						//�����¼���Ŀ
    unsigned char  Se_alert_appendix_flag[16];			//�����¼���Ϣ
    unsigned char  Se_alert_appendix_length[16];		//�����¼�����		
	unsigned char  Svac_inf_position_idc;				//λ�ñ����Ϣ
	unsigned short  Svac_inf_camera_idc;				//����ͷ�����Ϣ
	unsigned char  FrameNum;							//֡����i֡��0��p֡��֡��1
	unsigned char  RoiEn;								//ͼ���Ƿ����ROI��Ϣ	
	unsigned char  RoiNum;								//ͼ�����ROI��Ŀ
	unsigned char  RoiSkipMode;							//ROI��������ģʽ
	unsigned char  RoiSvcSkipMode;						//ROI_SVC��������ģʽ		
	SVAC_ROI	   RoiRect[15];							//ROI��Ϣ����SVC���������������ROI������Ϣ
	SVAC_ROI	   RoiSvcElRect[15];					//SVC��ǿ��ROI������Ϣ��SVC����Ч

	unsigned char	AInitEnable;
	unsigned char	AInit[256];
	unsigned char	AResEnable;
	unsigned char	ARes[256];

	unsigned char  vimc_enabel;
	unsigned char  custom_enabel;
	unsigned int   ExtEnableFlag[8];
	unsigned char  svac_ext_info_custom_num;
	SVAC_EXT_INFO_CUSTOM svac_ext_info_custom[MAX_CUSTOM_EXT_COUNT];

	DIVA_init_extension svac_diva_init;
	DIVA_info_extension svac_diva_info;

	int Reserved[252];
//	int Reserved[256];
}SVAC_EXT_INFOR_INTERNAL;


typedef struct
{
	unsigned char *pBuf;
	unsigned int  uBufLen;
	unsigned int  uSeekTypeFlag[8];
	unsigned int  reserved[4];
}SVAC_SEEK_INPUT_PARAM;

#define SEEK_SPS_MAX 4
typedef struct 
{
 	int						find_sps_flag;				//0-û�����µ�sps  >0-�ҵ��µ�sps�ĸ���.
#ifdef LINUX
	unsigned long long		sps_offset[SEEK_SPS_MAX];
#else
	unsigned __int64		sps_offset[SEEK_SPS_MAX];	//��find_sps_flag >0ʱ����ʾsps�����������е�ƫ������
														//��find_sps_flag==0ʱ�������塣
#endif
	SVAC_EXT_INFOR_INTERNAL inf;						//�����չ��Ϣ
} SVAC_SEEK_OUTPUT_PARAM;


typedef struct
{
	int  rsa_e;
	int  rsa_n;
	char aes_key[16];
}SVAC_AUTH_KEY;

typedef struct
{
	char *pBuf;
	int  uBufLen;
	int	 iLastFlag;
	int	 iOneframeFlag;
	int  reserved[4];
}SVAC_AUTH_INPUT_PARAM;


typedef struct 
{
	void*	pBitstream;		// �����׵�ַ
	int		nLength;		// ��������
	int		iLastFlag;		// pBuf�е������Ƿ�����Ƶ�����������, 0-��1-��
	int		iOneframeFlag;	// �������ͣ���ǵ�ǰ����������Ƿ����õ�һ֡�Ľ�β��0-��1-��
	int		nColorspace;	// ����������YUV��ʽ��0:400 1:420	2:422
} SVAC_DEC_INPUT_PARAM;

typedef struct 
{
	int		iPicFlag;		//  0: Frame, 1: Field
	int		iSvcOpenFlag;		// �Ƿ���svcģʽ
	int		iSvcDataFlag;		// �Ƿ��Ƿ��ѽ���svc
	int		iExtFlag;		// �Ƿ���SVAC��չ��Ϣ
	int		nWidth;			// ֡��(������)
	int		nHeight;		// ֡��(������)
	int		nWidth_El;		// ֡��(��ǿ��)
	int		nHeight_El;		// ֡��(��ǿ��)
	int		iAuthResFlag;	// ��4bit:�����㣬��4bit:��ǿ�㡣 0:success  1:error  2:no data  3:no res
//	int		nStrideY;		//Luma plane stride in pixel
//	int 	nStrideUV;		//Chroma plane stride in pixel
	SVAC_EXT_INFOR_INTERNAL *pSvacExtInfo;
	void* 	pY;				// �����y���������ַ
	void*	pU;				// �����u���������ַ
	void* 	pV;				// �����v���������ַ
	void* 	pY_SVC_EL;		// SVC��ǿ������y���������ַ
	void*	pU_SVC_EL;		// SVC��ǿ������u���������ַ
	void* 	pV_SVC_EL;		// SVC��ǿ������v���������ַ
} SVAC_DEC_OUTPUT_PARAM;

typedef struct 
{
	int		width;
	int		height;
	int		roi_flag;
    int		svc_flag;
	int		color_space;
	int		bit_depth_luma;
	int		bit_depth_chroma;
} SVAC_PREFETCH_PARAM;

#ifdef LINUX
extern int SVACDecInit();
extern char* SVACDecLibVer();
extern void* SVACDecOpen();
extern void* SVACDecOpen2(int thread_num);
extern void SVACDecClose(void *handle);
extern int SVACDecSetKey(void* handle, unsigned char* key);
extern int SVACPrefetchParam(unsigned char *pBuf, int iBufLen, SVAC_PREFETCH_PARAM *pPreParam);
extern int SVACDecFrame(void* hHandle, SVAC_DEC_INPUT_PARAM *deci, SVAC_DEC_OUTPUT_PARAM *deco);

extern void *SVACSeekOpen();
extern void SVACSeekClose(void *hseek);
extern int SVACSeekExtension(void *hseek, SVAC_SEEK_INPUT_PARAM *seeki, SVAC_SEEK_OUTPUT_PARAM *seeko);

extern void *SVACAuthOpen();
extern void SVACAuthClose(void *handle);
extern void SVACAuthSetKey(void *handle, SVAC_AUTH_KEY *param);
extern int SVACAuthDec(void *handle, SVAC_AUTH_INPUT_PARAM *authi);

#else

extern __declspec(dllexport) int SVACDecInit();
extern __declspec(dllexport) char* SVACDecLibVer();
extern __declspec(dllexport) void* SVACDecOpen();
extern __declspec(dllexport) void* SVACDecOpen2(int thread_num);
extern __declspec(dllexport) void SVACDecClose(void *handle);
extern __declspec(dllexport) int SVACDecSetKey(void* handle, unsigned char* key);
extern __declspec(dllexport) int SVACPrefetchParam(unsigned char *pBuf, int iBufLen, SVAC_PREFETCH_PARAM *pPreParam);

/* $Function		   :	SVAC_Dec_Decode
************************************************************************
** Argument			:	handle		- ���������
**					:	deci			- ��������������Ϣ
**					:	deco		- ����֡�����Ϣ
**					:
** Performance 		:
**					:
** Return			:	-1-DEC_ERROR
**					:    0-DEC_SUCCESS
**					:    1-DEC_NEED_MORE_BITS
**					:    2-DEC_NO_PICTURE
**					:    3-DEC_BUF_OVERFLOW
**					:
** Description		:	����һ֡
**					:   1�����뷵��DEC_SUCCESSʱ��˵���������һ֡���ݣ�
**					:   ����UINT8 *pBuf��ֵ���䣬UINT32 uBufLen��Ϊ0��
**					:   �������ñ�������ֱ������ֵ�Ƿ�DEC_SUCCESS��
**					:   2�����뷵��DEC_NEED_MORE_BITSʱ���������ñ�����, 
**					:   �������µ����ݺͳ��ȡ�
**					:   3�����뷵��DEC_NO_PICTUREʱ�����������
**					:   4�����뷵������ֵʱ������
**					:
** Modification		:
***********************************************************************/
extern __declspec(dllexport) int SVACDecFrame(void* hHandle, SVAC_DEC_INPUT_PARAM *deci, SVAC_DEC_OUTPUT_PARAM *deco);


extern __declspec(dllexport) void *SVACSeekOpen();
extern __declspec(dllexport) void SVACSeekClose(void *hseek);
extern __declspec(dllexport) int SVACSeekExtension(void *hseek, SVAC_SEEK_INPUT_PARAM *seeki, SVAC_SEEK_OUTPUT_PARAM *seeko);

extern __declspec(dllexport) void *SVACAuthOpen();
extern __declspec(dllexport) void SVACAuthClose(void *handle);
extern __declspec(dllexport) void SVACAuthSetKey(void *handle, SVAC_AUTH_KEY *param);
extern __declspec(dllexport) int SVACAuthDec(void *handle, SVAC_AUTH_INPUT_PARAM *authi);
#endif

#endif
