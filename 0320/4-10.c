// PROGRAM	: 4-10.c									2015.0910
// FUNCTION	: STM Timer Mode & Interrupt Control   		By Steven
#include "HT66F70A.h"
#include "4-10.H"
#include "MyType.H"
#define fSYS 8000000									//8000000
const u16 Pitch_TAB[] = {			      				//Pitch Control Table
		fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
		fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
		fSYS/(998*2*4),fSYS/(523*4*4),fSYS/(587*4*4),
		fSYS/(659*4*4),fSYS/(698*4*4),fSYS/(785*4*4),
		fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4)};
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;									//關閉看們狗計時器
	SPK_PortC=0;						            	//Config PC.4 as O/P
	_mf0e=1; _t2ae=1; 									//Enable MF0 and T2A Interrupt
	_tm2c0=0; _tm2c1=0b11000001;                 		//Timer/Counter, TM2A Match Clear課本2-43頁 控制暫存器
	_t2af=0; _mf0f=0; _emi=1;                    		//fINT=fSYS/4; Enable Interrupt
	while(1)
	{	for(i=0;i<15;i++)
		{//	_tm2ah=Pitch_TAB[i]>>8;						//若把高位原先放前面 音調會怪怪的 請看PDF P.98
			_tm2al=Pitch_TAB[i]&0xFF;		         	//TM2AL Should be Loaded First !!
		    _tm2ah=Pitch_TAB[i]>>8;          
			_t2on=1; PAUSE(40);							//Start Timer2 and Delay 400mS
			_t2on=0; PAUSE(10);							//Stop Timer2 and Delay 100mS  >> (400+100ms=0.5s)響一個音符 >> 每一秒響兩個音符
		}
	}
}
DEFINE_ISR(ISR_STM,0x14)
{	SPK_Port=!SPK_Port;								  	//Toggle PC.4
	_t2af=0;											//Clear T2AF
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);					//Delay i*10ms
}
