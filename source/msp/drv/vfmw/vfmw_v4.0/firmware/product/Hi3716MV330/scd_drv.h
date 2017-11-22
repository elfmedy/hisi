
#ifndef __SCD_DRV_H__
#define __SCD_DRV_H__

#include "basedef.h"
#include "mem_manage.h"
#include "vfmw.h"

#define SCDDRV_OK       (0)
#define SCDDRV_ERR      (-1)

#ifdef CFG_SCD_BUF
#define SCD_MSG_BUFFER  (CFG_SCD_BUF)
#else
#define SCD_MSG_BUFFER  (700 * 1024)
#endif

#define  WR_SCDREG(reg, dat)                          \
    do{                                       \
        MEM_WritePhyWord((s_RegPhyBaseAddr + reg),(dat));                   \
    }while(0)

#define  RD_SCDREG(reg)    MEM_ReadPhyWord((SCD_REG_PHY_ADDR + reg))

typedef enum
{
    INIT = 0,
    WRITE_DOWN_MSG = 1,
    IN_ISR = 2,
    SEEK_PTS = 3
} PUSH_RAW_OVER_STATE;

typedef enum
{
    FMW_OK = 0,
    FMW_ERR_PARAM = -1,
    FMW_ERR_NOMEM = -2,
    FMW_ERR_NOTRDY = -3,
    FMW_ERR_BUSY  = -4,
    FMW_ERR_RAWNULL = -5,
    FMW_ERR_SEGFULL = -6,
    FMW_ERR_SCD = -7
} FMW_RETVAL_E;

typedef enum
{
    SCDDRV_SLEEP_STAGE_NONE = 0,      // δ����
    SCDDRV_SLEEP_STAGE_PREPARE,       // �յ������������δ�������
    SCDDRV_SLEEP_STAGE_SLEEP          // ������
} SCDDRV_SLEEP_STAGE_E;

/* control registers */
#if 1
#define  REG_SCD_START        0x800
#define  REG_LIST_ADDRESS     0x804
#define  REG_UP_ADDRESS       0x808
#define  REG_UP_LEN           0x80c
#define  REG_BUFFER_FIRST     0x810
#define  REG_BUFFER_LAST      0x814
#define  REG_BUFFER_INI       0x818
#define  REG_SCD_INT_MASK     0x81c
#define  REG_SCD_PROTOCOL     0x820
#define  REG_SCD_INI_CLR      0x824
/* state registers */
#define  REG_SCD_OVER         0x840
//#define  REG_SCD_INT          0x844

#define REG_SCD_PREVIOUS_BYTE_MSB 0x844

#define  REG_SCD_NUM          0x84c
#define  REG_ROLL_ADDR        0x850
#define  REG_SRC_EATEN        0x854

// MV330 new items

#define REG_SEG_BUFFER_OFFSET 0x858
#define REG_SEG_NEXT_ADDR     0x85c

#else
#define  REG_SCD_START        0x000
#define  REG_LIST_ADDRESS     0x004
#define  REG_UP_ADDRESS       0x008
#define  REG_UP_LEN           0x00c
#define  REG_BUFFER_FIRST     0x010
#define  REG_BUFFER_LAST      0x014
#define  REG_BUFFER_INI       0x018
#define  REG_SCD_INT_MASK     0x01c
#define  REG_SCD_PROTOCOL     0x020
#define  REG_SCD_INI_CLR      0x024
/* state registers */
#define  REG_SCD_OVER         0x040
#define  REG_SCD_INT          0x044
#define  REG_SCD_NUM          0x04c
#define  REG_ROLL_ADDR        0x050
#define  REG_SRC_EATEN        0x054
#endif
//add by l00225186 2013-03-21 3716cv200
#define  REG_DSP_SPS_MSG_ADDRESS      0x828
#define  REG_DSP_PPS_MSG_ADDRESS      0x82c
#define  REG_DVM_MSG_ADDRESS           0x830
#define  REG_SED_TOP_ADDRESS           0x834
#define  REG_CA_MN_ADDRESS             0x838
//end add

// MV330 new items
#define REG_SCD_PREVIOUS_BYTE_LSB 0x83c

#define  REG_AVS_FLAG       0x0000
#define  REG_EMAR_ID        0x0004
#define  REG_VDH_SELRST        0x0008
#define  REG_VDH_ARBIT_CTRL_STATE             0X0010
#define  REG_VDH_CK_GT       0x000c
#define  REG_DSP_WATCH_DOG             0X0018
/*######################################################
       macro & constants
 ######################################################*/
// ʵ��״̬
#define SM_INST_MODE_IDLE   0
#define SM_INST_MODE_WORK   1
#define SM_INST_MODE_WAIT   2

