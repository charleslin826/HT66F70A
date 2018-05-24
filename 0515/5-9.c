// PROGRAM	: 5-9.c								   	2015.0911
// FUNCTION	: 20*2 LCM DDRAM Reading Control 	   	By Steven
#include "HT66F70A.h"
#include "5-9.H"
#include "Mytype.H"
const u8 Str1[]={"MISS!!"},Str2[]={"BINGO!"};
const u8 Str02F[]={"0123456789ABCDEF"};
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
u8 LCMRead(u8*);
void PAUSE(u8);
void main()
{	volatile u8 i,Random,temp,Factor=8;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SW_FasterC=1; SW_SlowerC=1; SW_HitC=1;		//Config Pin as I/P Mode
	SW_FasterPU=1; SW_SlowerPU=1; SW_HitPU=1;	//Enable Pins' Pull-up
	_tm0c1=0b11000000;							//CTM as Timer/Counter, TMRP Match Cleared
	_tm0c0=0b00011000;							//CLK[2:0]=001(fINT=fSYS), Start CTM
	LCMInit();									//LCM Initialization
	while(1)
	{	LCMWrite(0,1);							//Clear LCM Display
		GCC_DELAY(2000);
		LCMWrite(0,0xC0); i=0;					//Line 2, Position 0, Show 0~F
		while(Str02F[i]!=0) 
		   LCMWrite(1,Str02F[i++]);
		Random=(_tm0dh^_tm0dl)&0x0F;			//Get Random time0_10bit 0~1023 at fINT=fSYS speed 
		Random=Str02F[Random];					//Convert Random to ASCII
		LCMWrite(0,0x87);						//Line 1, Position 7
		LCMWrite(1,Random);						//Display Random
		i=0xC0;
		while(1)
		{	LCMWrite(0,i); 
			LCMRead(&temp);						//Read DDRAM Data  回傳第二行的值
			LCMWrite(0,i); LCMWrite(1,0xFF);	//Mask
			PAUSE(Factor);
			LCMWrite(0,i); LCMWrite(1,temp);	//Restore DDRAM Data
			if(!SW_Faster)						//SW_Faster Pressed
			{	if(--Factor<=1) Factor=2;		//Min. 20ms
				PAUSE(10);
			}
			else if(!SW_Slower)					//SW_Slower Pressed
			{	if(++Factor>=100) Factor=100;	//MAX. 1000ms
				PAUSE(10);
			}
			else if(!SW_Hit) 					//SW_Hit Pressed
			{	if(temp==Random)
				{	LCMWrite(0,0x8A); i=0;
					while(Str2[i]!=0)
					LCMWrite(1,Str2[i++]);
				}
				else
				{	LCMWrite(0,0x80); i=0;
					while(Str1[i]!=0)
					LCMWrite(1,Str1[i++]);
				}
				break;	
			}
		if(++i>=0xD4) i=0xC0;					//LCM Bounday Check
		}
		PAUSE(100);
		while(SW_Faster&SW_Slower&SW_Hit);	   	//Wiat all Key Released
		PAUSE(10);
		while(!(SW_Faster&SW_Slower&SW_Hit));  	//Wait Any Key Pressed
		PAUSE(10);
	}
}
u8 LCMRead(u8 *ptr)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;					//Config Port as I/P Mode
	LCM_RS=0; LCM_RW=1;							//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();					//EN=1
		BusyAC=LCM_DataPort;						
		LCM_EN=0;								//EN=0
	} while (BusyAC&0b10000000);				//Loop Until BF=0
	GCC_DELAY(1000);
	LCM_RS=1; LCM_RW=1; GCC_NOP(); GCC_NOP(); 	//RS=1 (DDRAM or CGRAM Read)
	LCM_EN=1; GCC_NOP(); GCC_NOP(); GCC_NOP();	//EN=1
	*ptr=LCM_DataPort; GCC_NOP(); GCC_NOP();	//Read IR or DR
	LCM_EN=0;									//EN=1
	return BusyAC;	
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;				//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;			//Config EN/RW/RS O/P Mode
	GCC_DELAY(80000);							//LCM Power-On Time
	LCMWrite(0,0x38);							//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);							//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);							//COMD:Increment, Not Shift
	LCMWrite(0,0x01);							//COMD:Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;					//Config Port as I/P Mode
	LCM_RS=0; LCM_RW=1;							//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();					//EN=1
		BusyAC=LCM_DataPort;					//Loop Until BF=0
		LCM_EN=0;								//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;							//Config Port as O/P Mode
	LCM_RW=0;									//RW=0 (Write)
	LCM_RS=DCFlag;								//Set RS State By DCFlag
	LCM_DataPort=CD;							//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;				//EN=1
	return BusyAC;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++)  GCC_DELAY(20000);		//Delay i*10mS 
}