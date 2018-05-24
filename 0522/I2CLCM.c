// PROGRAM	: I2CLCM.c						2017.1031
// FUNCTION	: Serial LCM(PCF8574) Control 	By Steven
#include <HT66F70A.h>
#include "MyType.H"
#include "SerialLCM.h"
void LCMInit(void);
void main()
  {	volatile u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	LCMInit();				       				//LCM初始設定
	while(1)
	{	LCMWrite(0,0x01); Delayms(2);			//清除LCM顯示、游標歸位						
		for(i=0;i<16;i++)
		{	LCMWrite(1,'a'); Delayms(100);		//顯示"1"並延遲0.2秒
		}
		LCMWrite(0,0x04);						//進入模式:Decrease, Not Shift 
		LCMWrite(0,0xCF);						//Set Line 2, Position 0 
		do
		{	Delayms(300);						//延遲0.1秒
		} while(LCMWrite(1,'2')>(0x40)); 		//顯示"2"並判斷是否到達列2行0
		Delayms(1000);							//延遲1秒
	}
}
void LCMInit(void)
{	Delayms(40);								//LCM Power-On Time
	I2C_START(); I2C_STOP();
	LCMWrite(0,0x28); 							//功能設定:4-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F); 							//顯示控制:Display/Cursor Blinking On
	LCMWrite(0,0x06); 							//進入模式:Increse, Not Shift
	LCMWrite(0,0x01); Delayms(2);				//清除LCM
}
