/*************************************************************************************************************
*                                                  MODULE                                                    *
*************************************************************************************************************/
#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
static inline CPU_BOOL BspAnalogGet (void)
{
    if (P4_bit.no2 == 1)
    {
        return DEF_HIGH;
    }
    else
    {
        return DEF_LOW;
    }
}


/*************************************************************************************************************
*                                            FUNCTION STATEMENT                                              *
*************************************************************************************************************/
void BspAnalogGetValue (CPU_INT16U *pvalue);
void BspAnalogOpenR (void);
void BspAnalogOpenF (void);
void BspAnalogOn(void);
void BspAnalogOff(void);


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
