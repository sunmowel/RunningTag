/*************************************************************************************************************
*                                              INCLUDE FILES                                                 *
*************************************************************************************************************/
#include <app.h>


/*************************************************************************************************************
*                                              LOCAL TABLES                                                  *
*************************************************************************************************************/
const FNCT_STATE STDHandle[] = 
{
    TagStateSleep,
    TagStateWork,
    TagStateStandby,
};

sTagRecordTypeDef TagRecord[TAG_RECORD_CNT];


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void TagPargInit (sTagPargTypeDef *parg)
{
    sTagInfoTypeDef *info;
    sTagParaTypeDef *para;
    sTagConfigTypeDef *config;
    sBspnRF24L01pConfigTypeDef rf_config;
    CPU_INT32U *p;
    CPU_INT32U value;
    CPU_INT32U data[TAG_PARA_SIZE];
    CPU_INT8U  i;
    
    p = (CPU_INT32U *)data;
    
    for (i = 0; i < TAG_INFO_SIZE; i++)
    {
        value = *(__far CPU_INT32U *)(TAG_INFO_ADDR + i * 4);
        p[i] = value;
    }
    info = (sTagInfoTypeDef *)data;
    parg->info = *info;
    
    for (i = 0; i < TAG_PARA_SIZE; i++)
    {
        value = *(__far CPU_INT32U *)(TAG_PARA_ADDR + i * 4);
        p[i] = value;
    }
    para = (sTagParaTypeDef *)data;
    parg->para = *para;
    parg->sn = parg->para.key_sn;
    parg->cnt = parg->para.work_cnt * TAG_WORK_TX_CNT_MUL;
    parg->state = TAG_STATE_SLEEP;
    BspSrand(parg->info.id);
    parg->rn = BspRand();
    
    for (i = 0; i < TAG_CONFIG_SIZE; i++)
    {
        value = *(__far CPU_INT32U *)(TAG_CONFIG_ADDR + i * 4);
        p[i] = value;
    }
    config = (sTagConfigTypeDef *)data; 
    parg->config = *config;
    rf_config.rf_aw = config->rf_aw;
    rf_config.rf_data_rate = config->rf_data_rate;
    rf_config.rf_tx_pwr = config->rf_tx_pwr;
    BspnRF24L01pInit(rf_config, config->rf_tx_addr, config->rf_rx_addr);
    TagRecordInit();
}

void TagTxPayloadGet (sTagPargTypeDef *parg)
{
    CPU_INT32U key;
    CPU_INT32U tmp;
    CPU_INT16U sn;
    CPU_INT16U option;
    CPU_INT16U power;
    CPU_INT8U  rn;
    sPayloadTypeDef *payload;
    
    rn = (CPU_INT8U)parg->rn;
    key =  NToHL(parg->info.key);
    sn = NToHS(parg->sn);
    power = (CPU_INT16U)BspPowerCheck();
    option = ((parg->delay << TAG_TX_PAYLOAD_OPTION_DELAY_SHIFT) & TAG_TX_PAYLOAD_OPTION_DELAY_MASK) 
           | ((power << TAG_TX_PAYLOAD_OPTION_ALARM_SHIFT) & TAG_TX_PAYLOAD_OPTION_ALARM_MASK);
    tmp = (((CPU_INT32U)sn << 16) & 0xFFFF0000) | ((CPU_INT32U)sn & 0x0000FFFF);
    key ^= tmp;
    tmp = (((CPU_INT32U)rn << 24) & 0xFF000000)
        | (((CPU_INT32U)rn << 16) & 0x00FF0000)
        | (((CPU_INT32U)rn << 8) & 0x0000FF00)
        | ((CPU_INT32U)rn & 0x000000FF);
    key ^= tmp;
    payload = (sPayloadTypeDef *)parg->payload;
    payload->option = NToHS(option);
    payload->user   = NToHL(parg->info.user);
    payload->id     = NToHL(parg->info.id);
    payload->rn     = rn;
    payload->crc    = GetCRC8(&parg->payload[TAG_TX_PAYLOAD_CRC_POS], TAG_TX_PAYLOAD_CRC_LEN);
    payload->user  ^= key;
    payload->id    ^= key;
    parg->check     = (((CPU_INT16U)rn << 8) & 0xFF00) | payload->crc;
}

eTagPipeTypeDef TagPipeGet (sTagPargTypeDef *parg)
{  
    if ((parg->pulse > parg->para.pipe[TAG_PIPE0].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE0].max_pulse))
    {
        return TAG_PIPE0;
    }
    if ((parg->pulse > parg->para.pipe[TAG_PIPE1].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE1].max_pulse))
    {
        return TAG_PIPE1;
    }
    if ((parg->pulse > parg->para.pipe[TAG_PIPE2].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE2].max_pulse))
    {
        return TAG_PIPE2;
    }
    if ((parg->pulse > parg->para.pipe[TAG_PIPE3].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE3].max_pulse))
    {
        return TAG_PIPE3;
    }
    if ((parg->pulse > parg->para.pipe[TAG_PIPE4].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE4].max_pulse))
    {
        return TAG_PIPE4;
    }
    if ((parg->pulse > parg->para.pipe[TAG_PIPE5].min_pulse) && (parg->pulse < parg->para.pipe[TAG_PIPE5].max_pulse))
    {
        return TAG_PIPE5;
    }
    
    parg->pulse = 0;
    return TAG_PIPE_NULL;
}

