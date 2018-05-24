// PROGRAM	: 4-10-1.c										20150910
// FUNCTION	: STM Compare Match Output Mode Control  		By Steven
#include "HT66F70A.h"
#include "4-10-1.H"
#include "MyType.H"
#define fSYS   8000000										//8MHz System Frequency
const u16 Pitch_TAB[] = {			      					//Pitch Control Table
			fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
			fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
			fSYS/(998*2*4),fSYS/(523*4*4),fSYS/(587*4*4),
			fSYS/(659*4*4),fSYS/(698*4*4),fSYS/(785*4*4),
			fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4),
			fSYS/(587*8*4)};
void PAUSE(u8);
void main()
{		
	_wdtc=0b10101111;										//關閉看們狗計時器
	_pcs2=0x01;												//Enable PC4 as TP2 Function
	_pcs1=0x10;
	_tm2c0=0; _tm2c1=0b00110001;							//STM: Compare Match O/P, CLR By CCRA
	_pas2=0x03;									//PA4 as AN4
	_adcr0=0b00000100;							//Select AN4, ADOFF=0
	_adcr1=0b00000110;							//VBGEN=ADRFS=VREFS=0,Clock=fSYS/64
	_ade=1; _emi=1;								//Enable ADC Interrupt 
	while(1)
	{	_start=1; _start=0;						//Start ADC Convert
		PAUSE(5);								//Delay 50mS		
	}
}

DEFINE_ISR(ISR_ADC,0x1C)
{	u8 i=0;
	if(_adrh>2) {
		i = _adrh>>4;
		_tm2al=Pitch_TAB[i]&0xFF;						//TM2AL Shold be Loaded First !!
		_tm2ah=Pitch_TAB[i]>>8;		
		_t2on=1;											//Start STM
		//PAUSE(500); _t2on=0; 							//Delay 250mS, Stop STM
	}else _t2on=0;

}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);						//Delay 10ms*i
}	