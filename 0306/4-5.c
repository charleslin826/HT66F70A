// PROGRAM	: 4-5.c									2016.0910
// FUNCTION	: 7 SEGMENT LED WITH BUTTON CONTROL    	By Steven
#include "HT66F70A.h"
#include "MyType.h"
#include "4-5.H"
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66, 	//7-Segment Table
			       		0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	u8 i,j=0;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0x0;									//Config Port as O/P Mode
	PB_SWC=1; PB_SWPU=1;                      		//Config Pin as I/P and Pull-up
	while(1)
	{	SEG_Port=SEG_TAB[j++];						//Read Table
	wait:
		while(PB_SW);						     	//Wait Until Key Pressed
		for(i=0;i<8;i++) GCC_DELAY(20000);			//Delay 120 mSec//這個時間跟按鍵的材質 力道有關
		if(PB_SW) goto wait; 		            	//If Key Released, Bouncing
		if(j>9) j=0;								//Boundary Check
	}
}	