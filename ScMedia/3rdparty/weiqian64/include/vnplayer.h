#ifndef _PLAY_H
#define _PLAY_H

#define PLAY_API  __declspec(dllexport)

#define CALLMETHOD __stdcall
#define CALLBACK __stdcall

#define  FUNC_MAX_PORT 101              //最大播放通道数


//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100
//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 
//缓冲类型
#define BUF_VIDEO_SRC 1     //视频源缓冲        
#define BUF_AUDIO_SRC 2     //音频源缓冲
#define BUF_VIDEO_RENDER 3  //解码后视频数据缓冲
#define BUF_AUDIO_RENDER 4  //解码后音频数据缓冲

//错误类型
#define	PLAY_NOERROR					0              //没有错误；
#define PLAY_PARA_OVER				    1              //输入参数非法；
#define PLAY_ORDER_ERROR				2              //调用顺序不对；
#define PLAY_TIMER_ERROR				3              //多媒体时钟设置失败；
#define PLAY_DEC_VIDEO_ERROR			4	           //视频解码失败；
#define PLAY_DEC_AUDIO_ERROR			5	           //音频解码失败；
#define PLAY_ALLOC_MEMORY_ERROR		    6		       //分配内存失败；
#define PLAY_OPEN_FILE_ERROR			7			   //文件操作失败；
#define PLAY_CREATE_OBJ_ERROR		    8	           //创建线程事件等失败；
#define PLAY_CREATE_DDRAW_ERROR		    9		       //创建directDraw失败；
#define PLAY_CREATE_OFFSCREEN_ERROR	    10		       //创建后端缓存失败；
#define PLAY_BUF_OVER				    11	           //缓冲区满，输入流失败；
#define PLAY_CREATE_SOUND_ERROR		    12		       //创建音频设备失败；
#define PLAY_SET_VOLUME_ERROR		    13	           //设置音量失败；
#define PLAY_SUPPORT_FILE_ONLY		    14		       //只能在播放文件时才能使用此接口；
#define PLAY_SUPPORT_STREAM_ONLY		15		       //只能在播放流时才能使用此接口；
#define PLAY_SYS_NOT_SUPPORT			16		       //系统不支持，解码器只能工作在Pentium 3以上；
#define PLAY_FILEHEADER_UNKNOWN		    17		       //没有文件头；
#define PLAY_VERSION_INCORRECT		    18	           //解码器和编码器版本不对应；
#define PLAY_INIT_DECODER_ERROR		    19		       //初始化解码器失败；
#define PLAY_CHECK_FILE_ERROR		    20		       //文件太短或码流无法识别；
#define PLAY_INIT_TIMER_ERROR		    21		       //初始化多媒体时钟失败；
#define PLAY_BLT_ERROR				    22		       //位拷贝失败；
#define PLAY_UPDATE_ERROR               23			   //显示overlay失败；
#define PLAY_STATUS_ERROR               24             //播放状态错误；
#define PLAY_BUF_NOTENOUGH_ERROR        25             //缓冲区不足或未分配缓存；

//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

 //chenfeng20090512 -s
#define MAX_PLAYING_BUF_NUM (50)
#define MIN_PLAYING_BUF_NUM (1)
#define DEF_PLAYING_BUF_NUM (3)

 //chenfeng20090512 -e
 
//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100
#define T_CH2_AUDIO16	201  //双声道16位
#define T_CH2_AUDIO8	200  //双声道8位

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//系统支持的功能，用于按位表示系统功能
#define SUPPORT_DDRAW		1  //支持DIRECTDRAW；如果不支持，则播放器不能工作。
#define SUPPORT_BLT         2  //显卡支持BLT操作；如果不支持，则播放器不能工作
#define SUPPORT_BLTFOURCC   4  //显卡BLT支持颜色转换；
#define SUPPORT_BLTSHRINKX  8  //显卡BLT支持X轴缩小；
#define SUPPORT_BLTSHRINKY  16 //显卡BLT支持Y轴缩小；
#define SUPPORT_BLTSTRETCHX 32 //显卡BLT支持X轴放大；
#define SUPPORT_BLTSTRETCHY 64 //显卡BLT支持Y轴放大；
#define SUPPORT_SSE         128 //CPU支持SSE指令,Intel Pentium3以上支持SSE指令；
#define SUPPORT_MMX			256 //CPU支持MMX指令集。

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
	long nWidth;  //画面宽，单位像素。如果是音频数据则为0；
	long nHeight; //画面高。如果是音频数据则为0；
	long nStamp;  //时标信息，单位毫秒。
	long nType;   //数据类型，T_AUDIO16，T_RGB32， T_YV12，详见宏定义说明。
	long nFrameRate; //编码时产生的图像帧率。
}FRAME_INFO;