// ���޳���
#ifdef CFG_MAX_RAW_NUM
#define MAX_STREAM_RAW_NUM  CFG_MAX_RAW_NUM
#else
#define MAX_STREAM_RAW_NUM  (1024)   ///?????? for test
#endif
#ifdef CFG_MAX_SEG_NUM
#define MAX_STREAM_SEG_NUM  CFG_MAX_SEG_NUM
#else
#define MAX_STREAM_SEG_NUM  (1024 + 128)
#endif
#define MIN_STREAM_SEG_NUM      4//��С����SCD����Ϣ�صĸ���
#define SM_MAX_SMID             MAX_CHAN_NUM
#define SM_SCD_UP_INFO_NUM      2
#ifdef SCD_MP4_SLICE_ENABLE
#define MAX_SM_SCD_UP_INFO_NUM  3  //MPEG4������Ϣ��ʹ��3��word������Э��ʹ��2��word��ȡ����
#else
#define MAX_SM_SCD_UP_INFO_NUM  SM_SCD_UP_INFO_NUM
#endif
#define SM_MAX_DOWNMSG_SIZE     (3 * MAX_STREAM_RAW_NUM * sizeof(SINT32))
#define SM_MAX_UPMSG_SIZE       (MAX_SM_SCD_UP_INFO_NUM * MAX_STREAM_SEG_NUM * sizeof(SINT32))

//add by l00225186 2013-03-22 3716cv200
#define DSP_SPS_MSG_SIZE    (32*8*4)
#define DSP_PPS_MSG_SIZE    (256*8*4)
#define DVM_SIZE             (2*64*4)
#define DSP_SED_TOP_SIZE    (64*4*1088)
#define CA_MN_SIZE           (64*4*1088)
//end add

#define SM_SEGWASTE_BUF_SIZE  64     //Segʣ��ռ��˷ѵĴ�С

//#define MIN_BTM_SEG_LEN  (2*1024)  // Ҫ��WORD������, �����������Ƶ�,������FPGA_SCD_SEG_BLANK_AHB_LEN
#define MIN_TOP_SEG_LEN  (1 * 1024)    // Ҫ��WORD�����������ܽ�ð��
#define SM_H263_THRESHOLD_NUM 30     //�������ٸ�H263ͷ���ֺ�����H263ģʽ

#define SM_RAW_DISCARD_SIZE    (1024 * 1024)

#ifdef ENV_ARMLINUX_KERNEL
#define WAIT_SEG_REL_MAX_TIME   1000
#elif defined(ENV_WIN32)
#define WAIT_SEG_REL_MAX_TIME   500
#else
#define WAIT_SEG_REL_MAX_TIME   100000
#endif

#ifdef ENV_ARMLINUX_KERNEL
#define WAIT_SCD_RDY_MAX_TIME   1000
#elif defined(ENV_WIN32)
#define WAIT_SCD_RDY_MAX_TIME   2000
#else
#define WAIT_SCD_RDY_MAX_TIME   2000
#endif

#define SM_VIDOBJLAY_START_CODE        0x00000120
#define SM_VOP_START_CODE              0x000001b6
#define SM_SHORT_VIDEO_START_CODE      0x00008000

#define SMSEG_STATE_INVALID   0
#define SMSEG_STATE_FRESH     1
#define SMSEG_STATE_READOUT   2

#define SMSEG_IS_READ( seg )     (((seg).SegState == SMSEG_STATE_READOUT) ? 1 : 0)
#define SMSEG_IS_RELEASED( seg ) (((seg).SegState == SMSEG_STATE_INVALID) ? 1 : 0)
#define SMSEG_IS_FRESH( seg )    (((seg).SegState == SMSEG_STATE_FRESH) ? 1 : 0)

#define SMSEG_SET_ISREAD( seg )                       \
    do{                                     \
        (seg).SegState = SMSEG_STATE_READOUT;                             \
    } while (0)

#define SMSEG_SET_ISRELEASED( seg )                     \
    do{                                     \
        (seg).SegState = SMSEG_STATE_INVALID;                             \
    } while (0)

#define SMSEG_SET_ISFRESH( seg )                      \
    do{                                     \
        (seg).SegState = SMSEG_STATE_FRESH;                             \
    } while (0)

#define FMW_ASSERT( cond )                          \
    do{                                     \
        if( !(cond) )                             \
        {                                   \
            return;                               \
        }                                   \
    } while (0)

#define FMW_ASSERT_RET( cond, ret )                     \
    do{                                     \
        if( !(cond) )                             \
        {                                   \
            return (ret);                           \
        }                                   \
    } while (0)

#define SMSEG_PHY2VIR( SegArrayPtr, phy, vir )                \
    do{                                     \
        (vir) = SegArrayPtr->pSegBufVirAddr+((phy)-SegArrayPtr->SegBufPhyAddr); \
    } while (0)

#define SM_CHECK_VALUE(Val,MinValue,MaxValue,RetAction) \
    do \
    {\
        if (((Val) < (MinValue)) || ((Val) > (MaxValue)))\
        {\
            RetAction;\
        }\
    }while(0)

/*######################################################
       struct defs.
 ######################################################*/
typedef struct
{
    STREAM_DATA_S RawPacket[MAX_STREAM_RAW_NUM];
    SINT32      Head;
    SINT32      Tail;
    SINT32      History;
    SINT32      FirstPacketOffset;
    SINT32      CurShowIndex;
    SINT32      RawTotalSize;
} RAW_ARRAY_S;

