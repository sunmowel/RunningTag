/*************************************************************************************************************
*                                              INCLUDE FILES                                                 *
*************************************************************************************************************/
#include <bsp.h>


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void BspnRF24L01pInit (sBspnRF24L01pConfigTypeDef config, CPU_INT8U *rf_tx_addr, CPU_INT8U *rf_rx_addr)
{
    CPU_INT8U data[BSP_NRF24L01P_AW_MAX] = {0x00, 0x00, 0x00, 0x00, 0x00};

    BspnRF24L01pCEHigh();
	BspnRF24L01pCELow();
	BspnRF24L01pCSNHigh();
    BspnRF24L01pWrReg(EN_AA, DISAA); 
    BspnRF24L01pWrReg(EN_RXADDR, ERX_P0);
    BspnRF24L01pWrReg(SETUP_RETR, AR_DISABLE);
    BspnRF24L01pWrReg(SETUP_AW,  config.rf_aw - 2);
    BspnRF24L01pWrReg(RF_CH, BSP_NRF24L01P_CH);
    BspnRF24L01pWrReg(RF_SETUP, config.rf_data_rate | config.rf_tx_pwr);   
    BspnRF24L01pWrIDCode(RX_ADDR_P0, rf_rx_addr, config.rf_aw);
    BspnRF24L01pWrIDCode(TX_ADDR, rf_tx_addr, config.rf_aw);
    BspnRF24L01pRdIDCode(TX_ADDR, data, config.rf_aw);
    BspnRF24L01pWrReg(DYNPD, DPL_P0);
    BspnRF24L01pWrReg(FEATURE, EN_DPL); 
    BspnRF24L01pClrTxFIFO();
    BspnRF24L01pClrRxFIFO();
    BspnRF24L01pSetSleep();   
} 

