// PROGRAM	: 5-7.c									2015.0703
// FUNCTION	: 20*2 LCM CGRAM Read/Write Demo	  	By Steven
#include "HT66F70A.h"
#include "5-7.H"
#include "Mytype.H"
const u8 TAB_CGRAM[] = {
		0x00,0x0C,0x1E,0x0C,0x06,0x07,0x07,0x0b,	//Man for Fig.5-7-3(a)
		0x00,0x00,0x00,0x00,0x00,0x18,0x04,0x02,
		0x11,0x01,0x01,0x01,0x02,0x1A,0x0C,0x00,
		0x10,0x10,0x08,0x06,0x03,0x01,0x01,0x00,
		0x00,0x0C,0x1E,0x0C,0x06,0x07,0x06,0x03,	//Man for Fig.5-7-3(b)
		0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x08,
		0x05,0x05,0x03,0x04,0x04,0x03,0x0F,0x00,
		0x08,0x10,0x10,0x10,0x08,0x06,0x0C,0x00};

void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	LCMInit();										//LCM Initialization
	LCMWrite(0,0x40);								//Set CGRAM Start Address
	for(i=0;i<64;i++) LCMWrite(1,TAB_CGRAM[i]);		//Write Data to CGRAM
	while(1)
	{	LCMWrite(0,0x89);							//Set Line 1/Position 9
		LCMWrite(1,0); LCMWrite(1,1);				//Display Data of CGRAM 0,1
		LCMWrite(0,0xC9);							//Set Line 2/Position 9
		LCMWrite(1,2); LCMWrite(1,3);				//Display Data of CGRAM 2,3
		PAUSE(20);									//Delay 200ms					
		LCMWrite(0,0x89);							//Set Line 1/Position 9
		LCMWrite(1,4); LCMWrite(1,5);				//Display Data of CGRAM 4,5				
		LCMWrite(0,0xC9);							//Set Line 2/Position 9
		LCMWrite(1,6); LCMWrite(1,7);				//Display Data of CGRAM 6,7
		PAUSE(20);									//Delay 200ms					
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;			//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;		//Config EN/RW/RS O/P Mode
	GCC_DELAY(50000);						//LCM Power-On Time
	LCMWrite(0,0x38);						//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);						//COMD:Display/Cursor Blinking Off
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
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000);		//Delay i*10mS 
}