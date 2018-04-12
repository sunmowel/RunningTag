/*************************************************************************************************************
*                                                  MODULE                                                    *
*************************************************************************************************************/
#ifndef BSP_TAG_H
#define BSP_TAG_H

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************************************************
*                                                 DEFINES                                                    *
*************************************************************************************************************/
#define TAG_INFO_ADDR					        0x00100u
#define TAG_PARA_ADDR					        0x00110u
#define TAG_CONFIG_ADDR					        0x00140u
  
#define TAG_INFO_SIZE					        4u
#define TAG_PARA_SIZE					        12u
#define TAG_CONFIG_SIZE					        4u
    
/* Bit fields for TX Payload Option. */        
#define TAG_TX_PAYLOAD_OPTION_PIPE_SHIFT        0   
#define TAG_TX_PAYLOAD_OPTION_PIPE_MASK         (0x7U << 0)     
#define TAG_TX_PAYLOAD_OPTION_PIPE_DEFAULT      (0x0U << 0)
#define TAG_TX_PAYLOAD_OPTION_PIPE_0            (0x0U << 0)
#define TAG_TX_PAYLOAD_OPTION_PIPE_1            (0x1U << 0)
#define TAG_TX_PAYLOAD_OPTION_PIPE_2            (0x2U << 0)
#define TAG_TX_PAYLOAD_OPTION_PIPE_3            (0x3U << 0)  
#define TAG_TX_PAYLOAD_OPTION_PIPE_4            (0x4U << 0)  
#define TAG_TX_PAYLOAD_OPTION_DELAY_SHIFT       0   
#define TAG_TX_PAYLOAD_OPTION_DELAY_MASK        (0xFFFU << 0)     
#define TAG_TX_PAYLOAD_OPTION_DELAY_DEFAULT     (0x0U << 3)
#define TAG_TX_PAYLOAD_OPTION_POWER_SHIFT       12   
#define TAG_TX_PAYLOAD_OPTION_POWER_MASK        (0x7U << 12)     
#define TAG_TX_PAYLOAD_OPTION_POWER_DEFAULT     (0x7U << 12)
#define TAG_TX_PAYLOAD_OPTION_ALARM_SHIFT       15   
#define TAG_TX_PAYLOAD_OPTION_ALARM_MASK        (0x1U << 15)     
#define TAG_TX_PAYLOAD_OPTION_ALARM_DEFAULT     (0x0U << 15)
#define TAG_TX_PAYLOAD_OPTION_ALARM_OFF         (0x0U << 15)
#define TAG_TX_PAYLOAD_OPTION_ALARM_ON          (0x1U << 15)

#define TAG_INFO_KEY                            0x00000000u
#define TAG_INFO_USERDEFINE                     0x00000000u  
#define TAG_INFO_VER_H					        1u
#define TAG_INFO_VER_L					        0u

#define TAG_TX_PAYLOAD_OPTION_SIZE              2u
#define TAG_TX_PAYLOAD_OUSER_SIZE               4u
#define TAG_TX_PAYLOAD_ID_SIZE                  4u
#define TAG_TX_PAYLOAD_RN_SIZE                  1u
#define TAG_TX_PAYLOAD_CRC_SIZE                 1u 
#define TAG_TX_PAYLOAD_LEN                      (2u + 4u + 4u + 1u + 1u)
#define TAG_TX_PAYLOAD_CRC_POS                  2u
#define TAG_TX_PAYLOAD_CRC_LEN                  (4u + 4u + 1u)
#define TAG_TX_ACK_LEN                          BSP_NRF24L01P_ACK_LEN
    
#define TAG_WORK_TX_CNT_DEFAULT                 (6u * 60u)
#define TAG_WORK_TX_CNT_MUL                     60u

#define TAG_PIPE_NUM                            6u
#define TAG_PARA_PIPE0_PULSE                    1750u
#define TAG_PARA_PIPE0_MIN_PULSE                1500u
#define TAG_PARA_PIPE0_MAX_PULSE                2100u
#define TAG_PARA_PIPE0_CH                       13u
#define TAG_PARA_PIPE0_ACK_CH                   14u
    
