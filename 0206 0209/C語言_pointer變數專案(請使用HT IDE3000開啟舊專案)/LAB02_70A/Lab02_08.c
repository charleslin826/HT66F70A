//Lab02_08    
/*   Basic C Program 
     Local and Global Variable */
#include <HT66F70A.h>					
#include "MyType.h"					
void swapV(void);					
u8 i,j;					//羆砰跑计產常眔
void main()
{	i=20; j=50;
	swapV();						
	GCC_NOP();						//砞耞翴芠代
}
void swapV()						
{ 	u8	temp;						//跋办跑计Τㄧ计眔
	temp=i;
	i=j;
	j=temp;
}
	