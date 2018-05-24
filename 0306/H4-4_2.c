// PROGRAM	: H4-4_2.c								2015.0908
// FUNCTION	: 7 SEGMENT WITH SPEED CONTROL   		By Steven
#include "HT66F70A.h"
#include "MyType.h"
#include "4-4.H"
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66,	//7-Segment Table
	         			0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	u8 i,j,k;
	_wdtc=0b10101111;								//闽超璸竟
	SEG_PortC=0x0;									//Config Port as O/P Mode
	DIP_PortC|=0b00001111;					   		//Config Port[3..0] as I/P
	DIP_PortPU|=0b00001111;				     		//Enable Port[3..0] Pull-up
	while(1)
	{	for (j=0;j<=9;j++)	
		{	if(!(j % 2) &&  (DIP_Port % 2)) j++;	//j案计PE01j+1锣计 //(j % 2) reverse
           	if( (j % 2) && !(DIP_Port % 2)) j++;	//j计PE00j+1锣案计 //(j % 2) j(1,3,5,7,9)=1 >>1 or 0 / j(0,2,4,6,8)=0 >>0
			//while(DIP_Port & 0b00001000);
			if(j<10) 
			{	SEG_Port=SEG_TAB[j];				//Read Table
				k=(DIP_Port & 0b00001111)*5; 
				for(i=0;i<k;i++) GCC_DELAY(20000);	//Delay k*10 mSec
			}
		}
	}
}	