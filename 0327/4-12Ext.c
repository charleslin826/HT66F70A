// PROGRAM	: 4-12Ext.c							2018.0314
// FUNCTION	: INT0/INT1 Nest Interrupt Demo 	By Steven
#include "HT66F70A.h"			
#include "4-12.H"
#include "MyType.H"			
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	LED_Port=0xFF; LED_PortC=0;					//Turn off LED, Config Port as O/P Mode
	SEG_Port=0; SEG_PortC=0;					//Turn off 7-SEG, Config Port as O/P Mode
	_pepu0=1; _pepu1=1;							//Enable PE.0,PE.1 Pull-up
	_ifs0=0x0A;									//Set INT0/INT1 at PE0/PE1
	_integ=0b00001010;							//Select INT0 Falling Edge Trigger
	_int0e=1; _int1e=1; _emi=1;			      	//Enable INT0 Interrupt 
	while(1)
	{	for(i=0;i<10;i++)						//0 ~ 9 DISPLAY LOOP 
		{	SEG_Port=SEG_TAB[i]; PAUSE(100);
		}
	}
}
DEFINE_ISR(ISR_ExtInt0,0x04)
{	u8 i,tmp;
	_int0e=0;									//避免Bounce造成Nest INT
	_emi=1;										//Enable Nest INT
	tmp=LED_Port;
	LED_Port=0b11111110;						//Set LED_Port Initial State
	while(LED_Port!=0b01111111) 
	{	for(i=0;i<20;i++) GCC_DELAY(20000);    	//Delay 0.2S
		LED_Port=(LED_Port<<1)|1;	 		    //Shift Left
	}
	while(LED_Port!=0xFF)
	{	for(i=0;i<20;i++) GCC_DELAY(20000);    	//Delay 0.2S
		LED_Port=(LED_Port>>1)|0x80;			//Shift Right
	}
	LED_Port=tmp;
	_int0f=0;									//Avoid Bouncing!
	_int0e=1;									//INT0重新致能中斷
}
DEFINE_ISR(ISR_ExtInt1,0x08)
{	u8 i,j,tmp;
	_int1e=0;									//避免Bounce造成Nest INT
	_emi=1;										//Enable Nest INT
	tmp=LED_Port;
	LED_Port=0xFF;								//Set LED_Port Initial State
	for(j=0;j<10;j++)
	{	LED_Port=~LED_Port;
		for(i=0;i<40;i++) GCC_DELAY(20000);    	//Delay 0.4S
	}
	LED_Port=tmp;
	_int1f=0;									//Avoid Bouncing!
	_int1e=1;									//INT1重新致能中斷
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);      	//Dealy i*10ms
}