typedef struct
{
    SINT8    ScdIntMask;
    SINT8    SliceCheckFlag;
    SINT8    ScdStart;
    UINT32   DownMsgPhyAddr;
    UINT32   *pDownMsgVirAddr;
    UINT32   UpMsgPhyAddr;
    UINT32   *pUpMsgVirAddr;
    UINT32   UpLen;
    UINT32   BufferFirst;
    UINT32   BufferLast;
    UINT32   BufferIni;
    SINT32   ScdProtocol;
    SINT32   ScdIniClr;
    SINT32   ScdLowdlyEnable;
    SINT32   reg_avs_flag;
} SM_CTRLREG_S;

typedef struct
{
    SINT32  Avs_Flag;
    SINT32  EMAR_ID;
    SINT32  VDH_SEL_RST_EN;
} GLB_CTRLREG_S;

typedef struct
{
    SINT32 Scdover;
    SINT32 ScdInt;
    SINT32 ShortScdNum;
    SINT32 StartCodeNum;
    SINT32 ScdRollAddr;
    SINT32 SrcEaten;
    UINT32 UpMsgLenInWord;
    UINT32 seg_next_addr;
} SM_STATEREG_S;

/* MEPG4 ���е���Ч������Ϣ */
typedef struct
{
    USIGN  IsShStreamFlag:        1;
    USIGN  SliceFlag:             1;
    USIGN  IsShortHeader:         1;
    USIGN  StartCodeBitOffset:    4;
    USIGN  StartCodeLength:       4;
    USIGN  Reserved:              21;
} MP4_SCD_UPMSG;

typedef struct
{
    UINT8     *VirAddr;
    SINT8     SegState;
    UINT8     IsLastSeg;
    UINT8     IsStreamEnd;
    UINT8     DspCheckPicOverFlag;
    UINT32    PhyAddr;
    UINT32    LenInByte;
    SINT32    StreamID;
    UINT64    Pts;
    UINT64    RawPts;
    UINT64    Usertag;
    UINT64    DispTime;
    UINT32    DispEnableFlag;
    UINT32    DispFrameDistance;
    UINT32    DistanceBeforeFirstFrame;
    UINT32    GopNum;
    /* MEPG4 ���е���Ч������Ϣ */
    MP4_SCD_UPMSG stMp4UpMsg;
} STREAM_SEG_S;

/********************************************************************************

RawPacket ԭʼ������Ϣ�ļ�¼�ռ䣬���ɼ�¼MAX_RAW_PACKET_NUM������������Ϣ��
Head    ��һ����Ч��¼��λ��
Tail    ���һ����Ч��¼��λ��
SegBufPhyAddr ����Ƭ�λ�����������ַ
pSegBufVirAddr  ����Ƭ�λ����������ַ
SegBufSize    ����Ƭ�λ�������С����λ���ֽ�
SegBufReadAddr  ����Ƭ�λ������Ķ���ַ
SegBufWriteAddr ����Ƭ�λ�������д��ַ
*********************************************************************************/
typedef struct
{
    UINT8         *pSegBufVirAddr;
    STREAM_SEG_S  StreamSeg[MAX_STREAM_SEG_NUM];
    UINT32        Head;
    UINT32        Tail;
    UINT32        History;
    UINT32        Current;
    UINT32        SegBufPhyAddr;
    UINT32        SegBufSize;
    UINT32        SegBufReadAddr;
    UINT32        SegBufWriteAddr;

    UINT32        SegTotalSize;    /* SegTotalSize:  Insert��, Release�� */
    UINT32        SegFreshSize;    /* SegFreshSize:  Insert��, Read�� */
    UINT32        SegFreshNum;
} SEG_ARRAY_S;


/********************************************************************************
Mode  ָ�����ú�SMʵ���Ĺ���ģʽ��
        0���ǹ���ģʽ
        1������ģʽ
        ���Mode��0�����ⲿģ��ϣ�����SMʵ��ֹͣ���������������ֻ��رմ�ʵ����������Ա��ȡֵ�����ԡ�
Priority    ���ȼ�
            ���ȼ�ͨ����һ�����������������ֵԽ�����ȼ�Խ�ߡ�
            0����"��Ȩ��"���������ȼ����κ�ʱ�򶼲��ᱻ���ȡ�
VidStd  VID_STD_E ��ƵЭ�����͡�������ƵЭ��Ķ����ԣ��������зֺ͹����п��ܴ�����Э����صĲ������������ָ��Э�����͡�
DownMsgAddr ������Ϣ������������������ַ
DownMsgSize ������Ϣ�Ĵ�С���ֽ�����
UpMsgAddr   ������Ϣ����ʼ���ַ������������ַ
UpMsgSize   ������Ϣ�Ĵ�С���ֽ�����
SegBufAddr  ������������������ַ������������д�ŵ��Ǳ�SCD����������Чģ�飩�и�õ���������������ַ��Ϊ������ַ�������ַ����Ϊ����ӦĳЩ����ϵͳ������Linux�����ص㣬����������ϵͳ�У������ַ��������ַ���ó�ͬһ��ֵ���ɡ�
SegBufSize  �������Ĵ�С�����ֽ�Ϊ��λ��
*********************************************************************************/
typedef struct
{
    UINT8        *pBufVirAddr;
    UINT8         Priority;
    VID_STD_E     VidStd;
    UINT32        BufPhyAddr;
    UINT32        BufSize;
    UINT32        RegPhyBaseAddr;
    STD_EXTENSION_U    StdExt;        /*��չ��Ϣ��VC1��ص��������Ƿ�ΪAP �Ͱ汾��Ϣ*/
    SINT32        ScdLowdlyEnable;          /* 0: ���ӳ�δʹ��; 1: ���ӳ�ʹ�� */
    SINT32        ScdLowBufEnable;          /* 0: �ͻ���δʹ��; 1: �ͻ���ʹ�� */
} SM_CFG_S;


