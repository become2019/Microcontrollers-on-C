/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:              i2c.c
** Latest modified Date:    2017-6-13
** Latest Version:          
** Descriptions:           i2c驱动实现文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              jsj
** Created date:            2017-6-13
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
#include"i2c.h"
#include"i2c_cfg.h"


/*********************************************************************************************************
** Function name:           i2cBitSend
** Descriptions:            i2c发送一位数据
** input parameters:        ucData：要发送的数据
** output parameters:       none
** Returned value:          none
**            
*********************************************************************************************************/
static void i2cBitSend(unsigned char ucData)
{
	if(ucData&0x80)
	  I2C_SDA=1;
	else
		I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cBitReceive
** Descriptions:            i2c接收一位数据
** input parameters:        none
** output parameters:       none
** Returned value:          ucReturnValue：接收的一位数据
**                   
*********************************************************************************************************/
static unsigned char i2cBitReceive(void)
{
	unsigned char ucReturnValue;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	ucReturnValue=I2C_SDA;
	I2C_SCL=0;
	return ucReturnValue;
}

/*********************************************************************************************************
** Function name:           i2cStartSend
** Descriptions:            i2c开始信号
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cStartSend(void)
{
	I2C_DELAY();
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cStopSend
** Descriptions:            i2c停止信号
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cStopSend(void)
{
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SDA=1;
}

/*********************************************************************************************************
** Function name:           i2cRestartSend
** Descriptions:            i2c重启发送
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cRestartSend(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cSendAck
** Descriptions:            i2c发送应答信号
** input parameters:        none
** output parameters:       none
** Returned value:       none
**                          
*********************************************************************************************************/
static void i2cSendAck(void)
{
	I2C_SDA=0;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
    I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cSendInvailAck
** Descriptions:            i2c发送非应答信号
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                          
*********************************************************************************************************/
static void i2cSendInvailAck(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
    I2C_SCL=0;
}

/*********************************************************************************************************
** Function name:           i2cReceiveAck
** Descriptions:            i2c接收应答信号
** input parameters:        none
** output parameters:       none
** Returned value:          none
**                         
*********************************************************************************************************/
static char i2cReceiveAck(void)
{
	I2C_SDA=1;
	I2C_DELAY();
	I2C_SCL=1;
	I2C_DELAY();
	if(I2C_SDA==1)
	{
		I2C_SCL=0;
		return 0;
	}
	I2C_SCL=0;
	return 1;
		
}



/*********************************************************************************************************
** Function name:           i2cByteSend
** Descriptions:            i2c发送一字节数据
** input parameters:        ucData：要发送的数据
** output parameters:       none
** Returned value:        none
**                          
*********************************************************************************************************/
static void i2cByteSend(unsigned char ucData)
{
	unsigned char i=8;
	
	while(i-->0 )
	{
		i2cBitSend(ucData);
		ucData=ucData<<1;
	}
		
		
}

/*********************************************************************************************************
** Function name:           i2cByteReceive
** Descriptions:            i2c接收一字节数据
** input parameters:        none
** output parameters:       none
** Returned value:        ucReturn：接收的数据
**                          
*********************************************************************************************************/
static unsigned char i2cByteReceive(void)
{
	unsigned char ucReturn=0;
	unsigned char i=8;
	I2C_SDA=1;
	while(i-->0)
	{
		ucReturn=ucReturn<<1;
		ucReturn=ucReturn+i2cBitReceive();
	}
	
	return ucReturn;
		
		
}

/*********************************************************************************************************
** Function name:           i2cInit
** Descriptions:            初始化i2c
** input parameters:        none
** output parameters:       none
** Returned value:          0:  成功
**                          -1: 失败
*********************************************************************************************************/
char i2cInit(void)
{
	I2C_SCL=0;
	i2cStopSend();
	return 0;
	
}

/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:            i2c写操作
** input parameters:         ucAdd:       从机地址
**                          uiResitAdd:    寄存器地址
**                          ucResitLength: 寄存器地址长度（字节为单位）
**                          ucData:      要写入的数据
**                          ucDataLen:    要写入的数据长度（字节为单位）
** output parameters:       none
** Returned value:          已经成功写入的字节数
*********************************************************************************************************/
 unsigned char i2cWrite(unsigned char ucAdd,
                                unsigned int  uiResitAdd,
                                unsigned char ucResitLength,
                                unsigned char *ucData,
                                unsigned char ucDataLen)
{
		unsigned char i;
		if(ucDataLen==0||ucData==0)
			return 0;
		i=ucDataLen;
		i2cStartSend();
		i2cByteSend(ucAdd&0xfe);
		
		if(i2cReceiveAck())
		{
			while(ucResitLength>0)
			{
				
				i2cByteSend(uiResitAdd);
				if(!i2cReceiveAck())
					break;
				ucResitLength--;
				uiResitAdd=uiResitAdd>>8;
			}
			
			if(ucResitLength==0)
			{
				do{
					
					i2cByteSend(*ucData++);
					if(!i2cReceiveAck())
						break;
				}while(--i!=0);
			}
			
		}
		i2cStopSend();
		return ucDataLen-i;
}


/*********************************************************************************************************
** Function name:           i2cRead
** Descriptions:            i2c读操作
** input parameters:         ucAdd:       从机地址
**                          uiResitAdd:    寄存器地址
**                          ucResitLength: 寄存器地址长度（字节为单位）
**                          ucData:      要读出的数据
**                          ucDataLen:    要读的数据长度（字节为单位）
** output parameters:       none
** Returned value:          已经成功读出入的字节数
*********************************************************************************************************/
 unsigned char i2cRead(unsigned char ucAdd,
                               unsigned int  uiResitAdd,
                               unsigned char ucResitLength,
                               unsigned char *ucData,
                               unsigned char ucDataLen)
{

	unsigned char i;
	if(ucDataLen==0||ucData==0)
		return 0;
	i2cStartSend();
	i2cByteSend(ucAdd&0xfe);
	
	if(i2cReceiveAck())
	{
		while(ucResitLength>0)
		{
			i2cByteSend(uiResitAdd);
			if(!i2cReceiveAck())
				break;
			ucResitLength--;
			uiResitAdd==uiResitAdd>>8;
		}
		if(ucResitLength==0)
		{
			i2cRestartSend();
			i2cByteSend(ucAdd|0x01);
			if(i2cReceiveAck())
			{
				i=ucDataLen-1;
				while(i--!=0)
				{
					*ucData++=i2cByteReceive();
					i2cSendAck();
				}
				*ucData=i2cByteReceive();
				i2cSendInvailAck();
			}
		}
	}
	else{
		ucDataLen=0;
	}
	i2cStopSend();
	return ucDataLen;
}
