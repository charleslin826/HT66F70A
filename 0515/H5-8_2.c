// PROGRAM	: H5-8_2.c							2016.0310
// FUNCTION	: LCM Combine with 4*4 Keypad Demo	By Steven
// 第一列滿換第二列，第二列滿清除第一列
#include "HT66F70A.h"
#include "5-8.H"
#include "Mytype.H"
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void PAUSE(u8);
u8 ScanKey(void);
void ClearLine(u8);
void main()
{	u8 AC=0,Key;
	_wdtc=0b10101111;						//關閉看們狗計時器
	LCMInit();								//LCM Initialization
	while(1)
	{	do Key=ScanKey(); while (Key==16);  //Wait Key Pressed
		PAUSE(20);							//Delay 200ms
		if(AC>=0x53) ClearLine(1);			//清除並換到第一列
		else if(AC==0x13) ClearLine(2);	   	//清除並換到第二列
		
		Key+=((Key>9) ? '7' : '0');			//Convert to ASCII		
		AC=LCMWrite(1,Key);					//Dispay Pressed Key
	}
}
void ClearLine(u8 line)
{	u8 i;
	line=(line==1) ? 0x80 : 0xC0;
	LCMWrite(0,line);
	for(i=0;i<16;i++) LCMWrite(1,' ');
	LCMWrite(0,line);		
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