//音频解码回调的数据结构，音频数据格式为PCM。
typedef struct
{
	long SamplesPerSec ;//采样率 
	long BitsPerSample ;//每个采样需要的BIT数 
	long Timestamp; //时戳（单位：毫秒） 
	char * Buffer ;//数据缓冲区
	long Size ;//数据长度 
}AUDIO_FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

// added by ZWW for extern information2011/07/10
typedef struct 
{
	unsigned int   roi_infor;							//ROI 区域信息,保留
	unsigned short top;									//ROI 顶边坐标 [y_min]	
	unsigned short left;								//ROI 左边坐标 [x_min]
	unsigned short bot;									//ROI 底边坐标 [y_max]
	unsigned short right;								//ROI 右边坐标 [x_max]
}SVAC_ROI_INFO;

typedef struct 
{
	unsigned char  TsEnable;							//是否包含时间信息
    unsigned char  Ts_time_stamp_flag;					//
    unsigned char  Ts_ref_date_flag;
    unsigned short Ts_time_year;						//年
    unsigned char  Ts_time_month;						//月
    unsigned char  Ts_time_day;							//日
    unsigned char  Ts_time_hour;						//时	
    unsigned char  Ts_time_minute;						//分	
    unsigned char  Ts_time_second;						//秒
    unsigned char  Ts_time_sec_fractional;				
    unsigned char  SeEnable;							//是否包含监控信息
    unsigned char  Se_roi_extension_flag;				//是否包含ROI扩展信息
    unsigned char  Se_event_extension_flag;				//是否包含事件扩展信息
    unsigned char  Se_event_num[4+1];					//事件信息
    unsigned char  Se_alert_extension_flag;				//是否包含报警信息
    unsigned char  Se_vm_alert_extension_flag;			//是否包含vimico报警信息
    unsigned char  Se_alert_num;						//报警事件数目
    unsigned char  Se_alert_appendix_flag[16];			//报警事件信息
    unsigned char  Se_alert_appendix_length[16];		//报警事件长度		
	unsigned char  Svac_inf_position_idc;				//位置编号信息
	unsigned char  Svac_inf_camera_idc;					//摄像头编号信息
	unsigned char  FrameNum;							//帧数，i帧置0，p帧逐帧加1
	unsigned char  RoiEn;								//图像是否包含ROI信息	
	unsigned char  RoiNum;								//图像包含ROI数目
	unsigned char  RoiSkipMode;							//ROI背景跳过模式
	unsigned char  RoiSvcSkipMode;						//ROI_SVC背景跳过模式		
	SVAC_ROI_INFO  RoiRect[4];							//ROI信息，如SVC开启，代表基本层ROI矩形信息		
	SVAC_ROI_INFO  RoiSvcElRect[4];						//SVC增强层ROI矩形信息，SVC下有效
}SVAC_EXT_INFO;
// end added for extern information2011/07/10



//视频编码或封装格式 
typedef enum  
{
	MPEG_PS,//符合国标GB/T28181-2011的PS流（不含RTP头） 
	H264,   //H.264. 
	MPEG2, //MPEG2. 
	MPEG4,//MPEG4. 
	MJPEG, //Motion JPEG. 
	SVAC_VIDEO  //SVAC视频编码 
}VideoCodeFormat;


//视频编码后帧类型 
typedef enum  
{
	I, //I帧 
	P, //P帧 
	B, //B帧 
	PARAM_SET  //PARAM_SET指H264的SPS、PPS等参数集信息 
}VideoFrameType;

//视频编码数据结构（未解码的编码格式），或GB/T 28181规范要求的PS封装的混合视音频包。 
typedef struct 
{
	char * Buffer;//数据缓冲区 
	long Size ;//数据长度 
	VideoCodeFormat CodeFormat ;//编码类型 
	VideoFrameType Type ;//帧类型 
	long Timestamp ;//时戳（单位：毫秒） 
	long FrameRate ;//图像帧率（单位：帧/秒） 
	long Width ;//图像宽度（单位：像素） 
	long Height ;//图像高度（单位：像素） 

}CodedVideoFrameInfo ;


