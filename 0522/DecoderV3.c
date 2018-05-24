// PROGRAM	: IR_testV3.c							      	2017.0701
// FUNCTION	: NEC IR Decoder Demo Program					By Steven
//          : PC5->Buzzer, PC3-> FM9038 O/P
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
void main()
{	u16 adrs, cmd; u8 state,i;
	_wdtc=0b10101111;										//關閉看門狗計時器
	_tm0c0=0; _tm0c1=0b00110001;							//TM0比對吻合輸出 
	_tm0al=500&0xFF; _tm0ah=500>>8;							//設定比對吻合週期=250us
	_pcs2=0x20;												//選擇TP0功能於PC6實現
	_tm2c0=0;									  			//TM2: STM fINT=fSYS/4  0.5s
	_ifs2=0b00000000;										//選擇TP2I功能於PC3實現
	LCMInit();
	LCMWrite(0,0x80); i=0;									//Select Row 1
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);				//顯示STR1[]字串
	LCMWrite(0,0xC0);i=0;									//Select Row 2
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);				//顯示STR2[]字串
	while(1)
	{	state=IRDecoder(&adrs,&cmd);						//讀取IR信號
		switch (state)
		{	case 2:
				LCMWrite(0,0x89); Display(&adrs);			//Select Row 1
				LCMWrite(0,0xC9); Display(&cmd);			//Select Row 2
				break;
			case 1:
				LCMWrite(0,0x8F); LCMWrite(1,'R');
				break;	
			case 0: 
				LCMWrite(0,0xCF); LCMWrite(1,'.');
				break;
		}	
		_t0on=1; Delayms(25); _t0on=0; Delayms(15);			//輸出2KHz方波並維持0.25秒
		_t0on=1; Delayms(25); _t0on=0; Delayms(50);			//輸出2KHz方波並維持0.25秒
		LCMWrite(0,0x8F); LCMWrite(1,' ');
		LCMWrite(0,0xCF); LCMWrite(1,' ');
	}
}
void Display(u16* ptr)
{	u16	x=0xF000;
	char tmp,i=3;
	do
	{	tmp=(*ptr & x)>>(4*i--);
		tmp=(tmp>9)? tmp+'7': tmp+'0';
		LCMWrite(1,tmp);
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
	{	if(_t2pf) {_t2on=0;	return 0; }						//若超過最大計數限制，回傳0
	}
	_t2on=0; _t2af=0; _t2pf=0;  							//停止TM2, 清除T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//取得START信號之時間長度
	if(TCnt<16000) return 0;								//若Start<8ms，回傳0 因為配合硬體要省成本 可能不會到9ms 裡面可能用RC震盪器 不穩定
	_tm2c1=0b01010000;										//輸入捕捉模式(負緣)
	_t2on=1; 
	while(!_t2af)											//等待SYNC信號結束
	{	if(_t2pf) {_t2on=0;	return 0; }						//若超過最大計數限制，回傳0
	}
	_t2on=0; _t2af=0; _t2pf=0; 								//停止TM2, 清除T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//取得SYNC信號之時間長度
	if(TCnt<4000 || TCnt>9600) return 0; 					//若SYNC<2ms 或 >4.8ms，回傳0
	if(TCnt<5200) return 1;									//若2ms<SYNC<2.6ms為重複碼，回傳1
	while(temp1!=0)											//接收資料位元
	{	_t2on=1;											//啟動計數
		while(!_t2af);										//等待位元時間結束;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;					//取得位元時間
		_t2on=0; _t2af=0;									//停止TM2, 清除T2AF
		if(TCnt>3000) temp|=temp1;							//若位元時間>1500us,則位元為1 
		temp1<<=1; 											//收取32個bit  低八高八位元是ADDRESS  下一個低八高八 是COMMAND
		
	}	 
	_t2on=0; 												//停止TM2 
	*ptradrs=(u16)temp;									//取得Custom Code
	*ptrcmd=(temp & 0xFFFF0000)>>16; 						//取得Command
	return 2;												//Command正確，回傳2
}

void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					      	//設定EN/RW/RS Pin為0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      	//設定EN/RW/RS 為輸出模式
	Delayms(40);									    	//LCM Power-On Time
	LCMWrite(0,0x38);								        //8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);								        //Display/Cursor Blinking On
	LCMWrite(0,0x06);								        //Increment, Not Shift
	LCMWrite(0,0x01);								        //Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;								//規劃Port為輸入模式
	LCM_RS=0; LCM_RW=1;										//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();								//EN=1
		BusyAC=LCM_DataPort;								//Loop Until BF=0
		LCM_EN=0;											//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;										//規劃Port為輸出模式
	LCM_RW=0;												//RW=0 (Write)
	LCM_RS=DCFlag;											//Set RS State By DCFlag
	LCM_DataPort=CD;										//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;							//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}