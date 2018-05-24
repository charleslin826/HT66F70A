// PROGRAM	: 4-11.c							2015.0910
// FUNCTION	: ADC With Interrupt Demo Program	By Steven
#include "HT66F70A.h"	
#include "MyType.h"		
#define LED_Port  _pc								
#define LED_PortC _pcc
void PAUSE(u8);
const u16 TABLE[]={1,3,7,15,31,63,127,255};
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
{	u8 j,i=0;
	
	i = _adrh>>5;				 //高手
//	i = _adrh/32;                //進階

/*	if(_adrh>=0&&_adrh<=31){     //入門
	i=1;}
	else if(_adrh>=32&&_adrh<=63){
	i=0b00000011;}
	else if(_adrh>=64&&_adrh<=96){
	i=0b00000111;}
	else if(_adrh>=97&&_adrh<=128){
	i=0b00001111;}
	else if(_adrh>=129&&_adrh<=160){
	i=0b00011111;}
	else if(_adrh>=161&&_adrh<=192){
	i=0b00111111;}
	else if(_adrh>=193&&_adrh<=224){
	i=0b01111111;}
	else if(_adrh>=225&&_adrh<=256){
	i=0b11111111;}*/
//	LED_Port=~i;
//	LED_Port=~TABLE[i];	
	if(_adrh) LED_Port=~TABLE[i];   //_adrh!=0, True
	else LED_Port=_adrh;			//_adrh=0, False

/*	if(_adrh) LED_Port=~TABLE[_adrh>>5];		
	else 		 LED_Port=~_adrh; */				
	

	
}
void PAUSE(u8 i)
{	u8	j;
	for(j=0;j<i;j++) GCC_DELAY(10000);			//Dealy i*10ms
}