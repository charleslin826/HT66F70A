// PROGRAM	: ADC.c										2018.0505
// FUNCTION	: ADC(12-Bit) and LCD Dec/Hex Display 		By Steven
#define	Decimal		// Mark To Display in HEX
#include "HT66F70A.h"
#include "5-5.H"
#include "MyType.H"
const u8 TransSegment[17]=
			{0x7B,0x30,0x5D,0x75,0x36,
			 0x67,0x6F,0x31,0x7F,0x77,
			 0x3F,0x6E,0x4C,0x7C,0x4F,
			 0x0F,0x00};
volatile u8 DisBuffer[5],Digit[4];
volatile u8 PhaseCount;
volatile u16 Result;
void Delayms(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;									//關閉看們狗計時器	
	_adcr0=0b00000100;									//ADOFF=0,AN4
	_adcr1=0b00100100;									//ADRFS=1,fSYS/64
	_pas2=0x03;											//PA4 as AN4
	SegByteC=0x00; SEG9C=0; 
	COM0C=0; COM1C=0; COM2C=0; COM3C=0;
	_scomc=0b01111111; 
	_mf0e=1; _t2ae=1;
	_tm2c0=0; _tm2c1=0b11000001; 
	_tm2al=(u8)8000; _tm2ah=8000>>8;					//TM2A=8000 (8000*0.5us=4ms)
	_t2af=0; _mf0f=0;_ade=1; _emi=1; 
	for(i=0;i<5;i++) DisBuffer[i]=0;
	for(i=0;i<4;i++) Digit[i]=0;
	_t2on=1;
	while(1)
	{	_start=1; _start=0;								// Start ADC Convert
		Delayms(100);	
	}
}
DEFINE_ISR(ISR_STM,0x14)
{	u8 i; u16 temp;
	_t2af=0;
	if(PhaseCount==0)
	{	
#ifdef Decimal
		Digit[0]=Result/1000; temp=Result%1000;			// Decimal Disply
		Digit[1]=temp/100; temp=Result%100;
		Digit[2]=temp/10; Digit[3]=temp%10; 
#else
		Digit[0]=0;
//		Digit[1]=Result/256; temp=Result%256;			// Hex Disply
//		Digit[2]=temp/16; Digit[3]=temp%16; 
		Digit[1]=Result>>8; temp=(u8)Result;			// Hex Disply
		Digit[2]=temp>>4; Digit[3]=temp&0x0F; 
#endif	
		for(i=0;i<4;i++) 
		DisBuffer[i]=TransSegment[Digit[i]];
		DisBuffer[4]=0;
	}
	else
	{	if(!(PhaseCount & 0x01))
		{	for(i=0;i<5;i++) GCC_RR(DisBuffer[i]);}
		for(i=0;i<5;i++) DisBuffer[i]=~DisBuffer[i];
	}	
	_pcs0=0x33; _pcs3=0x33; SegByte=0; SEG9=0;			//Set COM0~COM3 = VDD/2
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
	{	case 0: _pcs0=0x30; COM0=0; break;				//COM0(PC0)
		case 1: _pcs0=0x30; COM0=1; break;				//COM0(PC0)
		case 2: _pcs0=0x03; COM1=0; break;				//COM1(PC1)
		case 3: _pcs0=0x03; COM1=1; break;				//COM1(PC1)
		case 4: _pcs3=0x30; COM2=0; break;				//COM2(PC6)
		case 5: _pcs3=0x30; COM2=1; break;				//COM2(PC6)
		case 6: _pcs3=0x03; COM3=0; break;				//COM3(PC7)
		case 7: _pcs3=0x03; COM3=1; PhaseCount=0; break;
	}
}
DEFINE_ISR(ISR_ADC,0x1C)
{	
	Result=_adrh; Result=(Result<<8)+_adrl;
}
void Delayms(u8 delay)
{	u8	j;
	for(j=0;j<delay;j++) GCC_DELAY(2000);				//Dealy delay*1ms
}