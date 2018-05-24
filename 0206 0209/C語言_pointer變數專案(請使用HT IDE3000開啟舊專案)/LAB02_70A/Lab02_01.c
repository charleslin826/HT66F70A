//Lab02_1    
/*   Basic C Program 
     for() 					*/
#include <HT66F70A.H>  
void main()					//取消優化代碼
{	unsigned char i=0;	//因為char(8 bits)比int(16 bits)更精簡(但此編譯器不太好 反而會增加周期數)	
	unsigned int j=0;	//char 改成short or int 都是16個位元才可計算1加到100
	for(i=0;i<=100;i++)
	{	j=j+i;				//j+=i;
	}
	GCC_NOP();				//for Break Point Only   //查左邊外部文檔build-in.h #define GCC_NOP()			asm("nop")
}



