// PROGRAM	: 5-10.c								2017.0911
// FUNCTION	: 20*2 LCM 4-Bit Control Mode  			By Steven
#include "HT66F70A.h"
#include "5-10.H"
#include "Mytype.H"
const u8 TAB_CGRAM[]= {
		0x00,0x0C,0x1E,0x0C,0x06,0x07,0x07,0x0b,	//Man for Fig.5-7-3(a)
		0x00,0x00,0x00,0x00,0x00,0x18,0x04,0x02,
		0x11,0x01,0x01,0x01,0x02,0x1A,0x0C,0x00,
		0x10,0x10,0x08,0x06,0x03,0x01,0x01,0x00,
		0x00,0x0C,0x1E,0x0C,0x06,0x07,0x06,0x03,	//Man for Fig.5-7-3(b)
		0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x08,
		0x05,0x05,0x03,0x04,0x04,0x03,0x0F,0x00,
		0x08,0x10,0x10,0x10,0x08,0x06,0x0C,0x00};
void LCMInit(void);
u8 LCMWrite4(_Bool, u8);
void PAUSE(u8);
void main()
{	s8 i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	LCMInit();										//LCM Initialization
	LCMWrite4(0,0x40);								//Set CGRAM Start Address
	for(i=0;i<64;i++) LCMWrite4(1,TAB_CGRAM[i]);	//Write Data to CGRAM
	while(1)
	{	for(i=0;i<=18;i++)
		{	LCMWrite4(0,0x80+i);					//Set AC (Line1)
			LCMWrite4(1,0); LCMWrite4(1,1);			//Display Data of CGRAM 0,1						
			LCMWrite4(0,0xC0+i);					//Set AC (Line2)
			LCMWrite4(1,2); LCMWrite4(1,3);			//Display Data of CGRAM 0,1	
			PAUSE(20);								//Delay 200ms					
			LCMWrite4(0,0x80+i);					//Set AC (Line1)
			LCMWrite4(1,4); LCMWrite4(1,5);			//Display Data of CGRAM 0,1						
			LCMWrite4(0,0xC0+i);					//Set AC (Line2)
			LCMWrite4(1,6); LCMWrite4(1,7);			//Display Data of CGRAM 0,1	
			PAUSE(20);								//Delay 200ms
			LCMWrite4(0,0x80+i);					//Set AC (Line1)
			LCMWrite4(1,0x20); LCMWrite4(1,0x20);	//Clear line 1 Pattern
			LCMWrite4(0,0xC0+i);					//Set AC (Line2)
			LCMWrite4(1,0x20); LCMWrite4(1,0x20);	//Clear line 2 Pattern				
		}
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				//Config EN/RW/RS O/P Mode
	GCC_DELAY(80000);								//LCM Power-On Time
	LCMWrite4(0,0x28);								//COMD:8-Bit, 2-Line, 5*7
	LCMWrite4(0,0x0C);								//COMD:Display/Cursor Blinking Off
	LCMWrite4(0,0x06);								//COMD:Increment, Not Shift
	LCMWrite4(0,0x01);								//COMD:Clear LCM Display
}
u8 LCMWrite4(_Bool DCFlag, u8 CD)
{	u8 BusyAC;
	LCM_DataPortC|=0b11110000;						//Config LCM_DataPort[7:4] as I/P
	LCM_RS=0; LCM_RW=1;								//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();						//EN=1
		BusyAC=LCM_DataPort;						//Read Data[7:4] From LCM
		LCM_EN=0;									//EN=0
		BusyAC &= 0b11110000;						//Mask Low Nibble
		LCM_EN=1; GCC_NOP();						//EN=1
		BusyAC |= (LCM_DataPort>>4);				//Read Data[3:0] from LCM
		LCM_EN=0;									//EN=0
	} while (BusyAC&0b10000000);					//Loop until BF=0
	LCM_DataPortC &= 0b00001111;					//Config LCM_DataPort[7:4] as O/P Mode
	LCM_RW=0;										//RW=0 (Write)
	LCM_RS=DCFlag;									//Set RS State By DCFlag
	LCM_DataPort &= 0b00001111;						//Mask Port State[7:4]
	LCM_DataPort |= (CD&0b11110000);				//Write CD[7:4] to LCM		
	LCM_EN=1; GCC_NOP(); LCM_EN=0;					//EN=1
	LCM_DataPort &= 0b00001111;						//Mask Port State[7:4]
	LCM_DataPort |= (CD<<4);						//Write CD[3:0] to LCM		
	LCM_EN=1; GCC_NOP(); LCM_EN=0;					//EN=1
	return BusyAC;	
}
void PAUSE(u8 i)						
{	u8 j;
	for (j=0;j<i;j++)  GCC_DELAY(20000);			//Delay i*10mS 
}