// PROGRAM	: 4-1.c									2015.0908
// FUNCTION	: LED Scanning Demo Program (for)		By Steven
#include "HT66F70A.h" 			
#define  LED_Port    _pc								
#define  LED_PortC   _pcc				//�bC�y���� �S��\��Ȧs���n�p�g�B�e���n�[���u			
void main()
{	unsigned char i,j;	
	_wdtc=0b10101111;								//�����ݭ̪��p�ɾ�
	LED_PortC=0x0;									//Config LED_Port as Output //��V����
	LED_Port=~0x01;	// ~�N��ϦV 01(�G�C��) => FE (�G�@��) //�]0�~�|���q��t //Set Initial Data 
	while(1)
	{	for(j=0;j<7;j++)	
		{	for(i=0;i<100;i++) GCC_DELAY(2000);		//�t�ήɯ߬OXCL �ۭ^�_����(8MHz) �˼ƭ��W4 = 1/8*4=0.5 us * 2000 = 1 ms *100 = 1 s
				LED_Port=(LED_Port<<1)|1;			//Shift Left 11111110 �ܦ� 11111100 �q�G�Ĥ@���ܫG����
		}											//���ڭ̥u�Q�n�G��@�@�� �ҥH�h�M1(0x80)��or�B��
		for(j=0;j<7;j++)	
		{	for(i=0;i<200;i++) GCC_DELAY(2000);     //�t�ήɯ߬OXCL �ۭ^�_����(8MHz) �˼ƭ��W4 = 1/8*4=0.5 us * 2000 = 1 ms *200 = 2 s
				LED_Port=(LED_Port>>1)|0x80;		//Shift Right  	���^��
		}											////���ڭ̥u�Q�n�G��@�@�� �ҥH�h�M1(0x80)��or�B��
	}
}	