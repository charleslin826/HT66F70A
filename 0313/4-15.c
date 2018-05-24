// PROGRAM	: 4-15.c									2015.0911
// FUNCTION	: WDT Demo Program							By Steven
// Note		: Configuration Option Setting--
//			  fSUB Clock Source = LIRC 32KHz	
#include "HT66F70A.h"
#include "MyType.h"
#define SEG_Port  _pd
#define SEG_PortC _pdc
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void PAUSE(u8);
void main()
{	u8 i;	
	_wdtc=0b01010100;							//Enable WDT,Time-out=2^15/fS
	SEG_PortC=0x0;								//Config PD as Output
	for(i=0;i<10;i++)
	{	SEG_Port=SEG_TAB[i]; PAUSE(25);		   	//Read Table &Delay 0.25 Sec
	}
	SEG_Port=0;									//Turn-off 7-Segment LEDs
	while(1);									//Loop Forever
}
void PAUSE(u8 i)								//Delay i*10mS
{	u8 j;
	for (j=0;j<i;j++)							//Insert CLRWDT to This Loop							
	{	GCC_DELAY(20000);						//if WDT Period is Shorten
	}					
	GCC_CLRWDT();								//Clear WDT
}