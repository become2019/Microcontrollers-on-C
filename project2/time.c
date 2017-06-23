/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               time.c
** Latest modified Date:    2017-5-31
** Latest Version:          
** Descriptions:            定时器实现文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-31
** Version:                 
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
*--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#include "time.h"
#include<8051.h>
static unsigned int uiHigh16; //高16位
static  volatile unsigned char uctime32Flag=0;  //32位定时器溢出标志

/*********************************************************************************************************
** Function name:           allEnableOpen
** Descriptions:             总使能中断进行使能
** input parameters:      none
** output parameters:       char
** Returned value:      0------使能成功
                                 -1----使能失败
*********************************************************************************************************/
char allEnableOpen()
{
	EA=1;
	return 0;
}

/*********************************************************************************************************
** Function name:           allEnableClose
** Descriptions:             总使能中断进行禁止
** input parameters:      none
** output parameters:       char
** Returned value:      0------禁止成功
                                 -1----禁止失败
*********************************************************************************************************/
char allEnableClose()
{
	EA=0;
	return 0;
}


/*********************************************************************************************************
** Function name:           time0Init
** Descriptions:             定时器0初始化
** input parameters:      none
** output parameters:       char
** Returned value:      0------初始化成功
                                 -1----初始化失败
*********************************************************************************************************/
char time0Init()
{
	TMOD=(TMOD&0xf0)|0x01;
	ET0=1;
	return 0;
}

/*********************************************************************************************************
** Function name:           delay100us
** Descriptions:             延时函数，延时单位为100us
** input parameters:      延时时间
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void delay100us(unsigned int uiTime)
{
	 unsigned long ulSatrt;
	 unsigned int uiLow16;
	 ulSatrt=((11059200ul/12)/400)*uiTime/(10000ul/400);
	 ulSatrt=-ulSatrt;
	 
	 uiLow16=ulSatrt%0x10000;
	 TL0=uiLow16%256;
	 TH0=uiLow16/256;
	 
	 uiHigh16=ulSatrt/0x10000;
	 
	 TR0=1;
	 
	 while(uctime32Flag==0){};
	 uctime32Flag=0;
	   
}


/*********************************************************************************************************
** Function name:           time0Interrupt
** Descriptions:             定时器0中断函数
** input parameters:      none
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void time0Interrupt()  interrupt 1
{
	uiHigh16++;
	
	if(uiHigh16==0){
		uctime32Flag=1;
		TR0=0;
	}
}