typedef struct
{
    UINT8  *pSegBufVirAddr;
    UINT32 DownMsgPhyAddr;
    UINT32 *pDownMsgVirAddr;
    UINT32 DownMsgSize;

    UINT32 UpMsgPhyAddr;
    UINT32 *pUpMsgVirAddr;
    UINT32 UpMsgSize;
    UINT32 UpMsgNum;

    UINT32 SegBufPhyAddr;
    UINT32 SegBufSize;
} SM_BUFFERCFG_S;

/********************************************************************************
 SMʵ������Ϣ�ṹ�����ڶ��⴫���ڲ���Ϣ����GetInfo()�ӿ���ʹ��
*********************************************************************************/
typedef struct
{
    SINT8         InstMode;      /* 0: �ǹ���ģʽ,  1: ����ģʽ   */
    SINT32        RawNum;        /* ԭʼ��������Ŀ                */
    SINT32        SegNum;        /* ԭʼ������������              */
    SINT32        TotalRawSize;  /* ���и������Ƭ����Ŀ          */
    SINT32        TotalSegSize;  /* ���и������Ƭ����������      */
    SINT32        numReadSegFail;  /* ����������seg�ļ��� */
} SM_INST_INFO_S;

/********************************************************************************
 ÿ������Scd��Raw���������ԣ���Ҫ����SegStream��Ptsʹ��
*********************************************************************************/
typedef struct
{
    UINT8    *pCurrStartVirAddr;
    UINT8    *pCurrEndVirAddr;
    UINT32    CurrStartPhyAddr;
    UINT32    CurrEndPhyAddr;
    SINT32    Length;
    SINT32    TotalLen;
    UINT64    Pts;
} SM_PUSHRAWPACKET_S;

typedef struct
{
    SINT32 PushRawNum;
    SINT32 PushRawTotalLen;
    PUSH_RAW_OVER_STATE PushRawOverState;
} SM_PUSHRAW_S;

typedef enum
{
    SM_NOT_MPEG4 = 0,
    SM_MPEG4_NOTH263,
    SM_MPEG4_H263
} MPEG4_SUB_STD;

typedef struct
{
    UINT8    *pSegBufVirAddr;//Seg Buffer�������ַ,ȡ����ʱʹ��
    UINT32    *pScdUpMsg;      //�����˵�������Ϣ�ĵ�ַ
    SINT32    ProtocolType;
    SINT32    ModeFlag;       //0:�ڷ�Mpeg4ģʽ; 1:��һ�β���H263ģʽ, 2:��һ����H263ģʽ
    SINT32    LastH263Num;    //��һ�ν�������ΪH263ͷ������
    UINT32    SegBufPhyAddr;
    SINT32    SegBufSize;
    UINT32    SegBufRollAddr;
    SINT32    SegNum;         //�����˵�SegStream���ж��ٰ�
} SM_SEGSTREAMFILTER_S;

typedef struct
{
    SINT8          SegFullFlag;
    SINT8          IsCounting;
    SINT8          LastCfgAllRawFlag; // 1 : ��ʵ���ϴ�����SCDʱ�����е�RAW���������������ô������ñ�־λ��ÿ��SCD����ʱ�����жϸ�ֵ
    SINT8          FillNewRawFlag; // 1 : ��ʵ���ϴ�SCD�����������µ�RAW�������ñ�־λ����ÿ��SCD��������0
    SINT8          IsWaitSCD;
    SM_CFG_S       Config;
    RAW_ARRAY_S    RawPacketArray;
    SEG_ARRAY_S    StreamSegArray;
    SM_PUSHRAW_S   SmPushRaw;
    SM_BUFFERCFG_S BufAddrCfg;
    SINT32         InstID;
    SINT32         Mode;
    UINT32         Mpeg4ModeFlag;
    UINT32         LastH263Num;
    UINT32         BlockTimeInMs;  // ��������ʱ�䣬��λms
    UINT32         LastBlockTime;  // ��һ�α�������ʱ��(ϵͳʱ��)�����ں���ˢ������ʱ��
    UINT64         LastPts;//������ε�Pts���ϴ���ͬ�����-1
    SINT32         PrevCfgRawSize;
    SINT32         PrevCfgSegSize;

    /* ͳ������ */
    SINT32         TotalRawSize;
    UINT32         LastStatTime; //����ͳ�����ʵ�ʱ��
    UINT32         BitRate;  // ����, ��λKbps

    /* ����ͳ����Ϣ */
    SINT32         numReadSegFail;
    SINT32         LastSCDStartTime; //�ϴ�����SCD������ʱ�䣬��λ ����

    UINT32         UpMsgStepInWord;

    UINT16 pre_scd_previous_byte_msb;
    UINT32 pre_scd_previous_byte_lsb;

    UINT16 scd_previous_byte_msb;
    UINT32 scd_previous_byte_lsb; // near to the next seg

    UINT32 seg_next_addr;

    UINT32 first_start_scd_flag;

    UINT32 last_start_code_addr;
    UINT32 last_unfinished_seg_size;

    UINT32 roll_flag;
    UINT32 roll_addr;

    STREAM_SEG_S last_unfinished_seg;

    UINT32 raw_msg_arr[MAX_STREAM_RAW_NUM][2];
} SM_INSTANCE_S;


