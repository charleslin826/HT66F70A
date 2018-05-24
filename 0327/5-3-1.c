// PROGRAM	: 5-3-1.c								2015.0911
// FUNCTION	: 8*8 Dot Matrix LED for Work Man	   	By Steven
#include "HT66F70A.h"
#include "5-3-1.H"
#include "MyType.H"
const u8 TabStop[8] ={
    	0x18,0x18,0x3C,0x5A,0x5A,0x24,0x24,0x66};
const u8 TabWalk1[8]={
      0x3C,0x1C,0x08,0x0C,0x1A,0x28,0x14,0x14};
const u8 TabWalk2[8]={
      0x78,0x38,0x10,0x3E,0x4B,0xC8,0x16,0x63};
const u8 TabWalk3[8]={
      0x78,0x38,0x10,0x18,0x18,0x18,0x18,0x38};		  	 
const u8 TabWalk4[8]={
     	0x78,0x38,0x10,0x18,0x2C,0x28,0x14,0x14};
const u8 TabWalk5[8]={
		0x3C,0x1C,0x08,0x3C,0x6A,0x4B,0x34,0x22};
void PAUSE(u8);
u8 ScanCode,Buffer[8];
u8 *volatile ptr;
void main()
{	u8 i,j,TabIndex=1;
	_wdtc=0b10101111;									//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;							//Config ScanPort as O/P
	DotPort=0; DotPortC=0;								//Config DotPort as O/P
	_psc0=0x01; _tbc0=0x04;								//fTB=fSYS/4, 週期=4096*fTB
	_tb0e=1; _emi=1; 									//Enable TB0 Interrupt	
	ptr=Buffer; ScanCode=0b00000001;					//Initial Pointer and ScanCode
	while(1)
	{	for(i=0;i<8;i++) Buffer[i]=TabStop[i];    		//Load First Pattern
		_tb0on=1; PAUSE(250); PAUSE(250);				//Start TBO & Delay 5 Sec 分兩次因為pause 是 u8 必須小於256
		_tb0on=0; DotPort=0x00;							//Stop TB0
		for(j=0;j<20;j++)
		{	TabIndex=1;
			while(TabIndex++ < 6)
			{	switch(TabIndex)
				{	case 1:
						for(i=0;i<8;i++)				//Load Working Pattern 1
							Buffer[i]=TabWalk1[i];
						break;
					case 2:
						for(i=0;i<8;i++)				//Load Working Pattern 2
							Buffer[i]=TabWalk2[i];
						break;
					case 3:
						for(i=0;i<8;i++)				//Load Working Pattern 3 
							Buffer[i]=TabWalk3[i];
						break;
					case 4:
						for(i=0;i<8;i++)				//Load Working Pattern 4 
							Buffer[i]=TabWalk4[i];
						break;
					case 5:
						for(i=0;i<8;i++)				//Load Working Pattern 5 
							Buffer[i]=TabWalk5[i];
						break;
				}		
				ptr=Buffer; ScanCode=0b00000001;		//Initial Pointer and ScanCode
				if(j<10) i=18; else	i=8;			//切換速度 i=8 = 80ms 
				_tb0on=1; PAUSE(i);						//Start TBO & Delay i*10ms
				while(ptr!=Buffer);						//完整掃描完才換下個frame
				_tb0on=0; DotPort=0x00;					//Stop TB0 & Turn-off LEDs
			}			
		}
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0x00;										//Turn-off Before New data
	ScanPort=ScanCode; DotPort=*ptr++;					//Update Scan and Data
	ScanCode<<=1;										//Up data Scan Code
	if(ScanCode==0)										//If all Lines been Scanned
	{	ScanCode=0b00000001;							//Reload Scan Code &
		ptr=Buffer;										//Reset Pointer
	}	
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000); 					//Dealy i*10ms
}