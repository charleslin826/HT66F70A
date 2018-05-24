// PROGRAM	: Bluetooth_ADC8.c							    2017.0601
// FUNCTION	: Bluetooth Module Test Program for HT66F70A	By Steven
// 將ADC轉換結果(8-Bit)經由藍芽傳輸  需搭配老師寫好的AI2程式 BT_VoltMeter.apk
#include <HT66F70A.h>
#include "MyType.h"
//#include "Bluetooth70.H"
#define 	_RX			_pa3			//Connet to BT TX	
#define 	_RXC		_pac3	
#define 	_TX			_pa1			//Connet to BT RX
#define 	_TXC		_pac1	
#define 	fSYS		8000000	
#define		BaudRate	19200
#define		BITC		(fSYS/BaudRate)	//Bit Interval Time Constant 位元區間 (計數多久代表一個位元)

void UARTTXData(u8);
void Delayms(u16);	
volatile _Bool b_RX=0;
u8 RxData;
void main()
{	_wdtc=0b10101111;									//關閉看門狗計時器
	_RXC=1; _TX=1; _TXC=0;
	_integ=0x02;_papu3=1;								//接收時才會用到
	_ifs0=0x00;											//PA3 as INT0  
	_tm0c0=0b00010000;									//fINT=fSYS
	_tm0c1=0b11000001;									//T/C, TM0A Match Clear
	_int0e=1; _emi=1;
	_adcr0=0x04;										//ADOFF=0,選擇AN4
	_adcr1=0b00000110;									//fSYS/64,VREFS=0,ADRFS=0
	_pas2=0x03;											//設定PA4為AN4功能
	while(1)
	{	_start=1; _start=0;								//Start ADC Convert
		while(_eocb);									//Wait Conversion Complete
		UARTTXData(_adrh);		
		Delayms(200);									//0.2 Sec
	}
}
void UARTTXData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;
	_t0af=0;
	_TX=0;												//Start
	_t0on=1;//啟動TIMER
	while(!_t0af);
	_t0af=0;//TIMER到 重新清成0
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
void Delayms(u16 del)
{	u16 i;
	for(i=0;i<del;i++)  GCC_DELAY(2000);				//Delay del ms @ fSYS=8MHz
}