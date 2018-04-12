/*************************************************************************************************************
*                                              INCLUDE FILES                                                 *
*************************************************************************************************************/
#include <bsp.h>


/*************************************************************************************************************
*                                              LOCAL TABLES                                                  *
*************************************************************************************************************/


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void BspTimerDelayL (CPU_INT16U delay)
{
    TMKAMK = 1U;    /* disable INTIT interrupt */
    TMKAIF = 0U;    /* clear INTIT interrupt flag */
    ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
    ITMC = delay;
    TMKAMK = 0U;    /* enable INTIT interrupt */
    ITMC |= _8000_IT_OPERATION_ENABLE;    /* enable IT operation */
    __stop();
    TMKAMK = 1U;    /* disable INTIT interrupt */
    TMKAIF = 0U;    /* clear INTIT interrupt flag */
    ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
}

void BspTimerDelayH (CPU_INT16U delay)
{
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
	TDR00 = delay;
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TS0 |= _0001_TAU_CH0_START_TRG_ON;
	__halt();
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}

void BspTimerDelayUS (CPU_INT16U delay)
{
    R_TAU0_Channel0_Clear_Count();
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    if (delay > 18)
    {
        TDR00 = delay - 18;
    }
    else
    {
       TDR00 = delay; 
    }    
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TS0 |= _0001_TAU_CH0_START_TRG_ON;
    while (R_TAU0_Channel0_Get_Count() == 0)
    {
        __halt();
    }
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}

void BspTimerSynDelay (CPU_INT16U pulse, CPU_INT8U slot)
{
    CPU_INT16U delay;
    
    R_TAU0_Channel2_Clear_Count();
    TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
    /* Mask channel 2 interrupt */
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    delay = pulse * slot + 10;
    TDR02 = delay;
    TMMK02 = 0U;    /* enable INTTM02 interrupt */
    TS0 |= _0004_TAU_CH2_START_TRG_ON;
	while (R_TAU0_Channel2_Get_Count() == 0)
    {
        __halt();
    }
    R_TAU0_Channel2_Clear_Count();
    TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
    /* Mask channel 2 interrupt */
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    TDR02 = pulse;   
    TMMK02 = 0U;    /* enable INTTM02 interrupt */
    TS0 |= _0004_TAU_CH2_START_TRG_ON;
}

void BspTimerSynGet (void)
{
    CPU_INT16U cnt;
    
    cnt = R_TAU0_Channel2_Get_Count();
    while (cnt == R_TAU0_Channel2_Get_Count());
}

void BspTimerSynStop (void)
{
    R_TAU0_Channel2_Stop();
}

void BspTimerMeasureStart (void)
{
    R_TAU0_Channel1_Start();
}

CPU_INT16U BspTimerMeasureDelayGet (void)
{
    return R_TAU0_Channel1_Get_Count();
}

void BspTimerMeasureStop (void)
{
    R_TAU0_Channel1_Stop();
}

void BspTimerMeasureHoldOn (void)
{
    TT0 |= _0002_TAU_CH1_STOP_TRG_ON;
    /* Mask channel 1 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
}

void BspTimerMeasureHoldOff (void)
{
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    TMMK01 = 0U;    /* enable INTTM01 interrupt */
    TS0 |= _0002_TAU_CH1_START_TRG_ON;
}

/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/