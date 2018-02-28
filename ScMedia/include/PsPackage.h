#pragma once
/*
* �� ����� 
* 
*/
#define BYTE_ALIGNMENT       8       //�ֽڶ���
#define STREAM_TYPE_VIDEO_H264 0x1B
#define STREAM_TYPE_AUDIO_G711 0x90
#define OPTIONAL_FIELDS_ONLY_PTS (1 << 7) 
#define SPLIT_PACKET_LENGTH 60000 

#define OPTIONAL_FIELDS_PTS_DTS (1 << 6) 

#define OPTIONAL_FIELDS_ESCR (1 << 5)

#define OPTIONAL_FIELDS_ES_RATE (1 << 4)

#define OPTIONAL_FIELDS_DSM_TRICK_MODE (1 << 3)

#define OPTIONAL_FIELDS_ADDITIONAL_COPY_INFO (1 << 2)

#define OPTIONAL_FIELDS_PREVIOUS_PES_CRC (1 << 1)

#define OPTIONAL_FIELDS_PES_EXTENSION (1 << 0)
//Ps header flag;
#define PS_HEADER_FLAG_LEN 4
// ps header 16 bytes
#define PS_HEADER_FLAG (0xba010000)
#define PS_HEADER_LEN  16
#define PS_SYS_FLAG    (0xbb010000)
#define PS_SYS_LEN     18
#define PS_PSM_FLAG    (0xbc010000)
#define PS_PSM_LEN     24
#define PS_PES_HEADER_FLAG (0x01000000)
//���Ȳ�ȷ��,���ݲ�������
#define PS_PES_HEADER_LEN 0

typedef struct _StPSInfo
{
	unsigned long long u64SCR;
	unsigned int u32MuxRate;
	int s32MediaType;          //ý�����͡�0x01��ƵI֡��0x02��ƵP֡��0x08��ƵB֡��0x10��ƵG711
	int s32Flag;                //0x01��PSMͷ��־λ��0x02��SYSͷ��־λ
}StPSInfo;//��װPSʱ��Ҫ����Ϣ

typedef struct _StPESInfo
{
	unsigned char u8StreamID;
	unsigned int u32Flag;
	unsigned long long u64Pts;
	unsigned long long u64Dts;
	unsigned long long u64ESCRBase;
	unsigned short u16ESCRExtention;
	unsigned int u32ESRate;
}StPESInfo;//��װPESʱ��Ҫ����Ϣ
typedef struct _StMediaInfo
{
	int s32MediaType;		   //ý�����͡�0x01��ƵI֡��0x02��ƵP֡��0x08��ƵB֡��0x10��ƵG711
	unsigned int u32TimeStamp; //ʱ���
	//��Ƶ��ز���
	int s32VideoWidth;         //��Ƶ���
	int s32VideoHeight;        //��Ƶ�߶�
	int s32VideoFPS;           //��Ƶ֡��
	//��Ƶ��ز���
	int s32AudioSample;        //��Ƶ������
	int s32AudioRate;          //��Ƶ����
	//�ʳ�����
	int s32LaunchFlag;          //�ʳ�����ı�־��Ϣ��0x01��ETI_DVR_FILE_HEADͷ
}StMediaInfo;//ȥ��ͷ��Ϣ�����еõ���һЩ����ý�����ݵ���Ϣ��������ṹ�����»��ܣ��Ժ�Ĵ�����̿����õõ�

#define IN 
#define OUT

namespace SimpleCpp{
	class CBuffer;
}
using namespace SimpleCpp;
typedef enum _eFrameType
{
	eFT_I =0,
	eFT_P = 1,
	eFT_B = 2,
}eFrameType;

#define MAX_PS_SIZE (256*1024)
class CPsPackage
{
public:
	CPsPackage(int nW, int nH, int nFPS, int nBitRate);
	virtual ~CPsPackage(void);
	
