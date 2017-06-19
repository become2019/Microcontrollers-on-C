/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               led_disp.c
** Latest modified Date:    2017-5-2
** Latest Version:          
** Descriptions:            LED数码管驱动
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
#include<string.h>
#include "led_disp_cfg.h"    //包含模块/驱动配置头文件
#include "led_disp.h"         //包含模块/驱动应用头文件


/*********************************************************************************************************
** Function name:           ledDisplayInit
** Descriptions:            LED数码管驱动初始化
** input parameters:        none
** output parameters:       none
** Returned value:          0:  成功
**                          -1: 失败
*********************************************************************************************************/
char ledDisplayInit(void)
{
	return 0;
}

unsigned char GucLedDisplayShowBuf[6];  //定义显示缓冲区

static code  unsigned char GucShowTable[][2] = {                      /*  共阴极显示字库                    */
    {'0', 0x3f}, {'1', 0x06}, {'2', 0x5b}, {'3', 0x4f}, {'4', 0x66},
    {'5', 0x6d}, {'6', 0x7d}, {'7', 0x07}, {'8', 0x7f}, {'9', 0x6f},
    {'A', 0x77}, {'B', 0x7c}, {'C', 0x39}, {'D', 0x5e}, {'E', 0x79}, {'F', 0x71},
    {'a', 0x77}, {'b', 0x7c}, {'c', 0x39}, {'d', 0x5e}, {'e', 0x79}, {'f', 0x71},
    {'O', 0x3f}, {'R', 0x50}, {'P', 0x73}, {'N', 0x37}, {'-', 0x40},
    {'o', 0x5c}, {'r', 0x50}, {'p', 0x73}, {'n', 0x37}, {' ', 0x00}, {'\011', 0x00},
	{'L',0x38},{'l',0x30},{'V',0x3e},{'H',0x76},
    {0x00, 0x00}
};

static code unsigned char GucTimeShowTable[10]={
	0x3f, 0x06,0x5b,0x4f,0x66,0x6d,0x7d ,0x07,  0x7f, 0x6f
};

/*********************************************************************************************************
** Function name:           ledDisplayScan
** Descriptions:             LED数码管扫描程序，必须以不小于200Hz的频率调用
** input parameters:        none
** output parameters:       none
** Returned value:         
*********************************************************************************************************/
void ledDisplayScan(void)
{
	static unsigned char ucIndex=0;   //定义扫描位置索引静态变量
	
	/*
         关闭显示
         */
	
	_LED_DIG1_OFF();
	_LED_DIG2_OFF();
	_LED_DIG3_OFF();
	_LED_DIG4_OFF();
	_LED_DIG5_OFF();
	_LED_DIG6_OFF();
	
	/*
       显示ucIndex位：将待显示数字字符的数值送到段选位控制I/0口
      */
	_LED_SEG(~GucLedDisplayShowBuf[ucIndex]);
	switch(ucIndex)
	{
		case 0:
			_LED_DIG1_ON();     //点亮数码管1
			break;
		case 1:
			_LED_DIG2_ON();     //点亮数码管2
			break;
		case 2:
			_LED_DIG3_ON();     //点亮数码管3
			break;
		case 3:
			_LED_DIG4_ON();     //点亮数码管4
			break;
		case 4:
			_LED_DIG5_ON();     //点亮数码管5
			break;
		case 5:
			_LED_DIG6_ON();     //点亮数码管6
			break;
		default:
			break;
	}
	
	/*
        准备显示下一位
       */
	ucIndex++;
	if(ucIndex>=6)
		ucIndex=0;      //超出则回到起点
}

/*********************************************************************************************************
** Function name:           ledDisplayPuts
** Descriptions:             输出字符串
** input parameters:     要输出的字符串
** output parameters:       none
** Returned value:        0-------成功，
                                  -1------失败
*********************************************************************************************************/
char ledDisplayPuts(char *pStr)
{
	char i;
	unsigned char j;
	
	if(pStr==NULL)
		return -1;
	
	for(i=0;i<6;i++)
	{
		if(*pStr==0)
		{
			GucLedDisplayShowBuf[i]=0;//如果到了字符串尾，把剩下的数码管置成全熄灭
			continue;                       //指针不动，提前结束循环
		}
		
		/*
	          小数点单独处理:把小数点进行或运算合并到前一个字符去
              */
		if(*pStr=='.')
		{
			i--;
			GucLedDisplayShowBuf[i]|=0x80;
		}
		else
		{
			/*
		        查找字符串
                        */
			for(j=0;GucShowTable[j][0]!=0;j++)
			{
				if(*pStr==(char)GucShowTable[j][0])
				{
				   /*
				     将待显示的字符输入缓冲区
                                      */
					GucLedDisplayShowBuf[i]=GucShowTable[j][1];
					break;
				}
				
			}
		}
		pStr++;
	}
	return 0;
	
}

/*********************************************************************************************************
** Function name:           ledDisplayDecPuts
** Descriptions:             输出针对十进制字符串
** input parameters:     pcStr：要输入针对十进制字符串,ucLen：字符串的长度
** output parameters:       none
** Returned value:        0-------成功，
                                  -1------失败
*********************************************************************************************************/
char ledDisplayDecPuts(char *pStr,unsigned char ucLen)
{
	unsigned char i;
	
	if(pStr==NULL)
		return -1;
	for(i=0;i<ucLen;i++)
	{
		if(pStr[i]>='0'&&pStr[i]<='9')
		GucLedDisplayShowBuf[i]=GucTimeShowTable[pStr[i]-'0'];
	}
	return 0;
}

/*********************************************************************************************************
** Function name:           ledDisplayClr
** Descriptions:             清屏
** input parameters:     none
** output parameters:       none
** Returned value:        0-------成功，
                                  -1------失败
*********************************************************************************************************/
char ledDisplayClr(void)
{
	memset(GucLedDisplayShowBuf,0,6);//内存空间初始化
	return 0;
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
	 TL1  = (65536 - ((11059200ul / 12) /1000)) % 256;
    TH1  = (65536 - ((11059200ul / 12) / 1000)) / 256;
    ledDisplayScan();
}

/*********************************************************************************************************
** Function name:           time1nit
** Descriptions:             定时器1初始化
** input parameters:      none
** output parameters:       char
** Returned value:      0------初始化成功
                                 -1----初始化失败
*********************************************************************************************************/
char time1Init()
{
	TMOD = (TMOD & 0x0f) | 0x10;
    TL1  = (65536 - ((11059200ul / 12) /1000)) % 256;
    TH1  = (65536 - ((11059200ul / 12) / 1000)) / 256;
    TR1  = 1;
    ET1  = 1;
	PT1=1;
	return 0;
}

