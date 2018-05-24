// PROGRAM	: 5-13.c								2018.0503
// FUNCTION	: ETM Single Pulse O/P & STM Capture	By Steven
#include "HT66F70A.h"
#include "5-13.H"
#include "Mytype.H"
const u8 String1[] = {"A Width=     uS"};
const u8 String2[] = {"B Width=     uS"};
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
u16 Measure(void);
void DisplayDigit(u8*);
void WordHex2ASCII(u16,u8*);
void PAUSE(u8);
void main()
{	u8 Digit[5];
	u16 PulseA=20, PulseB=0, HexWord;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SW_PulseAC=1; SW_PulseBC=1;					//Config Pin as I/P Mode
	SW_PulseAPU=1; SW_PulseBPU=1;				//Enable Pins' Pull-up
	_tm2c0=0;									//STM fINT=fSYS/4
	_tm2c1=0b01100000;							//Capture I/P Mode, Rising/Falling Edge
	_tm1c0=0b00000000;							//ETM fINT=fSYS/4
	_tm1c1=0b10111000;							//TM1A Single Pulse O/P, Active-Hi
	_tm1c2=0b10111000;							//TM1B Single Pulse O/P, Active-Hi
	_pcs3=0x10;									//PC7 as TP1A Connect to PC4
	_pcs2=0x40;									//PC5 as TP1B Connect to PC3
	LCMInit();
	while(1)
	{	while(!SW_PulseA)						//SW_PulseA Pressed ?
		{	PulseA+=20;							//Yes, Increase A-Width By 20
			if(PulseA>1024) PulseA=20; 			//Check Boundary, Reset if Overrange
			PulseB=0; break;
		}
		while(!SW_PulseB)
		{	if((PulseA-PulseB)<20)  PulseB=0;	//Yes, Check Boundary, Reset if Overrange
			else  PulseB+=6;					//Increase B-Width By 8
			break;
		}
		_t1on=0;								//Stop ETM
		_tm1al=(u8)PulseA;	               		//Reload TM1A
		_tm1ah=PulseA>>8;
		_tm1bl=(u8)PulseB;	               		//Reload TM1B
		 _tm1bh=PulseB>>8;

		_ifs2=0x40;								//TP2I -- > PC4
		HexWord=Measure();						//Start Measuring
		WordHex2ASCII(HexWord,Digit+4);			//Convert Result to ASCII
		LCMWrite(0,0x88);						//Set DDRAM Address
		DisplayDigit(Digit+3);

		_ifs2=0x00;								//TP2I -- > PC3
		HexWord=Measure();						//Start Measuring
		WordHex2ASCII(HexWord,Digit+4);			//Convert Result to ASCII
		LCMWrite(0,0xC8);						//Set DDRAM Address
		DisplayDigit(Digit+3);	
		PAUSE(20);
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
{	u16 HexWord,TEMP,temp2;
	do
	{	_t2pf=0; _t2af=0; _t2on=1;_t1on=1;		//Clear T2PF/T2AF, Then Start STM(16bit 0~ 65535)/ETM (10bit 0~1023)
		while(!_t2af);							//Wait for First Edge
	} while(_t2pf);								//Loop if TM2RP Overflow
	TEMP=_tm2ah; temp2=_tm2al; 					//Get TM2A Count
	_t2af=0;
	while(!_t2af);								//Wait for Second Edge
	HexWord=_tm2ah; HexWord<<=8; 	            //Get TM2A Count
	HexWord|=_tm2al;
	TEMP=(TEMP<<8) | temp2;
	HexWord-=TEMP;
	_t2on=0; _t1on=0;							//Stop STM and ETM
	return HexWord>>1;	
}
void WordHex2ASCII(u16 WordHex, u8 *ptr)
{	u8 i; u16 Base=10000;
	for(i=0;i<4;i++)
	{	*ptr=(WordHex/Base)+0x30;				//Step by Step Get Digit
		WordHex%=Base;
		Base/=10; ptr--;
	}
	*ptr=WordHex+0x30;
}
void LCMInit(void)
{	u8 i;
	LCM_EN=0; LCM_RW=0; LCM_RS=0;				//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;			//Config EN/RW/RS O/P Mode
	GCC_DELAY(80000);							//LCM Power-On Time
	LCMWrite(0,0x38);							//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);							//COMD:Display/Cursor Blinking Off
	LCMWrite(0,0x06);							//COMD:Increment, Not Shift
	LCMWrite(0,0x01);							//COMD:Clear LCM Display

	LCMWrite(0,0x80); i=0;						//Display Measure Item & Unit
	while(String1[i]!=0)                   		// for Period
	   LCMWrite(1,String1[i++]);
	LCMWrite(0,0xC0); i=0;						//Display Measure Item & Unit
	while(String2[i]!=0) 	                  	// for Ton
	   LCMWrite(1,String2[i++]);
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
	for (j=0;j<i;j++) GCC_DELAY(20000);			//Delay i*10mS 
}