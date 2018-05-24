// PROGRAM	: H5-8_1.c							2016.0310
// FUNCTION	: LCM Combine with 4*4 Keypad Demo	By Steven
// 第一列滿換第二列，第二列滿清除全部
#include "HT66F70A.h"
#include "5-8.H"
#include "Mytype.H"
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void PAUSE(u8);
u8 ScanKey(void);
void main()
{	u8 AC=0,Key;
	_wdtc=0b10101111;						//關閉看們狗計時器
	LCMInit();								//LCM Initialization
	while(1)
	{	do Key=ScanKey(); while (Key==16);  //Wait Key Pressed
		PAUSE(20);							//Delay 200ms
//		while (ScanKey()!=16);				//Wait Key Released
//		PAUSE(5);							//Delay 50ms, Debouncing
		if(AC>=0x53)
		{	LCMWrite(0,0x01);				//Clear LCM Display	if Line 1 Full
			GCC_DELAY(4000);				//LCM Response Time for CLEAR Function
		}
		else if(AC==19) LCMWrite(0,0xC0);	//換到第二列
		
		Key+=((Key>9) ? '7' : '0');			//Convert to ASCII		
		AC=LCMWrite(1,Key);					//Dispay Pressed Key
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;			//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;		//Config EN/RW/RS O/P Mode
	GCC_DELAY(50000);						//LCM Power-On Time
	LCMWrite(0,0x38);						//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);						//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);						//COMD:Increment, Not Shift
	LCMWrite(0,0x01);						//COMD:Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;				//Config Port as I/P Mode
	LCM_RS=0; LCM_RW=1;						//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();				//EN=1
		BusyAC=LCM_DataPort;				//Loop Until BF=0
		LCM_EN=0;							//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;						//Config Port as O/P Mode
	LCM_RW=0;								//RW=0 (Write)
	LCM_RS=DCFlag;							//Set RS State By DCFlag
	LCM_DataPort=CD;						//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;			//EN=1
	return BusyAC;	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;						//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;		//Check Column 0
		key++;
		if(!(KeyPort & 1<<5)) break;		//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;		//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;		//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;	//Scancode for Next Row
	}
	return key;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000);		//Delay i*10mS 
}