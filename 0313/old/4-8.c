// PROGRAM	: 4-8.c									2015.0910
// FUNCTION	: GENERATE TONE By USING DELAY SKILL	By Steven
// NOTE: In Project Option: Language Must Select 
//       Enhanced Holtek C Compiler/Assembler, Due
//       to the Definition of fSYS Over range !!! 
#include "HT66F70A.h"
#include "MyType.h"
#define SPK_Port  	_pc4							//PC.4
#define SPK_PortC	_pcc4							//pcc.4
#define M1  1000000								   	//1000000
const u8 TAB_Pitch[] = {		   					//Pitch Constant
			M1/(523*2*10),M1/(587*2*10),
			M1/(659*2*10),M1/(698*2*10),
			M1/(785*2*10),M1/(880*2*10),
			M1/(988*2*10),M1/(523*2*2*10)};
const u16 TAB_Duration[] = { 	      				//Duration Constant
			523/2,587/2,659/2,698/2,
			785/2,880/2,988/2,(523*2)/2};
void PAUSE(u8);
void main()
{	u8 i;
	u16 j;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SPK_PortC=0;									//Config SPK_Port as Output
	while(1)
	{	for(i=0;i<8;i++)	   		
		{	for(j=0;j<TAB_Duration[i];j++)
			{	SPK_Port=!SPK_Port;				   	//Toggle PC.4
				PAUSE(TAB_Pitch[i]);
			}
		}
	}	
}
void PAUSE(u8 i)
{	u8 j;
    for(j=0;j<i;j++) GCC_DELAY(20);			      	//Delay i*10uS
}