//音频编码格式 
typedef enum  
{
	VISS_G711_PCMA,
	//G.711 A-law (常用) 

	VISS_G711_PCMU, 
	//G.711 µ-law (美国、日本标准) 

	VISS_G723_1,
	//G.723.1. 

	VISS_G729,
	//G.729. 

	VISS_SVAC_AUDIO,
	//SVAC音频编码 

	VISS_AMR_NB,
	//AMR NB. 

	VISS_AAC  
	//Advanced Audio Coding. 
}AudioCodeFormat;


//音频编码数据结构（未解码的编码格式）。 
typedef struct  
{
	char * Buffer ;
	//数据缓冲区 

	long Size ;
	//数据长度 

	AudioCodeFormat CodeFormat ;
	//音频编码格式 

	long Timestamp ;
	//时戳（单位：毫秒） 

	long SamplesPerSec ;
	//采样率 

	long BitsPerSample ;
	//每个采样需要的BIT数 
}CodedAudioFrameInfo;

//以下为对外接口，供用户作二次开发调用
//以下两个是可以不需要调用的接口
PLAY_API BOOL CALLMETHOD ZX_PLAY_InitDDraw(HWND hWnd);
PLAY_API BOOL CALLMETHOD ZX_PLAY_RealeseDDraw();

PLAY_API BOOL CALLMETHOD ZX_PLAY_OpenFile(LONG nPort,LPSTR sFileName);
PLAY_API BOOL CALLMETHOD ZX_PLAY_CloseFile(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Play(LONG nPort, HWND hWnd);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Stop(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Pause(LONG nPort,DWORD nPause);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Fast(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Slow(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_OneByOne(LONG nPort);//网络回放单帧
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPlayPos(LONG nPort,float fRelativePos);
PLAY_API float CALLMETHOD ZX_PLAY_GetPlayPos(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetVolume(LONG nPort,WORD nVolume);
PLAY_API BOOL CALLMETHOD ZX_PLAY_StopSound();
PLAY_API BOOL CALLMETHOD ZX_PLAY_PlaySound(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_CloseStream(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetFrameBufferSize4InputData(LONG nPort, long nSeconds);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ReplayBufferedFrames(LONG nPort, long nAction);
PLAY_API int  CALLMETHOD ZX_PLAY_GetCaps();
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetFileTime(LONG nPort);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetPlayedTime(LONG nPort);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetPlayedFrames(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_Back(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_BackOne(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved), long nUser = 0);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetFileTotalFrames(LONG nPort);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetCurrentFrameRate(LONG nPort);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetPlayedTimeEx(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetCurrentFrameNum(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetFileHeadLength();
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetSdkVersion();
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetLastError(LONG nPort);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_RefreshPlay(LONG nPort);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_PlaySoundShare(LONG nPort);
PLAY_API BOOL  CALLMETHOD ZX_PLAY_StopSoundShare(LONG nPort);
PLAY_API LONG CALLMETHOD ZX_PLAY_GetStreamOpenMode(LONG nPort);
PLAY_API LONG CALLMETHOD ZX_PLAY_GetOverlayMode(LONG nPort);
PLAY_API COLORREF CALLMETHOD ZX_PLAY_GetColorKey(LONG nPort);
PLAY_API WORD CALLMETHOD ZX_PLAY_GetVolume(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetSourceBufferRemain(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ResetSourceBuffer(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBuf__stdcall)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ResetSourceBufFlag(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetDisplayBuf(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_OneByOneBack(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetFileRefCallBack(LONG nPort, void (CALLBACK *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAY_API BOOL CALLMETHOD ZX_PLAY_InitDDrawDevice();
PLAY_API void CALLMETHOD ZX_PLAY_ReleaseDDrawDevice();
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetDDrawDeviceTotalNums();
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,long *hhMonitor);
PLAY_API int   CALLMETHOD ZX_PLAY_GetCapsEx(DWORD nDDrawDeviceNum);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDisplayType(LONG nPort,LONG nType);
PLAY_API long CALLMETHOD ZX_PLAY_GetDisplayType(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
PLAY_API BOOL CALLMETHOD ZX_PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_CloseStreamEx(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

PLAY_API BOOL CALLMETHOD ZX_PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (CALLBACK * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetAudioCallBack(LONG nPort, void (CALLBACK * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort, long nUser),long nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetMDRange(LONG nPort,RECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold);
PLAY_API DWORD CALLMETHOD ZX_PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue);
PLAY_API BOOL CALLMETHOD ZX_PLAY_CatchPic(LONG nPort,char* sFileName);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetFileEndCallBack(LONG nPort, void (CALLBACK *pFileEnd)(DWORD nPort,DWORD nUser),DWORD nUser);
//dataType 0 是原始码流，1是AVI
PLAY_API BOOL CALLMETHOD ZX_PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType=0);
PLAY_API BOOL CALLMETHOD ZX_PLAY_StopDataRecord(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_AdjustFluency(LONG nPort, int level);
PLAY_API BOOL CALLMETHOD ZX_PLAY_ChangeRate(LONG nPort, int rate);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDemuxCallBack(LONG nPort, void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,void * pParam, long nReserved,long nUser), long nUser);
// added by ZWW 2012/02/06
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetSVCBasicCallBack(LONG nPort, void (CALLBACK* SVCBasicCBFun)(long nPort,char * pBuf,	long nSize,void * pParam, long nReserved,long nUser), long nUser);
#define HIK_CMD_GetTime 1
#define HIK_CMD_GetFileRate 2
PLAY_API BOOL CALLMETHOD ZX_PLAY_QueryInfo(LONG nPort , int cmdType, char* buf, int buflen, int* returnlen);

typedef void (WINAPI *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_OpenAudioRecord(pCallFunction pProc, long nBitsPerSample, long nSamplesPerSec, long nLength, long nReserved, long nUser);
PLAY_API BOOL CALLMETHOD ZX_PLAY_CloseAudioRecord();

//reserved 0 表I帧帧数据水印信息 1 表帧水印 2 表水印校验 3表智能分析帧
typedef int (__stdcall* GetWaterMarkInfoCallbackFunc)(char* buf, long key, long len, long reallen, long reserved, long nUser);	//水印信息获取函数
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, long nUser);

PLAY_API DWORD CALLMETHOD ZX_PLAY_CreateFile(LPSTR sFileName);
PLAY_API BOOL CALLMETHOD ZX_PLAY_DestroyFile(LONG nPort);
PLAY_API DWORD CALLMETHOD ZX_PLAY_CreateStream(DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_DestroyStream(LONG nPort);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPlayingBufNum(LONG nPort, int iBufNum); //chenfeng20090513 -


#define PLAYPARAM_SETSVC 10
#define PLAYPARAM_SETSVACKEY 11
#define PLAYPARAM_SETPASSWORD	12

typedef struct _VN_SVC_PARAM
{
	LONG type;
	HWND hwnd;
}VN_SVC_PARAM;

typedef struct _VN_SVAC_KEY_PARAM
{
	HWND hWnd;
	UINT nMsg;
	char key[1024];
}VN_SVAC_KEY_PARAM;


PLAY_API BOOL CALLMETHOD ZX_PLAY_SetParam(LONG nPort, LONG iType, VOID * pParam);

//type：
//0, 默认方式，有增强层显示增强层，没有则显示普通层
//1, 普通层叠加在增强层左上角（画中画）
//2, 普通层和增加层单独显示，hwnd为增强层的显示窗口句柄（双窗口）
//3, 只显示基本层
PLAY_API BOOL CALLMETHOD ZX_PLAY_SetSvc(LONG nPort, LONG type, HWND hwnd);
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetExtInfo(LONG nPort, BOOL* pbSVC, int* piExt, SVAC_EXT_INFO *pSVACExData);

// added by ZWW 2012/02/17 for time extension based seek 
typedef struct _TimeExtInfo{
    unsigned short  Ts_time_year;				   //年
    unsigned char  Ts_time_month;				   //月
    unsigned char  Ts_time_day;				       //日
    unsigned char  Ts_time_hour;				   //时	
    unsigned char  Ts_time_minute;				   //分	
    unsigned char  Ts_time_second;				   //秒
    unsigned char  Ts_time_sec_fractional;			
} TimeExtInfo;
PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileByTime(LONG nPort, TimeExtInfo timeInfo, float* pPos, unsigned int* pFrameNum);
//获取下一扩展帧
PLAY_API BOOL CALLMETHOD ZX_PLAY_GetNextExtFrame(LONG nPort, unsigned int* pTime, unsigned int* pFrameNum);
//PLAY_API BOOL CALLMETHOD ZX_PLAY_GetFrameNumByTime(LONG nPort, TimeExtInfo timeInfo, float* pPos, unsigned int* pFrameNum);

typedef struct _TimePosInfo{
	unsigned short  Ts_time_year;				   //年
	unsigned char  Ts_time_month;				   //月
	unsigned char  Ts_time_day;				       //日
	unsigned char  Ts_time_hour;				   //时	
	unsigned char  Ts_time_minute;				   //分	
	unsigned char  Ts_time_second;				   //秒
	unsigned char  Ts_time_sec_fractional;	

	float Ts_time_pos;
} TimePosInfo;


typedef enum {
	NO_ALARM = 0,
	INPUT_ALARM1 = 1,		//第一路输入报警
	INPUT_ALARM2,			//第二路输入报警
	INPUT_ALARM3,			//第三路输入报警
	INPUT_ALARM4,			//第四路输入报警
	BLIND_ALARM,			//视频遮挡报警
	ROI_ALARM,				//roi报警
	ID_CARD				//roi报警
} ALARM_TYPE;

typedef struct _AlarmInfo{
	int m_alarm_type;
	TimeExtInfo m_alarm_begin_time;
	TimeExtInfo m_alarm_end_time;
} AlarmInfo;


typedef struct _IDInfo{
	char m_id[24];
	TimeExtInfo m_begin_time;
	TimeExtInfo m_end_time;
} IDInfo;


PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileTimePosInfo(LONG nPort, TimePosInfo* pTimePosInfo, int MaxSize, int* pSize);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileAlarmInfo(LONG nPort, AlarmInfo* pAlarmInfo, int MaxAlarmSize, int* pAlarmSize,
													  TimePosInfo* pTimePosInfo, int MaxTimeSize, int* pTimeSize);
PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileIDInfo(LONG nPort, 
												IDInfo* pIDInfo, 
												int MaxIDSize, 
												int* pIDSize,
												TimePosInfo* pTimePosInfo,
												int MaxTimeSize, 
												int* pTimeSize);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetNeedDecodePasswordCallbackFun(long nPort, 
																  void(CALLBACK* pNeedDecodePasswordFun)(long nPort, long nErrorCode, void* pUser), 
																  void* pUser);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDecodePassword(long nPort, char* sPassword);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetExtensionInfoCallbackFun(long nPort, 
															 void (CALLBACK* pExtensionInfoFun)(long nPort, LPCTSTR sExtensionInfo, void* pUser),
															 void* pUser);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetROI(long nPort,long type);

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetBytesPS(long nPort, long* TotalBytesPS, long* BlBytesPS);

PLAY_API BOOL CALLMETHOD ZX_PLAY_ShowTime(long nPort, bool bShow);

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetFileTotalTime(long nPort, long* pTotalTime);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPlayTimePos(long nPort, long nTimePos);

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetPlayTimePos(long nPort, long* pTimePos);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPlayAbsTimePos(long nPort, char* sTimePos );

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetPSCallBack(LONG nPort,
											   void (CALLBACK* PSCBFun)(long nPort,CodedVideoFrameInfo* pFrame, void* pUser), 
											   void* pUser);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetDecCallBackEx(LONG nPort,
												  void (CALLBACK* VideoDecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2),
												  void (CALLBACK* AudioDecCBFun)(long nPort,AUDIO_FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
												  );

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetPort(LONG* nPort);

PLAY_API BOOL CALLMETHOD ZX_PLAY_FreePort(LONG nPort);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileAlarmInfoByFile(char* pFileName,
														 AlarmInfo* pAlarmInfo, 
														 int MaxAlarmSize, 
														 int* pAlarmSize,
														 TimePosInfo* pTimePosInfo, 
														 int MaxTimeSize, 
														 int* pTimeSize);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SeekFileIDInfoByFile(char* pFileName,
													  IDInfo* pIDInfo, 
													  int MaxIDSize, 
													  int* pIDSize,
													  TimePosInfo* pTimePosInfo,
													  int MaxTimeSize, 
													  int* pTimeSize);

PLAY_API BOOL CALLMETHOD ZX_PLAY_RecordScissor(LPCTSTR  sSourceFileName,  
											   LPCTSTR  sDestFileName,  
											   long  iWriteMethod,  
											   long  iBeginTime,  
											   long  iDuration);

PLAY_API BOOL CALLMETHOD ZX_PLAY_SetRawCodeDataCallback(LONG nPort,
														void(CALLBACK *pVideoCallback)(long nPort, CodedVideoFrameInfo *pVideoFrame, void *pUser)  ,  
														void(CALLBACK *pAudioCallback)(long nPort, CodedAudioFrameInfo *pAudioFrame, void *pUser)  ,  
														void *  pUser );

PLAY_API BOOL CALLMETHOD ZX_PLAY_ShowLogo(LONG nPort,BOOL bshow);

PLAY_API BOOL CALLMETHOD ZX_PLAY_GetPlayAbsTimePos(long nPort, char* sTimePos );

#endif
