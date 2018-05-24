//Lab02_04    
/*   Basic C Program 
     if,else		   	*/
#include <HT66F70A.H>  
#include "MyType.h"
void main()
{	u8 i=0,j=0;   //u8是自己定義的  在MyType.h  = typedef	unsigned char	u8;  以後要從V3版本轉V1可以只改define就好
	while(1)
	{	if(i<=10)
		{	j+=i;				
			i++;
		}	
		else 
		{	break;		
		}
	}
	GCC_NOP();					//for Break Point Only	
}