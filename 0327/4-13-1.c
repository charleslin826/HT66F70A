// PROGRAM	: 4-13-1.c							   2017.0628
// FUNCTION	: Software PWM Implection for LEDs     By Steven
// Has been Changed for ESK-300 Board
#include "HT66F70A.h"
#include "4-13-1.H"
#include "MyType.H"
void main()
{	u8 i,j,LED,LED1,LED2;
	_wdtc=0b10101111;								//關閉看們狗計時器
	LEDPort=~0; LEDPortC=0;							//Config Port as O/P Mode
	while(1)
	{	LED=~0x01; LED2=~0b11011111;           		//Set Initial State
		for(i=0;i<12;i++)                  			//Counting Loop               
		{	for(j=0;j<40;j++)                   	//Speed Contol Loop
				{	LED1=LED2;                     						//LED1 = ~0b11011111(LED2)
					LEDPort=LED; GCC_DELAY(500); 	//Duty=25/4000　   	1st on
					LEDPort|=LED1; GCC_DELAY(4500);	//Duty=250/4000     LEDPort= ~00000001 |  ~0b11011111 = ~0b11011111
					GCC_RL(LED1);									//  11011111 >> 10111110
					LEDPort|=LED1; GCC_DELAY(15000);	//Duty=1000/4000    LEDPort= 11011111 |  10111110 =  
					GCC_RL(LED1);
					LEDPort|=LED1; GCC_DELAY(60000);	//Always on
				}	
			if (i<=2) LED<<=1;  // LED=~0x02
			else LED=(LED<<1)|0x01; //LED=0000 0011 | 0000 0001 = 0000 0011 
			GCC_RL(LED2);
		}
		LED=~0x80; LED2=~0b11111011;           		//Set Initial State
		for(i=0;i<12;i++)                         	//Counting Loop  
		{	for(j=0;j<20;j++)                      	//Speed Contol Loop
				{	LED1=LED2;
					LEDPort=LED; GCC_DELAY(50);  	//Duty=25/4000
					LEDPort |= LED1; GCC_DELAY(450);//Duty=250/4000
					GCC_RR(LED1);
					LEDPort |= LED1; GCC_DELAY(1500);//Duty=1000/4000
					GCC_RR(LED1);
					LEDPort |= LED1; GCC_DELAY(6000);//Always on
				}
			if (i<=2) LED>>=1; 
			else LED=(LED>>1)|0x80;
			GCC_RR(LED2);
		}
	}
}