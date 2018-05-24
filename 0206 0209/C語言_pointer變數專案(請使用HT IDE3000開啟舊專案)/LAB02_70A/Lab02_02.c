//Lab02_02    
/*   Basic C Program 
     while() and do while		*/
#include <HT66F70A.H>  
void main()						//取消優化代碼
{	unsigned char i=1,j=0;
	while (i<=10)
	{	j+=i;					//j=j+i
		i++;					//i=i+1 or i+=1;  //最後一次i=11
	}	
//  第一段
	i=j=0;
	while (i++<10)				//第一次 i=0
	{	j=j+i;					//但到這邊的時候 第一次 i=1
	}	
//	第二段
	i=j=0;
	do
	{	j=j+i;
	} while (i++<10);			//55! (Post-increment)	
//	第三段	
	i=j=0;
	do
	{	j=j+i;
	} while (++i<10);			//45 Why? (Pre-increment)	)
	GCC_NOP();					//for Break Point Only
}