/*************************************************************************************************************
*                                                   MODULE                                                   *
*************************************************************************************************************/
#ifndef CPU_H
#define CPU_H

#ifdef __cplusplus
extern "C" {
#endif
  
    
/*************************************************************************************************************
*                                                 DATA TYPES                                                 *
*************************************************************************************************************/
typedef unsigned char  CPU_BOOL;
typedef unsigned char  CPU_INT8U;              
typedef signed   char  CPU_INT8S;               
typedef unsigned short CPU_INT16U;             
typedef signed   short CPU_INT16S;            
typedef unsigned long  CPU_INT32U;             
typedef signed   long  CPU_INT32S;
typedef float          CPU_F32;           
typedef double         CPU_F64;

typedef void (*FNCT_VOID)(void); 
typedef void (*FNCT_IO)(CPU_BOOL *val);
typedef void (*FNCT_HANDLE)(void);
typedef void (*FNCT_COMM)(CPU_INT8U *pdata, CPU_INT16U len);
typedef void (*FNCT_PARA)(CPU_INT16U para); 
typedef void (*FNCT_RESULE)(CPU_INT16U *result); 


/*************************************************************************************************************
*                                                 DEFINES                                                    *
*************************************************************************************************************/   
#define DEF_ON                                  1u     
#define DEF_OFF                                 0u

#define DEF_TRUE                                1u     
#define DEF_FALSE                               0u

#define DEF_HIGH                                1u     
#define DEF_LOW                                 0u

#define DEF_ZERO                                0u

#define DEF_NULL                                (void *)0
    
#ifdef __cplusplus
#define DEF_I                                   volatile        /* defines 'read only' permissions          */
#else
#define DEF_I                                   volatile const  /* defines 'read only' permissions          */
#endif
#define DEF_O                                   volatile        /* defines 'write only' permissions         */
#define DEF_IO                                  volatile        /* defines 'read / write' permissions       */
    
#define DEF_BYTE                                8u                       
    
#define DEF_BIT0                                0x01U
#define DEF_BIT1                                0x02U
#define DEF_BIT2                                0x04U
#define DEF_BIT3                                0x08U
#define DEF_BIT4                                0x10U
#define DEF_BIT5                                0x20U
#define DEF_BIT6                                0x40U
#define DEF_BIT7                                0x80U
#define DEF_BIT8                                0x0100U
#define DEF_BIT9                                0x0200U
#define DEF_BIT10                               0x0400U
#define DEF_BIT11                               0x0800U
#define DEF_BIT12                               0x1000U
#define DEF_BIT13                               0x2000U
#define DEF_BIT14                               0x4000U
#define DEF_BIT15                               0x8000U


/*************************************************************************************************************
*                                               MODULE END                                                   *
*************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif


