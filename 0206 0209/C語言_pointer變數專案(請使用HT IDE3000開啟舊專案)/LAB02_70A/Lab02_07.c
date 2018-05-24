//Lab02_07    
/*   Basic C Program 
     Function call By Vaule/Reference example*/
#include <HT66F70A.H>     
#include "MyType.h"					
void swapV(u8,u8);					
void swapR(u8* ,u8*);				//指標 Pointer 指標變數為存放變數的位置 宣告方式 "u8 *ptr" // "ptr = &x"  其中&符號為取址運算子(若X=30 其記憶體位址為80h 則ptr = 80h) // "y=*ptr"其中*符號為取值運算子 (若繼承上方y=80(h)) 
void main()
{	u8 i=20,j=50;
	swapV(i,j);						//傳值呼叫
	GCC_NOP();						//設斷點觀測
	swapR(&i,&j);					//傳址呼叫
	GCC_NOP();						//& 取址運算子
}
void swapR(u8 *i,  u8 *j)			//Call By Reference(Address)
{ 	u8	temp;
	temp=*i;						//* 取值運算子
	*i=*j;
	*j=temp;
}
void swapV(u8 i, u8 j)				//Call By Value
{ 	u8	temp;
	temp=i;
	i=j;
	j=temp;
	GCC_NOP();						//設斷點觀測	
}
	
	
/*u8 Array[10];
u8 *ptr;
ptr=Array;  >>因為Array預設就是指向記憶體位址 所以不用加&符號  << 等於ptr=&Array[0] 
Array[8]=*ptr;   >>若ptr=1 則Array[8]=1  
ptr++;
Array[7]=*ptr;   >>若ptr=1+1 則Array[7]=2  
*/