// PROGRAM	: 4-3.c									2016.0908
// FUNCTION	: 7 SEGMENT LED Demo Program			By Steven
#include "HT66F70A.h"
#include "MyType.h"
#define SEG_Port	_pd
#define SEG_PortC	_pdc
const u8 SEG_TAB[] = {		      					//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	s8 i,j;	
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0;									//Config Port as O/P Mode
	while(1)
	{	j=9;
		while(j>=0)	
			{	SEG_Port=SEG_TAB[j--];;			   	//Read Table and j=j-1
				for(i=0;i<50;i++) GCC_DELAY(20000);	//Delay 0.5 Sec
			}			
	}
}