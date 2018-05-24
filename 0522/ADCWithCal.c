// PROGRAM	: ADC12WithCal.c					2017.0601
// FUNCTION	: ADC VBG Calibration 				By Steven
#include <HT66F70A.h>
#include "MyType.h"
const u16 VBG=1250;								//Babgap Voltage 1.25V
const u16 VDD=5000;								//Babgap Voltage 5.00V
#define	 SCL		_ph0						//e-Display SCL -> PH0
#define	 SDA		_ph1						//e-Display SDA -> PH1
#define	 SCLC		_phc0						//PH7
#define	 SDAC		_phc1						//PH6
#define	 RES		_ph2						//e-Display RES -> PH2
#define	 RESC		_phc2
#define	 DeviceID	(0x2D<<1)					//e-Display I2C 裝置位址
enum { cmdASC=1,cmdRET,cmdDOT,cmdCLR,cmdPIC,	//e-Display命令定義			
	   eBUSY=0x55};
enum { White=0xFFFF,Black=0x0000,Red=0xF800, 	//e-Display顏色定義
	   Green=0x07E0,Blue=0x001F,Yellow=0xFFE0,
	   Magenta=0xF81F,Cyanh=0x7FFF}; 
#define pause()	GCC_DELAY(25)
void I2C_START(void);
void I2C_STOP(void);
void CheckACK(void);
void eDisplayReset(void);
u8 e_Read(void);
void e_Command(u8*);
void eDisplayRet(u8,u8,u8,u8,u16);
void eDisplayPic(u8,u8,u8,u8,const u16* );
void eDisplayASC(u8,u8,u8*,u16);
void VoltDisplay(u8 x,u8 y,u16 ADR,u16 color,_Bool fg);
void e_DataRAM(u8*,u8);
void WriteByte(u8);
u8 ReadByte(void);
void Delayms(u16);	
void main()
{	u16 ADR,ADRVBG,Volt;
	u8 i;
	_wdtc=0b10101111;							//關閉看門狗計時器
	eDisplayReset();							//Reset eDisplay
	eDisplayRet(0,128,0,128,Blue);				//繪製矩形區域	
	eDisplayASC(15,5,"ADC VBG Test", Black);
	_adcr1=0b01100110;							//VBGEN=1,fSYS/64,VREFS=0,ADRFS=1
	_pas2=0x03;									//設定PA4為AN4功能
	while(1)
	{	_adcr0=0x10;							//ADOFF=0,選擇VBG 
		_start=1; _start=0;						//啟動AD轉換 
		while(_eocb);		
		ADRVBG=((u16)_adrh<<8)+_adrl;			//VBG 會返回5V 或是 3.3V
		_adcr0=0x04;							//ADOFF=0,選擇AN4	
		for(i=0;i<200;i++)
		{	_start=1; _start=0;					//啟動AD轉換
			while(_eocb);						//Wait Conversion Complete
			ADR=((u16)_adrh<<8)+_adrl;			//AN4  會變動 0~1024				
			VoltDisplay(20,30,ADR,Blue,0);
			Volt=((u32)ADR*VDD)>>12;			//Volt=(Result*VDD)/4096; VDD=5000
			VoltDisplay(20,50,Volt,Red,1);		
			Volt=((u32)ADR*VBG)/ADRVBG;			//Volt=(VBG*ADR2)/ADR1; VBG=1250  / ADRVBG=_adrh<<8)+_adrl
			VoltDisplay(20,70,Volt,Blue,1);
		}
	}
}
void VoltDisplay(u8 x,u8 y,u16 ADR,u16 color, _Bool fg)
{	u8	temp[10], *ptr;
	ptr=temp;
	*ptr++=ADR/1000+'0'; ADR%=1000;
	if(fg)
	{	*ptr++='.';
		eDisplayASC(x+40,y," volt",color);		//顯示
	}
	*ptr++=ADR/100+'0'; ADR%=100;
	*ptr++=ADR/10+'0'; *ptr++=ADR%10+'0';
	*ptr=0;
	eDisplayASC(x,y,temp,color);				//顯示
}
void eDisplayReset(void)
{	RES=0; RESC=0;
	Delayms(10);
	RES=1;
	Delayms(3000);
}
void eDisplayClear(u8 x,u8 xSize,u8 y,u8 ySize)
{	u8 Buffer[8]={cmdCLR,0,4,0,0,0,0,0};			//裝載命令
	e_Command(Buffer);								//送出e-Display清除命令
	Buffer[0]=x; Buffer[1]=xSize;					//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;
	e_DataRAM(Buffer,4);							//送出x/y座標起點及長度
	I2C_STOP();										//送出I2C STOP信號 
}
void eDisplayASC(u8 x, u8 y,u8 *ptr, u16 color)
{	u8 i=6,Buffer[22];
	while(*ptr) {Buffer[i]=*ptr++;i++;};
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=i;		//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=y;						//裝載參數
	Buffer[2]=color>>8;	Buffer[3]=(u8)color;
	Buffer[4]=0xFF;	Buffer[5]=0xFF;
	e_DataRAM(Buffer,i);							//送出參數
	I2C_STOP();										//送出I2C STOP信號 
}
void eDisplayRet(u8 x, u8 xSize,u8 y, u8 ySize, u16 color)
{	u8 Buffer[8]={cmdRET,0,6,0,0,0,0,0};		//裝載命令
	e_Command(Buffer);							//送出命令
	Buffer[0]=x; Buffer[1]=xSize;				//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;
	Buffer[4]=color>>8;	Buffer[5]=(u8)color;	
	e_DataRAM(Buffer,6);						//送出參數
	I2C_STOP();									//送出I2C STOP信號 
}
void e_Command(u8* ptr)
{	u8 i;
	while(e_Read()==eBUSY); 						//檢查e-Display忙碌狀態	
	I2C_START();
	WriteByte(DeviceID|0); CheckACK();				//送出DeviceID_W並等待回應ACK
	for(i=0;i<8;i++)								//e-Display命令長度固定為8
	{	WriteByte(*ptr++); CheckACK();				//逐Byte送出命令並等待回應ACK
	}
}
void e_DataRAM(u8* ptr,u8 Length)
{	u8 i;
	for(i=0;i<Length;i++)
	{	WriteByte(*ptr++); CheckACK();				//逐Byte送出RAM資料並等待回應ACK
	}
}
u8 e_Read(void)
{	u8 retval;
	I2C_START();									//送出I2C START信號 
	WriteByte(DeviceID|1); CheckACK();				//送出DeviceID_R並等待回應ACK
	retval=ReadByte();								//讀取裝置回傳值
	SDA=1; SDAC=0; 									//送出NO_ACK信號
	SCL=1; pause(); SCL=0; 	
	I2C_STOP();										//送出I2C STOP信號
	return retval;
}
void I2C_START(void)
{	SCL=0; SDA=0;									//設定 SCL=0, SDA=0
	SCLC=0; SDAC=0; 					   			//SCL/SDA為輸出模式
	SCL=1; SDA=1; pause();							//SCL=1, SDA=1
	SDA=0;											//SDA=0 			     						
	SCL=0;								      		//SCL=0	
}
void I2C_STOP(void)
{	SCL=0; SDA=0;									//設定 SCL=0, SDA=0
	SDAC=0;								   			//SDA 為輸出模式
	SCL=1;								      		//SCL=1
	SDA=1;								    		//SDA=1
	SCL=0; 											//SCL=0	
}
void CheckACK(void)
{	SDAC=1;							     			//SDA 為輸入模式
	SCL=1; 							     			//設定 SCL=1,
	while(SDA);										//等待 ACK(Low)
	SCL=0;					   						//設定 SCL=0
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SCL=0; SDAC=0;									//SCL=0, SDA為輸出模式
	do								
	{	SDA=(I2CData & temp)?1:0; pause();			//設定 SDA 準位
		SCL=1; pause(); SCL=0;    					//產生 SCL Clock
		temp>>=1;									//下一位元
	} while (temp!=0);								//傳送8個位元
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				//設定 SDA 為輸入模式
	do
	{	SCL=1; pause();								//設定 SCL=1
		if(SDA) I2CData|=temp;						//接收位元值
		SCL=0;										//設定 SCL=0
		temp>>=1;									//下一位元
	} while (temp!=0);								//接收8個位元
	return I2CData;
}
void Delayms(u16 del)								//@fSYS=8MH,延遲del*ms				
{	u16 i;							
	for(i=0;i<del;i++) GCC_DELAY(2000);				//延遲del*2000指令週期			
}
