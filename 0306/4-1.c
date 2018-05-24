// PROGRAM	: 4-1.c									2015.0908
// FUNCTION	: LED Scanning Demo Program (for)		By Steven
#include "HT66F70A.h" 			
#define  LED_Port    _pc								
#define  LED_PortC   _pcc				//在C語言中 特殊功能暫存器要小寫且前面要加底線			
void main()
{	unsigned char i,j;	
	_wdtc=0b10101111;								//關閉看們狗計時器
	LED_PortC=0x0;									//Config LED_Port as Output //方向控制
	LED_Port=~0x01;	// ~代表反向 01(亮七顆) => FE (亮一顆) //設0才會有電位差 //Set Initial Data 
	while(1)
	{	for(j=0;j<7;j++)	
		{	for(i=0;i<100;i++) GCC_DELAY(2000);		//系統時脈是XCL 石英震盪器(8MHz) 倒數乘上4 = 1/8*4=0.5 us * 2000 = 1 ms *100 = 1 s
				LED_Port=(LED_Port<<1)|1;			//Shift Left 11111110 變成 11111100 從亮第一顆變亮兩顆
		}											//但我們只想要亮單一一顆 所以去和1(0x80)做or運算
		for(j=0;j<7;j++)	
		{	for(i=0;i<200;i++) GCC_DELAY(2000);     //系統時脈是XCL 石英震盪器(8MHz) 倒數乘上4 = 1/8*4=0.5 us * 2000 = 1 ms *200 = 2 s
				LED_Port=(LED_Port>>1)|0x80;		//Shift Right  	往回移
		}											////但我們只想要亮單一一顆 所以去和1(0x80)做or運算
	}
}	