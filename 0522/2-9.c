// PROGRAM	: 2-9.c											2017.0701
// FUNCTION	: HT66F50 EEPROM DM Read/Write Demo Program		By Steven
#include "HT66F70A.h"
#include "2-9.H" 
const u8 Str1[]={"A.Input B.RD EEP"};
void LCMInit(void);											//�禡�쫬�ŧi
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
u8 ScanKey(void);
void Write4Byte(u8*);
void Read4Byte(u8*);
void main()
{	u8 i,Key,Code[4];
	_wdtc=0b10101111;										//�����ݭ̪��p�ɾ�
	_tm0c0=0; _tm0c1=0b00110001; 							//TM0���k�X��X�Ҧ�
	_pcs2=0x20;												//PC5->TP0
	LCMInit();												//LCM��l��
	while(1) 
	{	do Key=ScanKey(); while (Key==16);					//���ݫ�������
		Delayms(10); 
		while(ScanKey()!=16); Delayms(10);					//���ݫ�������	
		switch (Key)
		{	case 0x0A:										//���UA���
				LCMWrite(0,0xC2);							//�C2��2
				for(i=0;i<4;i++) LCMWrite(1,' ');			//�M���w������
				LCMWrite(0,0xC2);							//�C2��2
				for(i=0;i<4;i++)
				{	do Key=ScanKey(); while (Key>9);		//���ݫ���0~9����
					Code[i]=Key; LCMWrite(1,Key+'0');		//������
					Delayms(300);
				}
				Write4Byte(Code);							//�K�X�s���EEPROM
				_tm0al=(u8)250; _tm0ah=250>>8;				//�]�w���k�X�g��=250us
				_t0on=1; Delayms(200); _t0on=0; 			//�W�v=1/(250us*2)=2KHz,0.2��
				Delayms(100);								//���j0.1��
				_t0on=1; Delayms(100); _t0on=0;
				break;
			case 0x0B:
				Read4Byte(Code);							//��EEPROMŪ�^�x�s��
				LCMWrite(0,0xCA);							//�C2��10
				for(i=0;i<4;i++) LCMWrite(1,Code[i]+'0');	//����x�s��	
				_tm0al=(u8)500; _tm0ah=500>>8;				//�]�w���k�X�g��=500us
				_t0on=1; Delayms(1000); _t0on=0; 			//�W�v=1/(500us*2)=1KHz,1��	
				break;			
		}
	}
}
void Read4Byte(u8 *ptr)
{	u8 i;
	for(i=0;i<4;i++)
	{	_eea=i;												//�]�wEEPROM��}
		_mp1h=0x01; _mp1l=0x40;								//MP1=EEC (Bank1)
		_iar1=RDEN; _iar1|=RD;								//�]�wRDEN=1,RD=1
		while(_iar1&RD);									//����Ū������
		_iar1=0;											//�T��EEPROMŪ�g
		*ptr++=_eed;										//��EEPROMŪ�^���,���л��W
	}		
}
void Write4Byte(u8 *ptr)
{	u8 i;
	for(i=0;i<4;i++)
	{	_eea=i;												//�]�wEEPROM��}
		_eed=*ptr++;										//�]�w�g�J���,���л��W
		_mp1h=0x01; _mp1l=0x40;								//MP1=EEC (Bank1)
		_iar1=WREN; _iar1|=WR;								//�]�wWREN=1,WR=1
		while(_iar1&WR);									//���ݼg�J����
		_iar1=0;											//�T��EEPROMŪ�g
	}
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;					   			//��X/��J�W���íP�ണ�ɹq��
	KeyPort=0b11111110;								      		//��l���y�X
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				      		//�ˬd��1��
		key++;
		if(!(KeyPort & 1<<6)) break;				      		//�ˬd��2��
		key++;
		if(!(KeyPort & 1<<5)) break;				      		//�ˬd��3��
		key++;
		if(!(KeyPort & 1<<4)) break;				      		//�ˬd��4��
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;			   			//���ͤU�@�C���y�X
	}
	return key;	
}
void LCMInit(void)
{	u8 i;
	LCM_EN=0; LCM_RW=0; LCM_RS=0;	        				//�]�wEN/RW/RS�}�쬰�C�q��
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	  					//�]�wEN/RW/RS�}�쬰��X�Ҧ�
	GCC_DELAY(80000);										//LCM Power-On Time
	LCMWrite(0,0x38);										//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);										//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);										//COMD:Increment, Not Shift
	LCMWrite(0,0x01); i=0;									//COMD:Clear LCM Display
	while(Str1[i]!=0) LCMWrite(1,Str1[i++]);				//���Str1�r��
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;								//�W��Port����J�Ҧ�
	LCM_RS=0; LCM_RW=1;										//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();								//EN=1
		BusyAC=LCM_DataPort;								//Loop Until BF=0
		LCM_EN=0;											//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;										//�W��Port����X�Ҧ�
	LCM_RW=0;												//RW=0 (Write)
	LCM_RS=DCFlag;											//Set RS State By DCFlag
	LCM_DataPort=CD;										//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;			  			  	//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=4MH,����del*100us
	for(i=0;i<del;i++) GCC_DELAY(2000);
		
}