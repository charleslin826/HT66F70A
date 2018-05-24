// PROGRAM	: I2CLCM.c						2017.1031
// FUNCTION	: Serial LCM(PCF8574) Control 	By Steven
#include <HT66F70A.h>
#include "MyType.H"
#include "SerialLCM.h"
void LCMInit(void);
void main()
  {	volatile u8 i;
	_wdtc=0b10101111;							//�����ݭ̪��p�ɾ�
	LCMInit();				       				//LCM��l�]�w
	while(1)
	{	LCMWrite(0,0x01); Delayms(2);			//�M��LCM��ܡB����k��						
		for(i=0;i<16;i++)
		{	LCMWrite(1,'a'); Delayms(100);		//���"1"�é���0.2��
		}
		LCMWrite(0,0x04);						//�i�J�Ҧ�:Decrease, Not Shift 
		LCMWrite(0,0xCF);						//Set Line 2, Position 0 
		do
		{	Delayms(300);						//����0.1��
		} while(LCMWrite(1,'2')>(0x40)); 		//���"2"�çP�_�O�_��F�C2��0
		Delayms(1000);							//����1��
	}
}
void LCMInit(void)
{	Delayms(40);								//LCM Power-On Time
	I2C_START(); I2C_STOP();
	LCMWrite(0,0x28); 							//�\��]�w:4-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F); 							//��ܱ���:Display/Cursor Blinking On
	LCMWrite(0,0x06); 							//�i�J�Ҧ�:Increse, Not Shift
	LCMWrite(0,0x01); Delayms(2);				//�M��LCM
}
