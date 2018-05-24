// PROGRAM	: 5-3.c									2015.0911
// FUNCTION	: 8*8 Dot Matrix LED Static Control 	By Steven
#include "HT66F70A.h"
#include "5-3.H"
#include "MyType.H"
const u8 TAB1[8] ={
     0x18,0x18,0x3C,0x7E,0xFF,0x18,0x18,0x18};
const u8 TAB2[8] ={
     0x10,0x18,0x1C,0xFF,0xFF,0x1C,0x18,0x10};
void PAUSE(u8);
u8 ScanCode,Buffer[8];
u8 *ptr;
void main()
{	u8	i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;						//Config ScanPort as O/P
	DotPort=0; DotPortC=0;							//Config DotPort as O/P
	_psc0=0x01; _tbc0=0x04;							//fTB=fSYS/4, 週期=4096*fTB
	ptr=Buffer; ScanCode=0b00000001;				//Initila Pointer and ScanCode
	_tb0e=1; _emi=1; 								//Enable TB0 Interrupt	
	while(1)
	{	for(i=0;i<8;i++) Buffer[i]=TAB1[i];	      	//Copy First Pattern			
		_tb0on=1; PAUSE(200);						//Satrt TB0 & Delay 2 Sec					
		_tb0on=0; DotPort=0x00;						//Stop TB0
		for(i=0;i<8;i++) Buffer[i]=TAB2[i];       	//Copy Second Pattern			
		_tb0on=1; PAUSE(200);						//Satrt TB0 & Delay 2 Sec					
		_tb0on=0; DotPort=0x00;						//Stop TB0
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0;										//Turn-off Before New data
	ScanPort=ScanCode; DotPort=*ptr++;		      	//Update Scan and Data
	ScanCode<<=1;									//Update Scan Code
	if(ScanCode==0)									//If all Lines been Scanned
		{	ScanCode=0b00000001;			     	//Reload Scan Code &
			ptr=Buffer;						     	//Reset Pointer
		}	
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);				//Dealy i*10ms
}	