typedef struct hiSCD_DRV_MEM_S
{
    SINT32         HwMemAddr;
    SINT32         HwMemSize;
    SINT32         DownMsgMemAddr;
    UINT32        *pDownMsgMemVirAddr;
    SINT32         DownMsgMemSize;
    SINT32         UpMsgMemAddr;
    SINT32        *pUpMsgMemVirAddr;
    SINT32         UpMsgMemSize;
    SINT32         ScdRegAddr;
    SINT32         ScdResetRegAddr;
} SCD_DRV_MEM_S;

/*
    ���ӳ�����Ҫά��SPS,PPS��Ϣ��DDT MEM ����
*/
typedef struct
{
    MEM_RECORD_S   stBaseMemInfo;
} DSP_CTX_MEM_S;

/********************************************************************************
SmInstArray     SMʵ�����飬��¼����ʵ������Ϣ
SmInstPriority  SM��ʵ�������ȼ�
          0����������ȼ���1��֮����������
ThisInstID    ��ǰSCD���ڴ�����ʵ�����
ScdState    SCD�Ĺ���״̬��
          0�����У�δ������
          1�����У����������У�
*********************************************************************************/
typedef struct
{
    SCD_DRV_MEM_S       ScdDrvMem;
    DSP_CTX_MEM_S       DspCtxMem[MAX_CHAN_NUM];
    //    SM_INSTANCE_S       SmInstArray[MAX_CHAN_NUM];
    SM_INSTANCE_S      *pSmInstArray[MAX_CHAN_NUM];
    SINT32              SmInstPriority[MAX_CHAN_NUM];
    SINT32              IsScdDrvOpen;
    SINT32              ThisInstID;
    SINT32              SCDState;
    UINT32              LastProcessTime;
} SM_IIS_S;


/*######################################################
       interface functions.
 ######################################################*/
SINT32 SCDDRV_PrepareSleep(VOID);
SCDDRV_SLEEP_STAGE_E SCDDRV_GetSleepStage(VOID);
VOID SCDDRV_ForceSleep(VOID);
VOID SCDDRV_ExitSleep(VOID);

VOID ResetSCD(VOID);

/************************************************************************
  ԭ��  VOID ResetRawStreamArray( RAW_ARRAY_S *pRawStreamArray )
  ����  ��һ��ԭʼ�������ϸ�λ������������м�¼
  ����  pRawStreamArray ָ��ԭʼ��������
  ����ֵ  ��
************************************************************************/
VOID ResetRawStreamArray(RAW_ARRAY_S *pRawStreamArray);

SINT32 SCDDRV_InsertRawPacket(SINT32 SmID, STREAM_DATA_S *pRawPacket);
/************************************************************************
  ԭ��  SINT32 GetRawIsFull(SINT32 SmID)
  ����  �õ�Raw Buffer�ܷ�����״̬
  ����  SmID  ��������ģ���ʵ���ı�ʶ
  ����ֵ  ���Բ���Raw Packet�ͷ���FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetRawState(SINT32 SmID);

/************************************************************************
  ԭ��  SINT32 SetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 Offset )
  ����  ���õ�һ������������Ч�ֽ�ƫ��
  ����  pRawStreamArray ָ��ԭʼ��������
    Offset  ��һ�����ݰ�����Ч�ֽ�ƫ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 SetFirstOffset(RAW_ARRAY_S *pRawStreamArray, SINT32 Offset);

/************************************************************************
  ԭ��  SINT32 GetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset )
  ����  ��ȡ��һ������������Ч�ֽ�ƫ��
  ����  pRawStreamArray ָ��ԭʼ��������
        pOffset ��һ�����ݰ�����Ч�ֽ�ƫ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetFirstOffset(RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset);

SINT32 DeleteRawPacket(RAW_ARRAY_S *pRawStreamArray, UINT32 DelNum);

/************************************************************************
ԭ��    SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag)
����    ��history��ʼ������ɾ����head
����    pRawStreamArray ָ��ԭʼ��������
����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag);

SINT32 GetRawNumOffset(RAW_ARRAY_S *pRawStreamArray, SINT32 RawPacketLength, SINT32 *pRawNum, SINT32 *pPacketOffset, UINT32 *pIndex);

/************************************************************************
  ԭ��  SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen )
  ����  �ӵ�һ��������ʼ������ɾ��DelLen�����������ɾ���ĳ��Ȳ�������Ҫ��ƫ�ơ�
  ����  pRawStreamArray ָ��ԭʼ��������
        DelLen  �ܹ���Ҫɾ���ĳ���
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen );

/************************************************************************
  ԭ��  SINT32 DeleteLastSendRaw( UINT32 SmID  )
  ����  ɾ��SmID��ָ���ͨ�����ϴ�������SCD������
  ����  SmIDͨ����
  ����ֵ  ��
************************************************************************/
VOID DeleteLastSendRaw( UINT32 SmID );