#define TAG_PARA_PIPE1_PULSE                    2500u
#define TAG_PARA_PIPE1_MIN_PULSE                2250u
#define TAG_PARA_PIPE1_MAX_PULSE                2850u
#define TAG_PARA_PIPE1_CH                       17u
#define TAG_PARA_PIPE1_ACK_CH                   18u
    
#define TAG_PARA_PIPE2_PULSE                    3250u
#define TAG_PARA_PIPE2_MIN_PULSE                2900u
#define TAG_PARA_PIPE2_MAX_PULSE                3600u
#define TAG_PARA_PIPE2_CH                       15u
#define TAG_PARA_PIPE2_ACK_CH                   16u
    
#define TAG_PARA_PIPE3_PULSE                    4000u
#define TAG_PARA_PIPE3_MIN_PULSE                3650u
#define TAG_PARA_PIPE3_MAX_PULSE                4350u
#define TAG_PARA_PIPE3_CH                       19u
#define TAG_PARA_PIPE3_ACK_CH                   20u
    
#define TAG_PARA_PIPE4_PULSE                    5000u
#define TAG_PARA_PIPE4_MIN_PULSE                4800u
#define TAG_PARA_PIPE4_MAX_PULSE                5200u
#define TAG_PARA_PIPE4_CH                       21u
#define TAG_PARA_PIPE4_ACK_CH                   22u
    
#define TAG_PARA_PIPE5_PULSE                    6000u
#define TAG_PARA_PIPE5_MIN_PULSE                5800u
#define TAG_PARA_PIPE5_MAX_PULSE                6200u
#define TAG_PARA_PIPE5_CH                       23u
#define TAG_PARA_PIPE5_ACK_CH                   23u
    
#define TAG_PARA_WORK_CH                        11u
#define TAG_PARA_STANDBY_CH                     12u
#define TAG_PARA_WAKE_FILTER_CNT                20u
#define TAG_PARA_WAKE_WAIT_CNT                  10u
#define TAG_PARA_TX_RETRY_MAX                   30u
#define TAG_PARA_TX_SLOT_MAX                    128u
#define TAG_PARA_SEND_MODE_H                    1u
#define TAG_PARA_SEND_MODE_L                    0u
#define TAG_PARA_KEY_SN                         0x0000u  
    
#define TAG_CONFIG_RF_AW                        BSP_NRF24L01P_AW_MAX
#define TAG_CONFIG_RF_DATA_RATE                 RF_DR_250kbps
#define TAG_CONFIG_RF_TX_PWR                    RF_PWR_0dBm

#define TAG_RECORD_CNT                          32u
    
    
/*************************************************************************************************************
*                                                 DATA TYPES                                                 *
*************************************************************************************************************/
#pragma pack(1)
typedef struct
{
    CPU_INT32U id;  
    CPU_INT32U key;
    CPU_INT32U user;
    CPU_INT16U ver_h;
    CPU_INT16U ver_l;
} sTagInfoTypeDef;

typedef struct
{
    CPU_INT16U min_pulse;
    CPU_INT16U max_pulse;
    CPU_INT8U  ch;
    CPU_INT8U  ack_ch;
} sTagPipeTypeDef;

typedef struct
{
    sTagPipeTypeDef pipe[TAG_PIPE_NUM]; 
    CPU_INT16U key_sn;
    CPU_INT16U work_cnt;
    CPU_INT8U  work_ch;  
    CPU_INT8U  standby_ch;
    CPU_INT8U  fliter_cnt;
    CPU_INT8U  wake_cnt;
    CPU_INT8U  tx_retry_max;
    CPU_INT8U  tx_slot_max; 
    CPU_INT8U  tag_send_mode;
    CPU_INT8U  measure_pulse;
} sTagParaTypeDef;

typedef struct
{
    sTagInfoTypeDef info;
    sTagParaTypeDef para; 
} sTagLoadTypeDef;

typedef struct
{
    CPU_INT8U rf_tx_addr[BSP_NRF24L01P_AW_MAX];
    CPU_INT8U rf_rx_addr[BSP_NRF24L01P_AW_MAX];
    CPU_INT8U rf_aw;
    CPU_INT8U rf_data_rate;
    CPU_INT8U rf_tx_pwr;
} sTagConfigTypeDef;

