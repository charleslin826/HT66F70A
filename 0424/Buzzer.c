// PROGRAM	: Buzzer.c										2018.0418
// FUNCTION	: Bluetooth Module Test Program for HT66F70A	By Steven
#include 	"HT66F70A.h"
#include 	"MyType.h"
#define	 	_RX			_pa3							//Connet to BT TX	
#define	 	_RXC		_pac3	
#define	 	_TX			_pa1							//Connet to BT RX
#define	 	_TXC		_pac1	
#define	 	fSYS		8000000	
#define	 	BaudRate	19200
#define	 	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
#define  	KeyPort		_pe
#define  	KeyPortC	_pec
#define  	KeyPortPU	_pepu
const u16 Pitch_TAB[] = {			      				//音調常數建表區
		   fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
		   fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
		   fSYS/(998*2*4),fSYS/(523*4*4),fSYS/(587*4*4),
		   fSYS/(659*4*4),fSYS/(698*4*4),fSYS/(785*4*4),
		   fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4),
		   fSYS/(587*8*4)};
void Delayms(u16);
void UARTTXData(u8);
u8 ScanKey();
volatile u8 RxData;
volatile _Bool b_RX=0;
void main()
{	u8 temp;
	_wdtc=0b10101111;									//關閉看們狗計時器
	_RXC=1; _TX=1; _TXC=0;
	_pcs2=0x01;											//設定PC4為TP2功能
	_tm2c0=0; _tm2c1=0b00110001;						//STM: Compare Match O/P, CLR By CCRA(P2-58)
	_integ=0x02;
	_ifs0=0x00;											//PA3 as INT0 
	_tm0c0=0b00010000;									//fINT=fSYS
	_tm0c1=0b11000001;									//T/C, TM0A Match Clear
	_int0e=1; _emi=1;
	while(1)
	{	if(b_RX==1)										//是否接收完成？
		{	b_RX=0;										//清除接收完成旗標
			RxData-=(RxData<'A')?'0':'7';				//ASCII轉換成數值    因用手機到HT66是用ASCII碼 也可手機端改掉 這邊就不用減  因為"9"是57[0x39]  A是65[0x41] 要到58 所以-7
			_tm2al=(u8)Pitch_TAB[RxData];				//TM2AL Shold be Loaded First !!
			_tm2ah=Pitch_TAB[RxData]>>8;
			_t2on=1;									//Start STM
			Delayms(250); _t2on=0; 
		}
		temp=ScanKey();									//未接收到資料
		if(temp!=16) 									//是否按壓鍵盤？
		{	temp+=(temp<10)? '0' : 'A'-10;				//轉換成ASCII	HT66到手機
			UARTTXData(temp);							//透過藍芽傳送
			Delayms(250);
		}
	}
}
DEFINE_ISR(ISR_ExtINT0,0x04) //微控制器端的Software的UART最重要	//接受的優先權比傳送高
{	u8 temp=0b00000001;	
	_tm0al=(u8)(BITC/2); _tm0ah=(BITC/2)>>8;			//0.5T
	_t0af=0; _t0on=1;
	RxData=0;
	while(!_t0af);										//等待0.5T
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;					//T
	do 
	{	_t0af=0;
		while(!_t0af);									//等待1T時間
		if(_RX) RxData|=temp;							//擷取資料
		temp<<=1;										//RxData左移
	} while (temp);										//若temp不為0接收下一位元
	_t0on=0;
	b_RX=1;												//設定接收完成旗標
	_int0f=0;
}	
void UARTTXData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;					//T
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
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;						//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;								   	//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				   	//Check Column 0
		key++;
		if(!(KeyPort & 1<<6)) break;				   	//Check Column 1
		key++;
		if(!(KeyPort & 1<<5)) break;				   	//Check Column 2
		key++;
		if(!(KeyPort & 1<<4)) break;				   	//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;				//Scancode for Next Row
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;
	for(i=0;i<del;i++)  GCC_DELAY(2000);				//Delay del ms @ fSYS=8MHz
}