/************************************************************************
  ԭ��  SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize)
  ����  ��ԭʼ�������������а��ĳ����ۼ�������Ϊ����������Ŀ���ǻ��Ŀǰ������ռ�������
  ����  pRawStreamArray ָ��ԭʼ��������
  ����ֵ  �ɹ������������ȣ����򷵻ش����루��������
************************************************************************/
SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize);

/************************************************************************
    ԭ��  SINT32 GetRawStreamNum( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum )
    ����  ��ԭʼ�����������ѱ����͵���δ���и������������Ŀ���ǻ��Ŀǰ������ռ�������
    ����  pRawStreamArray ָ��ԭʼ��������
    ����ֵ  �ɹ�����pStreamNum����������������FMW_OK,ʧ���򷵻ش����루��������
************************************************************************/
SINT32 GetRawStreamNum( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum );

/*========================================================================
    part2.    stream segment management module
========================================================================*/

/************************************************************************
  ԭ��  SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UINT32 BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize )
  ����  Ϊ����Ƭ�μ������ñ�Ҫ����Ϣ��������Ƭ�λ��������׵�ַ�����ȵȡ�
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
        BufPhyAddr  ����Ƭ�λ�����������ַ
        BufSize ����Ƭ�λ�������С����λ���ֽ�
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UINT32 BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize );

/************************************************************************
  ԭ��  VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray )
  ����  ��һ���и�����Ƭ�μ��ϸ�λ������������м�¼���ͷ�ȫ���и���������ռ䡣
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
  ����ֵ  ��
************************************************************************/
VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray );
UINT32 GetSegBufFreeSize(SEG_ARRAY_S *pStreamSegArray);

/************************************************************************
  ԭ��  SINT32 InsertStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  ����  ���ض�������Ƭ�μ��в���һ������Ƭ�Ρ�
      ����������������������һ�ǽ�����������Ƭ�ε�������Ϣ���뵽�����У��ڶ��Ǹ�������Ƭ�λ�������д��ַ��
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
      pStreamSeg  ����������Ƭ�ε�������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 InsertStreamSeg(SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg , SINT32 InstID);

/************************************************************************
  ԭ��  SINT32 SCDDRV_GetStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  ����  ���ض�������Ƭ�μ���ȡ��һ������Ƭ�Σ������ڶ���ͷ������Ƭ����Ϣȡ����
  ����  pStreamSegArray ָ����Ƭ�μ���
        pStreamSeg  �洢����Ƭ�ε�������Ϣ�Ľṹָ��
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 SCDDRV_GetStreamSeg(SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg);

/************************************************************************
  ԭ��  SINT32 ReleaseStreamSeg( SEG_ ARRAY_S *pStreamSegArray, UINT32 StreamID)
  ����  ��IDΪStreamID������Ƭ���ͷţ�����������Ƭ������ʷ���Ѷ�ȡ��δ�ͷŵĵ�һ����������ͬ����������Ƭ�λ������Ķ���ַ��
  ����  pStreamSegArray ָ����Ƭ�μ���
      StreamID  ���ͷ�����Ƭ�ε�ID
        ���StreamIDȡֵ��0~ MAX_STREAM_SEG_NUM-1֮�����ʾҪ�ͷ�������ΪStreamID������Ƭ�Σ�
        ���StreamID = 0xffffffff�����ʾ�ͷŵ�һ������Ƭ�Ρ����������ʹ�ó����ǣ��������
      ����ģ�鳤ʱ�䲻�ͷ��������������ݴ�����SMģ����Ҫǿ���ͷŵ�һ�������ڳ��ռ��������и�������
      ������������������£����۵�һ������Ƭ���Ƿ񱻶��ߣ���ǿ���ͷš�
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ReleaseStreamSeg(SEG_ARRAY_S *pStreamSegArray, UINT32 StreamID);

/************************************************************************
    ԭ��  SINT32 GetSegStreamSize( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize)
    ����  ������Ƭ�ϼ��������а��ĳ����ۼ�������Ϊ����������Ŀ���ǻ��Ŀǰ������ռ�������
    ����  pSegStreamArray ָ������Ƭ�ϼ���
    ����ֵ  �ɹ������������ȣ����򷵻ش����루��������
************************************************************************/
SINT32 GetSegStreamSize(SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize);
UINT32 GetSegStreamNum(SEG_ARRAY_S *pSegStreamArray);

VOID GetFreshSegStream( SEG_ARRAY_S *pSegStreamArray, SINT32 *pFreshNum, SINT32 *pFreshSize);

SINT32 SM_OpenSCDDrv(SINT32 MemAddr, SINT32 MemSize, SINT32 RegAddr, SINT32 ResetRegAddr);
SINT32 SM_CloseSCDDrv(VOID);
VOID   SM_GiveThreadEvent(SINT32 SmID);
VOID   SCDDRV_MaskInt(VOID);
VOID   SCDDRV_EnableInt(VOID);
SINT32 SM_GetInstanceStreamEmptyFlag(SINT32 InstID);

