// PROGRAM	: 4-11.c							2015.0910
// FUNCTION	: ADC With Interrupt Demo Program	By Steven
#include "HT66F70A.h"	
#include "MyType.h"		
#define LED_Port  _pc								
#define LED_PortC _pcc
void PAUSE(u8);
void main()
{	_wdtc=0b10101111;							//關閉看們狗計時器
	LED_PortC=0;	      						//Config Port O/P Mode
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
{	LED_Port=~_adrh;
}
void PAUSE(u8 i)
{	u8	j;
	for(j=0;j<i;j++) GCC_DELAY(10000);			//Dealy i*10ms
}