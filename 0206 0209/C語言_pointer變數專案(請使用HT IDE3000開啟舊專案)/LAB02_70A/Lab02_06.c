//Lab02_06    
/*   Basic C Program 
     Function example	*/		//取消優化代碼
#include <HT66F70A.H>  
#include "MyType.h"				//編譯器至當前工作目錄找，找不到再至環境設定參數找					
u8 FindMax(u8,u8);				//函數原型宣告 Function Prototype
void main()
{	u8 i=20,j=50,max;           //觀察上下函數變數i j 記憶體位置不一樣 所以不會互相影響
	max=FindMax(i,j);			//傳值呼叫 (Call By Value)
	GCC_NOP();					//for Break Point Only	
}
u8 FindMax(u8 i, u8 j)			//函數定義 Function Definition, Local Variable
{ 	u8 temp;
    if(i>j) temp=i ; else temp=j;
    //temp = (i>j) ? i : j;		//三運算元指令
    i+=10; j+=10;				//Local Variable Test Only	
    return	temp;
}

	