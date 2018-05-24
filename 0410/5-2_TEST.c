// PROGRAM	: 5-2.c								2015.0911
// FUNCTION	: Multi 7 SEGMENT LED Control 	   	By Steven
#include "HT66F70A.h"
#include "5-2.H"
#include "MyType.H"
const u8 SEG_TAB[] = {			   				//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
volatile _Bool FG_100ms,FG_GoStop;
volatile u8 *ptr,R100ms,ScanCode,Digit[4];
static u8 second=0;
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0; 						//Config Port as Output
	ScanPort&=0xF0; ScanPortC&=0xF0;
	_tm2c0=0;									//fINT=fSYS/4(0.5us)
	_tm2c1=0b11000001;							//Timer/Counter, TM2A Match Clear
	_tm2al=10000&0xFF; _tm2ah=10000>>8;        	//TM2A=10000 (10000*0.5us=5ms)
	_ifs0=0x00;									//INT0 --> PA3
	_papu3=1;									//Pull-Up
	_integ=0b00000010;							//INT0 Falling Edge
	_int0e=1;									//Enable INT0 Interrupt
	R100ms=200; FG_100ms=0;						//Initial Counter(20*5ms)=1 Sec
	ptr=Digit; ScanCode=0b10000000;		      	//Initial Pointer
	for(i=0;i<4;i++) Digit[i]=0;				//Initial Count
	_mf0e=1; _t2ae=1;							//Enable TM2 Interrupt
	_emi=1; _t2on=1; FG_GoStop=0;				//Start TM2, Interrupt
	Digit[1]=5; Digit[0]=8;							//設定分鐘
	Digit[3]=2; Digit[2]=3;							//設定小時
	while(1)
	{	while(!FG_100ms);						//Wait for 1 Sec
		FG_100ms=0;
		if(++second==3){
			second=0;
			if(++Digit[0]==10)
			{	Digit[0]=0;
				if(++Digit[1]==6)
				{	Digit[1]=0;
					if(++Digit[2]==4 && Digit[3]==2)	//Check 24:00
				{	Digit[2]=0; Digit[3]=0;
				}else{
					if(++Digit[2]==10)
					{	Digit[2]=0;
						if(++Digit[3]==2) Digit[3]=0;
					}
				}
				}
			}
		}
	}	
}
DEFINE_ISR(ISR_ExtInt0,0x04)
{	FG_GoStop=!FG_GoStop;						//Update FG_GoStop
	_int0f=0;									//for Bouncing
}
DEFINE_ISR(ISR_STM,0x14)
{	SEGPort=0;									//Turn-off 7-Seg 避免殘影 但此HT66只有四個所以看不出來
	GCC_RL(ScanCode);							//Update Scan Code 從1開始顯示
	if(ScanCode==0b00010000)
	{	ScanCode=0b00000001; ptr=Digit;	      	//Restart ScanCode	
	}
	ScanPort=ScanCode;	
	if(R100ms<100) SEGPort=SEG_TAB[*ptr++]; 
	else SEGPort=SEG_TAB[*ptr++]|0b10000000;
	
//	if(FG_GoStop)
	{ 	if(--R100ms==0)
		{	FG_100ms=1;
			R100ms=200; 
		}
	}
	_t2af=0;			
}