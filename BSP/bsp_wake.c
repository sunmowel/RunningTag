/*************************************************************************************************************
*                                              INCLUDE FILES                                                 *
*************************************************************************************************************/
#include <bsp.h>


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void BspWakeUp (void)
{
    R_INTC1_Flag_Clear();
    R_INTC1_Start();
    __stop();
    R_INTC1_Stop();
}

CPU_BOOL BspWakeWait (CPU_INT16U cnt)
{
    CPU_INT16U i;
    
    R_INTC1_Flag_Clear();
    R_INTC1_Start(); 
    for (i = 0; i < cnt; i++)
    {
        TMKAMK = 1U;    /* disable INTIT interrupt */
        TMKAIF = 0U;    /* clear INTIT interrupt flag */
        ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
        ITMC = BSP_TIMER_DELAY_L_65MS;
        TMKAMK = 0U;    /* enable INTIT interrupt */
        ITMC |= _8000_IT_OPERATION_ENABLE;    /* enable IT operation */
        __stop();
        TMKAMK = 1U;    /* disable INTIT interrupt */
        TMKAIF = 0U;    /* clear INTIT interrupt flag */
        ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
        if (R_INTC1_Flag_Get() == 1)
        {
            R_INTC1_Stop();
            return DEF_ON;
        }
    }

    return DEF_OFF;
}

void BspWakeFilter (CPU_INT16U cnt)
{
    CPU_INT16U i;
    
    for (i = 0; i < cnt; i++)
    {
        TMKAMK = 1U;    /* disable INTIT interrupt */
        TMKAIF = 0U;    /* clear INTIT interrupt flag */
        ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
        ITMC = BSP_TIMER_DELAY_L_65MS;
        TMKAMK = 0U;    /* enable INTIT interrupt */
        ITMC |= _8000_IT_OPERATION_ENABLE;    /* enable IT operation */
        __stop();
        TMKAMK = 1U;    /* disable INTIT interrupt */
        TMKAIF = 0U;    /* clear INTIT interrupt flag */
        ITMC &= (CPU_INT16U)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
    }
}



/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/