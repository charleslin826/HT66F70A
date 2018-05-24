// PROGRAM	: 2-9.c											2017.0701
// FUNCTION	: HT66F50 EEPROM DM Read/Write Demo Program		By Steven
#include "HT66F70A.h"
#include "2-9.H" 
const u8 Str1[]={"A.Input B.RD EEP"};
void LCMInit(void);											//函式原型宣告
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
u8 ScanKey(void);
void Write4Byte(u8*);
void Read4Byte(u8*);
void main()
{	u8 i,Key,Code[4];
	_wdtc=0b10101111;										//關閉看們狗計時器
	_tm0c0=0; _tm0c1=0b00110001; 							//TM0比對吻合輸出模式
	_pcs2=0x20;												//PC5->TP0
	LCMInit();												//LCM初始化
	while(1) 
	{	do Key=ScanKey(); while (Key==16);					//等待按壓按鍵
		Delayms(10); 
		while(ScanKey()!=16); Delayms(10);					//等待按鍵釋放	
		switch (Key)
		{	case 0x0A:										//壓下A鍵時
				LCMWrite(0,0xC2);							//列2行2
				for(i=0;i<4;i++) LCMWrite(1,' ');			//清除已顯示鍵值
				LCMWrite(0,0xC2);							//列2行2
				for(i=0;i<4;i++)
				{	do Key=ScanKey(); while (Key>9);		//等待按壓0~9按鍵
					Code[i]=Key; LCMWrite(1,Key+'0');		//顯示鍵值
					Delayms(300);
				}
				Write4Byte(Code);							//密碼存放至EEPROM
				_tm0al=(u8)250; _tm0ah=250>>8;				//設定比對吻合週期=250us
				_t0on=1; Delayms(200); _t0on=0; 			//頻率=1/(250us*2)=2KHz,0.2秒
				Delayms(100);								//間隔0.1秒
				_t0on=1; Delayms(100); _t0on=0;
				break;
			case 0x0B:
				Read4Byte(Code);							//由EEPROM讀回儲存值
				LCMWrite(0,0xCA);							//列2行10
				for(i=0;i<4;i++) LCMWrite(1,Code[i]+'0');	//顯示儲存值	
				_tm0al=(u8)500; _tm0ah=500>>8;				//設定比對吻合週期=500us
				_t0on=1; Delayms(1000); _t0on=0; 			//頻率=1/(500us*2)=1KHz,1秒	
				break;			
		}
	}
}
void Read4Byte(u8 *ptr)
{	u8 i;
	for(i=0;i<4;i++)
	{	_eea=i;												//設定EEPROM位址
		_mp1h=0x01; _mp1l=0x40;								//MP1=EEC (Bank1)
		_iar1=RDEN; _iar1|=RD;								//設定RDEN=1,RD=1
		while(_iar1&RD);									//等待讀取完成
		_iar1=0;											//禁能EEPROM讀寫
		*ptr++=_eed;										//由EEPROM讀回資料,指標遞增
	}		
}
void Write4Byte(u8 *ptr)
{	u8 i;
	for(i=0;i<4;i++)
	{	_eea=i;												//設定EEPROM位址
		_eed=*ptr++;										//設定寫入資料,指標遞增
		_mp1h=0x01; _mp1l=0x40;								//MP1=EEC (Bank1)
		_iar1=WREN; _iar1|=WR;								//設定WREN=1,WR=1
		while(_iar1&WR);									//等待寫入完成
		_iar1=0;											//禁能EEPROM讀寫
	}
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;					   			//輸出/輸入規劃並致能提升電阻
	KeyPort=0b11111110;								      		//初始掃描碼
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				      		//檢查第1行
		key++;
		if(!(KeyPort & 1<<6)) break;				      		//檢查第2行
		key++;
		if(!(KeyPort & 1<<5)) break;				      		//檢查第3行
		key++;
		if(!(KeyPort & 1<<4)) break;				      		//檢查第4行
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;			   			//產生下一列掃描碼
	}
	return key;	
}
void LCMInit(void)
{	u8 i;
	LCM_EN=0; LCM_RW=0; LCM_RS=0;	        				//設定EN/RW/RS腳位為低電位
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	  					//設定EN/RW/RS腳位為輸出模式
	GCC_DELAY(80000);										//LCM Power-On Time
	LCMWrite(0,0x38);										//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);										//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);										//COMD:Increment, Not Shift
	LCMWrite(0,0x01); i=0;									//COMD:Clear LCM Display
	while(Str1[i]!=0) LCMWrite(1,Str1[i++]);				//顯示Str1字串
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
	LCM_EN=1; GCC_NOP(); LCM_EN=0;			  			  	//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=4MH,延遲del*100us
	for(i=0;i<del;i++) GCC_DELAY(2000);
		
}