// PROGRAM	: H5-4Ext.c									2016.0414
// FUNCTION	: 8*8 Dot Matrix LED Dynamic(0~9) Control 	By Steven
#include "HT66F70A.h"
#include "5-4.H"
#include "MyType.H"
const u8 TAB[10][8] = {{0x1C,0x22,0x32,0x2A,0x26,0x22,0x1C,0x00},	//0
					   {0x08,0x0C,0x08,0x08,0x08,0x08,0x1C,0x00},	//1
					   {0x1C,0x22,0x20,0x10,0x08,0x04,0x3E,0x00},	//2	
					   {0x3E,0x10,0x08,0x10,0x20,0x22,0x1C,0x00},	//3	
					   {0x10,0x18,0x14,0x12,0x3E,0x10,0x10,0x00},	//4	
					   {0x3E,0x02,0x1E,0x20,0x20,0x22,0x1C,0x00},	//5					   				
					   {0x18,0x04,0x02,0x1E,0x22,0x22,0x1C,0x00},	//6					   				
					   {0x3E,0x20,0x10,0x08,0x04,0x04,0x04,0x00},	//7					   				
					   {0x1C,0x22,0x22,0x1C,0x22,0x22,0x1C,0x00},	//8					   				
					   {0x1C,0x22,0x22,0x3C,0x20,0x10,0x0C,0x00}};	//9					   				

void PAUSE(u8);
u8 ScanCode,Buffer[16];
u8 *volatile ptr;
void main()
{	u8 i,temp,k,l;
	_wdtc=0b10101111;	
	ScanPort=0; ScanPortC=0;							//Config ScanPort as O/P
	DotPort=0; DotPortC=0;								//Config DotPort as O/P
	_psc0=0x01; _tbc0=0x04;								//fTB=fSYS/4, ¶g´Á=4096*fTB
	ptr=Buffer; ScanCode=0b00000001;					//Initial Pointer and ScanCode
	_tb0e=1; _emi=1; 									//Enable TB0 Interrupt	
	while(1)
	{	for(k=0;k<10;k++)
		{	for(i=0;i<16;i++)							
			{	if(i<8) Buffer[i]=0; 					//Clear Buffer[0]~Buffer[7]
			 	else Buffer[i]=TAB[k][i-8];				//Copy Pattern to Buffer[8]~Buffer[15]
			}

 			for(l=0;l<16;l++)
			{	ptr=Buffer;								//Initial Pointer			
				_tb0on=1; PAUSE(10);					//Satrt TB0 & Delay 100ms					
				while(ptr!=Buffer);
				_tb0on=0; DotPort=0x00;					//Stop TB0
	
				temp=Buffer[0];
				for(i=0;i<15;i++) Buffer[i]=Buffer[i+1];//Buffer Shift		
				Buffer[i]=temp;
			}
		}
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0;											//Turn-off Before New data
	ScanPort=ScanCode; DotPort=*ptr++; 					//Update Scan and Data
	ScanCode<<=1;										//Up data Scan Code
	if(ScanCode==0)										//If all Lines been Scanned
	{	ScanCode=0b00000001;							//Reload Scan Code &
		ptr=Buffer;										//Reset Pointer
	}	
}
void PAUSE(u8 i)
{	u8 j;
	for(j=0;j<i;j++) GCC_DELAY(20000);					//Dealy i*10ms
}	