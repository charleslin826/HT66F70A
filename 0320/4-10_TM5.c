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
		fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4),
		fSYS/(587*8*4)};
u8 ScanKey(void);
void PAUSE(u8);
void main()
{	//u8 i;
	u8 Key;
	_wdtc=0b10101111;									//�����ݭ̪��p�ɾ�
	SPK_PortC=0;						            	//Config PC.4 as O/P
	_mf4e=1; _t5ae=1; 									//Enable MF0 and T2A Interrupt
	_tm5c0=0; _tm5c1=0b11000001;                 		//Timer/Counter, TM2A Match Clear�ҥ�2-43�� ����Ȧs��
	_t5af=0; _mf4f=0; _emi=1;                    		//fINT=fSYS/4; Enable Interrupt
	
	while(1)
	{	
	do Key=ScanKey();while(Key==16);	   		//Wait Key Pressed //C�y���@��i�H����ӱԭz �u�n�Τ����j�}�N�n do��{}�w�ٲ�				   		
				_tm5al=Pitch_TAB[Key]&0xFF;		         	//TM2AL Should be Loaded First !!
		    	_tm5ah=Pitch_TAB[Key]>>8;          
				_t5on=1; PAUSE(40);							//Start Timer2 and Delay 400mS
				_t5on=0; PAUSE(10);							
}
}

DEFINE_ISR(ISR_STM,0x38)  //��TM5�o��]�n��V�q
{	SPK_Port=!SPK_Port;								  	//Toggle PC.4
	_t5af=0;											//Clear T2AF
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);					//Delay i*10ms
}

u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xf0; KeyPortPU=0xf0;			   		//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;					         	//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;		      	//Check Column 0 //& 1<<4�Omask �h�ˬd0001 0000  //�Ĥ@���Y���UA�h�������O1  
		key++;
		if(!(KeyPort & 1<<5)) break;			   	//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;			   	//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			   	//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;	   		//Scancode for Next Row   �O�ұ��]�X�u���@��0(�p���~�i�T�{���G)
	}
	return key;	//�Y���S�����O�^��16 //���UA�O�^��10=>KEY = +4+4+2 = 10 (=16�i�A)
}