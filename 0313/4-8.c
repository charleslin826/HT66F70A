// PROGRAM	: 4-8.c									2015.0910
// FUNCTION	: GENERATE TONE By USING DELAY SKILL	By Steven
// NOTE: In Project Option: Language Must Select 
//       Enhanced Holtek C Compiler/Assembler, Due
//       to the Definition of fSYS Over range !!! 
#include "HT66F70A.h"
#include "MyType.h"
#include "4-7.h"
#define SPK_Port  	_pc4							//PC.4
#define SPK_PortC	_pcc4							//pcc.4
#define M1  1000000								   	//1000000
const u8 TAB_Pitch[] = {		   					//Pitch Constant  F
			M1/(523*2*10),M1/(587*2*10),
			M1/(659*2*10),M1/(698*2*10),
			M1/(785*2*10),M1/(880*2*10),
			M1/(988*2*10),M1/(523*2*2*10),
			M1/(523*2*2*10),M1/(587*2*2*10),
			M1/(659*2*2*10),M1/(698*2*2*10),
			M1/(785*2*2*10),(M1/10)/(880*2*2),
			(M1/10)/(988*2*2),(M1/10)/(523*2*2*2)};  //compilier �������� �]���������Ʀr�L�j�ɭPoverflow �ҥH�u�n���}���N�i�H
const u16 TAB_Duration[] = { 	      				//Duration Constant S
			523/2,587/2,659/2,698/2,
			785/2,880/2,988/2,(523*2)/2,
			523/2/2,587/2/2,659/2/2,698/2/2,
			785/2/2,880/2/2,988/2/2,(523*2)/2/2};
void PAUSE(u8);
u8 ScanKey(void);
void main()
{	u8 Key;
	u16 j;
	_wdtc=0b10101111;								//�����ݭ̪��p�ɾ�
	SPK_PortC=0;									//Config SPK_Port as Output
	while(1)
	{do Key=ScanKey();while(Key==16);	   		//Wait Key Pressed //C�y���@��i�H����ӱԭz �u�n�Τ����j�}�N�n do��{}�w�ٲ�				
		//for(i=0;i<8;i++){	   		
			for(j=0;j<TAB_Duration[Key];j++)
			{	SPK_Port=!SPK_Port;				   	//Toggle PC.4
			//	PAUSE(TAB_Pitch[i]);				
				PAUSE(TAB_Pitch[Key]);				      	//Read Table Index By Key					
			}
		//}
	}
	//for(i=0;i<100;i++) GCC_DELAY(20000); 	
}
void PAUSE(u8 i)
{	u8 j;
    for(j=0;j<i;j++) GCC_DELAY(20);			      	//Delay i*10uS
}

u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xf0; KeyPortPU=0xf0;			   		//I/O Mode Config & Pull-up Enable
	KeyPort=0b11111110;					         	//Initial Scancode
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<4)) break;		      	//Check Column 0 //& 1<<4�Omask �h�ˬd0001 0000  //�Ĥ@���Y���UA�h�������O1  
		key++;
		if(!(KeyPort & 1<<5)) break;			   	//Check Column 1
		key++;
		if(!(KeyPort & 1<<6)) break;			   	//Check Column 2
		key++;
		if(!(KeyPort & 1<<7)) break;			   	//Check Column 3
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;	   		//Scancode for Next Row   �O�ұ��]�X�u���@��0(�p���~�i�T�{���G)
	}
	return key;	//�Y���S�����O�^��16 //���UA�O�^��10=>KEY = +4+4+2 = 10 (=16�i�A)
}