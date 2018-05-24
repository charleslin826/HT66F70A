// PROGRAM	: 5-5.c									2015.0911
// FUNCTION	: HT66F70A LCD Interface Control  	   	By Steven
#include "HT66F70A.h"
#include "5-5.H"
#include "MyType.H"
const u8 TransSegment[17]= {
			0x7B,0x30,0x5D,0x75,0x36,0x67,
			0x6F,0x31,0x7F,0x77,0x3F,0x6E,
			0x4C,0x7C,0x4F,0x0F,0x00};
volatile u8 DisBuffer[5],Digit[4];
volatile u8 PhaseCount,SecCounter;
volatile _Bool FG_HalfSec;
void main()
{	u8 i,Second=0,Minute=0;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SegByteC=0x00; SEG9C=0; 						//Config Pins' I/O Mode
	COM0C=0; COM1C=0; COM2C=0; COM3C=0;
	_scomc=0b00011111; 								//Enable LCD, Set 1/2 Bias
	_mf0e=1; _t2ae=1;								//Enable TM2 Interrupt
	_tm2c0=0; _tm2c1=0b11000001; 					//fINT=fSYS/4, Timer/Counter Mode
	_tm2al=(u8)8000; _tm2ah=8000>>8;				//TM2A=8000 (8000*0.5us=4ms)
 	_t2af=0; _mf0f=0; _emi=1; 						//Enable Interrupt
 	SecCounter=125; FG_HalfSec=0; 					//125*4ms=0.5 Second
 	PhaseCount=0; 									//Initial PhaseCount as 0	
	for(i=0;i<5;i++) DisBuffer[i]=0;				//Clear Buffer
	for(i=0;i<4;i++) Digit[i]=0;
	DisBuffer[0]|=Col; DisBuffer[2]|=AM;			//Display COL and AM Segment
	_t2on=1; 										//Start STM
	while(1)
	{	for(i=0;i<2;i++)							// 1 Sec Waitting Loop
		{	while(!FG_HalfSec);						//Wait 0.5 SecCounter
			FG_HalfSec=0;							//Clear Half Second Flag
			while(PhaseCount!=0);					//Wait for PhaseCount=0
			DisBuffer[0]^=Col;						//Flash "COL(:)" Segment XOR Col[0x80]只有反向最高位元  每0.5秒到反向一次 = 閃爍 
		}											//#define		Col			0x80			
		if(++Second==60)							//Time Updating
		{	Second=0;
			if(++Minute==15)						//15 Minute Boundary 
			{	Minute=0;
				DisBuffer[2]^=AM; DisBuffer[3]^=PM;	//Toggle AM/PM Segment State   #define		AM&PM			0x80
			}
		Digit[0]=Minute/10; Digit[1]=Minute%10;	   	//Convert to Segment Data
		}
		Digit[2]=Second/10; Digit[3]=Second%10;	   	//Convert to Segment Data
	}
}
DEFINE_ISR(ISR_STM,0x14)
{	u8 i;
	_t2af=0;
	if(PhaseCount==0)								//If PhaseCount=0, 
	{	for(i=0;i<4;i++) 							//Update Display Data
		{	DisBuffer[i]&=0b10000000;              //只保留最高位元(和數字沒關係) 其餘0~6 bit清掉
			DisBuffer[i]|=TransSegment[Digit[i]];  //查表更新
		}
	}
	else
	{	if(!(PhaseCount & 0x01))					//If PhaseCount=2,4,6 (even number),
		{	for(i=0;i<5;i++) GCC_RR(DisBuffer[i]);}	//Rotate Buffer Right 1 Bit     let i=0 DisBuffer[0] = 0111 1011  >RR> 1011 1101 [這裡會跑7次]
		for(i=0;i<5;i++) DisBuffer[i]=~DisBuffer[i];//Complement DispBuffer	         1011 1101  >> 0100 0010
	}	
	_pcs0=0x33; _pcs3=0x33; SegByte=0; SEG9=0;		//Set COM0~COM3 = VDD/2 , when = VDD/2 it means won't display LCD
	if(DisBuffer[0] & 0x01) SEG1=1;					//Set SEG1~SEG9 State   // SEGx = 1 就是要亮
	if(DisBuffer[0] & 0x10) SEG2=1;
	if(DisBuffer[1] & 0x01) SEG3=1;
	if(DisBuffer[1] & 0x10) SEG4=1;
	if(DisBuffer[2] & 0x01) SEG5=1;
	if(DisBuffer[2] & 0x10) SEG6=1;
	if(DisBuffer[3] & 0x01) SEG7=1;
	if(DisBuffer[3] & 0x10) SEG8=1;
	if(DisBuffer[4] & 0x01) SEG9=1;	
	switch(PhaseCount++)
	{	case 0: _pcs0=0x30; COM0=0; break;			//COM0(PC0 as IO, so it can output 1 or 0 to display)  //at same time PC1.6.7 as SCOM1.2.3 = VDD/2 
		case 1: _pcs0=0x30; COM0=1; break;			//COM0(PC0) same as above
		case 2: _pcs0=0x03; COM1=0; break;			//COM1(PC1 as IO, so it can output 1 or 0 to display)  //at same time PC0.6.7 as SCOM0.2.3 = VDD/2 
		case 3: _pcs0=0x03; COM1=1; break;			//COM1(PC1) same as above
		case 4: _pcs3=0x30; COM2=0; break;			//COM2(PC6 as IO, so it can output 1 or 0 to display)  //at same time PC0.1.7 as SCOM0.1.3 = VDD/2
		case 5: _pcs3=0x30; COM2=1; break;			//COM2(PC6) same as above
		case 6: _pcs3=0x03; COM3=0; break;			//COM3(PC7 as IO, so it can output 1 or 0 to display)  //at same time PC0.1.6 as SCOM0.1.2 = VDD/2
		case 7: _pcs3=0x03; COM3=1; 				//COM3(PC7)	same as above	
//==================================== Due to Compiler Bug, Replaced By Block ABC
				for(i=0;i<5;i++) 					//Restore Display Buffer
				{	GCC_RR(DisBuffer[i]);   // 暨Line58 的七次後跑最後一次 回原始位置
					GCC_SWAP(DisBuffer[i]);  //將被移位過的資料還原   SWAP 是高4低4互換  >> 減少回復的動作 增加效率 [原先是左旋3次回去]
					//GCC_SWAP(varname) [1] = varname 的前四位與後四位交換
					DisBuffer[i]=~DisBuffer[i]; //原本0,1的狀態被我們反向7次了 這邊最後在反向一次
				}
//==================================== Block ABC Start		for old syntax
//                for(i=0;i<5;i++) 					//Restore Display Buffer
//				{   PhaseCount=DisBuffer[i];
//					GCC_RR(PhaseCount); 
//					GCC_SWAP(PhaseCount);
//					DisBuffer[i]=~PhaseCount;
//				}
//==================================== Block ABC STOP				
				PhaseCount=0; break;				//Reset PhaseCount
	}
	if(--SecCounter==0)
		{SecCounter=125; FG_HalfSec=1;}				//Reload Half Second Counter
}