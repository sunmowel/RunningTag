/*************************************************************************************************************
*                                                  MODULE                                                    *
*************************************************************************************************************/
#ifndef BSP_LED_H
#define BSP_LED_H

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************************************************
*                                            FUNCTION PROTOTYPES                                             *
*************************************************************************************************************/
static inline void BspLedOn(void)
{
	P2_bit.no2 = 1;
}

static inline void BspLedOff(void)
{
	P2_bit.no2 = 0;
}

static inline void BspLedToggle(void)
{
	P2_bit.no2 = ~P2_bit.no2;
}


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
