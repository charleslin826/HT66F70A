// PROGRAM	: 4-1-1.c								2016.0921
// FUNCTION	: LED Scanning Demo Program (while)		By Steven
#include	"HT66F70A.h"
#include	"MyType.h"			
#define LED_Port  _pc								
#define LED_PortC _pcc							
void main()
{	u8 i;	
	_wdtc=0b10101111;									//Disable CP1 Function
	LED_PortC=0x0;										//Config LED_Port as Output
	LED_Port=~0x01;										//Set Initial Data
	while(1)
	{	while(LED_Port & 0b10000000)
		{	for(i=0;i<100;i++) GCC_DELAY(2000);
			LED_Port=(LED_Port<<1)|1;				//Shift Left
		}
		while(LED_Port & 0b00000001)	
		{	for(i=0;i<200;i++) GCC_DELAY(2000);
			LED_Port=(LED_Port>>1)|0x80;							//Shift Right
		}				
	}
}	