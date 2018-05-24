// PROGRAM	: combination lock.c							   	2017.0701
// FUNCTION	: Combination Lock with Build in EEPROM				By Steven
#include "HT66F70A.h"
#include "2-9.h"
const u8 Str1[]={"Input Code:"};
const u8 Str2[]={"Save  Code:"};
const u8 Str3[]={"Good Job!"};
const u8 Str4[]={"Sorry!!"};
const u8 Str5[]={"Save OK!"};
void LCMInit(void);												//�禡�쫬�ŧi
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
u8 ScanKey(void);
void Write4Byte(u8*);
void Read4Byte(u8*);
u8 Get3Keys(u8*);
void Verify(u8*,u8*);
void main()
{	u8 i,Flag=0,Key=0x0B,*ptr,SaveCode[4],InputCode[4];
	_wdtc=0b10101111;										//�����ݭ̪��p�ɾ�
	_tm0c0=0; _tm0c1=0b00110001; 							//TM0���k�X��X�Ҧ�
	_pcs2=0x20;
	LCMInit();													//LCM��l��
	do 
	{	switch (Key)
		{	case 0x0A:											//���UA���
			{	LCMWrite(0,1);									//�M��LCM�B����k��
				i=0; while(Str2[i]!=0) LCMWrite(1,Str2[i++]);	//���"Save Code:"
				Flag=0; break;
			}
			case 0x0B:
			{	LCMWrite(0,1);									//�M��LCM�B����k��
				i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]); 	//���"Input Code:"
				Flag=1; break;
			}
			default:
			{	if(Key<10) 
				{	LCMWrite(1,Key+'0');						//������
					ptr=(Flag) ? InputCode : SaveCode;			//�]�wptr���V�}�C
					*ptr=Key; ptr++;							//�x�s���
					if(Get3Keys(ptr))							//���U�M����?
					{	LCMWrite(0,0x8B); 						//��в��ܦC1��12
						i=0; while(i++<4) LCMWrite(1,' ');		//�M��4�Ӧ�m
						LCMWrite(0,0x8B); 						//��в��ܦC1��12
						break;												
					}
					if(Flag) 									//Flag=1,�K�X��J�Ҧ�
					{	Read4Byte(SaveCode);					//��EEPROMŪ�^�K�X
						Verify(InputCode,SaveCode);				//�i��K�X���
					}
					else										//Flag=0,�K�X�]�w�Ҧ�
					{	Write4Byte(SaveCode);					//�K�X�s���EEPROM
						LCMWrite(0,0xC0); i=0;					//��в��ܦC2��0
						while(Str5[i]!=0) LCMWrite(1,Str5[i++]);//���"Save OK!"
						_tm0al=(u8)500; _tm0ah=500>>8;			//�]�w���k�X�g��=500us
						_t0on=1; Delayms(200); _t0on=0;			//�W�v=1/(500us*2)=1KHz,0.2��
					}
					Delayms(2000);								//���T/���~�T�����2��
					Flag=1; LCMWrite(0,1); i=0;					//�M��LCM�B����k��
					while(Str1[i]!=0) LCMWrite(1,Str1[i++]);	//���"Input Code:"
				}
			}
		}
		do Key=ScanKey(); while (Key==16);						//���ݫ�������
		Delayms(15); while(ScanKey()!=16); Delayms(15);			//���ݫ�������
	} while(1);
}
u8 Get3Keys(u8 *ptr)
{	u8 key, i=0;
	while(1)
	{	do key=ScanKey(); while (key==16);			   			//���ݫ�������
		if(key<10 && i<3)										//��J"0" ~ "9"
		{	*ptr=key; ptr++; i++;					   			//�x�s�ƭ�
			LCMWrite(1,key+'0');								//��ܸ��
		}
		Delayms(15); while(ScanKey()!=16); Delayms(15);			//���ݫ�������
		if(key==0x0F && i==3) return 0;							//�� F ��A������J
		if(key==0x0E) return 1;									//�� E ��A���s��J
	}
}
void Verify(u8 *ptr1,u8 *ptr2)
{	u8 i,flag=0;
	for(i=0;i<4;i++)											//�i��K�X���
	{	if(*ptr1++ != *ptr2++) flag++;
	}
	LCMWrite(0,0xC0);  											//�]�wLCD�C�G�B��0
	if(flag)													//flag!=0,�����~
	{	i=0; while(Str4[i]!=0) LCMWrite(1,Str4[i++]);  			//���"Sorry!!"
		_tm0al=(u8)1000; _tm0ah=1000>>8;						//�]�w���k�X�g��=1ms
		_t0on=1; Delayms(1000); _t0on=0; 						//�W�v=1/(1ms*2)=500Hz
	}
	else														//flag=0,��勵�T
	{	i=0; while(Str3[i]!=0) LCMWrite(1,Str3[i++]);  			//���"Good Job"
		for(i=0;i<2;i++)													
		{	_tm0al=(u8)250; _tm0ah=250>>0;						//�]�w���k�X�g��=250us
			_t0on=1; Delayms(200); _t0on=0; Delayms(100);		//�W�v=1/(250us*2)=2KHz
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
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					     		//�]�wEN/RW/RS Pin��0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      		//�]�wEN/RW/RS ����X�Ҧ�
	Delayms(40);									         	//LCM Power-On Time
	LCMWrite(0,0x38);								        	//8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);								       		//Display/Cursor Blinking On
	LCMWrite(0,0x06);								        	//Increment, Not Shift
	LCMWrite(0,0x01);								  			//Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;									//�W��Port����J�Ҧ�
	LCM_RS=0; LCM_RW=1;											//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();									//EN=1
		BusyAC=LCM_DataPort;									//Loop Until BF=0
		LCM_EN=0;												//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;											//�W��Port����X�Ҧ�
	LCM_RW=0;													//RW=0 (Write)
	LCM_RS=DCFlag;												//Set RS State By DCFlag
	LCM_DataPort=CD;											//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;								//EN=1
	return BusyAC;	
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
void Delayms(u16 del)
{	u16 i;														//@fSYS=4MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(1000);
}