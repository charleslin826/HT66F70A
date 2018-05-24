// PROGRAM	: 5-4.c										2015.0911
// FUNCTION	: 8*8 Dot Matrix LED Dynamic Control 		By Steven
#include "HT66F70A.h"
#include "5-4.H"
#include "MyType.H"
const u8 TAB[8] ={
  			0x18,0x18,0x3C,0x7E,0xFF,0x18,0x18,0x18};
void PAUSE(u8);
u8 ScanCode,Buffer[16];
u8 *volatile ptr;
void main()
{	u8 i,temp,j;
	_wdtc=0b10101111;									//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;							//Config ScanPort as O/P
	DotPort=0; DotPortC=0;								//Config DotPort as O/P
	_psc0=0x01; _tbc0=0x04;								//fTB=fSYS/4, 週期=4096*fTB
	ptr=Buffer; ScanCode=0b00000001;					//Initial Pointer and ScanCode
	_tb0e=1; _emi=1; 									//Enable TB0 Interrupt	
	for(i=0;i<16;i++)									//Clear Buffer[0]~Buffer[7]
	{	if(i>=8) *ptr++=0; else *ptr++=TAB[7-i];	  		//Copy Pattern to Buffer[8]~Buffer[15]
	}
 	while(1)
	{	ptr=Buffer;										//Initial Pointer			
		_tb0on=1; PAUSE(100);							//Satrt TB0 & Delay 100ms					
		while(ptr!=Buffer);
		_tb0on=0; DotPort=0x00;							//Stop TB0
		/*ptr=Buffer;*/
		ptr=Buffer+15;										//Initial Pointer
/*		temp=*ptr++;									//Backup Buffer[0]之前的compiler 只接受這樣的作法
		for(i=0;i<15;i++) 								//Buffer Shift
		{	j=*ptr--; 
			*ptr=j;
			ptr+=2;
		}		
		ptr--; *ptr=temp;								//Reload temp to Buffer[15]
*/		
	/*	temp=*ptr;										//Backup temp=Buffer[0] 
		for(i=0;i<15;i++) *ptr=*(++ptr);				//Buffer Shift  Buffer[0]=Buffer[1],Buffer[1]=Buffer[2]...Buffer[14]=Buffer[15]
		*ptr=temp;		//(這個時候ptr已經指到第16)ptr=Buffer[0] */
		temp=*ptr;										//Backup temp=Buffer[15] 
		for(i=0;i<15;i++) *ptr=*(--ptr);				//Buffer Shift  Buffer[15]=Buffer[14],Buffer[14]=Buffer[13]...Buffer[1]=Buffer[0]
		*ptr=temp;		//(這個時候ptr已經指到第1)ptr=Buffer[15] 
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