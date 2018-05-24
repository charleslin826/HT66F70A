// PROGRAM	: SG90.c								2016.0805
// FUNCTION	: STM PWM O/P Mode for Servo Control   	By Steven
#include <HT66F70A.h>
#include "MyType.H"
const u16 TAB_PWM[] = {  						//TM2A Table (Duty Control)	
		1000,3000,5000,3000};					//for SG90  0.5ms~2.5ms
		//1400,3000,4500,3000};					//for SH-0253 700us~2250us
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	_pcs2=0x01;									//PC4 as TP2
	_tm2c0=0; _tm2c1=0b10101000;			 	//fINT=fSYS/4, PWM O/P Mode //Active HI,Non-Inv
	_tm2rp=160;									//256*160*(1/fINT)=20.480ms
	_tm2al=(u8)2000; _tm2ah=2000>>8;			//Set PWM Duty
	_t2on=1;									//Start STM
	while(1)
	{	for(i=0;i<4;i++)
		{	_tm2al=(u8)TAB_PWM[i];				//Set PWM Duty
		 	_tm2ah=TAB_PWM[i]>>8;
		 	PAUSE(100);
		}	
	}
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++)  GCC_DELAY(20000); 		//Delay 10ms*i
}