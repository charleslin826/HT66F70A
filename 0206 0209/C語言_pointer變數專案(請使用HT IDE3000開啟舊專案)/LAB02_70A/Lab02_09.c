//Lab02_09    
/*   Basic C Program 
     Pointer Demo*/
#include <HT66F70A.h>					     
#include "MyType.h"					
void main()
{	u16 x=4,temp,Array[]={0,1,2};
	u16 *ptr1,*ptr2;		
	ptr1=&x;
	temp=*ptr1;						//temp=x
	GCC_NOP();						//�]�_�I�[��
	ptr2=Array;						//ptr2=&Array[0],�}�C���W�٧Y�N���}
	temp=*ptr2++;					//ptr2=Array[0]=Array����m 0x008a
	GCC_NOP();						//�]�_�I�[��
	temp=*ptr2;						//ptr2=Array[1]
	GCC_NOP();						//�]�_�I�[��							
}
	