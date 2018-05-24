// PROGRAM	: RGB.c									2016.0601
// FUNCTION	: RGB LED Simple Control By BT			By Steven
#include <HT66F70A.h>
#include "RGB.H"
u8 UARTRxData(void);
volatile u8	RxData; 
volatile _Bool b_RX;
void main()
{	u16 temp;
	u8 index,rR=0,rG=0,rB=0,rA=128;					//rA是亮度(0~255)
	_wdtc=0b10101111;								//關閉WDT
	_RXC=1; _integ=0x02; _int0e=1;					//INT0負源觸發
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

 	_emi=1;    										//致能中斷
 	b_RX=0;  			
	_t1on=1; _t3on=1;
	while(1)
	{	while(!b_RX); b_RX=0;						//接收資料指標
		index=RxData; 
		switch(index)
		{	case Red:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//因為我們TIMER只有十個位元 所以原先16移成10位元
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				break;
			case Green:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				break;
			case Blue:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case Alpha:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rA=RxData;							//Update Alpha
				temp=((u16)rR*rA)>>6;
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 5:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 6:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rA=128;
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//因為我們TIMER只有十個位元 所以原先16移成10位元
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				rB=RxData;
				temp=((u16)rB*rA)>>6;
				_tm1bl=(u8)temp; _tm1bh=temp>>8;	//Update Duty(B)
				break;
			case 7:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//因為我們TIMER只有十個位元 所以原先16移成10位元
				_tm3al=(u8)temp; _tm3ah=temp>>8;	//Update Duty(R)
				break;
			case 8:
				while(!b_RX); b_RX=0;  				//等待色彩資料
				rA=128;
				rG=RxData;
				temp=((u16)rG*rA)>>6;
				_tm1al=(u8)temp; _tm1ah=temp>>8;	//Update Duty(G)
				rR=RxData;
				temp=((u16)rR*rA)>>6;				//因為我們TIMER只有十個位元 所以原先16移成10位元
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
	_tm0al=(BITC/2); _tm0ah=(BITC/2)>>8;				//0.5T  一進入中斷 先數半個位元的時間到達位元中間 這樣讀值比較穩定不會錯
	_t0af=0; _t0on=1;
	RxData=0;
	while(!_t0af);										//等待0.5T
	_tm0al=(u8)BITC; _tm0ah=BITC>>8;					//T
	_t0af=0;
	do 
	{	while(!_t0af);									//等待1T時間
		_t0af=0;
		if(_RX) RxData|=temp;							//擷取資料
		temp<<=1;										//RxData左移
	} while (temp);										//若temp不為0接收下一位元
	while(!_t0af);										//等待1T時間(STOP Bit)	
	_t0on=0;
	b_RX=1;												//設定接收完成旗標
	_int0f=0;											//防止原先的負緣觸發中斷在傳送資料時觸發
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