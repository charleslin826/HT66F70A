// PROGRAM	: IRLedIntensity.c							2017.07.01
// FUNCTION	: LED Control By IR Remote Controller(NEC)	By Steven
//            Software PWM By Using Timer/Counter Operation
/* Note		: When Increase PWM Channels, The IRDevoder() may
			  Fault Due to the ISR Execution Cycles. Changing
			  the TM3 Comapre-match Time to 200us and Period	   
	            to 1000 could solve this problem! */ 
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
#define	Period 200											//PWM周期常數
volatile u8 PCnt,Bcnt[4]={10,10,10,10};
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
	PCnt=Period; 	
	_tm3c0=0x08; _tm3c1=0b11000001;							//TM3計時/計數模式 
	_tm3al=200%256; _tm3ah=200>>8;							//設定比對吻合週期=100us
	_t3ae=1; _mf2e=1; _emi=1;
	LCMInit();
	LCMWrite(0,0x80); i=0;									//Select Row 1
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);				//顯示STR1[]字串
	LCMWrite(0,0xC0);i=0;									//Select Row 2
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);				//顯示STR2[]字串
	while(1)
	{	state=IRDecoder(&adrs,&cmd);						//讀取IR信號
		if(state==2 && adrs==CID)
		{	_t0on=1; LED(cmd); 
			LCMWrite(0,0x89); Display(&adrs);				//Select Row 1
			LCMWrite(0,0xC9); Display(&cmd);				//Select Row 2
			Delayms(20); 									//輸出2KHz方波
		}
		else if(state==1 && adrs==CID)
		{	_t0on=1; LED(cmd);								//輸出2KHz方波
			LCMWrite(0,0x90); LCMWrite(1,'R');
			 Delayms(15);									
		}	
		LCMWrite(0,0x90); LCMWrite(1,' ');
		_t0on=0;
	}
}
void LED(u16 cmd)
{	switch(cmd)
	{	case LED0:
			if(Bcnt[0]<Period) Bcnt[0]+=5;
			break;
		case LED1:
			if(Bcnt[1]<Period) Bcnt[1]+=5;
			break;
		case LED2:
			if(Bcnt[2]<Period) Bcnt[2]+=5;
			break;
		case LED3:
			if(Bcnt[3]<Period) Bcnt[3]+=5;
			break;			
		case LED0_:
			if(Bcnt[0]>=5) Bcnt[0]-=5;
			break;
		case LED1_:
			if(Bcnt[1]>=5) Bcnt[1]-=5;
			break;
		case LED2_:
			if(Bcnt[2]>=5) Bcnt[2]-=5;
			break;
		case LED3_:
			if(Bcnt[3]>=5) Bcnt[3]-=5;;
			break;					
	}
}
DEFINE_ISR(ISR_TM3,0x20)
{	static u8 cnt[4];								//試試若不加static結果如何?
	if(PCnt--==0)									//判斷PWM周期是否已結束
	{	PCnt=Period; 								//是，還原所有值
		cnt[0]=Bcnt[0]; cnt[1]=Bcnt[1];
		cnt[2]=Bcnt[2]; cnt[3]=Bcnt[3];
		pLED0=(Bcnt[0]==0)? 1 : 0;					//依Duty設定腳位初始狀態
		pLED1=(Bcnt[1]==0)? 1 : 0;					//依Duty設定腳位初始狀態
		pLED2=(Bcnt[2]==0)? 1 : 0;					//依Duty設定腳位初始狀態
		pLED3=(Bcnt[3]==0)? 1 : 0;					//依Duty設定腳位初始狀態
	}
	else
	{	if(cnt[0]!=0) cnt[0]-- ; else pLED0=1; 		//判斷Duty若是結束設定接腳為0
		if(cnt[1]!=0) cnt[1]-- ; else pLED1=1;
		if(cnt[2]!=0) cnt[2]-- ; else pLED2=1;
		if(cnt[3]!=0) cnt[3]-- ; else pLED3=1;
	}
	_t3af=0;				  						//清除T3AF旗標
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
	if(TCnt<16000) {_emi=1; return 0;}						//若Start<8ms，回傳0
	_tm2c1=0b01010000;										//輸入捕捉模式(負緣)
	_t2on=1; 
	while(!_t2af)											//等待SYNC信號結束
	{	if(_t2pf) {_t2on=0; return 0; }						//若超過最大計數限制，回傳0
	}
	_t2on=0; _t2af=0; _t2pf=0; 								//停止TM2, 清除T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//取得SYNC信號之時間長度
	if(TCnt<4000 || TCnt>9600) return 0;					//若SYNC<2ms 或 >4.8ms，回傳0
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
