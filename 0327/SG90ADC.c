// PROGRAM	: SG90ADC.c							2017.0628
// FUNCTION	: Servo Control with ADC   			By Steven
#include <HT66F70A.h>
#include "MyType.H"
void PAUSE(u8);
void main()
{	u16 adcr;
	_wdtc=0b10101111;							//關閉看們狗計時器
	_pas2=0x03;									//PA4 as AN4
	_adcr0=0b00000100;							//Select AN4, ADOFF=0
	_adcr1=0b00100110;							//VBGEN=VREFS=0,ADRFS=1,Clock=fSYS/64
	_pcs2=0x01;									//PC4 as TP2
	_tm2c0=0; _tm2c1=0b10101000;			 	//fINT=fSYS/4, PWM O/P Mode //Active HI,Non-Inv
	_tm2rp=160;									//Set Period=256*160*(1/fINT)=20.480ms
	_tm2al=(u8)3000; _tm2ah=3000>>8;			//Set PWM Duty
	_t2on=1;									//Start STM
	while(1)
	{	_start=1; _start=0;						//Start ADC
		while(_eocb);
		adcr=_adrl+((u16)_adrh<<8);				//Get 12-Bit Result
		adcr=adcr+1000;						
		adcr=(adcr>5000) ? 5000 : adcr;			//Boundary Check	
		while(!_t2pf); _t2pf=0; _t2on=0;		//Wait Period Finish
		_tm2al=(u8)adcr; _tm2ah=adcr>>8;		//Set PWM Duty
		_t2on=1;
	}
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++)  GCC_DELAY(20000); 		//Delay 10ms*i
}