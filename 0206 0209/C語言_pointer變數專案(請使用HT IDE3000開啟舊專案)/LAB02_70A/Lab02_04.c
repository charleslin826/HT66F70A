//Lab02_04    
/*   Basic C Program 
     if,else		   	*/
#include <HT66F70A.H>  
#include "MyType.h"
void main()
{	u8 i=0,j=0;   //u8�O�ۤv�w�q��  �bMyType.h  = typedef	unsigned char	u8;  �H��n�qV3������V1�i�H�u��define�N�n
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