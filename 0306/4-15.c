// PROGRAM	: 4-15.c									2015.0911
// FUNCTION	: WDT Demo Program							By Steven
// Note		: Configuration Option Setting--
//			  fSUB Clock Source = LIRC 32KHz	
#include "HT66F70A.h"
#include "MyType.h"
#define SEG_Port  _pd
#define SEG_PortC _pdc
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void PAUSE(u8);
void main()
{	u8 i;	
	_wdtc=0b01010000;								//Enable WDT,Time-out=2^15/fS [�᭱�T�ӼƦr �аѾ\�x���Up.67] ��000 �ܦ�2^8/fs ~= 8ms
	SEG_PortC=0x0;								//Config PD as Output
	for(i=0;i<10;i++)
	{	SEG_Port=SEG_TAB[i]; PAUSE(50);		   	//Read Table &Delay 0.25 Sec
	}
	SEG_Port=0;	   							//Turn-off 7-Segment LEDs
	while(1);									//Loop Forever
}
void PAUSE(u8 i)								//Delay i*10mS
{	u8 j;
	for (j=0;j<i;j++)							//Insert CLRWDT to This Loop							
	{	GCC_DELAY(15000);    				//if WDT Period is Shorten  GCC_DELAY(20000)=10ms *25 = 0.25 sec  == GCC_DELAY(10000)=5ms*50=0.25sec   (�@���O0.5us)
	GCC_CLRWDT();						//�令10000�O5ms�M���@��   �A�u�Ƨ令15000�ܦ�7.5ms�M���@�� ���CPU�ϥΦ��� ���F��P�ˮĪG ���L�O����ݤ��X��
	}					
									//Clear WDT ��Ӧb�o��   ���]���ݭ̪��M�����ɶ��ܧ֤F �ҥH �]�n�[�ֲM��
}