/************************************************************************
  ԭ��  SINT32 SM_Reset ( SINT32 SmID )
  ����  ���������Ը�λһ����������ģ���ʵ����
      ������ʹ��ID��ΪSmID����������ģ��ʵ��������״̬���ص���ʼֵ��
  ����  SmID  ��ʶ��������ģ�����������Ϣ���ڶ�·�����У�ÿһ·����������һ����������ģ���
      ʵ����SmIDָ��ĳ���ض���ʵ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻��ض��Ĵ�����
************************************************************************/
SINT32  SM_ClearInst(SINT32 SmID);
SINT32  SM_Reset(SINT32 SmID);
HI_VOID SM_Start(SINT32 SmID);
SINT32  SM_Stop(SINT32 SmID);

/************************************************************************
  ԭ��  SINT32 SM_Config ( SINT32 SmID, SM_CFG_S *pSmCfg )
  ����  ��������������һ����������ģ���ʵ���������ʵ����ʼ����֮ǰ��������ô˺����������ñ�Ҫ����Ϣ��
  ����  SmID  ��ʶ��������ģ�����������Ϣ���ڶ�·�����У�ÿһ·����������һ����������ģ���ʵ����
      SmIDָ��ĳ���ض���ʵ����
      pSmCfg  SMʵ����������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻��ض��Ĵ�����
************************************************************************/
SINT32 SM_Config(SINT32 SmID, SM_CFG_S *pSmCfg);

/************************************************************************
    ԭ��    SINT32 SM_GetInfo( SINT32 SmID, SM_INST_INFO_S *pSmInstInfo )
    ����  ��������ѯ��������ģ����ԭʼ�������ۼ��˶��ٰ������и������������ж��ٶΡ��ڶ�·���뻷���£��ϲ���ȳ��������Ҫ����ÿһ·����Щ��Ϣ��������SCD�������һ·ȥ�и�������
    ����  SmID  ��������ģ���ʵ���ı�ʶ
            pSmInstInfo  ���ʵ����Ϣ�Ľṹ
    ����ֵ  FMW_ERR_PARAM or FMW_OK
************************************************************************/
SINT32 SM_GetInfo(SINT32 SmID, SM_INST_INFO_S *pSmInstInfo);

SINT32 SM_ReadSegStream(SINT32 SmID, STREAM_SEG_S *pStreamSeg);

/************************************************************************
  ԭ��  SINT32 SM_ReleaseStreamSeg( SINT32 SmID, SINT32 StreamID )
  ����  ��������Э����Ѿ�������ϵ�����Ƭ�黹����������ģ��
  ����  SmID  ��������ģ���ʵ���ı�ʶ
        StreamID  ����Ƭ��ID
  ����ֵ  ��
************************************************************************/
SINT32 SM_ReleaseStreamSeg(SINT32 SmID, SINT32 StreamID);

SINT32 CalcInstBlockTime(SM_INSTANCE_S *pSmInstArray, SINT32 FirstCalc);

/************************************************************************
  ԭ��  SINT32 SetInstMode( SINT32 SmID, SINT32 Mode )
  ����  ����ָ��ʵ����������ʱ�䣬���ϴ�����ʱ���뵱ǰʱ��֮���ۼӵ�
          ������ʱ����ȥ�����Ҹ���"�ϴ�����ʱ��"
  ����  SmID  ��������ģ���ʵ���ı�ʶ
          Mode    SM_INST_MODE_WORK  ����ģʽ
                  SM_INST_MODE_WAIT  ����ģʽ
  ����ֵ  �ɹ�����FMW_OK�� ���򷵻ش�����
************************************************************************/
SINT32 SetInstMode(SINT32 SmID, SINT32 Mode);


/*========================================================================
    part4.   SCD level �����и�Ϳ�����ģ��
========================================================================*/

/************************************************************************
  ԭ��  SINT32 CutStreamWithSCD(RAW_ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, UINT32 StdType, SINT32 *pCutRawNum)
    ����  ����SCD�и�������
            ��������ԭʼ��������ȡ�����ɸ����������ø�SCD��Ȼ������SCD�иһ���и��ԭʼ����������ȡ��������������
            1.  ����Ƭ�λ������Ŀ��пռ�
            2.  ԭʼ������PTS�ֲ�
            �༴�����и���������ܳ��Ȳ��ô�������Ƭ�λ������Ŀ��пռ�������һ���и��������PTS���ܱ仯������MPEGϵ�п��������ܴ����ƣ���
            ����������ԭʼ����������ģ���ShowFirstRawPacket() / ShowNextRawPacket()����������ɨ��ԭʼ�������õ����и������������
    ����  pRawStreamArray ԭʼ������
          pStreamSegArray �и�����Ƭ�μ�
          StdType ������Э�����͡�
            SCDͬ��ͷ���������Э�����͡�
            pCutRawNum ���и����������Ŀ������0��������
    ����ֵ  FMW_OK�������
************************************************************************/
SINT32 CutStreamWithSCD(SM_INSTANCE_S *pScdInstance);