	//�����ⳤ�ȵ� h264 ���ݴ��,�ڲ��Զ���֡
	int Package(unsigned char *pH264, int nLen, unsigned char *pPsStream, int &nLenOut);
	int Package(unsigned char *pH264, int nLen, CBuffer *pBufferPsPkg);
	//��һ֡ h264 ���
	//nFrameType: eFT_I, eFT_P
	int PackageFrame(unsigned char *pH264Frame, int nLen, int nFrame,CBuffer *pBufferPsPkg);
	//��ps �����, ���Ϊ��׼ h264��.
	//pPsStream, ����, nLen: ����
	//pH264Stream: �������.��Ҫ�û�������㹻�Ŀռ�.һ�� 512kB�㹻. 
	int UnPackage(unsigned char *pPsStream, int nLen, unsigned char *pH264Stream, int &nLenOut);
	int UnPackage(unsigned char *pPsStream, int nLen, CBuffer *pBufferH264);
protected:
	/*���� h264 ��֡
	* @ pBufferH264  : ����� h264 ��
	* @ pBufferFrame :    ������һ�� h264
	* @ return       : passed pos, 
	* @ ÿ�ε��� ֻ�ܽ���һ֡���ݣ���Ҫ��������, 5 7 8 ��Ϊ I
	*/
	int ParseH264Frame(CBuffer *pBufferH264, CBuffer *pBufferFrame, int &nFrameType);
	//
	int PackageH2642Ps(CBuffer *pBufferFrame, CBuffer *pBufferPsPkg, int nFrameType);
	// nFrameType: eFT_I, eFT_P
	int PackageH2642Ps(unsigned char *pBufferFrame, int nLen,int nFrameType, CBuffer *pBufferPsPkg);
	//
	/*
	* ��ʵ������
		*
		* |дPSͷ|-->|I֡ǰ��PSMͷ|-->|Media2PESStream|-->|�ְ�����|-->|Media2PESPacket|
		*
		* ���ܣ���������һ֡ý�����ݷ�װ��һ��PS��
		* ����1��pMediaBuf        [in]    һ֡ý������
		* ����2��s32MediaBufSize  [in]    һ֡ý�����ݵĳ���
		* ����3��pstPsInfo        [in]    ��װPS��Ҫ����Ϣ
		* ����4��pPSBuf           [out]   ��װ���PS��
		* ����5��pPSBufSize       [out]   ��װ��PS���ĳ���
		* ����ֵ���ɹ�����0��ʧ�ܷ���-1
		*/
	int Media2PSPacket(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPSInfo *pstPsInfo,
		OUT unsigned char *pPSBuf, OUT int *pPSBufSize);

	/*
	* ����	:���մ���ֽ���д16λ����
	* ����1	��pBuf		��out��	    Ҫд���buf
	* ����2	��u16Value	��in��		С���ֽ����16λ����
	* ����ֵ	���ɹ����� 0�� ʧ�ܷ��� -1
	*/
	unsigned short Write16bit(OUT unsigned char *pBuf, IN unsigned short u16Value);

	/*
	* ����	:���մ���ֽ���д32λ����
	* ����1	��pBuf		��out��	    Ҫд���buf
	* ����2	��u32Value	��in��		С���ֽ����32λ����
	* ����ֵ	���ɹ����� 0�� ʧ�ܷ��� -1
	*/
	unsigned short Write32bit(OUT unsigned char *pBuf, IN unsigned int u32Value);
	/*
	* ���ܣ�дsystem_clock_reference_base 6�ֽ�
	* ����1��pBuf		��out��	�ռ�ָ��
	* ����2��u64SCR		��in��	SCRֵ
	* ����ֵ���ɹ�����0��ʧ�ܷ���-1
	*/
	int WriteSCR(OUT unsigned char *pBuf, IN unsigned long long u64SCR);
	/*
	*���ܣ�дsystem_header�ֶ� 
	* ����1��pBuf 			��out��	�����������ɵ�ϵͳͷ(SystemHeader�ֶ�) 
	* ����2��pu16BufLen		��out��	ϵͳͷ�ĳ��� 
	* ����3��u32SysHeadFlag	��in��	ϵͳͷ�ı�־λ 
	* ����4��u16HeaderLength	��in��	header_length��ֵ 
	* ����5��u32RateBound		��in��	rate_bound��ֵ 
	* ����6��u8AudioBound		��in��	audio_bound��ֵ 
	* ����7��u8Videobound		��in��	video_bound��ֵ
	* ����8��u8StreamID		��in��	stream_id��ֵ 
	* ����8��u8AudioBound		��in��	P-STD_buffer_size_bound��ֵ 
	* ����ֵ���ɹ�����0�� ʧ�ܷ���-1 
	*/
	int WriteSystemHeader(unsigned char *pBuf, unsigned short *pu16bufLen, unsigned int u32SysHeadFlag, \
		unsigned short u16HeaderLength, unsigned int u32RateBound, unsigned char u8AudioBound, \
		unsigned char u8Videobound, unsigned char u8StreamID, unsigned short u16PSTDBufSize);


