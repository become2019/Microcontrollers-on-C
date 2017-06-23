#include<8051.h>
#include"led_disp.h"
#include"delay.h"
#include"Key.h"
#include"buzzer.h"
void main()
{
	
	char cString[6]={0,0,0,0,0,0};
	char cKey;
	unsigned char i;
	ledDisplayInit();
	ledDisplayDecPuts(cString,1);
		while(1)
		{
			//等待按键按下
			while(1)
			{
				if((cKey=KeyNumberGet())>0)
				{
					for(i=0;i<100;i++)
						ledDisplayScan();
					if(cKey==KeyNumberGet())
						break;
				}
				ledDisplayScan();
			}
			cString[0]=cKey;
			ledDisplayDecPuts(cString,1);
			PlayMusic(cKey-'0',ledDisplayScan);
			while(1)
			{
				if(KeyNumberGet()<0)
				{
					for(i=0;i<100;i++)
						ledDisplayScan();
					if(KeyNumberGet()<0)
						break;
				}
				ledDisplayScan();
			}
		}

}
