/*
*******************************************************************************
* Copyright(C) 2010, 2011 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by CodeGenerator for RL78/G13
* 16-Bit Single-Chip Microcontrollers
* Filename:	        r_cg_macrodriver.h
* Abstract:	        This file implements general head file.
* APIlib:	        CodeGenerator for RL78/G13 V1.01.00 [31 May 2011]
* Device:	        R5F100LE
* Compiler:	        ICCRL78
* Creation date:	06/07/2011
*******************************************************************************
*/

#ifndef _MDSTATUS_
#define _MDSTATUS_
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include <intrinsics.h>
#include <ior5f10268.h>
#include <ior5f10268_ext.h>
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#ifndef __TYPEDEF__
typedef signed char		    int8_t;
typedef unsigned char		uint8_t;
typedef signed short		int16_t;
typedef unsigned short		uint16_t;
typedef signed long		    int32_t;
typedef unsigned long		uint32_t;
typedef	unsigned short		MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE		0x00U
#define MD_OK			(MD_STATUSBASE + 0x00U)	/* register setting OK */
#define MD_SPT			(MD_STATUSBASE + 0x01U)	/* IIC stop */
#define MD_NACK			(MD_STATUSBASE + 0x02U)	/* IIC no ACK */
#define MD_BUSY1		(MD_STATUSBASE + 0x03U)	/* busy 1 */
#define MD_BUSY2		(MD_STATUSBASE + 0x04U)	/* busy 2 */

/* Error list definition */
#define MD_ERRORBASE		0x80U
#define MD_ERROR		(MD_ERRORBASE + 0x00U)	/* error */
#define MD_ARGERROR		(MD_ERRORBASE + 0x01U)	/* error agrument input error */
#define MD_ERROR1		(MD_ERRORBASE + 0x02U)	/* error 1 */
#define MD_ERROR2		(MD_ERRORBASE + 0x03U)	/* error 2 */
#define MD_ERROR3		(MD_ERRORBASE + 0x04U)	/* error 3 */
#define MD_ERROR4		(MD_ERRORBASE + 0x05U)	/* error 4 */
#define __TYPEDEF__
#endif
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/

#endif

