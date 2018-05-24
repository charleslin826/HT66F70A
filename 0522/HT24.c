// PROGRAM	: HT24.c							           		2014.1226
// FUNCTION	: Combination Lock with HT24LC32					By Steven
#include <HT66F70A.h>
#include "HT24.h"
void main()
{	u8 i,Flag,Key=0x0B,*ptr,SaveCode[4],InputCode[4];
	_wdtc=0b10101111;												//關閉看門狗計時器
	_tm0c0=0x00; _tm0c1=0x31; 										//比對吻合輸出
	_pcs2=0x20;														//PC5為TP0功能						
	LCMInit();														//LCM初始化
	do 
	{	switch (Key)
		{	case 0x0A:												//壓下A鍵時
			{	LCMWrite(0,1);										//清除LCM、游標歸位
				i=0; while(Str2[i]!=0) LCMWrite(1,Str2[i++]);		//顯示"Save Code:"
				Flag=0; break;
			}
			case 0x0B:
			{	LCMWrite(0,1);										//清除LCM、游標歸位
				i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]);  		//顯示"Input Code:"
				Flag=1; break;
			}
			default:
			{	if(Key<10) 
				{	LCMWrite(1,Key+'0');							//顯示鍵值
					ptr=(Flag) ? InputCode : SaveCode;				//設定ptr指向陣列
					*ptr=Key; ptr++;								//儲存鍵值
					if(Get3Keys(ptr))								//按下清除鍵?
					{	LCMWrite(0,0x8B); 							//游標移至列1行12
						i=0; while(i++<4) LCMWrite(1,' ');			//清除4個位置
						LCMWrite(0,0x8B); 							//游標移至列1行12
						break;												
					}
					if(Flag) 										//Flag=1,密碼輸入模式
					{	I2C_SeqRandomRead(0,SaveCode,4);			//由EEPROM讀回密碼
						Verify(InputCode,SaveCode);					//進行密碼比對
					}
					else											//Flag=0,密碼設定模式
					{	I2C_PageWrite(0,SaveCode,4);				//密碼存放至EEPROM
						LCMWrite(0,0xC0); i=0;						//游標移至列2行0
						while(Str5[i]!=0) LCMWrite(1,Str5[i++]);	//顯示"Save OK!"
						_tm0al=(u8)1000; _tm0ah=1000>>8;			//設定比對吻合週期=500us
						_t0on=1; Delayms(200); _t0on=0;				//頻率=1/(500us*2)=1KHz,0.2秒
					}
					Delayms(2000);									//正確/錯誤訊息顯示2秒
					Flag=1; LCMWrite(0,1);							//清除LCM、游標歸位
					i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]);	//顯示"Input Code:"
				}
			}
		}
		do Key=ScanKey(); while (Key==16);							//等待按壓按鍵
		Delayms(15); while(ScanKey()!=16); Delayms(15);				//等待按鍵釋放
	} while(1);
}
u8 Get3Keys(u8 *ptr)
{	u8 key, i=0;
	while(1)
	{	do key=ScanKey(); while (key==16);			   				//等待按壓按鍵
		if(key<10 && i<3)											//輸入"0" ~ "9"
		{	*ptr=key; ptr++; i++;					   				//儲存數值
			LCMWrite(1,key+'0');									//顯示資料
		}
		Delayms(15); while(ScanKey()!=16); Delayms(15);				//等待按鍵釋放
		if(key==0x0F && i==3) return 0;								//壓 F 鍵，結束輸入
		if(key==0x0E) return 1;										//壓 E 鍵，重新輸入
	}
}
void Verify(u8 *ptr1,u8 *ptr2)
{	u8 i,flag=0;
	for(i=0;i<4;i++)												//進行密碼比對
	{	if(*ptr1++ != *ptr2++) flag++;
	}
	LCMWrite(0,0xC0);  												//設定LCD列二、行0
	if(flag)														//flag!=0,比對錯誤
	{	i=0; while(Str4[i]!=0) LCMWrite(1,Str4[i++]);  				//顯示"Sorry!!"
		_tm0al=(u8)2000%256; _tm0ah=2000>>8;						//設定比對吻合週期=1ms
		_t0on=1; Delayms(1000); _t0on=0; 							//頻率=1/(1ms*2)=500Hz
	}
	else															//flag=0,比對正確
	{	i=0; while(Str3[i]!=0) LCMWrite(1,Str3[i++]);  				//顯示"Good Job"
		for(i=0;i<2;i++)													
		{	_tm0al=(u8)500; _tm0ah=500>>8;							//設定比對吻合週期=250us
			_t0on=1; Delayms(200); _t0on=0; Delayms(100);			//頻率=1/(250us*2)=2KHz
		}	
	}
}
void I2C_START(void)
{	SCL=0; SDA=1;													//設定 SCL=0, SDA=1
	SCLC=0; SDAC=0; 					   							//SCL/SDA為輸出模式
	SCL=1; 															//SCL=1, SDA=1
	GCC_DELAY(1);
	SDA=0;															//SDA=0 			     						
	GCC_DELAY(1);
	SCL=0;								      						//SCL=0	
}
void I2C_STOP(void)
{	SDA=0; SDAC=0;							   						// SDA=0,SDA 為輸出模式
	SCL=1;															//SCL=1
	GCC_DELAY(1);
	SDA=1;								    						//SDA=1
	GCC_DELAY(1);
	SCL=0; 															//SCL=0	
}
void CheckACK(void)
{	SDAC=1; 										      			//SDA 為輸入模式
	SCL=1; 	GCC_DELAY(1);							      			//設定 SCL=1, 
	while(SDA);										    			//等待 ACK(Low)
	SCL=0;					   										//設定 SCL=0
}
void I2C_DeviceSelect(_Bool FG_RW)
{	WriteByte(DeviceID|FG_RW);										//結合DeviceID與RW位元
	CheckACK();		
} 
void I2C_SetAddress(u16 I2CAddress)
{	WriteByte(I2CAddress>>8);										//1'st Word Address
	CheckACK();
	WriteByte((u8)I2CAddress);										//2'nd Word Address
	CheckACK();
}
void I2C_SeqRandomRead(u16 Address,u8 *ptr,u8 Count)
{	u8 i;
	I2C_START();
	I2C_DeviceSelect(0);				      						//Device ID/A2~A0/Write
	I2C_SetAddress(Address);					      				//設定 a11~a0
	I2C_START();
	I2C_DeviceSelect(1);				      						//Device ID/A2~A0/Read
	for(i=0;i<Count;i++)
	{	*ptr++=ReadByte();
		if(i==(Count-1)) SDA=1; else SDA=0;							//若為最末位元組NO_ACK,否則ACK
		SDAC=0;
		SCL=1;  SCL=0; 		
	}
	I2C_STOP();										         		//STOP 
}
void I2C_PageWrite(u16 Address,u8 *ptr,u8 Count)
{	u8 i;
	I2C_START();
	I2C_DeviceSelect(0);				      						//Device ID/A2~A0/Write
	I2C_SetAddress(Address);					      				//設定 a11~a0
	for(i=0;i<Count;i++)
	{	WriteByte(*ptr++);							     			//送出一個Byte
		CheckACK();	
	}
	I2C_STOP();										         		//STOP 
	Delayms(5);									         			//Delay 5ms for tW	
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SCL=0; SDAC=0;									         		//SCL=0, SDA為輸出模式
	do
	{	SDA=(I2CData & temp)?1:0; //Delay5us();				   		//設定 SDA 準位並延遲 5us
		SCL=1; GCC_DELAY(1); 
		SCL=0; GCC_DELAY(1);	   									//產生 SCL Clock
		temp>>=1;									         		//下一位元
	} while (temp!=0);
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				         		//設定 SDA 為輸入模式
	do
	{	SCL=1; GCC_DELAY(1);							      		//設定 SCL=1, Delay 5us
		if(SDA==1) I2CData|=temp;						      		//接收位元值 **
		SCL=0; GCC_DELAY(1);							      		//設定  SCL=0, Delay 5us
		temp>>=1;										         	//下一位元
	} while (temp!=0);
	return I2CData;
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					      			//設定EN/RW/RS Pin為0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      			//設定EN/RW/RS 為輸出模式
	Delayms(40);									         		//LCM Power-On Time
	LCMWrite(0,0x38);								         		//8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);								         		//Display/Cursor Blinking On
	LCMWrite(0,0x06);								         		//Increment, Not Shift
	LCMWrite(0,0x01);								         		//Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;										//規劃Port為輸入模式
	LCM_RS=0; LCM_RW=1;												//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();										//EN=1
		BusyAC=LCM_DataPort;										//Loop Until BF=0
		LCM_EN=0;													//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;												//規劃Port為輸出模式
	LCM_RW=0;														//RW=0 (Write)
	LCM_RS=DCFlag;													//Set RS State By DCFlag
	LCM_DataPort=CD;												//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;								    //EN=1
	return BusyAC;	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;					   				//輸出/輸入規劃並致能提升電阻
	KeyPort=0b11111110;								      			//初始掃描碼
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				      			//檢查第1行
		key++;
		if(!(KeyPort & 1<<6)) break;				      			//檢查第2行
		key++;
		if(!(KeyPort & 1<<5)) break;				      			//檢查第3行
		key++;
		if(!(KeyPort & 1<<4)) break;				      			//檢查第4行
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;			   				//產生下一列掃描碼
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;															//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}