void BspnRF24L01pWrReg (CPU_INT8U addr, CPU_INT8U value)
{
    CPU_INT8U cmd;
    
    cmd = W_REGISTER | addr; 
    BspnRF24L01pCSNLow();   
    SPITxData(&cmd, 1);
    SPITxData(&value, 1);
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pRdReg (CPU_INT8U addr, CPU_INT8U *value)
{
    CPU_INT8U cmd;

    cmd = R_REGISTER | addr;
    BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPIRxData(value, 1); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pWrIDCode (CPU_INT8U pipe, CPU_INT8U * const paddr, CPU_INT16U len)
{
    CPU_INT8U cmd;
	
	cmd = W_REGISTER | pipe;
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPITxData(paddr, len); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pRdIDCode (CPU_INT8U pipe, CPU_INT8U *paddr, CPU_INT16U len)
{
    CPU_INT8U cmd;
	
	cmd = R_REGISTER | pipe;
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPIRxData(paddr, len); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pClrRxFIFO (void)
{
    CPU_INT8U cmd;
    
    cmd = FLUSH_RX; 
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pClrTxFIFO (void)
{
    CPU_INT8U cmd;
    
    cmd = FLUSH_TX; 
    BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pRxFIFOPWGet (CPU_INT8U *pw)
{
    CPU_INT8U cmd;
    
    cmd = R_RX_PL_WID;
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPIRxData(pw, 1); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pSetSleep (void)
{
	BspnRF24L01pCELow();
    BspnRF24L01pWrReg(CONFIG, MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT); 
}

void BspnRF24L01pSetPowerUp (void)
{
    BspnRF24L01pCELow();
    BspnRF24L01pWrReg(CONFIG, EN_CRC | CRCO | PWR_UP);
    BspTimerDelayUS(1200);
}

void BspnRF24L01pEnhancedShockBurst (void)
{
	CPU_INT16U i;
	
    BspnRF24L01pCEHigh();
    for(i = 10; i > 0; i--);
    BspnRF24L01pCELow();  
}

void BspnRF24L01pWrTxFIFO (CPU_INT8U * const pdata, CPU_INT16U len)
{
    CPU_INT8U cmd;
    
    cmd = W_TX_PAYLOAD;
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPITxData(pdata, len); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pRdRxFIFO (CPU_INT8U *pdata, CPU_INT16U len)
{
    CPU_INT8U cmd;
    
    cmd = R_RX_PAYLOAD;
	BspnRF24L01pCSNLow();    
    SPITxData(&cmd, 1);
    SPIRxData(pdata, len); 
    BspnRF24L01pCSNHigh();
}

void BspnRF24L01pTx (CPU_INT8U ch, CPU_INT8U * const pdata, CPU_INT16U len)
{
    BspnRF24L01pWrReg(RF_CH, ch);
    BspnRF24L01pClrTxFIFO();
	BspnRF24L01pWrTxFIFO(pdata, len);
    BspnRF24L01pWrReg(STATUS, TX_DS);
}

void BspnRF24L01pRx (CPU_INT8U ch)
{
    BspnRF24L01pWrReg(RF_CH, ch);
    BspnRF24L01pClrRxFIFO();
    BspnRF24L01pWrReg(CONFIG, EN_CRC | CRCO | PWR_UP | PRIM_RX);
    BspTimerDelayUS(80);
    BspnRF24L01pCEHigh(); 
}

CPU_INT8U BspnRF24L01pComplete (CPU_INT8U ch, CPU_INT8U *pdata, CPU_INT16U check)
{
    CPU_INT8U  n;
    CPU_INT8U  pw;
    CPU_INT8U  status;
    CPU_INT16U ack;
    CPU_BOOL   flag;
    
    BspTimerDelayUS(20);
	BspnRF24L01pEnhancedShockBurst();
    BspTimerDelayUS(20);
	
	/* Wait for TX complete*/
    n = 0;
    while (BspnRF24L01pIrq() != DEF_LOW)
    {
        n++;
        if (n == BSP_NRF24L01P_TX_WAIT)
        {
            break;
        }
        BspTimerDelayUS(20);
    }

    if (n < BSP_NRF24L01P_TX_WAIT)    
    {
        BspTimerMeasureHoldOn();
        BspnRF24L01pWrReg(STATUS, RX_DR | TX_DS | MAX_RT);
        BspnRF24L01pRx(ch);
        /* Wait for TX complete*/
        n = 0;
        while (BspnRF24L01pIrq() != DEF_LOW)
        {
            n++;
            if (n == BSP_NRF24L01P_RX_WAIT)
            {
                break;
            }
            BspTimerDelayUS(20);
        }
        //BspnRF24L01pRdReg(STATUS, &status);
        //if (status & RX_DR)
        if (n < BSP_NRF24L01P_RX_WAIT)
        {
            BspnRF24L01pRdReg(STATUS, &status);
            if (status & RX_DR)
            {
                BspnRF24L01pRxFIFOPWGet(&pw);
                if (pw <= BSP_NRF24L01P_ACK_LEN)
                {
                    BspnRF24L01pRdRxFIFO(pdata, pw);
                    ack = ((CPU_INT16U)(pdata[0] << 8) & 0xFF00) | pdata[1];
                    if (ack == check)
                    {
                        flag = BSP_RF_OK;
                    }
                    else
                    {
                        flag = BSP_RF_ERR_ACK;
                    }
                }
                else
                {
                    flag = BSP_RF_ERR_LEN;
                }
            }
            else
            {
                flag = BSP_RF_ERR_RX;
            }
        }
        else
        {
            //BspLedOn();//
            //BspLedOff();//
            flag = BSP_RF_ERR_RX_TIMEOUT;
        }
        BspTimerMeasureHoldOff();
    }
    else
    {
        flag = BSP_RF_ERR_TX_TIMEOUT;
    }
    
    BspnRF24L01pWrReg(STATUS, RX_DR | TX_DS | MAX_RT);
	BspnRF24L01pSetSleep();
    
    return flag;
}


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/