// PROGRAM	: 4-16-1.c									2017.0701
// FUNCTION	: HALT Function Demo Program				By Steven
//			  SLEEP1 Mode with WDT Enable & LVDEN=0	
// Note		: Configuration Option Setting--
//			  Resb = IC_RESET_PIN
//			  PB0/RES Pin Options = RES pin	and Must Connect to RC Circuit
//			  Watcdog Timer Function = Enable	
//			  fSUB Clock Source = LIRC 32KHz
//			  WDT Clock Source fS = fSUB	
#include "HT66F70A.h"
#include "4-16-1.H"
#include "MyType.H"
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void WDT_WakeUp(void);
void PAUSE(u8);
void main()
{	static u8 Index, SleepCount; 				//不加static,Index初值會設為0
	_wdtc=0b01010111;							//Enable WDT, Time-out=(2**18)/fS
	SEG_PortC=0;								//Config PD as Output
	PB_PortC=1; PB_Pull=1; PB_Wake=1;			//PB I/P Mode, Enable Pull-up/Wake-up
	_ifs0=0x00;									//INT0 --> PA3
	_papu3=1;									//Enable PA.3 Pull-up
	_integ=0b00000010;							//Select INT0 Falling Edge Trigger
	_idlen=0; _emi=1;							//Clear IDLEN Bit & Enable EMI
	if(_pdf) 									//If PDF=1 ?
	{	if(_to) WDT_WakeUp();					//Yes. If WDT Overflow, call WDT_WakeUp()
		GCC_CLRWDT();							//Clear PDF
	} 
	else										//Power-on Reset
	{	Index=0;
	}	
	while(1)
	{	SEG_Port=SEG_TAB[Index];				//Dispaly Value 
		SleepCount=25;
		do
		{	PAUSE(20); 							//Delay 0.2 Sec
			SEG_Port^=0x80;						//Toggle dp Segment
			if(--SleepCount==0)					//0.2 Sec*50=10 Sec without Pressing Key
			{	SEG_Port=0;						//Turn-off 7-Segment LEDs
				_int0f=0;						//Clear INT0F
				_int0e=1;						//Enable INT0E 
				GCC_HALT();						//Goto Sleep....
				_int0e=0;						//INT0/PA0 Wake-up, Disable INT0E	
				break;							//Exit do...while Loop
			}
		} while(PB_Port);						//Wait Key Pressed
		if(++Index==10) Index=0; 				//Index Boundary Checking
	}
}
void WDT_WakeUp(void)
{	u8 i;
	for(i=0;i<10;i++)
	{	SEG_Port^=0b11111111;					//Flashing 7-SEG LEDS
		PAUSE(25);								//Delay 0.25 Sec
	}
}
DEFINE_ISR(ISR_ExtInt0,0x04)					//INT0 Interrupt Vector
{	u8 i,j;
	SEG_Port=0b00000001;						//Turn-off 7-Segment
	for(i=0;i<6;i++) 
	{	for(j=0;j<40;j++) GCC_DELAY(20000); 	//Delay 0.4S
		GCC_CLRWDT();
		SEG_Port<<=1;	 						//Turn-on Next Segment
	}
	_int0f=0;									//Avoid Bouncing!
	GCC_CLRWDT();								//Clear PDF
}
void PAUSE(u8 i)					
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000); 		//Delay i*10mS
	GCC_CLRWDT();
}