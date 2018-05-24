// PROGRAM	: RGB.c									2016.0601
// FUNCTION	: RGB LED Simple Control By BT			By Steven
#include <HT66F70A.h>
#include "RGB.H"
u8 UARTRxData(void);
volatile u8	RxData; 
volatile _Bool b_RX;
void main()
{	u16 temp;
	u8 index,rR=0,rG=0,rB=0,rA=128;					//rA�O�G��(0~255)
	_wdtc=0b10101111;								//����WDT
	_RXC=1; _integ=0x02; _int0e=1;					//INT0�t��Ĳ�o
	_tm0c0=0b00010000;								//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;								//T/C, TM0A Match Clear
	
	_tm1c0=0b00110000;								//fINT=fSYS/64,T1RP=000
	_tm1c1=0b10101000;								//PWM G, Act Hi,TM1RP Match Clear
	_tm1c2=0b10101000;								//PWM B, Act Hi,Edge Aligned
	_tm1al=0; _tm1ah=0;								//Initial 0 Duty(G)
	_tm1bl=0; _tm1bh=0;								//Initial 0 Duty(B)
	
	_tm3c0=0b00110000;								//fINT=fSYS/64,T3RP=000
	_tm3c1=0b10101000;								//PWM R, Act Hi,TM3RP for Period
	_tm3al=0; _tm3ah=0;								//Initial 0 Duty(R)

	_pcs3=0x10;										//Enable PC7 as TP1A (G)	
	_pcs0=0x10;										//Enable PC1 as TP1B (B)	
	_pds0=0x01;										//Enable PD0 as TP3	 (R)

 	_emi=1;    										//�P�त�_
 	b_RX=0;  			
	_t1on=1; _t3on=1;
	while(1)
	{	while(!b_RX); b_RX=0;						//������ƫ���
		index=RxData; 
		switch(index)
		{	case Red:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//�]���ڭ�TIMER�u���Q�Ӧ줸 �ҥH���16����10�줸
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				break;
			case Green:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				break;
			case Blue:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case Alpha:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rA=RxData;							//Update Alpha
				temp=((u16)rR*rA)>>6;
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 5:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 6:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rA=128;
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//�]���ڭ�TIMER�u���Q�Ӧ줸 �ҥH���16����10�줸
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 7:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//�]���ڭ�TIMER�u���Q�Ӧ줸 �ҥH���16����10�줸
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				break;
			case 8:
				while(!b_RX); b_RX=0;  				//���ݦ�m���
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//�]���ڭ�TIMER�u���Q�Ӧ줸 �ҥH���16����10�줸
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
		}				
	}
}	
DEFINE_ISR(ISR_ExtINT0,0x04)
{	u8 temp=0b00000001;
	_tm0al=(BITC/2); _tm0ah=(BITC/2)>>8;				//0.5T  �@�i�J���_ ���ƥb�Ӧ줸���ɶ���F�줸���� �o��Ū�Ȥ��í�w���|��
	_t0af=0; _t0on=1;
	RxData=0;
	while(!_t0af);										//����0.5T
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;					//T
	_t0af=0;
	do 
	{	while(!_t0af);									//����1T�ɶ�
		_t0af=0;
		if(_RX) RxData|=temp;							//�^�����
		temp<<=1;										//RxData����
	} while (temp);										//�Ytemp����0�����U�@�줸
	while(!_t0af);										//����1T�ɶ�(STOP Bit)	
	_t0on=0;
	b_RX=1;												//�]�w���������X��
	_int0f=0;											//���������t�tĲ�o���_�b�ǰe��Ʈ�Ĳ�o
}	
void UARTTXData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;
	_t0af=0;
	_TX=0;												//Start
	_t0on=1;
	while(!_t0af);
	_t0af=0;
	do 
	{	if(data & temp) _TX=1; else _TX=0;
		while(!_t0af);
		_t0af=0;
		temp<<=1;
	} while (temp);	
	_TX=1;												//Stop
	while(!_t0af);
	_t0on=0;
}