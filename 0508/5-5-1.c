// PROGRAM	: 5-5-1.c										2018.0505
// FUNCTION	: LCD Control with Time/Alarm  Function			By Steven
#include "HT66F70A.h"
#include "5-5-1.H"
#include "MyType.H"
const u8 TransSegment[17] = {
			0x7B,0x30,0x5D,0x75,0x36,0x67,
			0x6F,0x31,0x7F,0x77,0x3F,0x6E,
			0x4C,0x7C,0x4F,0x0F,0x00};
volatile u8 DisBuffer[5],Digit[4];
volatile u8 PhaseCount,SecCounter;
volatile u8 Second;
_Bool	FG_HalfSec,FG_Second,FG_Adj,FG_Alarm,FG_Select,FG_State;
struct TimeFormat
{	u8 Hour;
	u8 Minute;
}	Time,Alarm;
struct	TimeFormat *ptr;
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;										//關閉看們狗計時器
	SW_AdjC=1; SW_EnterC=1;	SPKC=0;				   			// I/O Config
	SW_AdjPU=1; SW_EnterPU=1;SPK=0;				   			// Pull-up
	SegByteC=0x00; SEG9C=0; 
	COM0C=0; COM1C=0; COM2C=0; COM3C=0;
	_scomc=0b01111111; 
	_mf0e=1; _t2ae=1;
	_tm2c0=0; _tm2c1=0b11000001; 
	_tm2al=(u8)8000; _tm2ah=8000>>8;						//TM2A=8000 (8000*0.5us=4ms)
	_t2af=0; _mf0f=0; _emi=1; 
	FG_HalfSec=0; FG_Second=0;
	FG_Adj=0;												//Normal Mode
	Second=0; SecCounter=125; PhaseCount=0; 
	Time.Minute=0; Time.Hour=0;
	Alarm.Minute=0; Alarm.Hour=12;
	for(i=0;i<5;i++) DisBuffer[i]=0;
	for(i=0;i<4;i++) Digit[i]=0;
	DisBuffer[4]=(1<<3); 							   		//Turn-on P4
	ptr=&Time; _t2on=1;
	while(1)
	{	if(!(SW_Adj | SW_Enter))					   		//Both Keys Pressed ?
		{	FG_Adj=1; FG_State=0; FG_Alarm=0;				//Time Adjust Mode
		   PAUSE(20); 
			while(!(SW_Adj & SW_Enter));			   		//Wait Both Key Released
			while(SW_Enter)						      		//Pressed Enter Stop Select								
		 	{	if(!SW_Adj)								
		 		{	FG_Alarm^=1; 							//Time/Alarm Adj Mode Switch
		 			if(FG_Alarm) ptr=&Alarm;
		 			else ptr=&Time;
		 			PAUSE(25);								//Select Time/Alarm Adjest	
		 		}
		 	}
			FG_Select=0; FG_State=1; PAUSE(10);  			//Hour Adjust
			while(!SW_Enter); PAUSE(10); 		      		//Wait Enter Released								
			while(SW_Enter)						      		//Pressed Enter Stop Hour ADJ								
		 	{	if(!SW_Adj)
				{	if(++ptr->Hour>=24) ptr->Hour=0;	
					PAUSE(40);
				}
		 	}
			FG_Select=1;		
			PAUSE(10); while(!SW_Enter); PAUSE(10); 		//Wait Enter Released								
			while(SW_Enter)									//Pressed Enter Stop Minute ADJ								
		 	{	if(!SW_Adj)
				{	if(++ptr->Minute>=60)ptr->Minute=0;
					PAUSE(20);
				}
		 	}
			PAUSE(25);		
			ptr=&Time; FG_Adj=0; FG_Alarm=0;				
		}
		if((Time.Hour==Alarm.Hour)&&(Time.Minute==Alarm.Minute)) 
		{ 	
			while(SW_Adj & SW_Enter)
			{	for(i=0;i<150;i++)
				{	SPK=1; GCC_DELAY(100);
					SPK=0; GCC_DELAY(100);
				}
				for(i=0;i<200;i++)
				{	SPK=1; GCC_DELAY(150);
					SPK=0; GCC_DELAY(150);
				}				
			}
			PAUSE(200);	
		}
	}
}
DEFINE_ISR(ISR_STM,0x14)
{	u8 i;
	_t2af=0;
	if(PhaseCount==0)
	{	for(i=0;i<4;i++) 
		{	DisBuffer[i]&=0b10000000;
			DisBuffer[i]|=TransSegment[Digit[i]];
		}
	}
	else
	{	if(!(PhaseCount & 0x01))
		{	for(i=0;i<5;i++) GCC_RR(DisBuffer[i]);}
		for(i=0;i<5;i++) DisBuffer[i]=~DisBuffer[i];
	}	
	_pcs0=0x33; _pcs3=0x33; SegByte=0; SEG9=0;				//Set COM0~COM3 = VDD/2
	if(DisBuffer[0] & 0x01) SEG1=1;
	if(DisBuffer[0] & 0x10) SEG2=1;
	if(DisBuffer[1] & 0x01) SEG3=1;
	if(DisBuffer[1] & 0x10) SEG4=1;
	if(DisBuffer[2] & 0x01) SEG5=1;
	if(DisBuffer[2] & 0x10) SEG6=1;
	if(DisBuffer[3] & 0x01) SEG7=1;
	if(DisBuffer[3] & 0x10) SEG8=1;
	if(DisBuffer[4] & 0x01) SEG9=1;	
	switch(PhaseCount++)
	{	case 0: if(FG_HalfSec)								//Check 0.5 Sec
				{	FG_HalfSec=0; DisBuffer[0]^=Col;		//Flash ":"
					FG_Second^=1;							//Toggle Second Flag
					if(!FG_Second)							//Check 1 Second
					{	DisBuffer[1]&=0x7F; 				//Clear "C"
						if(DisBuffer[4]&1) DisBuffer[4]=(1<<4);
						else GCC_RR(DisBuffer[4]);
						if(++Second == 60)					//Time Update
						{	Second=0;
							if(++Time.Minute == 60) 
							{	Time.Minute=0;
								if(++Time.Hour==24) Time.Hour=0; 
							}
						}
					}	
				}
				if(FG_Adj)
				{	if (FG_Alarm) DisBuffer[1]|=_C;
		 			else DisBuffer[1]&=0x7F; 
		 			if(FG_State)
		 			{ 	if (FG_Select) DisBuffer[4]=0x0C;
		 				else DisBuffer[4]=0x03 ;
		 			}
				 	else DisBuffer[4]=0x0F;
				}				
				Digit[0]=(*ptr).Hour/10; Digit[1]=(*ptr).Hour%10;	
				Digit[2]=ptr->Minute/10; Digit[3]=ptr->Minute%10;					
				_pcs0=0x30; COM0=0; break;			//COM0(PC0)
		case 1: _pcs0=0x30; COM0=1; break;			//COM0(PC0)
		case 2: _pcs0=0x03; COM1=0; break;			//COM1(PC1)
		case 3: _pcs0=0x03; COM1=1; break;			//COM1(PC1)
		case 4: _pcs3=0x30; COM2=0; break;			//COM2(PC6)
		case 5: _pcs3=0x30; COM2=1; break;			//COM2(PC6)
		case 6: _pcs3=0x03; COM3=0; break;			//COM3(PC7)
		case 7: _pcs3=0x03; COM3=1;		
		
//==================================== Due to Compiler Bug, Replaced By Block ABC
				for(i=0;i<5;i++) 						//Restore Display Buffer
				{	GCC_RR(DisBuffer[i]); 
					GCC_SWAP(DisBuffer[i]);
					DisBuffer[i]=~DisBuffer[i];
				}
//==================================== Block ABC Start		
//                for(i=0;i<5;i++) 						//Restore Display Buffer
//				{   PhaseCount=DisBuffer[i];
//					GCC_RR(PhaseCount); 
//					GCC_SWAP(PhaseCount);
//					DisBuffer[i]=~PhaseCount;
//				}
//==================================== Block ABC STOP		
				PhaseCount=0; break;
	}
	if(--SecCounter==0)
		{SecCounter=125; FG_HalfSec=1;}
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);			      	//Dealy i*10ms
}