// PROGRAM	: 5-6EXT.c							2018.0503
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
		LCMWrite(0,0x06);					//COMD:Increment, Not Shift
		for(i=0;i<20;i++)
		{	LCMWrite(1,'1'); PAUSE(10);  	//Dispay "1"
		}
			
		LCMWrite(0,0x80+0x5A);				//Set Line 2, Position 5A		
		LCMWrite(1,'H');		
		LCMWrite(1,'e');
		LCMWrite(1,'l');
		LCMWrite(1,'l');
		LCMWrite(1,'o');
		LCMWrite(1,'!');
		
		LCMWrite(0,0xC0+19);				//Set Line 2, Position 19
		LCMWrite(0,0x04);					//COMD:Decrement, Not Shift
		for(i=0;i<20;i++) 
		{	LCMWrite(1,'2'); PAUSE(10);		//Dispay "2"
		}  
		for(i=0;i<20;i++) 
		{	LCMWrite(0,0x18);				//shift left
			PAUSE(10);
		}  
		PAUSE(100);
		for(i=0;i<20;i++) 
		{	LCMWrite(0,0x1C);				//Shift right
			PAUSE(10);
		}  
		
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	     	//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	  	//Config EN/RW/RS O/PAUSE
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
	GCC_NOP(); 								//tAS
	do
	{	LCM_EN=1; GCC_NOP();				//EN=1,tDDR
		BusyAC=LCM_DataPort;				//Loop Until BF=0  
		LCM_EN=0;							//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;						//Config Port as O/P Mode
	LCM_RW=0;								//RW=0 (Write)
	LCM_RS=DCFlag;							//Set RS State By DCFlag ==> DCFlag = 1 >>Data Register
	LCM_DataPort=CD;						//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;			//EN=1,pWEN
	return BusyAC;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000);		//Delay i*10mS 
}