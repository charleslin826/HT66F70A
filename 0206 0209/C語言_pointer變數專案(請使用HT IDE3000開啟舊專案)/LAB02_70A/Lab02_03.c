//Lab02_03    
/*   Basic C Program 
     if,while(), break	    	*/
#include <HT66F70A.H>  
void main()
{	unsigned char i=0,j=0;
	while(1)					//Endless Loop
	{	j+=i;					//可以寫成 j+=i++，然後刪除下一行;
		i++;
		if(i>10) break;				
	}
	GCC_NP();					//for Break Point Only
}