SINT32 SCDDRV_StartSCD(SM_INSTANCE_S *pScdInstance, SM_CTRLREG_S *pSmCtrlReg, UINT32 SegStreamSize);

/************************************************************************
  ԭ��  VOID WriteScdVtrlReg()
    ����  ����Scd״̬�Ĵ�������
    ����
    ����ֵ
************************************************************************/
VOID WriteScdVtrlReg(SINT32 inst_id, SM_CTRLREG_S *pSmCtrlReg);

/************************************************************************
  ԭ��  SINT32 WriteScdMsg(SM_PUSHRAW_S *pSmPushRaw, SINT32 *pDownMsgVirAddr, SINT32 DownMsgPhyAddr)
    ����  ����Scd������Ϣ��
    ����
    ����ֵ
************************************************************************/
SINT32 WriteScdMsg(SINT32 inst_id, SM_PUSHRAW_S *pSmPushRaw, SINT32 SegStreamSize, RAW_ARRAY_S *pRawStreamArray,
                   SINT32 *pDownMsgVirAddr, SINT32 DownMsgPhyAddr, SINT32 LowdlyFlag);

/************************************************************************
  ԭ��  VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg)
    ����  ��ȡScd״̬�Ĵ�������
    ����
    ����ֵ
************************************************************************/
VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg);

SINT32 CheckSegValid(STREAM_SEG_S *pSegPacket, SEG_ARRAY_S *pStreamSegArray);
VOID GetSegPts(RAW_ARRAY_S *pRawStreamArray, UINT32 Len, UINT64 *pLastPts, STREAM_SEG_S *pSegPacket);

/************************************************************************
ԭ��  SINT32 ProcessSCDReturn(RAW_ ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, SINT32 *pCutRawNum)
����  ����SCD�ķ�����Ϣ��
        ��������SCD�ļĴ������ϡ�������Ϣ���ж�ȡ��һ�ε������и���Ϣ������������ֲ�����
        1.  ����������Ϣ����֡����NAL��������STREAM_SEG_S��ʽ��֯���Ҳ��뵽����Ƭ�μ�pStreamSegArray�й�������
        2.  �����˴��и������˶���ԭʼ��������������Щ�������ͷš�
        ����
        pRawStreamArray ԭʼ������
        pStreamSegArray �и�����Ƭ�μ�
����ֵ  FMW_OK�������
************************************************************************/
SINT32 ProcessScdReturn(SM_INSTANCE_S *pScdInstance);

/************************************************************************
  ԭ��  VOID SM_SCDIntServeProc ( VOID )
  ����  ������ΪSCD���жϷ��������ӦSCD���ж��źŲ������䷵�ص���Ϣ��
  ����  ��
  ����ֵ  ��
************************************************************************/
VOID SM_SCDIntServeProc(VOID);

/************************************************************************
  ԭ��  VOID SM_Wakeup ( VOID )
  ����  ���������ڻ���SMģ�飬����SMͣ�����޷��ָ����С�
      ��������̼߳��SCD��������߳���ÿ����һ֡���ô˺�����
      ������ö�ʱ�жϼ��SCD�����ڶ�ʱ�ж��е��ô˺�����
  ����  ��
  ����ֵ  ��
************************************************************************/
VOID SM_Wakeup(VOID);

/************************************************************************
  ԭ��  VOID SM_GetBasePhyVir(SINT32 SmID, SINT32 *pBasePhyAddr, UINT8 **pBaseVirAddr)
  ����  ���Ի�������ַ��������ַ
  ����  ��
  ����ֵ  ����������ַ
************************************************************************/
VOID SM_GetBasePhyVir(SINT32 SmID, SINT32 *pBasePhyAddr, UINT8 **pBaseVirAddr);

/************************************************************************
  ԭ��  UINT8 *SM_PhyToVir(SINT32 BasePhyAddr, UINT8 *pBaseVirAddr, SINT32 PhyAddr)
  ����  ������ַת�������ַ
  ����  ��
  ����ֵ  ����������ַ
************************************************************************/
UINT8 *SM_PhyToVir(UINT32 PhyAddr);

/************************************************************************
ԭ��  UINT8 *SM_ScdPhyToVir(SINT32 BasePhyAddr, UINT8 *pBaseVirAddr, SINT32 PhyAddr)
����  ������ַת�������ַ
����  ��
����ֵ  ����������ַ
************************************************************************/
UINT8 *SM_ScdPhyToVir(UINT32 BasePhyAddr, UINT8 *pBaseVirAddr, UINT32 PhyAddr);

/************************************************************************
ԭ��  VOID PrintScdVtrlReg()
����  ��ӡScd���ƼĴ�������
����
����ֵ  ��
************************************************************************/
VOID PrintScdVtrlReg(VOID);

/************************************************************************
ԭ��  VOID PrintScdStateReg()
����  ��ӡScd״̬�Ĵ�������
����
����ֵ  ��
************************************************************************/
VOID PrintScdStateReg(SM_STATEREG_S *pSmStateReg);

SINT32 SM_SeekPts(SINT32 ChanID, UINT64 *pArgs);

VOID WriteHexFile(SINT32 eVidStd);

UINT32 get_scd_msg_size(VOID);

#endif  // __SCD_DRV_H__