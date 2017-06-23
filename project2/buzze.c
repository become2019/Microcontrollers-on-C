#include"buzze.h"
#include"buzze_cfg.h"
/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               buzze.h
** Latest modified Date:    2017-5-31
** Latest Version:          
** Descriptions:            蜂鸣器实现文件
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

/*********************************************************************************************************
** Function name:           buzzeInit
** Descriptions:             蜂鸣器初始化
** input parameters:      none
** output parameters:       char
** Returned value:      0------初始化成功
                                 -1----初始化失败
*********************************************************************************************************/

static volatile unsigned char GucLow8;
static volatile unsigned char GucHigh8;

static unsigned int GuiHigh16; //高16位
static  volatile unsigned char Guctime32Flag=0;  //32位定时器溢出标志
char buzzeInit()
{
	//定时器1
	TMOD=(TMOD&0x0f)|0x10;
	TR1=0;
	TF1=0;
	ET1=1;
	PT1=1;
	//定时器0
	time0Init();
   return 0;
}


/*********************************************************************************************************
** Function name:           buzzeRun
** Descriptions:             蜂鸣器鸣叫
** input parameters:      uiHz:特定频率,ulTime;特定时间，以100us为单位
** output parameters:       none
** Returned value:      
                                 
*********************************************************************************************************/
void buzzeRun(unsigned int uiHz,unsigned long ulTime )
{
	unsigned int uiStart;
	
	uiStart=0x10000-(11059200ul/12)/(uiHz*2);
	GucHigh8=uiStart/0x100;
	GucLow8=uiStart%0x100;
	
	TH1=GucHigh8;
	TL1=GucLow8;
	TR1=1;
	delay100us(ulTime);
	
	
}


/*********************************************************************************************************
** Function name:           time1Interrupt
** Descriptions:             定时器1中断函数
** input parameters:      none
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
void time1Interrupt()  interrupt 3
{
	TR1=0;
	
	TH1=GucHigh8;
	TL1=GucLow8;
	TR1=1;
	
	BUZZE_PIN=!BUZZE_PIN;
}

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
void delay100us(unsigned long uiTime)
{
	 unsigned long ulSatrt;
	 unsigned int uiLow16;
	 ulSatrt=((11059200ul/12)/400)*uiTime/(10000ul/400);
	 ulSatrt=-ulSatrt;
	 
	 uiLow16=ulSatrt%0x10000;
	 TL0=uiLow16%256;
	 TH0=uiLow16/256;
	 
	 GuiHigh16=ulSatrt/0x10000;
	 
	 TR0=1;
	 
	 while(Guctime32Flag==0){};
	 Guctime32Flag=0;
	   
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
	GuiHigh16++;
	if(GuiHigh16==0){
		Guctime32Flag=1;
		TR0=0;
		TR1=0;
		
	}
}


