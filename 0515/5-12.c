// PROGRAM	: 5-12.c								2018.0503
// FUNCTION	: CTM PWM & STM Capture Mode DEmo 	   	By Steven
#include "HT66F70A.h"
#include "5-12.H"
#include "Mytype.H"
const u8 String1[] = {"Period=     uS"};
const u8 String2[] = {"   Ton=     uS"};
const u16 TAB_TonLimit[] = {1023,127,255,383,511,639,767,895};
const u16 TAB_TonStep[]  = { 40, 10,  10,  20, 20, 30, 30, 40};
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
u16 Measure(void);
void DisplayDigit(u8*);
void WordHex2ASCII(u16,u8*);
void PAUSE(u8);
void main()
{	u8 Digit[5], PWMPeriod=0;
	u16 TonLimit, PWMTon, HexWord;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SW_PeriodC=1; SW_TONC=1;						//Config Pin as I/P Mode
	SW_PeriodPU=1; SW_TONPU=1;						//Enable Pins' Pull-up
	_tm2c0=0;									   	//STM fINT=fSYS/4
	_ifs2=0x00;										//TP2I --> PC3	
	_tm0c0=0b00000000;								//CTM fINT=fSYS/4
	_tm0c1=0b10101000;								//PWM,Active-Hi,Non-Inv, T0RP Match Clear
	_pcs3=0x01;										//PC6 as TP0 (PWM Output)
	TonLimit=TAB_TonLimit[PWMPeriod];				//Get TON Limit for Specific Period Index
	PWMTon=20;										//Initial Ton Step
	LCMInit();
	while(1)
	{	while(!SW_Period)
		{	if(++PWMPeriod>7) PWMPeriod=0;			//PWM Period Index Boundary Check
			TonLimit=TAB_TonLimit[PWMPeriod];		//Get TON Limit for Specific Period Index
			PWMTon=20;								//Reset Ton Step
			PAUSE(50);
		}
		while(!SW_TON)
		{	PWMTon+=TAB_TonStep[PWMPeriod];			//Update PWM TON
			if(PWMTon>TonLimit) 					//PWMTon Out of Range ?
			PWMTon=20;								//Yes, Reset Ton Step
			PAUSE(50);
		}
		_t0on=0;									//Stop CTM
		_tm0c0=(_tm0c0&0b11111000)|PWMPeriod;		//Update T0RP[2:0] By PWMPeriod
		_tm0al=(PWMTon&0xFF); _tm0ah=PWMTon>>8;		//Reload TM0A
		_t0on=1;									//Start CTM
		_tm2c1=0b01000000;							//Capture I/P Mode, Rising Edge
		HexWord=Measure();							//Start Measuring
		WordHex2ASCII(HexWord,Digit+4);				//Convert Result to ASCII
		LCMWrite(0,0x87);							//Set DDRAM Address
		DisplayDigit(Digit+3);	
		_tm2c1=0b01100000;							//Capture I/P Mode, Rising/Falling Edge
		while(_pc3);								//Wait for Low State
		HexWord=Measure();							//Start Measuring
		WordHex2ASCII(HexWord,Digit+4);				//Convert Result to ASCII
		LCMWrite(0,0xC7);							//Set DDRAM Address
		DisplayDigit(Digit+3);	
	}
}
void DisplayDigit(u8 *ptr)
{	_Bool LeadingZero=1; s8 i;
	for(i=3;i>=0;i--)		
	{	if((LeadingZero==1) && (*ptr==0x30))
		{	LCMWrite(1,0x20); }
		else
		{	LCMWrite(1,*ptr); LeadingZero=0; }
		ptr--;
	}	
}	
u16 Measure(void)
{	u16 HexWord,temp;
	do
	{	_t2pf=0; _t2af=0; _t2on=1;					//Clear T2PF/T2AF, Then Start STM
		while(!_t2af);								//Wait for First Edge
	} while(_t2pf);									//Loop if TM2RP Overflow
	temp=_tm2ah; temp<<=8; temp|=_tm2al;			//Get TM2A Count
	_t2af=0;
	while(!_t2af);									//Wait for Second Edge
	HexWord=_tm2ah; HexWord<<=8;	            	//Get TM2A Count
	HexWord|=_tm2al;
	HexWord-=temp;                            		//Compute
	_t2on=0;										//Stop STM
	return HexWord>>1;	
}
void WordHex2ASCII(u16 WordHex, u8 *ptr)
{	s8 i; s16 Base=10000;
	for(i=0;i<4;i++)
	{	*ptr=(WordHex/Base)+0x30;					//Step by Step Get Digit  EX:WordHex=65535, *ptr= (6)+0x30 = 0x36[ASCII_Hex='6']
		WordHex%=Base;//65535%10000 = 5535 => 535 => 35 => 5 => 0
		Base/=10; ptr--;//10000/10=1000   , ptr--
	}
	*ptr=WordHex+0x30;  //WordHex = ['6','5','5','3','5'] = [0x36,0x35,0x35,0x33,0x35] 因這邊實際上只有4個數字(0~1023),所以陣列中最後一個值是0[0x30]
}
void LCMInit(void)
{	u8 i;
	LCM_EN=0; LCM_RW=0; LCM_RS=0;					//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				//Config EN/RW/RS O/PAUSE
	GCC_DELAY(80000);								//LCM Power-On Time
	LCMWrite(0,0x38);								//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);								//COMD:Display/Cursor Blinking Off
	LCMWrite(0,0x06);								//COMD:Increment, Not Shift
	LCMWrite(0,0x01);								//COMD:Clear LCM Display
	
	LCMWrite(0,0x80); i=0;							//Display Measure Item & Unit
	while(String1[i]!=0)                      		// for Period
	   LCMWrite(1,String1[i++]);	            
	LCMWrite(0,0xC0); i=0;							//Display Measure Item & Unit
	while(String2[i]!=0)                      		// for Ton
	   LCMWrite(1,String2[i++]);	
}
u8 LCMWrite(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;						//Config Port as I/P Mode
	LCM_RS=0; LCM_RW=1;								//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();						//EN=1
		BusyAC=LCM_DataPort;						//Loop Until BF=0
		LCM_EN=0;									//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;								//Config Port as O/P Mode
	LCM_RW=0;										//RW=0 (Write)
	LCM_RS=DCFlag;									//Set RS State By DCFlag
	LCM_DataPort=CD;								//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;					//EN=1
	return BusyAC;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000); 			//Delay i*10mS 
}