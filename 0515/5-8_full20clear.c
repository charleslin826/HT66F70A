// PROGRAM	: 5-8.c								2015.0911
// FUNCTION	: LCM Combine with 4*4 Keypad Demo	By Steven
#include "HT66F70A.h"
#include "5-8.H"
#include "Mytype.H"
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void PAUSE(u8);
u8 ScanKey(void);
void main()
{	u8 AC=0,Key,i;
	_wdtc=0b10101111;						//關閉看們狗計時器
	LCMInit();								//LCM Initialization
	while(1)
	{	for(i=1;i<21;i++){
		do Key=ScanKey(); while (Key==16);  //Wait Key Pressed
		PAUSE(5);							//Delay 50ms, Debouncing
		while (ScanKey()!=16);				//Wait Key Released
		PAUSE(5);							//Delay 50ms, Debouncing
		Key+=((Key>9) ? '7' : '0');			//Convert to ASCII		
		AC=LCMWrite(1,Key);					//Dispay Pressed Key
		}
		LCMWrite(0,0xC0);
		do Key=ScanKey(); while (Key==16);  //Wait Key Pressed
		PAUSE(5);							//Delay 50ms, Debouncing
		while (ScanKey()!=16);				//Wait Key Released
		PAUSE(5);							//Delay 50ms, Debouncing
		if(AC>=38) //address counter
		{	LCMWrite(0,0x01);				//Clear LCM Display	if Line 1 Full
			GCC_DELAY(4000);				//LCM Response Time for CLEAR Function (about 2ms > require: 1.6ms)
		}
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
	KeyPortC=0xF0; KeyPortPU=0xF0;					   				//輸出/輸入規劃並致能提升電阻
	KeyPort=0b11111110;								      			//初始掃描碼
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				      			//檢查第1行
		key++;
		if(!(KeyPort & 1<<6)) break;				      			//檢查第2行
		key++;
		if(!(KeyPort & 1<<5)) break;				      			//檢查第3行
		key++;
		if(!(KeyPort & 1<<4)) break;				      			//檢查第4行
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;			   				//產生下一列掃描碼
	}
	return key;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000);		//Delay i*10mS 
}