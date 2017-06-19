#ifndef __LED_DISPLAY_H
#define __LED_DISPLAY_H
/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               led_disp.h
** Latest modified Date:    2017-5-2
** Latest Version:          
** Descriptions:            LED数码管驱动头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-2
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
** Function name:          ledDisplayInit
** Descriptions:            LED数码管驱动初始化
** input parameters:        none
** output parameters:       none
** Returned value:          0:  成功
**                          -1: 失败
*********************************************************************************************************/

extern char ledDisplayInit(void);


/*********************************************************************************************************
** Function name:           ledDisplayScan
** Descriptions:             LED数码管扫描程序，必须以不小于200Hz的频率调用
** input parameters:        none
** output parameters:       none
** Returned value:         
*********************************************************************************************************/
extern void ledDisplayScan(void);

/*********************************************************************************************************
** Function name:           ledDisplayPuts
** Descriptions:             输出字符串
** input parameters:     要输出的字符串
** output parameters:       none
** Returned value:        0-------成功，
                                  -1------失败
*********************************************************************************************************/

extern char ledDisplayPuts(char *pcStr);
                                            
/*********************************************************************************************************
** Function name:           ledDisplayDecPuts
** Descriptions:             输出针对十进制字符串
** input parameters:     pcStr：要输入针对十进制字符串,ucNumber：字符串的长度
** output parameters:       none
** Returned value:        0-------成功，
                                  -1------失败
*********************************************************************************************************/

extern char ledDisplayDecPuts(char *pcStr,unsigned char ucLen);
/*********************************************************************************************************
** Function name:           ledDisplayClr
** Descriptions:            清屏
** input parameters:        none
** output parameters:       none
** Returned value:          0:  成功
**                          -1: 失败
*********************************************************************************************************/

extern char ledDisplayClr(void);

extern unsigned char GucLedDisplayShowBuf[]; //显示缓冲区

/*********************************************************************************************************
** Function name:           time1Init
** Descriptions:             定时器1初始化
** input parameters:      none
** output parameters:       char
** Returned value:      0------初始化成功
                                 -1----初始化失败
*********************************************************************************************************/
extern char time1Init();

/*********************************************************************************************************
** Function name:           time1Interrupt
** Descriptions:             定时器1中断函数
** input parameters:      none
** output parameters:       none
** Returned value:      
*********************************************************************************************************/
extern void time1Interrupt(void)  interrupt 3;


#endif
