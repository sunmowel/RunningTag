/*************************************************************************************************************
*                                                  MODULE                                                    *
*************************************************************************************************************/
#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************************************************
*                                                 DEFINES                                                    *
*************************************************************************************************************/
#define BSP_TIMER_DELAY_L_200US                 0x0001U
#define BSP_TIMER_DELAY_L_240US                 0x0003U
#define BSP_TIMER_DELAY_L_241US                 0x0004U
#define BSP_TIMER_DELAY_L_300US                 0x0001U
#define BSP_TIMER_DELAY_L_1600US          	    0x0013U
#define BSP_TIMER_DELAY_L_2MS                   0x001EU	
#define BSP_TIMER_DELAY_L_3MS                   0x002DU	
#define BSP_TIMER_DELAY_L_5MS                   0x004BU	
#define BSP_TIMER_DELAY_L_65MS  			    0x03D8U

#define BSP_TIMER_DELAY_H_16US                  0x000AU
#define BSP_TIMER_DELAY_H_20US                  0x0020U 
#define BSP_TIMER_DELAY_H_50US     			    0x018FU
#define BSP_TIMER_DELAY_H_200US                 0x07D0U	// 0x05F0U,0x0640U,0x0690U,0x06E0U,0x0730U,0x0780U,0x07D0U
#define BSP_TIMER_DELAY_H_300US                 0x0910U	
#define BSP_TIMER_DELAY_H_320US                 0x09B0U	
#define BSP_TIMER_DELAY_H_340US                 0x0A50U	
#define BSP_TIMER_DELAY_H_360US                 0x0AF0U	
#define BSP_TIMER_DELAY_H_380US                 0x0B90U	 
#define BSP_TIMER_DELAY_H_400US                 0x0C30U
#define BSP_TIMER_DELAY_H_420US                 0x0CD0U
#define BSP_TIMER_DELAY_H_460US                 0x0E10U
#define BSP_TIMER_DELAY_H_500US                 0x0F50U
#define BSP_TIMER_DELAY_H_540US                 0x1090U
#define BSP_TIMER_DELAY_H_560US                 0x1130U
#define BSP_TIMER_DELAY_H_580US                 0x11D0U
#define BSP_TIMER_DELAY_H_640US                 0x13B0U
#define BSP_TIMER_DELAY_H_720US                 0x1630U
#define BSP_TIMER_DELAY_H_740US                 0x16D0U
#define BSP_TIMER_DELAY_H_800US                 0x18B0U

#define BSP_TIME_SYN_WAIT				        160u


/*************************************************************************************************************
*                                                 DATA TYPES                                                 *
*************************************************************************************************************/



/*************************************************************************************************************
*                                            FUNCTION STATEMENT                                              *
*************************************************************************************************************/
void BspTimerDelayL (CPU_INT16U delay);
void BspTimerDelayH (CPU_INT16U delay);
void BspTimerDelayUS (CPU_INT16U delay);
void BspTimerSynDelay (CPU_INT16U pulse, CPU_INT8U slot);
void BspTimerSynGet (void);
void BspTimerSynStop (void);
void BspTimerMeasureStart (void);
CPU_INT16U BspTimerMeasureDelayGet (void);
void BspTimerMeasureStop (void);
void BspTimerMeasureHoldOn (void);
void BspTimerMeasureHoldOff (void);


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
