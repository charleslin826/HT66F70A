// PROGRAM	: 4-2.c									2015.0908
// FUNCTION	: LEDs PILI Light Demo Program	      	By Steven
#include "HT66F70A.h"
#define LED_PortC	_pcc
#define LED_Port	_pc
void main()
{	unsigned char i,j;	
	unsigned char x, y;
	_wdtc=0b10101111;								//關閉看們狗計時器
	LED_PortC=0x0;									//Config LED_Port as Output
	LED_PortC=0x0;									//Config Port as O/P Mode
	while(1)
	{	x = 0b00000001; y=0b10000000;               //若把xy的值定義在上面 則這邊沒有初值 第二次的j==3就不是我們想要的位置
		for(j=0;j<6;j++)	
			{	LED_Port=~(x|y);												      
				for(i=0;i<100;i++) GCC_DELAY(2000);	
				GCC_RL(x); GCC_RR(y);	
				if(j==3) {GCC_RL(x); GCC_RR(y);}				
			}
	}
}