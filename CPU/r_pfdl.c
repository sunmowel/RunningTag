/**************************************************
 *
 * This is a template file.
 *
 * Copyright 2011 IAR Systems AB.
 *
* $Revision: 205 $
 *
 **************************************************/
#include "ior5f10268.h"
#include "ior5f10268_ext.h"
#include "intrinsics.h"

#include "pfdl.h"  

#include "r_pfdl.h" 
   

void ERROR_Handler(void)
{
	WDTE = 0xAC;   
}

void PFDL_Init(void)
{
    pfdl_descriptor_t my_pfdl_descriptor_t;         
    pfdl_status_t my_pfdl_status_t;             

	my_pfdl_descriptor_t.fx_MHz_u08 = 1;   //1MHz, must be integer     
	my_pfdl_descriptor_t.wide_voltage_mode_u08 = 0x01;  //00: full-speed mode, 01 wide voltage mode   
	my_pfdl_status_t = PFDL_Open((__near pfdl_descriptor_t*) &my_pfdl_descriptor_t);  
	if (my_pfdl_status_t != PFDL_OK) ERROR_Handler();   
}

unsigned char PFDL_BlankCheck(unsigned int Flash_index,unsigned int Length)
{      
    pfdl_status_t my_pfdl_status_t;           
    pfdl_request_t my_pfdl_request_t; 
    
	my_pfdl_request_t.index_u16 = Flash_index;        
	my_pfdl_request_t.bytecount_u16 = Length;   
	my_pfdl_request_t.command_enu = PFDL_CMD_BLANKCHECK_BYTES;  
	my_pfdl_status_t = PFDL_Execute(&my_pfdl_request_t);      	
	do 
	{
		my_pfdl_status_t = PFDL_Handler();
	}
	while(my_pfdl_status_t == PFDL_BUSY);     	
	return (my_pfdl_status_t);   
}

void PFDL_Erase(unsigned int Flash_index)
{      
    pfdl_status_t my_pfdl_status_t;           
    pfdl_request_t my_pfdl_request_t; 
    
	my_pfdl_request_t.index_u16 = Flash_index;        
	my_pfdl_request_t.command_enu = PFDL_CMD_ERASE_BLOCK;  
	my_pfdl_status_t = PFDL_Execute(&my_pfdl_request_t);      	
	do 
	{
		my_pfdl_status_t = PFDL_Handler();
	}
	while(my_pfdl_status_t == PFDL_BUSY);     	
	if (my_pfdl_status_t != PFDL_OK)  ERROR_Handler();       
}

void PFDL_Write(unsigned int Flash_index,unsigned char *W_DataFla_buff,unsigned int Data_Count)
{       
    pfdl_status_t my_pfdl_status_t;           
    pfdl_request_t my_pfdl_request_t; 
    
	my_pfdl_request_t.index_u16 = Flash_index;
	my_pfdl_request_t.data_pu08 = W_DataFla_buff;     
	my_pfdl_request_t.bytecount_u16 = Data_Count;   
	my_pfdl_request_t.command_enu = PFDL_CMD_WRITE_BYTES;  
	my_pfdl_status_t = PFDL_Execute(&my_pfdl_request_t);      	
	do 
	{
		my_pfdl_status_t = PFDL_Handler();
	}
	while(my_pfdl_status_t == PFDL_BUSY);     	
	if (my_pfdl_status_t != PFDL_OK)  ERROR_Handler();     
}

unsigned char PFDL_Iverify(unsigned int Flash_index,unsigned int Length)
{
    pfdl_status_t my_pfdl_status_t;           
    pfdl_request_t my_pfdl_request_t; 
    
	my_pfdl_request_t.index_u16 = Flash_index;        
	my_pfdl_request_t.bytecount_u16 = Length; 	
	my_pfdl_request_t.command_enu = PFDL_CMD_IVERIFY_BYTES;  
	my_pfdl_status_t = PFDL_Execute(&my_pfdl_request_t);      	
	do 
	{
		my_pfdl_status_t = PFDL_Handler();
	}
	while(my_pfdl_status_t == PFDL_BUSY);     	
	return (my_pfdl_status_t);  
}   

void PFDL_Read(unsigned int Flash_index,unsigned char *R_DataFla_buff,unsigned int Data_Count)
{
    pfdl_status_t my_pfdl_status_t;           
    pfdl_request_t my_pfdl_request_t; 
    
	my_pfdl_request_t.index_u16 = Flash_index;
	my_pfdl_request_t.data_pu08 = R_DataFla_buff;     
	my_pfdl_request_t.bytecount_u16 = Data_Count;   
	my_pfdl_request_t.command_enu = PFDL_CMD_READ_BYTES;  
	my_pfdl_status_t = PFDL_Execute(&my_pfdl_request_t);      	
	do 
	{
		my_pfdl_status_t = PFDL_Handler();
	}
	while(my_pfdl_status_t == PFDL_BUSY);     	
	if (my_pfdl_status_t != PFDL_OK)  ERROR_Handler();     
}