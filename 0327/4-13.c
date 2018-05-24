// PROGRAM	: 4-13.c							2015.0910
// FUNCTION	: STM PWM O/P Mode Control   		By Steven
// for ESK-300
#include "HT66F70A.h"
#include "4-13.H"
#include "MyType.H"
const u16 TAB_PWM[] = {  						//TM1B Table (Duty Control)	
		10,50,100,200,300,400,500,600,800,1023};
void PAUSE(u8);
void main()
{	u8 Index;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SW_BRIGHTC=1 ; SW_DARKC=1;					//Set Port Bit as I/P Mode
	SW_BRIGHTPU=1; SW_DARKPU=1;				 	//Enable Port Bit Pull-up
	_pcs0=0x11;									//PC0,PC1 as TP1B  11(H) >　０００１００１（Ｂ）
	_pcs2=0x60;									//PC5 as TP1B
	_tm1c0=0; _tm1c1=0b11000001;			 	//fINT=fSYS/4, TM1A T/C Mode
	_tm1c2=0b10100000;						  	//Active Low,Non-Inv., Edge Aligned
	_tm1al=(1024-1)&0xFF; _tm1ah=(1024-1)>>8; 	//Set PWM Period
	Index=5; _t1on=1;							//Initial Index and Start ETM
	while(1)
	{	_tm1bl=TAB_PWM[Index]&0xFF;				//TM1BL Should be Loaded First !!
		_tm1bh=TAB_PWM[Index]>>8;
		PAUSE(50);								//Delay 0.5 Sec
		if(!SW_BRIGHT)
		{	if(Index<9) Index++;
		}
		else if (!SW_DARK)
		{	if(Index>0) Index--;
		}
	}
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++)  GCC_DELAY(20000); 		//Delay 10ms*i
}