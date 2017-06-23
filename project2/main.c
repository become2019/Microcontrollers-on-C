#include<8051.h>
#include"keyboard_scan.h"
#include"buzze.h"
void main()	
{
	char cKey;
	keyboardInit();
	allEnableOpen();
	buzzeInit();
		while(1)
		{
			//等待按键按下
			while(1)
			{
				if((cKey=isExsitPushKey())>0)
				  break;
			}
			buzzeRun((cKey-'0')*100+900,100000);
			
		}

}
