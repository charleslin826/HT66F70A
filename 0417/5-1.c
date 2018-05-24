// PROGRAM	

//0: 5-1.c										2015.0911
// FUNCTION	: ETM PWM DC Motro Control with H-Bridge 	By Steven
// Note :  IN1->PC0, IN2->PC1, IN3->GND
#include "HT66F70A.h"
#include "5-1.H"
#include "MyType.H"
const u8 SEG_TAB[] = {								//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
const u16 PWM_TAB[] = {								//PWM Duty Cycle
			100,200,300,400,500,
			600,700,800,900,1000};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
void PAUSE(u8);			 
void main()
{	s8 Index=0;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0; 							//Config Port as Output
	SW_SpeedUpC=1; SW_SpeedUpPU=1;			   		//Config Pin Function
	SW_SpeedDownC=1; SW_SpeedDownPU=1;		   		//Config Pin Function
	SW_DirectionC=1; SW_DirectionPU=1;		   		//Config Pin Function
	_pcs0=0x01;										//PC0 as TP1B
	_tm1c0=0x20;									//fINT=fSYS/16(2us)
	_tm1c1=0b11101001;								//TM1A PWM, TM1A Match Clear
	_tm1c2=0b10101000;								//TM1B PWM 
	_tm1al=(u8)1023; _tm1ah=1023>>8;				//PWM Period=1023*1/fINT 2ms
	_pc&=0b11111100; _pcc&=0b11111100;				//Config PC0/PC1 as O/P
	_t1on=1;										//Start ETM
	while(1)
	{	SEGPort=(_pcs0==0x01)                      	//Display Speed Index
			? SEG_TAB[Index]:SEG_TAB[Index]|(1<<7);	
		_tm1bl=(u8)PWM_TAB[Index]; 					//Get Duty Cycle
		_tm1bh=PWM_TAB[Index]>>8;
		PAUSE(25);									//Delay 250ms
		while(1)
		{	if(!SW_SpeedUp)
			{	if(++Index>=9) Index=9; break;   	//Update Index & Boundary Check
			}
			else if(!SW_SpeedDown)
			{	if(--Index<=0) Index=0; break;   	//Update Index & Boundary Check
			}
			else if(!SW_Direction)
			{	if(_pcs0==0x01)						//Motor Direction Changing
				{	_pcs0=0x00; PAUSE(25);			//Turn-off & Dead-Zone Delay0
					_pcs0=0x10; break;				//Motor On(PC1 as TP1B)
				}
				else
				{	_pcs0=0x00; PAUSE(25);			//Turn-off & Dead-Zone Delay
					_pcs0=0x01; break;				//Motor On(PC0 as TP1B)
				}
			}
		}
	}
}
void PAUSE(u8 i)
{	u8 j;
	for (j=0;j<i;j++) GCC_DELAY(20000);				//Delay i*10mS
}