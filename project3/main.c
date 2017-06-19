#include"led_disp.h"
#include"i2c.h"
#include"time.h"
#include"keyboard_scan.h"
#include"buzzer.h"
#include"speak.h"
#include<8051.h>
#include <stdio.h>
#include <stdlib.h>
static code char *GcTable[]={
	"000","125","250","375","500","625","750","875"
};
	
void main()
{
	  char cBuf[8]={
	'9','9'	,'9','9','9','\0'
	};
	 
	char cIndex=0;
	char i;
	 float fTemp1=0;
	 float fSetTemp=100.0;
	char cTemp[2];
	char cKey1,cKey2;
	ledDisplayInit();
	ledDisplayPuts("000000");
	time0Init();
	time1Init();
	buzzerInit();
	allEnableOpen();
	i2cInit();
	while(1)
	{
		if(i2cRead(0x90,0,1,(unsigned char *)cTemp,2)==2)
		{
			if(cTemp[0]<0)
			{
				sprintf(cBuf,"-%2d.%s",-cTemp[0],GcTable[((cTemp[1])>>5)&0x07]);
			}
			else
			{
				sprintf(cBuf,"%3d.%s",cTemp[0],GcTable[((cTemp[1])>>5)&0x07]);
			}
			fTemp1=atof(cBuf+1);
			ledDisplayPuts(cBuf);
		}
		else
		{
			ledDisplayPuts("000000");
		}
		
		
		if((cKey1=allKeyCheck())=='#')
		{
			delay100us(100);
			cKey2=allKeyCheck();
			if(cKey1==cKey2)
			{
				while(1){
					
				while(allKeyCheck()>0)
				{
					
				}
				delay100us(100);
				if(allKeyCheck()<0)
					break;
				}
				cBuf[0]='\0';
		ledDisplayPuts(cBuf);
		while(1){
			
				while(1)
				{
					while(1)
					{
						cKey1=allKeyCheck();
						if(cKey1>0)
							break;
					}
					delay100us(100);
					cKey2=allKeyCheck();
					if(cKey1==cKey2)
						break;
					
				}
				
				if(cKey1=='#'||cIndex==6)
				{
					fSetTemp=atof(cBuf);
					cIndex=0;
					while(1)
				{
					while(allKeyCheck()>0)
						;
					delay100us(100);
					if(allKeyCheck()<0)
						break;
				}
					break;
				}
				else
				{
					cBuf[cIndex]=cKey1;
					cBuf[cIndex+1]='\0';
					cIndex++;
				}
				ledDisplayPuts(cBuf);
				while(1)
				{
					while(allKeyCheck()>0)
						;
					delay100us(100);
					if(allKeyCheck()<0)
						break;
				}
				}
			}
			else
			{
				
			}
		}
	
		
		
		if((cKey1=allKeyCheck())=='.')
		{
			delay100us(100);
			cKey2=allKeyCheck();
			if(cKey1==cKey2)
			{
				while (1){

					while (allKeyCheck()>0)
					{

					}
					delay100us(100);
					if (allKeyCheck()<0)
						break;
				}
				//²¥±¨ÓïÒô
				speak(14);
				speak(20);
				for(i=0;i<8;i++)
				{
					if(cBuf[i]>='1'&&cBuf[i]<='9')
					{
						speak(cBuf[i]-'0'+1);
					}
					else if(cBuf[i]=='0')
						speak(31);
					else if(cBuf[i]=='.')
						speak(13);
				}
				speak(28);
			}
				
		}
	if(fSetTemp<=fTemp1)
	{
		while(fSetTemp<=fTemp1){
			if(i2cRead(0x90,0,1,(unsigned char *)cTemp,2)==2)
		{
			if(cTemp[0]<0)
			{
				sprintf(cBuf,"-%2d.%s",-cTemp[0],GcTable[((cTemp[1])>>5)&0x07]);
			}
			else
			{
				sprintf(cBuf,"%3d.%s",cTemp[0],GcTable[((cTemp[1])>>5)&0x07]);
			}
			fTemp1=atof(cBuf+1);
			ledDisplayPuts(cBuf);
		}
		else
		{
			ledDisplayPuts("000000");
		}
		buzzerSpecialHzTweet(99);
		
		}
		
		
	}
	
	
			
		delay100us(500);
	}
	
}
