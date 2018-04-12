/*************************************************************************************************************
*                                              INCLUDE FILES                                                 *
*************************************************************************************************************/
#include <bsp.h>


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
void BspAnalogGetValue (CPU_INT16U *pvalue)
{
    CPU_INT16U value;
    
    ADIF = 0U;  /* clear INTAD interrupt flag */
    ADCS = 1U;  /* enable AD conversion */
    /* Wait for the A/D conversion to complete */
	while(ADIF == 0);
	/* Clear ADC interrupt flag */
	ADIF = 0;
    value = ADCR >> 6;
    *pvalue = value;
}

void BspAnalogOpenR (void)
{
	ADCS = 0U;  /* disable AD conversion */
    ADMK = 1U;  /* disable INTAD interrupt */
    ADIF = 0U;  /* clear INTAD interrupt flag */
    ADCE = 0U;  /* disable AD comparator */
	ADS = _00_AD_INPUT_CHANNEL_0;
	ADCE = 1U;  /* enable AD comparator */
}

void BspAnalogOpenF (void)
{
	ADCS = 0U;  /* disable AD conversion */
    ADMK = 1U;  /* disable INTAD interrupt */
    ADIF = 0U;  /* clear INTAD interrupt flag */
    ADCE = 0U;  /* disable AD comparator */
	ADS = _01_AD_INPUT_CHANNEL_1;
	ADCE = 1U;  /* enable AD comparator */
}

void BspAnalogOn(void)
{
    R_ADC_Set_OperationOn();
    BspAnalogOpenR();
}

void BspAnalogOff(void)
{
    R_ADC_Set_OperationOff();
}


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/