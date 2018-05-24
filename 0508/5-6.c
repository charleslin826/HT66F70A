// PROGRAM	: 5-6.c								2018.0503
// FUNCTION	: 20*2 LCM Contrl Demo Program		By Steven
#include "HT66F70A.h"
#include "5-6.H"
#include "Mytype.H"

void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void PAUSE(u8);
void main()
 {	u8 i;
	_wdtc=0b10101111;						//關閉看們狗計時器
	LCMInit();				           		//LCM Initialization

	while(1)
	{	LCMWrite(0,0x01);					//Clear LCM Display						
		for(i=0;i<20;i++)
		{	LCMWrite(0,0x80+i);
			LCMWrite(1,'1'); PAUSE(10);  	//Dispay "1"
			LCMWrite(0,0xC0+i);	
			LCMWrite(1,'2'); PAUSE(10);
		}
	
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	     	//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	  	//Config EN/RW/RS O/PAUSE
	GCC_DELAY(40000);						//LCM Power-On Time
	LCMWrite(0,0x38);						//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);						//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);						//COMD:Increment, Not Shift
	LCMWrite(0,0x01);						//COMD:Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;				//Config Port as I/P Mode  設定70A  讀取
	LCM_RS=0; LCM_RW=1;						//RS=0,RW=1 (Read IR)
	GCC_NOP();   							// GCC_NOP() = wait 500ns 
	do
	{	LCM_EN=1; GCC_NOP();				//EN=1 // wait 500ns 
		BusyAC=LCM_DataPort;				//Loop Until BF=0
		LCM_EN=0;							//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;						//Config Port as O/P Mode 設定70A  寫入
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