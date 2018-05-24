//Lab02_05    
/*   Basic C Program 
     Type Define example	*/
#include <HT66F70A.H>  
#include "MyType.h"			//編譯器至當前工作目錄找，找不到再至環境設定參數找					
//#include <MyType.h>		//編譯器只到環境設定參數找(Can not Find)					
void main()
{	u8 i=0,j=0;
	while(1)
	{	if(i<=10)
		{	j+=i;				
			i++;
		}	
		else 
		{	break;		
		}
	}
	GCC_NP();				//for Break Point Only		
}