/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Key.c
** Latest modified Date:    2017-5-15
** Latest Version:          
** Descriptions:                 矩阵键盘动态扫描驱动
**
**--------------------------------------------------------------------------------------------------------
** Created by:             LX
** Created date:            2017-5-10
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
#include"./Key_cfg.h"
#include"./Key.h"

/*********************************************************************************************************
** Function name:         KeyNumberGet
** Descriptions:            矩阵键盘的行列扫描
** input parameters:        none
** output parameters:       none
** Returned value:          -1: 无按键按下
**                          	   其他：相应的键位
*********************************************************************************************************/
char KeyNumberGet(void)
{
	char KeyNumber;//键值
	unsigned char KeySum;  //检测是否有按键按下
	
	KeyNumber=-1;
	KeySum=0;
	
	__KEY_C1=1;
	__KEY_C2=1;
	__KEY_C3=1;
	__KEY_R1=1;
	__KEY_R2=1;
	__KEY_R3=1;
	__KEY_R4=1;
	
	//扫描第一行
	__KEY_R1=0;
	if(__KEY_C1==0)
	{
		KeyNumber=1;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=2;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=3;
		KeySum++;
	}
	__KEY_R1=1;//第一行扫描完毕
	
	//扫描第二行
	__KEY_R2=0;
	if(__KEY_C1==0)
	{
		KeyNumber=4;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=5;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=6;
		KeySum++;
	}
	__KEY_R2=1;//第二行扫描完毕
	
	//扫描第三行
	__KEY_R3=0;
	if(__KEY_C1==0)
	{
		KeyNumber=7;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=8;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=9;
		KeySum++;
	}
	__KEY_R3=1;//第三行扫描完毕
	
	//扫描第四行
	__KEY_R4=0;
	if(__KEY_C1==0)
	{
		KeyNumber=-2;
		KeySum++;
	}
	if(__KEY_C2==0)
	{
		KeyNumber=0;
		KeySum++;
	}
	if(__KEY_C3==0)
	{
		KeyNumber=-3;
		KeySum++;
	}
	__KEY_R4=1;//第一行扫描完毕
	
	if(KeySum!=1)
	{
		return -1;
	} 
	if(KeyNumber>=0)
		KeyNumber+='0';
	return KeyNumber;
}


