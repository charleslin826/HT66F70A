// PROGRAM	: 4-9.c									2015.0910
// FUNCTION	: 7-SEG With Delay Control By CTM 	   	By Steven
#include "HT66F70A.h"
#include "MyType.h"
#define SEG_Port 	_pd
#define SEG_PortC 	_pdc
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66,	//7-Segment Table
						0x6D,0x7D,0x07,0x7F,0x67};
void PAUSE(void);
void main()
{	u8 i;	
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEG_PortC=0x00;								//Config Port as OP Mode
	_tm2c0=0b00100000;							//T0ck[2:0]=010,fINT=fH=fSYS/16 石英震盪器為8Hz fINT=fH/16=fSYS/16=500KHz 1/fINT=2us 每隔2us TM0D加1   其他查表課本2-43頁
	_tm2c1=0b11000001;							//CTM as Counter/Timer 前面兩個數字=11, TMA Match Clear 精簡型計時模組 最後一個數字=1 =>TMA達到目標值後清除 其他查表課本2-44頁
	_tm2al=10000&0xFF; _tm2ah=10000>>8;	      	//TM0A=1000,1000/fINT(500KHz)=2mS  //設定目標值10000(十進位) //_tm0al 只看低8位low  ;_tm0ah只看高8位high 
	while(1)
	{	for(i=0;i<10;i++)
		{	SEG_Port=SEG_TAB[i];				//Read Table
			PAUSE();							//Delay 1 Sec
		}
	}
}
void PAUSE(void)
{	u8 i;
	_t2on=1;									//Start CTM  供電=1
	for(i=0;i<50;i++)							//500*2mS=1 Sec
		{ 	while(!_t2af);						//Wait T0AF=1  (flag)
			_t2af=0;							//Clear T0AF 
		}
	_t2on=0;									//Stop CTM   供電=0
}	