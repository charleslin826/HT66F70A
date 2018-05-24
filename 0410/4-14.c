// PROGRAM	: 4-14.c							2017.0701
// FUNCTION	: Analog Comparator Contrl        	By Steven
// Note		: Changing to Fit ESK-300
#include "HT66F70A.h"
#include "MyType.h"			
#define LED_Port	_pc
#define LED_PortC	_pcc
void main()
{	_wdtc=0b10101111;							//關閉看們狗計時器
	LED_Port=0xFF; LED_PortC=0;					//Turn off LED, LED_Port O/P Mode
	_pfs0=0x77;									//PF1(PA2) as C1P, PF0(PA3) as C1N
	_pgs0=0x10;									//PG1 as C1X
	_cp1c=0b11100000;							//Enable CP1, C1POL=C1OS=1
	_cp1e=1; _emi=1;							//Enable CP1 Interrupt 
	while(1);									//Loop Forever
}
DEFINE_ISR(ISR_CP1,0x10)						//CP1 Interrupt Vector
{	if(!_c1out)									//C1P>C1N (C1POL=1) ?
	{ 	while(LED_Port!=0xFF) 					//No, Less Refelction Detect
		{	LED_Port>>=1; LED_Port|=0x80; 		//Shift Right By 1 
			GCC_DELAY(200000);					//Dealay 0.1 Sec	
		}
	}
	else										//Yes,C1P>C1N
	{ 	while(LED_Port!=0x00)
		{	LED_Port<<=1; 						//Shift Left and Replace LSB By 1
			GCC_DELAY(200000);					//Dealay 0.1 Sec

		}
	}
}