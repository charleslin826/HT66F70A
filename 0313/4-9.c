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
	_wdtc=0b10101111;							//�����ݭ̪��p�ɾ�
	SEG_PortC=0x00;								//Config Port as OP Mode
	_tm0c0=0b00100000;							//T0ck[2:0]=010,fINT=fH=fSYS/16 �ۭ^�_������8Hz fINT=fH/16=fSYS/16=500KHz 1/fINT=2us �C�j2us TM0D�[1   ��L�d��ҥ�2-43��
	_tm0c1=0b11000001;							//CTM as Counter/Timer �e����ӼƦr=11, TMA Match Clear ��²���p�ɼҲ� �̫�@�ӼƦr=1 =>TMA�F��ؼЭȫ�M�� ��L�d��ҥ�2-44��
	_tm0al=1000&0xFF; _tm0ah=1000>>8;	      	//TM0A=1000,1000/fINT(500KHz)=2mS   //�]�w�ؼЭ�10000(�Q�i��) //_tm0al �u�ݧC8��low  ;_tm0ah�u�ݰ�8��high 
	while(1)
	{	for(i=0;i<10;i++)
		{	SEG_Port=SEG_TAB[i];				//Read Table
			PAUSE();							//Delay 1 Sec
		}
	}
}
void PAUSE(void)    // �n�����polling
{	u16 i;
	_t0on=1;									//Start CTM  �ѹq=1
	for(i=0;i<500;i++)							//500*2mS=1 Sec    
		{ 	while(!_t0af);						//Wait T0AF=1  (flag)
			_t0af=0;							//Clear T0AF 
		}
	_t0on=0;									//Stop CTM   �ѹq=0
}	