	/*
	* ���ܣ�����program_stream_map��Ŀ��ӳ��.Ŀǰ��������Ŀ��������(һ��H264����Ƶ��һ��G711����Ƶ)���Ժ���Ҫ��չ�ɿ����õġ�
	* ����1��u32VideoType  ��in��       ��Ƶ����
	* ����2��u32AudioType  ��in��       ��Ƶ����
	* ����3��pBuf          ��out��      �ռ�ָ��
	* ����4��u32BufSize	   ��out��      ���ɵ�PSM�ĳ���
	* ����ֵ���ɹ�����0��ʧ�ܷ���-1
	*/
	int CreatePSM(IN unsigned int u32VideoType, IN unsigned int u32AudioType, OUT unsigned char *pBuf, OUT unsigned int *pBufSize);
	/*
	* ���ܣ���������ý�����ݷ�װ��PES����(���ý�����ݳ��ȴ���һ��PES����Ҫ�󣬻���зְ�����
	*      ��ʱһ֡ý�����ݻ᷵�ض��PES����ɵ�PES��)
	* ����1��pMediaBuf        [in]    һ֡ý������(��������Ƶ��������Ƶ)
	* ����2��s32MediaBufSize  [in]    һ֡ý�����ݵĳ���
	* ����3��pstPesInfo       [in]    ��װPES��Ҫ����Ϣ
	* ����4��pPESBuf          [out]   ��װ���PES��
	* ����5��pPESBufSize      [out]   ��װ��PES���ĳ���
	* ����ֵ���ɹ�����0��ʧ�ܷ���-1
	*/
	int Media2PESStream(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPESInfo *pstPesInfo, \
		OUT unsigned char *pPESBuf, OUT int *pPESBufSize);
	/*
	* ���ܣ����ְ����ý������(��ʱ��ý�����ݲ�һ��ʱһ֡������ʱһ֡��ɵĶ������)��װ��PES����
	* ����1��pMediaBuf        [in]    �ְ����ý������
	* ����2��s32MediaBufSize  [in]    �ְ���ý�����ݵĳ���
	* ����3��pstPesInfo       [in]    ��װPES��Ҫ����Ϣ
	* ����4��pPESBuf          [out]   ��װ���PES��
	* ����5��pPESBufSize      [out]   ��װ��PES���ĳ���
	* ����ֵ���ɹ�����0��ʧ�ܷ���-1
	*/
	int Media2PESPacket(IN unsigned char *pMediaBuf, IN int s32MediaBufSize, IN StPESInfo *pstPesInfo, \
		OUT unsigned char *pPESBuf, OUT int *pPESBufSize);

	/*
	* ���ܣ�����PES��ͷ��PES_header_data_length�ֶεĳ���
	* ����1��pstPesInfo       [in]    ��װPES��Ҫ����Ϣ
	* ����ֵ���ɹ�����PES_header_data_length�ֶεĳ��ȣ�ʧ�ܷ���-1
	*/
	int CalculatePESHeaderDataLength(IN StPESInfo *pstPesInfo);
	/*
	* ����	����64λ��ʱ�������PES��Э��Ҫ��д������Ŀռ�
	* ����1	��pBuf			��out��	    Ҫд���buf
	* ����2	��u8ID			��in��		ʱ���ID��ȡֵΪ0x01,0x02,0x03.��ͬ��ȡֵ��Э��дʱ�������
	* ����3	��u64TimeStamp	��in��		64λ��ʾ��ʱ���
	* ����ֵ	���ɹ����� 0�� ʧ�ܷ��� -1
	*/
	unsigned short WriteTimeStamp(OUT unsigned char *pBuf, IN unsigned char u8ID, IN unsigned long long u64TimeStamp);

protected:
	CBuffer *m_pBufferH264;

	int m_nTimeStamp;
	int m_nW;
	int m_nH;
	int m_nFPS;
	int m_nBitRate;
};
