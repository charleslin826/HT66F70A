//Lab02_08    
/*   Basic C Program 
     Local and Global Variable */
#include <HT66F70A.h>					
#include "MyType.h"					
void swapV(void);					
u8 i,j;					//�`���ܼơA�j�a���ݱo��
void main()
{	i=20; j=50;
	swapV();						
	GCC_NOP();						//�]�_�I�[��
}
void swapV()						
{ 	u8	temp;						//�ϰ��ܼơA�u���ŧi����Ƭݱo��
	temp=i;
	i=j;
	j=temp;
}
	