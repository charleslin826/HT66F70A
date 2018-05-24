// PROGRAM	: combination lock.c							   	2017.0701
// FUNCTION	: Combination Lock with Build in EEPROM				By Steven
#include "HT66F70A.h"
#include "2-9.h"
const u8 Str1[]={"Input Code:"};
const u8 Str2[]={"Save  Code:"};
const u8 Str3[]={"Good Job!"};
const u8 Str4[]={"Sorry!!"};
const u8 Str5[]={"Save OK!"};
void LCMInit(void);												//函式原型宣告
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
u8 ScanKey(void);
void Write4Byte(u8*);
void Read4Byte(u8*);
u8 Get3Keys(u8*);
void Verify(u8*,u8*);
void main()
{	u8 i,Flag=0,Key=0x0B,*ptr,SaveCode[4],InputCode[4];
	_wdtc=0b10101111;										//關閉看們狗計時器
	_tm0c0=0; _tm0c1=0b00110001; 							//TM0比對吻合輸出模式
	_pcs2=0x20;
	LCMInit();													//LCM初始化
	do 
	{	switch (Key)
		{	case 0x0A:											//壓下A鍵時
			{	LCMWrite(0,1);									//清除LCM、游標歸位
				i=0; while(Str2[i]!=0) LCMWrite(1,Str2[i++]);	//顯示"Save Code:"
				Flag=0; break;
			}
			case 0x0B:
			{	LCMWrite(0,1);									//清除LCM、游標歸位
				i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]); 	//顯示"Input Code:"
				Flag=1; break;
			}
			default:
			{	if(Key<10) 
				{	LCMWrite(1,Key+'0');						//顯示鍵值
					ptr=(Flag) ? InputCode : SaveCode;			//設定ptr指向陣列
					*ptr=Key; ptr++;							//儲存鍵值
					if(Get3Keys(ptr))							//按下清除鍵?
					{	LCMWrite(0,0x8B); 						//游標移至列1行12
						i=0; while(i++<4) LCMWrite(1,' ');		//清除4個位置
						LCMWrite(0,0x8B); 						//游標移至列1行12
						break;												
					}
					if(Flag) 									//Flag=1,密碼輸入模式
					{	Read4Byte(SaveCode);					//由EEPROM讀回密碼
						Verify(InputCode,SaveCode);				//進行密碼比對
					}
					else										//Flag=0,密碼設定模式
					{	Write4Byte(SaveCode);					//密碼存放至EEPROM
						LCMWrite(0,0xC0); i=0;					//游標移至列2行0
						while(Str5[i]!=0) LCMWrite(1,Str5[i++]);//顯示"Save OK!"
						_tm0al=(u8)500; _tm0ah=500>>8;			//設定比對吻合週期=500us
						_t0on=1; Delayms(200); _t0on=0;			//頻率=1/(500us*2)=1KHz,0.2秒
					}
					Delayms(2000);								//正確/錯誤訊息顯示2秒
					Flag=1; LCMWrite(0,1); i=0;					//清除LCM、游標歸位
					while(Str1[i]!=0) LCMWrite(1,Str1[i++]);	//顯示"Input Code:"
				}
			}
		}
		do Key=ScanKey(); while (Key==16);						//等待按壓按鍵
		Delayms(15); while(ScanKey()!=16); Delayms(15);			//等待按鍵釋放
	} while(1);
}
u8 Get3Keys(u8 *ptr)
{	u8 key, i=0;
	while(1)
	{	do key=ScanKey(); while (key==16);			   			//等待按壓按鍵
		if(key<10 && i<3)										//輸入"0" ~ "9"
		{	*ptr=key; ptr++; i++;					   			//儲存數值
			LCMWrite(1,key+'0');								//顯示資料
		}
		Delayms(15); while(ScanKey()!=16); Delayms(15);			//等待按鍵釋放
		if(key==0x0F && i==3) return 0;							//壓 F 鍵，結束輸入
		if(key==0x0E) return 1;									//壓 E 鍵，重新輸入
	}
}
void Verify(u8 *ptr1,u8 *ptr2)
{	u8 i,flag=0;
	for(i=0;i<4;i++)											//進行密碼比對
	{	if(*ptr1++ != *ptr2++) flag++;
	}
	LCMWrite(0,0xC0);  											//設定LCD列二、行0
	if(flag)													//flag!=0,比對錯誤
	{	i=0; while(Str4[i]!=0) LCMWrite(1,Str4[i++]);  			//顯示"Sorry!!"
		_tm0al=(u8)1000; _tm0ah=1000>>8;						//設定比對吻合週期=1ms
		_t0on=1; Delayms(1000); _t0on=0; 						//頻率=1/(1ms*2)=500Hz
	}
	else														//flag=0,比對正確
	{	i=0; while(Str3[i]!=0) LCMWrite(1,Str3[i++]);  			//顯示"Good Job"
		for(i=0;i<2;i++)													
		{	_tm0al=(u8)250; _tm0ah=250>>0;						//設定比對吻合週期=250us
			_t0on=1; Delayms(200); _t0on=0; Delayms(100);		//頻率=1/(250us*2)=2KHz
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
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					     		//設定EN/RW/RS Pin為0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      		//設定EN/RW/RS 為輸出模式
	Delayms(40);									         	//LCM Power-On Time
	LCMWrite(0,0x38);								        	//8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);								       		//Display/Cursor Blinking On
	LCMWrite(0,0x06);								        	//Increment, Not Shift
	LCMWrite(0,0x01);								  			//Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;									//規劃Port為輸入模式
	LCM_RS=0; LCM_RW=1;											//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();									//EN=1
		BusyAC=LCM_DataPort;									//Loop Until BF=0
		LCM_EN=0;												//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;											//規劃Port為輸出模式
	LCM_RW=0;													//RW=0 (Write)
	LCM_RS=DCFlag;												//Set RS State By DCFlag
	LCM_DataPort=CD;											//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;								//EN=1
	return BusyAC;	
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
void Delayms(u16 del)
{	u16 i;														//@fSYS=4MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(1000);
}