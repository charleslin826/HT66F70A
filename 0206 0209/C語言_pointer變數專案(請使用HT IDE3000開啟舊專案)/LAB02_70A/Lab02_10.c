//Lab02_10    
/*   Basic C Program 
     switch case Demo*/
#include <HT66F70A.h>					     
#include "MyType.h"
#define LED_Port	_pc					//Port C Data Register
#define LED_PortC	_pcc				//Port C Control Register		
void main()
{	u8 x=0;
	_wdtc=0b10101111;
	LED_Port=0; LED_PortC=0;   //0000 0000���G  �]�wPCC��V
	while(1)
	{	switch (x)
		{	case 1: LED_Port=~0x01; // ( ~�O���ϦV/�ɼƪ��N��  �N�O0000 0000 �ܦ� 1111 1111 )(!�O�޿�ϦV �u�ܰ� ���ܯu) 
		/*   ~0x01  = 0000 0001���ϦV = 1111 1110 >>>�u�G��1�� */
					break;
			case 2: LED_Port=~0x02;
		/*   ~0x02  = 0000 0010���ϦV = 1111 1101>>>�u�G��2�� */
					break;					
			case 3: LED_Port=~0x04;
		/*   ~0x04  = 0000 0100���ϦV = 1111 1011>>>�u�G��3�� */
					break;
			case 4: LED_Port=~(1<<3);	//�N1�����T�줸
		/*   ~0x04  = 0000 0001�����T�줸 = 1111 0111>>>�u�G��4�� */
					break;
			case 5: LED_Port=~(1<<4);
					break;
			case 6: LED_Port=~(1<<5);
					break;
			case 7: LED_Port=~(1<<6);
					break;
			case 8: LED_Port=~(1<<7);
					break;
			default:					//x!=1~8�ɰ��楻�q
					x=0;
		}
		x+=1;
		GCC_DELAY(263690);		//����0~263690�ӫ��O�g�� �������s�۩w�q�� �i��build-in.h
	}
}	