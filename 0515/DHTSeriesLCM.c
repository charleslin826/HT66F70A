// PROGRAM	: DHTSeriesLCM.c							    2017.1130
// FUNCTION	: DHT22,11 Series Sensor Reading Test 				By Steven
#include <HT66F70A.h>
#include "DHTSeries.h"
u8 ReadDHT(u16* h,u16* t);
void Delayms(u16);
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
const u8 String1[] = {"  Humidity :  .  %RH"};
const u8 String2[] = {"Temperature:  .  "};
void main()
{	u16 h,t;
	const u8* ptr;
	_wdtc=0b10101111;										//關閉看門狗計時器
	pDHTPU=1; pDHTC=1;										//config as I/P
	LCMInit();				           						//LCM Initialization
	LCMWrite(0,0x80); ptr=String1;	
	while(*ptr!=0) LCMWrite(1,*ptr++);                     	// for Humidity
	LCMWrite(0,0xC0); ptr=String2;	
	while(*ptr!=0) LCMWrite(1,*ptr++);                      // for Temperature
	LCMWrite(1,0xB2); LCMWrite(1,'C');
	while(1)
	{	if(ReadDHT(&h,&t)==1)
		#ifdef 	DHT22
		{	LCMWrite(0,0x8C);
			LCMWrite(1,h/100+'0'); h%=100;
			LCMWrite(1,h/10+'0'); h%=10;
			LCMWrite(0,0x8F);
			LCMWrite(1,h+'0');
			LCMWrite(0,0xCC);
			LCMWrite(1,t/100+'0'); t%=100;
			LCMWrite(1,t/10+'0'); t%=10;
			LCMWrite(0,0xCF);
			LCMWrite(1,t+'0');
		}
		#else
		{	h>>=8; t>>=8;									//DHT11
			LCMWrite(0,0x8C);
			LCMWrite(1,h/10+'0'); h%=10;
			LCMWrite(1,h+'0');
			LCMWrite(0,0xCC);
			LCMWrite(1,t/10+'0'); t%=10;
			LCMWrite(1,t+'0');
		}
		#endif
		Delayms(2000);
	}
}
u8 ReadDHT(u16* ptrh,u16* ptrt)
{	u32	temp=0,temp1=(u32)1<<31;
	volatile u16	TCnt; u8 parity=0;
	_tm2rp=3;												//Capture I/P Limit
	_tm2c0=0;												//fINT=fSYS/4
	_tm2c1=0b10110000;										//Single-Pulse/Active Low
	_tm2al=(u8)DHTStartTC; _tm2ah=DHTStartTC>>8;			//1ms/20ms Start Signal
	_pds0=0x10;												//PD1 as TP2	
	_t2af=0; _t2on=1; 										//開始輸出
	while(!_t2af); 											//等待Start Signal結束
	_pds0=0x00;												//PD1 as I/O(Pull-High)			
	_tm2c1=0b01010000;										//Capture I/P with Falling-Edge
	_ifs2=0x80;												//TP2I -> PD1	
 	_t2af=0; _t2pf=0; 
 	while(pDHT);											//等待DHT Pull-low
	_t2on=1; 												//啟動Capture
	while(!_t2af)											//等待DHT結束Response	
	{	if(_t2pf) { _t2on=0; return 0;}						//超過時間
	} 
	_t2on=0;
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;	
	if(TCnt<(DHTSSDTC-50) || TCnt>(DHTSSDTC+50)) return 0;	//Response Single Count=480 
	while(temp1!=0)											//取得32-Bit資料
	{	_t2af=0; _t2on=1;									//啟動Capture
		while(!_t2af);										//等待負緣捕捉		
		_t2on=0;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;	
		if(TCnt>(DHTBit0TC+40)) temp|=temp1;							
		temp1>>=1;
	}
	temp1=1<<7;	 											//取得Checksum
	while(temp1!=0)
	{	_t2af=0; _t2on=1;									//啟動Capture
		while(!_t2af);										//等待負緣捕捉
		_t2on=0;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;	
		if(TCnt>(DHTBit0TC+40)) parity|=temp1;
		temp1>>=1;
	}
	TCnt=temp;												//計算Checksum
	TCnt+=temp>>8;
	TCnt+=temp>>16;
	TCnt+=temp>>24;
	while(!pDHT);											//等待End Signal結束
	if((u8)TCnt!=parity) return 0;							//Checksum Error
	*ptrt=temp; *ptrh=temp>>16;								//Get Temperature & Humidity
	return 1;
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	     	//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	  	//Config EN/RW/RS O/PAUSE
	GCC_DELAY(50000);						//LCM Power-On Time
	LCMWrite(0,0x38);						//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);						//COMD:No Display/Cursor Blinking Off
	LCMWrite(0,0x06);						//COMD:Increment, Not Shift
	LCMWrite(0,0x01);						//COMD:Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;				//Config Port as I/P Mode
	LCM_RS=0; LCM_RW=1;						//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();				//EN=1
		BusyAC=LCM_DataPort;				//Loop Until BF=0
		LCM_EN=0;							//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;						//Config Port as O/P Mode
	LCM_RW=0;								//RW=0 (Write)
	LCM_RS=DCFlag;							//Set RS State By DCFlag
	LCM_DataPort=CD;						//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;			//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;									//延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);		//Delay 1ms @ fSYS Hz
}
