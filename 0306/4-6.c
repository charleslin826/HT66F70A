// PROGRAM	: 4-6.c										2015.0910
// FUNCTION	: STEP MOTOR HALF STEP CONTROL     			By Steven
#include "HT66F70A.h"
#include "MyType.h"
#define Motor_Port   _pe
#define Motor_PortC  _pec
const u8 TAB_CW[] = {	0b0001,0b0011,0b0010,0b0110,	//Excitation Table 步進馬達
			   			0b0100,0b1100,0b1000,0b1001};
void main()
{	s8 i,j;	
	_wdtc=0b10101111;									//關閉看們狗計時器
	Motor_PortC=0x0;									//Config Port as O/P Mode
	while(1)
	{	for(i=0;i<50;i++)
		{	for(j=0;j<8;j++)	
			{	Motor_Port=TAB_CW[j];					//Read Table
				GCC_DELAY(20000);						//Delay 10mS
			}
		}
		for(i=0;i<50;i++)
		{	for(j=7;j>0;j--)	
			{	Motor_Port=TAB_CW[j];					//Read Table
				GCC_DELAY(20000);						//Delay 10mS
			}
		}
	}
}