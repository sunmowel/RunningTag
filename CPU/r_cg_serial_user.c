/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial_user.c
* Version      : CodeGenerator for RL78/G12 V2.02.00.02 [11 Feb 2014]
* Device(s)    : R5F10268
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 2014/8/1
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_csi00_rx_address;         /* csi00 receive buffer address */
extern volatile uint16_t  g_csi00_rx_length;           /* csi00 receive data length */
extern volatile uint16_t  g_csi00_rx_count;            /* csi00 receive data count */
extern volatile uint8_t * gp_csi00_tx_address;         /* csi00 send buffer address */
extern volatile uint16_t  g_csi00_send_length;         /* csi00 send data length */
extern volatile uint16_t  g_csi00_tx_count;            /* csi00 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_csi00_interrupt
* Description  : This function is INTCSI00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTCSI00_vect
__interrupt static void r_csi00_interrupt(void)
{
    uint8_t err_type;
    uint8_t sio_dummy;

    err_type = (uint8_t)(SSR00 & _0001_SAU_OVERRUN_ERROR);
    SIR00 = (uint16_t)err_type;

    if (err_type != 1U)
    {
        if (g_csi00_tx_count > 0U)
        {
            if (0U != gp_csi00_rx_address)
            {
                *gp_csi00_rx_address = SIO00;
                gp_csi00_rx_address++;
            }
            else
            {
                sio_dummy = SIO00;
            }

            if (0U != gp_csi00_tx_address)
            {
                SIO00 = *gp_csi00_tx_address;
                gp_csi00_tx_address++;
            }
            else
            {
                SIO00 = 0xFFU;
            }
            g_csi00_tx_count--;        
        }
        else
        {
            if (0U == g_csi00_tx_count)
            {
                if (0U != gp_csi00_rx_address)
                {
                    *gp_csi00_rx_address = SIO00;
                }
                else
                {
                    sio_dummy = SIO00;
                }
            }

            r_csi00_callback_sendend();    /* complete send */
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_csi00_callback_sendend
* Description  : This function is a callback function when CSI00 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    __no_operation();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void SPITxByte(uint8_t * const pbyte)
{
	uint8_t  rx_buf;
   
    R_CSI00_Send_Receive(pbyte, 1, &rx_buf);
	__halt();
}

void SPIRxByte(uint8_t *pbyte)
{
	uint8_t  tx_buf;
	
	tx_buf = 0;
    R_CSI00_Send_Receive(&tx_buf, 1, pbyte);
	__halt();
}

void SPITxData(uint8_t * const pdata, uint16_t len)
{
    uint16_t i;
	
    for (i = 0; i < len; i++)
    {  
        SPITxByte(&pdata[i]);
    }
}

void SPIRxData(uint8_t *pdata, uint16_t len)
{
    uint16_t i;
	
    for (i = 0; i < len; i++)
    {  
        SPIRxByte(&pdata[i]);
    }
}
/* End user code. Do not edit comment generated here */
