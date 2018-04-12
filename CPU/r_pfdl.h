/*================================================================================================*/
/* Project      = Flash Data Library T04 (PicoFDL)                                                */
/* Module       = pfdl.h                                                                          */
/* Device:      = RL78                                                                            */
/* Version      = V1.04                                                                           */
/* Date         = 13.04.2012                                                                      */
/*================================================================================================*/
/*                                  COPYRIGHT                                                     */
/*================================================================================================*/
/* Copyright (c) 2011-2012 by Renesas Electronics Europe GmbH, a company of the Renesas           */
/* Electronics Corporation. All rights reserved.                                                  */
/*================================================================================================*/
/*                                                                                                */
/* Purpose:     contains the C language API definition of the Flash Data Library.                 */
/*                                                                                                */
/*================================================================================================*/
/*                                                                                                */
/* Warranty Disclaimer                                                                            */
/*                                                                                                */
/* Because the Product(s) is licensed free of charge, there is no warranty of any kind whatsoever */
/* and expressly disclaimed and excluded by Renesas, either expressed or implied, including but   */
/* not limited to those for non-infringement of intellectual property, merchantability and/or     */
/* fitness for the particular purpose.                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the        */
/* supplied Product(s) and/or the Application.                                                    */
/*                                                                                                */
/* Each User is solely responsible for determining the appropriateness of using the Product(s)    */
/* and assumes all risks associated with its exercise of rights under this Agreement, including,  */
/* but not limited to the risks and costs of program errors, compliance with applicable laws,     */
/* damage to or loss of data, programs or equipment, and unavailability or interruption of        */
/* operations.                                                                                    */
/*                                                                                                */
/* Limitation of Liability                                                                        */
/*                                                                                                */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect,   */
/* or punitive damage (including but not limited to lost profits) regardless of whether such      */
/* liability is based on breach of contract, tort, strict liability, breach of warranties,        */
/* failure of essential purpose or otherwise and even if advised of the possibility of such       */
/* damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in            */
/* connection with the Product(s) and/or the Application.                                         */
/*                                                                                                */
/*================================================================================================*/


#ifndef PFDL_H
#define PFDL_H

void ERROR_Handler(void);
void PFDL_Init(void);
unsigned char PFDL_BlankCheck(unsigned int Flash_index,unsigned int Length);
void PFDL_Erase(unsigned int Flash_index);
void PFDL_Write(unsigned int Flash_index,unsigned char *W_DataFla_buff,unsigned int Data_Count);
unsigned char PFDL_Iverify(unsigned int Flash_index,unsigned int Length);
void PFDL_Read(unsigned int Flash_index,unsigned char *R_DataFla_buff,unsigned int Data_Count);


#endif
