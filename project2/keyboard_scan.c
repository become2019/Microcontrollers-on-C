/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               keyboard_scan.c
** Latest modified Date:    2017-5-9
** Latest Version:          
** Descriptions:            键盘驱动头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-5-9
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
#include<8051.h>
#include"./keyboard_scan.h"
#include"./keyboard_scan_cfg.h"


/*********************************************************************************************************
** Function name:           keyboardInit
** Descriptions:             键盘初始化
** input parameters:      none
** output parameters:       char
** Returned value:      0------初始化成功
                                 -1----初始化失败
*********************************************************************************************************/

 char keyboardInit()
 {
	 return 0;
 }


/*********************************************************************************************************
** Function name:           allKeyCheck
** Descriptions:             检测有按键是否被按下
** input parameters:      none
** output parameters:       none
** Returned value:        ‘key’-------有按下key键，
                                  -1------无按下
*********************************************************************************************************/
char allKeyCheck()
{
	char cOut=-1;
	unsigned char i,j;
	for(i=0;i<4;i++)
	{
		KEYBOARD_KR1_PIN=1;
		KEYBOARD_KR2_PIN=1;
		KEYBOARD_KR3_PIN=1;
		KEYBOARD_KR4_PIN=1;
		KEYBOARD_KC1_PIN=1;
		KEYBOARD_KC2_PIN=1;
		KEYBOARD_KC3_PIN=1;
		switch(i)
		{
			case 0:
				KEYBOARD_KR1_PIN=0;
				break;
			case 1:
				KEYBOARD_KR2_PIN=0;
				break;
			case 2:
				KEYBOARD_KR3_PIN=0;
				break;
			case 3:
				KEYBOARD_KR4_PIN=0;
				break;
		}
		for(j=0;j<3;j++)
		{
			KEYBOARD_NC_PIN=1;
			switch(j)
			{
				case 0:
					if(KEYBOARD_KC1_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
				case 1:
					if(KEYBOARD_KC2_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
				case 2:
					if(KEYBOARD_KC3_PIN==0)
					KEYBOARD_NC_PIN=0;
					break;
			}
			if(KEYBOARD_NC_PIN==0)
			{
				cOut=i*3+j+'1';
			}
		}
	}
	if(cOut==('0'+10)||cOut==('0'+12))
		cOut=-1;
	if(cOut==('0'+11))
		cOut='0';
	return cOut;
}

/*********************************************************************************************************
** Function name:           throwError
** Descriptions:             消抖
** input parameters:      none
** output parameters:       none
** Returned value:        none
*********************************************************************************************************/

void throwError()
{
	unsigned char uiNumber=100;
	unsigned char i;
	do{
		i=46;
		do{
		}while(--i!=0);
	}while(--uiNumber!=0);
}

/*********************************************************************************************************
** Function name:           isExsitPushKey
** Descriptions:             是否存在按下的按键，已经消抖
** input parameters:      none
** output parameters:       none
** Returned value:        ‘key’-------有按下key键，
                                  -1------无按下
*********************************************************************************************************/
char isExsitPushKey()
{
	char cKey;
	if((cKey=allKeyCheck())>0)
	{
		throwError();
		if(cKey==allKeyCheck())
			;
		else
			cKey=-1;
	}
	return cKey;
}

/*********************************************************************************************************
** Function name:           isExsitRealaseKey
** Descriptions:             是否存在按下的按键已经释放，已经消抖
** input parameters:      none
** output parameters:       none
** Returned value:        0-------有释放
                                  -1------无释放
*********************************************************************************************************/
char isExsitRealaseKey()
{
	if(allKeyCheck()<0)
	{
		throwError();
		if(allKeyCheck()<0)
		   return 0;
	}
	return -1;
	
}

