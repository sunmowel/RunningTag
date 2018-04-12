/*************************************************************************************************************
*                                               INCLUDE FILES                                                *
*************************************************************************************************************/
#include <app.h>


/*************************************************************************************************************
*                                              LOCAL TABLES                                                  *
*************************************************************************************************************/
#pragma location = "TAG_INFO_COD"
__root const sTagInfoTypeDef TagInfo = 
{
    .id    = 10,\
    .key   = TAG_INFO_KEY,\
    .user  = TAG_INFO_USERDEFINE,\
    .ver_h = TAG_INFO_VER_H,\
    .ver_l = TAG_INFO_VER_L,\
};

#pragma location = "TAG_PARA_COD"
__root const sTagParaTypeDef TagPara = 
{
    .pipe[TAG_PIPE0].min_pulse  = TAG_PARA_PIPE0_MIN_PULSE,\
    .pipe[TAG_PIPE0].max_pulse  = TAG_PARA_PIPE0_MAX_PULSE,\
    .pipe[TAG_PIPE0].ch         = TAG_PARA_PIPE0_CH,\
    .pipe[TAG_PIPE0].ack_ch     = TAG_PARA_PIPE0_ACK_CH,\
    .pipe[TAG_PIPE1].min_pulse  = TAG_PARA_PIPE1_MIN_PULSE,\
    .pipe[TAG_PIPE1].max_pulse  = TAG_PARA_PIPE1_MAX_PULSE,\
    .pipe[TAG_PIPE1].ch         = TAG_PARA_PIPE1_CH,\
    .pipe[TAG_PIPE1].ack_ch     = TAG_PARA_PIPE1_ACK_CH,\
    .pipe[TAG_PIPE2].min_pulse  = TAG_PARA_PIPE2_MIN_PULSE,\
    .pipe[TAG_PIPE2].max_pulse  = TAG_PARA_PIPE2_MAX_PULSE,\
    .pipe[TAG_PIPE2].ch         = TAG_PARA_PIPE2_CH,\
    .pipe[TAG_PIPE2].ack_ch     = TAG_PARA_PIPE2_ACK_CH,\
    .pipe[TAG_PIPE3].min_pulse  = TAG_PARA_PIPE3_MIN_PULSE,\
    .pipe[TAG_PIPE3].max_pulse  = TAG_PARA_PIPE3_MAX_PULSE,\
    .pipe[TAG_PIPE3].ch         = TAG_PARA_PIPE3_CH,\
    .pipe[TAG_PIPE3].ack_ch     = TAG_PARA_PIPE3_ACK_CH,\
    .pipe[TAG_PIPE4].min_pulse  = TAG_PARA_PIPE4_MIN_PULSE,\
    .pipe[TAG_PIPE4].max_pulse  = TAG_PARA_PIPE4_MAX_PULSE,\
    .pipe[TAG_PIPE4].ch         = TAG_PARA_PIPE4_CH,\
    .pipe[TAG_PIPE4].ack_ch     = TAG_PARA_PIPE4_ACK_CH,\
    .pipe[TAG_PIPE5].min_pulse  = TAG_PARA_PIPE5_MIN_PULSE,\
    .pipe[TAG_PIPE5].max_pulse  = TAG_PARA_PIPE5_MAX_PULSE,\
    .pipe[TAG_PIPE5].ch         = TAG_PARA_PIPE5_CH,\
    .pipe[TAG_PIPE5].ack_ch     = TAG_PARA_PIPE5_ACK_CH,\
    .key_sn                     = TAG_PARA_KEY_SN,\
    .work_cnt                   = TAG_WORK_TX_CNT_DEFAULT,\
    .work_ch                    = TAG_PARA_WORK_CH,\
    .standby_ch                 = TAG_PARA_STANDBY_CH,\
    .fliter_cnt                 = TAG_PARA_WAKE_FILTER_CNT,\
    .wake_cnt                   = TAG_PARA_WAKE_WAIT_CNT,\
    .tx_retry_max               = TAG_PARA_TX_RETRY_MAX,\
    .tx_slot_max                = TAG_PARA_TX_SLOT_MAX,\
    .tag_send_mode              = TAG_PARA_SEND_MODE_H,\
    .measure_pulse              = DEF_OFF,\
};

#pragma location = "TAG_CONFIG_COD"
__root const sTagConfigTypeDef TagConfig = 
{
    .rf_tx_addr   = {0xE7, 0x7E, 0xE3, 0xE7, 0xE7},\
    .rf_rx_addr   = {0xE3, 0x7E, 0xE3, 0xE7, 0xE7},\
    .rf_aw        = TAG_CONFIG_RF_AW,\
    .rf_data_rate = TAG_CONFIG_RF_DATA_RATE,\
    .rf_tx_pwr    = TAG_CONFIG_RF_TX_PWR,\
};


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void main (void)
{
    sTagPargTypeDef parg;
    
    TagPargInit(&parg);
    BspLedOff();
    while (1)
    {
        TagStateProcess(&parg);
        R_WDT_Restart();
    }
}

/*************************************************************************************************************
*                                                 END FILE                                                   *
*************************************************************************************************************/
