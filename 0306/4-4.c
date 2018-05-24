// PROGRAM	: 4-4.c									2016.0908
// FUNCTION	: 7 SEGMENT WITH SPEED CONTROL         	By Steven
#include "HT66F70A.h"
#include "MyType.h"
#include "4-4.H"									//**NOTE: PA --> PE
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66,	//7-Segment Table
			         	0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	u8 i,j,k;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0x0;									//Config Port as O/P Mode
	DIP_PortC|=0b00001111;					      	//Config Port[4..0] as I/P 
	DIP_PortPU|=0b00001111;				         	//Enable Port[4..0] Pull-up 
	while(1)
	{	if(DIP_Port & 0b00000001) k=1;
		else k=0;
		for (j=k;j<=9;j+=2)							//
		{	SEG_Port=SEG_TAB[j];					//Read Table
			k=(DIP_Port & 0b00001111)*5;            //& 0b00001111去遮蔽/遮罩(MASK)   *5是放大五倍
			while(DIP_Port & 0b00001000);			//當撥開最左邊數過來第一個時 原地空轉
			for(i=0;i<k;i++) GCC_DELAY(20000);		//Delay k*10 mSec
		}
		}
}	