typedef struct
{
    CPU_INT16U option;
    CPU_INT32U user;
    CPU_INT32U id;
    CPU_INT8U  rn; 
    CPU_INT8U  crc; 
} sPayloadTypeDef;  

typedef struct
{
    CPU_INT8U sn[2];
    CPU_INT8U cnt[2];
} sTagTxACKReadyTypeDef;

typedef struct
{
    CPU_INT8U rid[2];
    CPU_INT8U utc[4];
    CPU_INT8U ms;
} sTagTxACKMiddleTypeDef;

typedef struct
{
    CPU_INT8U tid[4];
    CPU_INT8U rid[2];
} sTagTxACKRecordTypeDef;

typedef union
{
    sTagTxACKReadyTypeDef ready;
    sTagTxACKMiddleTypeDef middle;
} uTagTxACKDataTypeDef;

typedef struct
{
    CPU_INT8U check[2];
    CPU_INT8U type;
    uTagTxACKDataTypeDef data; 
} sTagTxACKTypeDef;

typedef struct
{
    CPU_INT16U rid;
    CPU_INT32U utc;
    CPU_INT16U ms;
} sTagRecordPointTypeDef;
#pragma pack() 

typedef enum
{
    TAG_POINT_READY   = 0xA1, 
    TAG_POINT_START   = 0xA2, 
    TAG_POINT_MIDDLE  = 0xA3, 
    TAG_POINT_END     = 0xA4, 
    TAG_POINT_STANDBY = 0xA5, 
    TAG_POINT_RECORD  = 0xA6, 
} eTagPointTypeDef;

typedef enum
{
    TAG_PIPE0, 
    TAG_PIPE1, 
    TAG_PIPE2, 
    TAG_PIPE3, 
    TAG_PIPE4, 
    TAG_PIPE5,
    TAG_PIPE6,
    TAG_PIPE_NULL,
} eTagPipeTypeDef;

typedef struct
{
    sTagRecordPointTypeDef point;
    CPU_INT8U flag;
} sTagRecordTypeDef;

typedef struct
{
    sTagInfoTypeDef info;
    sTagParaTypeDef para;
    CPU_INT8U  state;
    CPU_INT8U  rf_error;
    CPU_INT16U sn;
    CPU_INT32U cnt;
    CPU_INT16U rn;
    CPU_INT32U pulse;
    CPU_INT16U delay;
    CPU_INT16U check;
    eTagPipeTypeDef pipe;
    sTagConfigTypeDef config;
    CPU_INT8U  payload[FIFO_MAX_SIZE];
    CPU_INT8U  ack[FIFO_MAX_SIZE];
} sTagPargTypeDef;

typedef void (*FNCT_STATE)(sTagPargTypeDef *parg);

typedef enum
{
    TAG_STATE_SLEEP, 
    TAG_STATE_WORK, 
    TAG_STATE_STANDBY,
} eTagStateTypeDef;


/*************************************************************************************************************
*                                            FUNCTION STATEMENT                                              *
*************************************************************************************************************/
void TagPargInit (sTagPargTypeDef *parg);
void TagTxPayloadGet (sTagPargTypeDef *parg);
CPU_BOOL TagRFTx (sTagPargTypeDef *parg, CPU_INT8U ch_tx, CPU_INT8U ch_ack);
eTagPipeTypeDef TagPipeGet (sTagPargTypeDef *parg);
CPU_BOOL TagSendData (sTagPargTypeDef *parg, CPU_BOOL trg);
void TagStateProcess (sTagPargTypeDef *parg);
void TagStateSleep (sTagPargTypeDef *parg);
void TagStateWork (sTagPargTypeDef *parg);
void TagStateStandby (sTagPargTypeDef *parg);
void TagRecordInit (void);
void TagRecordIn (sTagPargTypeDef *parg);
CPU_BOOL TagRecordOut (sTagRecordPointTypeDef *point);
void TagRecordDel (CPU_INT16U rid);


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