CPU_BOOL TagRFTx (sTagPargTypeDef *parg, CPU_INT8U ch_tx, CPU_INT8U ch_ack)
{
    //BspLedOn();//
    BspnRF24L01pSetPowerUp();
    parg->rn = BspRand();
    TagTxPayloadGet(parg);
    BspnRF24L01pTx(ch_tx, parg->payload, TAG_TX_PAYLOAD_LEN);
    //BspLedOff();//
    return BspnRF24L01pComplete(ch_ack, parg->ack, parg->check);
}

CPU_BOOL TagSendData (sTagPargTypeDef *parg, CPU_BOOL trg)
{
    CPU_INT32U i, j;
    CPU_INT8U  slot;
    sBspnRF24L01pConfigTypeDef rf_config;
    
    BspLedOn();//
    BspLedOff();//
    if (trg == DEF_ON)
    {
        parg->rf_error = 0;
        BspTimerMeasureStart();
        if (parg->para.measure_pulse == DEF_ON)
        {
            BspMeasure(&parg->pulse);
            parg->pipe = TagPipeGet(parg);
            if (parg->pipe == TAG_PIPE_NULL)
            {
                BspTimerMeasureStop();
                return DEF_FALSE;
            }
        }
        else
        {
            if (BspSyn() == DEF_FALSE)
            {
                BspTimerMeasureStop();
                return DEF_FALSE;
            }
            parg->pulse = TAG_PARA_PIPE0_PULSE;
            parg->pipe = TAG_PIPE0;
        }
        BspLedOn();//
        BspLedOff();//
        rf_config.rf_aw = parg->config.rf_aw;
        rf_config.rf_data_rate = parg->config.rf_data_rate;
        rf_config.rf_tx_pwr = parg->config.rf_tx_pwr;
        BspnRF24L01pInit(rf_config, parg->config.rf_tx_addr, parg->config.rf_rx_addr);
        parg->delay = BspTimerMeasureDelayGet();
        for (i = 0; i < parg->para.tx_retry_max; i++)
        {
            //BspLedOn();//
            //BspLedOff();//
            parg->info.user = (i << 16) | parg->rf_error;
            slot = parg->rn % parg->para.tx_slot_max;
            if (parg->para.tag_send_mode == TAG_PARA_SEND_MODE_L)
            {
                BspTimerDelayL(BSP_TIMER_DELAY_L_3MS * slot);
                parg->delay = parg->delay + 3 * slot + 2;
            }
            else
            {
                for (j = 0; j < slot; j++)
                {
                    BspTimerDelayUS(1000);
                }
                parg->delay = BspTimerMeasureDelayGet();
            }
            if (parg->para.measure_pulse == DEF_ON)
            {
                parg->rf_error = TagRFTx(parg, parg->para.pipe[parg->pipe].ch, parg->para.pipe[parg->pipe].ack_ch);
            }
            else
            {
                parg->rf_error = TagRFTx(parg, parg->para.pipe[TAG_PIPE0].ch, parg->para.pipe[TAG_PIPE0].ack_ch);
            }
            if (parg->rf_error == BSP_RF_OK)
            {
                BspTimerMeasureStop();
                return DEF_TRUE;
            }
            else
            {
                parg->rf_error = parg->rf_error;
            }
        }
        
        BspTimerMeasureStop();
        return DEF_FALSE;
    } 
    
    parg->pipe = TAG_PIPE6;
    parg->pulse = 0;
    parg->delay = 0;
    parg->rf_error = TagRFTx(parg, parg->para.work_ch, parg->para.work_ch);
    if (parg->rf_error == BSP_RF_OK)
    {
        return DEF_TRUE;
    }
    return DEF_FALSE;
}

void TagStateProcess (sTagPargTypeDef *parg)
{ 
    STDHandle[parg->state](parg);
}

