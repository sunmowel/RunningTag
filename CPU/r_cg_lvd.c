/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_lvd.c
* Version      : CodeGenerator for RL78/G12 V2.03.03.03 [07 Mar 2016]
* Device(s)    : R5F1026A
* Tool-Chain   : CCRL
* Description  : This file implements device driver for LVD module.
* Creation Date: 2016/8/23
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_lvd.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LVD_Create
* Description  : This function initializes the voltage detector.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LVD_Create(void)
{
    LVIMK = 1U;        /* disable INTLVI interrupt */
    LVIIF = 0U;        /* clear INTLVI interrupt flag */
    /* Set INTLVI low priority */
    LVIPR1 = 1U;
    LVIPR0 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_LVD_InterruptMode_Start
* Description  : This function enables the voltage detector interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LVD_InterruptMode_Start(void)
{
    LVIIF = 0U;     /* clear INTLVI interrupt flag */
    LVIMK = 0U;     /* enable INTLVI interrupt */
}

/* Start user code for adding. Do not edit comment generated here */
uint8_t R_LVD_LVIF_Get (void)
{
	return LVIF;
}
/* End user code. Do not edit comment generated here */
