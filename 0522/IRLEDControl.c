// PROGRAM	: IRLedControl.c							2015.1110
// FUNCTION	: LED Control By IR Remote Controller(NEC)	By Steven
//          : PC5->Buzzer, PC3-> FM9038 O/P ,PD[3:0]->LEDs
#include "HT66F70A.h"
#include "MyType.H"
#include "Decoder.H"
u8 IRDecoder(u16*,u16*);
void Delayms(u16 del);
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void Display(u16*);
const u8 STR1[]={"CUS. ID:"};
const u8 STR2[]={"Command:"};
void LED(u16);
void main()
  {	u16 adrs,cmd;
	u8 state,i;
	_wdtc=0b10101111;										//關閉看門狗計時器
	LEDPort|=0x0F; LEDPortC&=0xF0;							//***
	_tm0c0=0; _tm0c1=0b00110001;							//TM0比對吻合輸出 
	_tm0al=500&0xFF; _tm0ah=500>>8;							//設定比對吻合週期=250us
	_pcs2=0x20;												//選擇TP0功能於PC5實現
	_tm2c0=0;									  			//TM2: STM fINT=fSYS/4
	_ifs2=0b00000000;									  	//TP2I -> PC3
	LCMInit();
	LCMWrite(0,0x80); i=0;									//Select Row 1
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);				//顯示STR1[]字串
	LCMWrite(0,0xC0);i=0;									//Select Row 2
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);				//顯示STR2[]字串
	while(1)
	{	state=IRDecoder(&adrs,&cmd);						//讀取IR信號
		if(state==2 && adrs==CID)
		{	LED(cmd);
			LCMWrite(0,0x89); Display(&adrs);				//Select Row 1
			LCMWrite(0,0xC9); Display(&cmd);				//Select Row 2
			_t0on=1; Delayms(50); _t0on=0; Delayms(100);	//輸出2KHz方波並維持50ms
			_t0on=1; Delayms(40); _t0on=0; 					//輸出2KHz方波並維持40ms
		}
		else if(state==1 && adrs==CID)
		{	LED(cmd);	
			LCMWrite(0,0x90); LCMWrite(1,'R');
			_t0on=1; Delayms(20); _t0on=0; 					//輸出2KHz方波並維持0.2秒
		}
		else if(state==0)
		{	LCMWrite(0,0xD0); LCMWrite(1,'.');
			Delayms(80);
		}	
		LCMWrite(0,0x90); LCMWrite(1,' ');
		LCMWrite(0,0xD0); LCMWrite(1,' ');
	}
}
void LED(u16 cmd)
{	switch(cmd)
	{	case LED0:
			LEDPort^=1;
			break;
		case LED1:
			LEDPort^=(1<<1);
			break;
		case LED2:
			LEDPort^=(1<<2);
			break;
		case LED3:
			LEDPort^=(1<<3);
			break;			
	}
}
void Display(u16 *ptr)
{	u16	x=0xF000;
	u8 tmp,i=3;
	do
	{	tmp=(*ptr & x)>>(4*i--);
		tmp=(tmp>9)? tmp+'7': tmp+'0';
		LCMWrite(1,tmp);
		if(i==1) LCMWrite(1,' ');
	} while((x>>=4)!=0);		
}	
u8 IRDecoder(u16 *ptradrs,u16 *ptrcmd)
{	u32 temp=0,temp1=1;
	u16 TCnt;												//Time Tick Counter, Address
	_tm2rp=80;												//256*80*fINT=10240us(計數最大限制)
	_tm2c1=0b01000000;										//輸入捕捉模式(正緣)
	_t2pf=0; _t2af=0;										//清除T2AF、T2PF旗標
//	while(!IR_Pin);											//等待SPACE
	while(IR_Pin);											//等待Start Bit
	_t2on=1;												//開始計數
	while(!_t2af)											//等待STRAT信號結束
	{	if(_t2pf) {_t2on=0; return 0; }						//若超過最大計數限制，回傳0
	}
	_t2on=0; _t2af=0; _t2pf=0;  							//停止TM2, 清除T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//取得START信號之時間長度
	if(TCnt<16000) return 0;								//若Start<8ms，回傳0
	_tm2c1=0b01010000;										//輸入捕捉模式(負緣)
	_t2on=1; 
	while(!_t2af)											//等待SYNC信號結束
	{	if(_t2pf) {_t2on=0; return 0; }						//若超過最大計數限制，回傳0
	}
	_t2on=0; _t2af=0; _t2pf=0; 								//停止TM2, 清除T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//取得SYNC信號之時間長度
	if(TCnt<4000 || TCnt>9600) return 0; 					//若SYNC<2.0ms 或 >4.8ms，回傳0
	if(TCnt<5200)  return 1;								//若2ms<SYNC<2.6ms為重複碼，回傳1
	while(temp1!=0)											//接收資料位元
	{	_t2on=1;											//啟動計數
		while(!_t2af);										//等待位元時間結束;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;					//取得位元時間
		_t2on=0; _t2af=0;									//停止TM2, 清除T2AF
		if(TCnt>3000) temp=temp|temp1;						//若位元時間>1500us,則位元為1 
		temp1<<=1; 
	}	 
	_t2on=0; 												//停止TM2 
	*ptradrs=(u16)temp;										//取得Custom Code
	*ptrcmd=(temp & 0xFFFF0000)>>16; 						//取得Command
	return 2;												//Command正確，回傳2
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	            			//設定EN/RW/RS腳位為低電位
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	         			//設定EN/RW/RS腳位為輸出模式
	GCC_DELAY(50000);							         	//LCM Power-On Time
	LCMWrite(0,0x38);							      		//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);						         		//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);							      		//COMD:Increment, Not Shift
	LCMWrite(0,0x01);							      		//COMD:Clear LCM Display
}	
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;								//規劃Port為輸入模式
	LCM_RS=0; LCM_RW=1;										//RS=0,RW=1 (Read IR)
	_nop(); 
	do
	{	LCM_EN=1; _nop();							   		//EN=1
		BusyAC=LCM_DataPort;						   		//Loop Until BF=0
		LCM_EN=0;									   		//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;								   		//規劃Port為輸出模式
	LCM_RW=0;										   		//RW=0 (Write)
	LCM_RS=DCFlag;									   		//Set RS State By DCFlag
	LCM_DataPort=CD;								   		//Sent Command or Data
	LCM_EN=1; _nop(); LCM_EN=0;			      				//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}