void TagStateSleep (sTagPargTypeDef *parg)
{
    sTagTxACKTypeDef *ack;
    CPU_INT16U cnt;
    
    ack = (sTagTxACKTypeDef *)parg->ack;
    BspWakeUp();
    if (TagSendData(parg, DEF_ON) == DEF_TRUE)
    {
        switch (ack->type)
        {
            case TAG_POINT_READY:   parg->sn = (((CPU_INT16U)ack->data.ready.sn[0] << 8) & 0xFF00) 
                                             | ((CPU_INT16U)ack->data.ready.sn[1] & 0x00FF); 
                                    cnt = (((CPU_INT16U)ack->data.ready.cnt[0] << 8) & 0xFF00) 
                                        | ((CPU_INT16U)ack->data.ready.cnt[1] & 0x00FF);
                                    parg->cnt = cnt * TAG_WORK_TX_CNT_MUL;
                                    parg->state = TAG_STATE_SLEEP;
                                    break;
            case TAG_POINT_START:   if (parg->cnt < (parg->para.work_cnt * TAG_WORK_TX_CNT_MUL))
                                    {
                                        parg->cnt = parg->para.work_cnt * TAG_WORK_TX_CNT_MUL;
                                    }
                                    TagRecordInit();
                                    parg->state = TAG_STATE_WORK;
                                    break;
            case TAG_POINT_MIDDLE:  parg->state = TAG_STATE_SLEEP;
                                    break;
            case TAG_POINT_END:     parg->cnt = 0;
                                    parg->state = TAG_STATE_SLEEP;
                                    break;
            default:                parg->state = TAG_STATE_SLEEP;
                                    break;
        }
        BspWakeFilter(parg->para.fliter_cnt);
    }
}

void TagStateWork (sTagPargTypeDef *parg)
{
    sTagTxACKTypeDef *ack;
    CPU_BOOL flag;
    
    ack = (sTagTxACKTypeDef *)parg->ack;
    if (parg->cnt > 0)
    {
        parg->cnt--;
        flag = BspWakeWait(parg->para.wake_cnt);
        if (TagSendData(parg, flag) == DEF_TRUE)
        {
            switch (ack->type)
            {
                case TAG_POINT_READY:   parg->state = TAG_STATE_WORK;
                                        break;
                case TAG_POINT_START:   parg->state = TAG_STATE_WORK;
                                        break;
                case TAG_POINT_MIDDLE:  //TagRecordIn(parg);
                                        parg->state = TAG_STATE_WORK;
                                        break;
                case TAG_POINT_END:     parg->state = TAG_STATE_STANDBY;
                                        break;
                default:                parg->state = TAG_STATE_WORK;
                                        break;
            }
            if (flag == DEF_ON)
            {
                BspWakeFilter(parg->para.fliter_cnt);
            }
        }
    }
    else
    {
        parg->state = TAG_STATE_SLEEP;
    }
}

void TagStateStandby (sTagPargTypeDef *parg)
{
    parg->state = TAG_STATE_SLEEP;
}

CPU_BOOL TagSendRecord (sTagPargTypeDef *parg, CPU_BOOL trg)
{
    return DEF_TRUE;
}

void TagRecordInit (void)
{
    CPU_INT16U i;
    
    for (i = 0; i < TAG_RECORD_CNT; i++)
    {
        TagRecord[i].flag = DEF_OFF;
    }
}

void TagRecordIn (sTagPargTypeDef *parg)
{
    CPU_INT16U i;
    sTagTxACKTypeDef *ack;
    sTagRecordPointTypeDef point;
    
    ack = (sTagTxACKTypeDef *)parg->ack;
    point.rid = (((CPU_INT16U)ack->data.middle.rid[0] << 8) & 0xFF00) 
              | ((CPU_INT16U)ack->data.middle.rid[1] & 0x00FF); 
    point.utc = (((CPU_INT32U)ack->data.middle.utc[0] << 24) & 0xFF000000) 
              | (((CPU_INT32U)ack->data.middle.utc[1] << 16) & 0x00FF0000) 
              | (((CPU_INT32U)ack->data.middle.utc[2] << 8) & 0x0000FF00) 
              | ((CPU_INT32U)ack->data.middle.utc[3] & 0x000000FF);
    point.ms = (CPU_INT16U)ack->data.middle.ms * 100 + parg->rn % 100;
    for (i = 0; i < TAG_RECORD_CNT; i++)
    {
        if (TagRecord[i].flag == DEF_ON)
        {
            if (point.rid == TagRecord[i].point.rid)
            {
                return;
            }
        }
    }
    for (i = 0; i < TAG_RECORD_CNT; i++)
    {
        if (TagRecord[i].flag == DEF_OFF)
        {
            TagRecord[i].point = point;
            TagRecord[i].flag = DEF_ON;
            break;
        }
    }
}

CPU_BOOL TagRecordOut (sTagRecordPointTypeDef *point)
{
    CPU_INT16U i;
    
    for (i = 0; i < TAG_RECORD_CNT; i++)
    {
        if (TagRecord[i].flag == DEF_ON)
        {
            *point = TagRecord[i].point;
            
            return DEF_TRUE;
        }
    }
    
    return DEF_FALSE;
}

void TagRecordDel (CPU_INT16U rid)
{
    CPU_INT16U i;
    
    for (i = 0; i < TAG_RECORD_CNT; i++)
    {
        if (TagRecord[i].flag == DEF_ON)
        {
            if (rid == TagRecord[i].point.rid)
            {
                TagRecord[i].flag = DEF_OFF;
                return;
            }
        }
    }
}

/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/