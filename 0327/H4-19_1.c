// PROGRAM	: H4-19_1.c							2015.0911
// FUNCTION	: fSYS and Slow Mode Switching 		By Steven
#include	"HT66F70A.h"
#include	"MyType.H"
#include	"4-19.H"
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void Display029(void);
void PAUSE(u8);
void main()
{	u8 Mode;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEG_Port=0; SEG_PortC=0;					//Clear & Config SEG_Port as O/P
	while(1)
	{ 	_hlclk=1;								//HLCLK=1, fSYS=fH
		Display029();
		Mode=0b01000000;						//Mode Change From 010 to 111
		do
		{	_smod&=0b00011110;					//CKS[2:0]=000, HLCLK=0
			_smod|=Mode;						//Update CKS[2:0] By Mode
			Display029();
			Mode+=0b00100000;					//Update Mode
		} while (Mode!=0);
	}	
}
void Display029(void)
{	u8 i;
		for(i=0;i<10;i++)
		{	SEG_Port=SEG_TAB[i]; 				//Disply Data
			PAUSE(10);							//Delay
		}	
}
void PAUSE(u8 i)					      
{	u8 j;
	if(_hlclk)
		for (j=0;j<i;j++) GCC_DELAY(20000);		//Delay i*20K Instruction Cycles
	else
		switch (_smod & 0b11100000)
		{	case 0b01000000:
				for (j=0;j<i;j++) GCC_DELAY(20000/64);	//Delay i*156 Instruction Cycles
				break;
			case 0b01100000:
				for (j=0;j<i;j++) GCC_DELAY(20000/32);	//Delay i*312 Instruction Cycles
				break;
			case 0b10000000:
				for (j=0;j<i;j++) GCC_DELAY(20000/16);	//Delay i*625 Instruction Cycles
				break;
			case 0b10100000:
				for (j=0;j<i;j++) GCC_DELAY(20000/8);	//Delay i*1250 Instruction Cycles
				break;
			case 0b11000000:
				for (j=0;j<i;j++) GCC_DELAY(20000/4);	//Delay i*2500 Instruction Cycles
				break;
			case 0b11100000:
				for (j=0;j<i;j++) GCC_DELAY(20000/2);	//Delay i*5K Instruction Cycles
				break;
		}			

}