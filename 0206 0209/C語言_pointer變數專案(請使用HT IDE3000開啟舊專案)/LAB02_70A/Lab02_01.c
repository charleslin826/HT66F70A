//Lab02_1    
/*   Basic C Program 
     for() 					*/
#include <HT66F70A.H>  
void main()					//�����u�ƥN�X
{	unsigned char i=0;	//�]��char(8 bits)��int(16 bits)���²(�����sĶ�����Ӧn �Ϧӷ|�W�[�P����)	
	unsigned int j=0;	//char �令short or int ���O16�Ӧ줸�~�i�p��1�[��100
	for(i=0;i<=100;i++)
	{	j=j+i;				//j+=i;
	}
	GCC_NOP();				//for Break Point Only   //�d����~������build-in.h #define GCC_NOP()			asm("nop")
}



