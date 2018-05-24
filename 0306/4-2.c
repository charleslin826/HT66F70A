// PROGRAM	: 4-2.c									2015.0908
// FUNCTION	: LEDs PILI Light Demo Program	      	By Steven
#include "HT66F70A.h"
#define LED_Port	_pc
#define LED_PortC	_pcc
const unsigned char Pili_TAB[] = {          		//Pili Table 霹靂燈 //寫const 等於放在ROM 否則會放在RAM(RAM較小 程式很大時會造成記憶體空間不足)
	        0b10000001,0b01000010,0b00100100,
	        0b00011000,0b00100100,0b01000010};
void main()
{	unsigned char i,j;	
	_wdtc=0b10101111;								//關閉看們狗計時器
	LED_PortC=0x0;									//Config LED_Port as Output
	LED_PortC=0x0;									//Config Port as O/P Mode
	while(1)
	{	for(j=0;j<6;j++)	
			{	LED_Port=~Pili_TAB[j];		      	//Read Table
				for(i=0;i<80;i++) GCC_DELAY(2000);	//Delay 80 ms
			}
	}
}