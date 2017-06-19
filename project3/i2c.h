/****************************************Copyright (c)****************************************************
**
**--------------File Info---------------------------------------------------------------------------------
** File name:              i2c.h
** Latest modified Date:    2017-6-13
** Latest Version:          
** Descriptions:           i2c驱动头文件
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

#ifndef I2C_H_
#define I2C_H_

/*********************************************************************************************************
** Function name:           i2cInit
** Descriptions:            初始化i2c
** input parameters:        none
** output parameters:       none
** Returned value:          0:  成功
**                          -1: 失败
*********************************************************************************************************/
extern char i2cInit(void);

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
extern unsigned char i2cWrite(unsigned char ucAdd,
                                unsigned int  uiResitAdd,
                                unsigned char ucResitLength,
                                unsigned char *ucData,
                                unsigned char ucDataLen);


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
extern unsigned char i2cRead(unsigned char ucAdd,
                               unsigned int  uiResitAdd,
                               unsigned char ucResitLength,
                               unsigned char *ucData,
                               unsigned char ucDataLen);



#endif


