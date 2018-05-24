// PROGRAM	: 4-7.c									2016.0910
// FUNCTION	: 4X4 MATRIX KEYPAD DEMO PROGRAM		By Steven
#include "HT66F70A.h"
#include "MyType.h"
#include "4-7.h"
const u8 SEG_TAB[] = {0x3F,0x06,					//7-Segment Table
			0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
			0x67,0x77,0x7C,0x58,0x5E,0x79,0x71};
u8 ScanKey(void);
void main()
{	u8 i,Key;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0x0;									//Config Port as O/P Mode 
	while(1)
	{	SEG_Port=0;									//Turn-Off Display
		do Key=ScanKey(); while(Key==16);	   						//Wait Key Pressed
		SEG_Port=SEG_TAB[Key];				      	//Read Table Index By Key
		for(i=0;i<100;i++) GCC_DELAY(20000);  		//Delay 1 Sec
	}	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xf0; KeyPortPU=0xf0;			   		//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;					         	//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;		      	//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;			   	//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;			   	//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			   	//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;	   		//Scancode for Next Row
	}
	return key;	
}