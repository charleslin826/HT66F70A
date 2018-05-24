// PROGRAM	: 5-11.c								2015.0911
// FUNCTION	: 20*2 LCM 4-Bit Control Mode 			By Steven
//            with Random Guessing Game
#include "HT66F70A.h"
#include "5-11.H"
#include "Mytype.H"
const u8 TAB_CGRAM[]=
		{0x00,0x04,0x04,0x15,0x15,0x04,0x0C,0x00,	//"小"
		 0x00,0x04,0x04,0x1F,0x04,0x0A,0x11,0x00};	//"大"
const u8 String1[]={"MISS!"};
const u8 String2[]={"BINGO!"};
u8 Digit[3];		 
void LCMInit(void);
u8 LCMWrite4(_Bool, u8);
void LCMPrint(const u8*);
void Hex2ASCII(u8);
void PAUSE(u8);
void main()
{	s8 i;
	u8 Click,Random,temp;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SW_GreatC=1; SW_LessC=1; SW_EnterC=1;			//Config Pin as I/P Mode
	SW_GreatPU=1; SW_LessPU=1; SW_EnterPU=1;		//Enable Pins' Pull-up
	_tm2rp=0;										//Set TM2RP=0
	_tm2c1=0b11000000;								//STM as Timer/Counter, TMRP Match Cleared
	_tm2c0=0b00011000;								//CLK[2:0]=001(fINT=fSYS), Start STM
	LCMInit();										//LCM Initialization
	LCMWrite4(0,0x40);								//Set CGRAM Start Address
	for(i=0;i<16;i++) LCMWrite4(1,TAB_CGRAM[i]);	//Write Data to CGRAM
	while(1)
	{	LCMWrite4(0,1);								//Clear LCM Display
		Random=(_tm2dh^_tm2dl);						//Generate Random 1
		Hex2ASCII(Random);							//Convert to ASCII
		LCMWrite4(0,0x82);
		for(i=2;i>=0;i--) LCMWrite4(1,Digit[i]);	//Display Random 1
		LCMWrite4(0,0x86); LCMWrite4(1,0);			//Display "小"	
		LCMWrite4(0,0xC6); LCMWrite4(1,1);			//Display "大"
		Click=0x87;		
		while(SW_Enter)
		{	if(!SW_Less) Click=0x87;
			if(!SW_Great) Click=0xC7;
			LCMWrite4(0,Click); PAUSE(5);
		}
		PAUSE(5); while(!SW_Enter);					//Wait SW_Enter Released
		temp=(_tm2dh^_tm2dl);						//Generate Random 2
		Hex2ASCII(temp);							//Convert to ASCII
		LCMWrite4(0,0xC2);
		for(i=2;i>=0;i--) LCMWrite4(1,Digit[i]);	//Display Random 1
		
		if((temp<Random) && !(Click&0b01000000))	//temp<Random & Guess Less ?
		{	LCMWrite4(0,0xC9);						//Yes.
			LCMPrint(String2);						//Display BINGO!
		}
		else if((temp>Random) && (Click&0b01000000))//temp>Random & Guess Great ?
			{	LCMWrite4(0,0xC9);					//Yes.
				LCMPrint(String2);					//Display BINGO!
		}
		else										//No.
		{	LCMWrite4(0,0x89);
			LCMPrint(String1);						//Dieplay MISS!
		}
		PAUSE(250);									//Delay 2.5 Sec
	}
}
void Hex2ASCII(u8 i)								//Conert Byte Data to
{	Digit[2]=i/100+0x30; i%=100;					//3-Digit ASCII 
	Digit[1]=i/10+0x30;
	Digit[0]=i%10+0x30;
}
void LCMPrint(const u8 *ptr)
{	while(*ptr!=0) LCMWrite4(1,*ptr++);
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					//Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				//Config EN/RW/RS O/P Mode
	GCC_DELAY(80000);								//LCM Power-On Time
	LCMWrite4(0,0x28);								//COMD:8-Bit, 2-Line, 5*7
	LCMWrite4(0,0x0F);								//COMD:Display/Cursor Blinking On
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
	for (j=0;j<i;j++)  GCC_DELAY(20000); 			//Delay i*10mS 
}