// PROGRAM	: 4-10-1.c										20150910
// FUNCTION	: STM Compare Match Output Mode Control  		By Steven
#include "HT66F70A.h"
#include "4-10-1.H"
#include "MyType.H"
#define fSYS   8000000										//8MHz System Frequency
const u16 Pitch_TAB[] = {			      					//Pitch Control Table
			fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
			fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
			fSYS/(998*2*4),fSYS/(523*4*4),fSYS/(587*4*4),
			fSYS/(659*4*4),fSYS/(698*4*4),fSYS/(785*4*4),
			fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4),
			fSYS/(587*8*4)};
void PAUSE(u8);
u8 ScanKey(void);
void main()
{	u8 Pitch;
	_wdtc=0b10101111;										//關閉看們狗計時器
	_pcs2=0x01;												//Enable PC4 as TP2 Function
	_pcs1=0x10;
	_tm2c0=0; _tm2c1=0b00110001;							//STM: Compare Match O/P, CLR By CCRA
	while(1)
	{	do Pitch=ScanKey(); while (Pitch==16);	   			//Wait Key Pressed
		_tm2al=Pitch_TAB[Pitch]&0xFF;						//TM2AL Shold be Loaded First !!
		_tm2ah=Pitch_TAB[Pitch]>>8;
		_t2on=1;											//Start STM
		while (ScanKey()!=16);	                  			//Wait Key Released
		PAUSE(25); _t2on=0; 								//Delay 250mS, Stop STM
	}
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;							//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;							   			//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;				   		//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;				   		//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;				 		//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			   			//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;					//Scancode for Next Row
	}
	return key;	
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);						//Delay 10ms*i
}	