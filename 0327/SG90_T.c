// PROGRAM	: SG90.c								2016.0805
// FUNCTION	: STM PWM O/P Mode for Servo Control   	By Steven
#include <HT66F70A.h>
#include "MyType.H"
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;							//�����ݭ̪��p�ɾ�
	_pcs2=0x01;									//PC4 as TP2
	_tm2c0=0; _tm2c1=0b10101000;			 	//fINT=fSYS/4, PWM O/P Mode //Active HI,Non-Inv
	_tm2rp=160;									//256*160*(1/fINT)=20.480ms
	_tm2al=(u8)2000; _tm2ah=2000>>8;			//Set PWM Duty
	_t2on=1;									//Start STM
	
	_adcr0=0b00000100;									//Select AN4, ADOFF=0
	_adcr1=0b00000110;									//A/D Clock=fSYS/64,ADRFS=1
	_pas2=0x03;											//PA4 as AN4
	_ade=1; _emi=1;											//Enable ADC Interrupt 
	_start=1; _start=0;									//Start ADC Convert   
	while(1);                                   //�W�@�Ӷg���٨S�����n������ �_�h�|���ög��
}


DEFINE_ISR(ISR_ADC,0x1C)
{
//	 PWM = 1000;
	u16 PWM=1000+_adrh*15.625;   // _adrh = 0~255
	if(PWM<1000) PWM=1000;
	if(PWM>5000) PWM=5000;
	while(!_t2pf);  		 // ��X��=0�ɡA���� (�i�ܹq���S���Q���)	
	_t2pf=0;	             // ���M�źX��//�]���O�ϥ�TM2 P�O����g�� A �O������Ť�
	_tm2al=(u8)PWM;				//Set PWM Duty  �������FPWM�q�y �h���
	_tm2ah=PWM>>8;				//				�������FPWM�q�y �h���
	_start=1; _start=0;			//Start ADC Convert
}
	