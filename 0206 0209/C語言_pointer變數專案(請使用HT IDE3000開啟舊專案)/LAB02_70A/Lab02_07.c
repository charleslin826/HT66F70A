//Lab02_07    
/*   Basic C Program 
     Function call By Vaule/Reference example*/
#include <HT66F70A.H>     
#include "MyType.h"					
void swapV(u8,u8);					
void swapR(u8* ,u8*);				//���� Pointer �����ܼƬ��s���ܼƪ���m �ŧi�覡 "u8 *ptr" // "ptr = &x"  �䤤&�Ÿ������}�B��l(�YX=30 ��O�����}��80h �hptr = 80h) // "y=*ptr"�䤤*�Ÿ������ȹB��l (�Y�~�ӤW��y=80(h)) 
void main()
{	u8 i=20,j=50;
	swapV(i,j);						//�ǭȩI�s
	GCC_NOP();						//�]�_�I�[��
	swapR(&i,&j);					//�ǧ}�I�s
	GCC_NOP();						//& ���}�B��l
}
void swapR(u8 *i,  u8 *j)			//Call By Reference(Address)
{ 	u8	temp;
	temp=*i;						//* ���ȹB��l
	*i=*j;
	*j=temp;
}
void swapV(u8 i, u8 j)				//Call By Value
{ 	u8	temp;
	temp=i;
	i=j;
	j=temp;
	GCC_NOP();						//�]�_�I�[��	
}
	
	
/*u8 Array[10];
u8 *ptr;
ptr=Array;  >>�]��Array�w�]�N�O���V�O�����} �ҥH���Υ[&�Ÿ�  << ����ptr=&Array[0] 
Array[8]=*ptr;   >>�Yptr=1 �hArray[8]=1  
ptr++;
Array[7]=*ptr;   >>�Yptr=1+1 �hArray[7]=2  
*/