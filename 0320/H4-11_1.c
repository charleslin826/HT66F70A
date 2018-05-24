// PROGRAM	: H4-11_1.c							   	2015.0910
// FUNCTION	: ADC With Interrupt Demo Program	   	By Steven
#include "HT66F70A.h"			
#include "MyType.h"			
#define LED_Port  _pc								
#define LED_PortC _pcc
const u8 TabLed[]={0x01,0x3,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
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
{	if(_adrh) LED_Port=~TabLed[_adrh>>5];		//_adrh!=0, True
	else 		 LED_Port=~_adrh; 				//_adrh=0, False
/*	if(_adrh < 32) LED_Port=~0x01;
	else if ((_adrh >=  32) && (_adrh <  64))	LED_Port=~0x03;
	else if ((_adrh >=  64) && (_adrh <  96))	LED_Port=~0x07;
	else if ((_adrh >=  96) && (_adrh < 128))	LED_Port=~0x0F;
	else if ((_adrh >= 128) && (_adrh < 160))   LED_Port=~0x1F;
	else if ((_adrh >= 160) && (_adrh < 192))	LED_Port=~0x3F;
	else if ((_adrh >= 192) && (_adrh < 226))	LED_Port=~0x7F;
	else  LED_Port=~0xFF;*/
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);			//Dealy i*10ms
}