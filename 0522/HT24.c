// PROGRAM	: HT24.c							           		2014.1226
// FUNCTION	: Combination Lock with HT24LC32					By Steven
#include <HT66F70A.h>
#include "HT24.h"
void main()
{	u8 i,Flag,Key=0x0B,*ptr,SaveCode[4],InputCode[4];
	_wdtc=0b10101111;												//�����ݪ����p�ɾ�
	_tm0c0=0x00; _tm0c1=0x31; 										//���k�X��X
	_pcs2=0x20;														//PC5��TP0�\��						
	LCMInit();														//LCM��l��
	do 
	{	switch (Key)
		{	case 0x0A:												//���UA���
			{	LCMWrite(0,1);										//�M��LCM�B����k��
				i=0; while(Str2[i]!=0) LCMWrite(1,Str2[i++]);		//���"Save Code:"
				Flag=0; break;
			}
			case 0x0B:
			{	LCMWrite(0,1);										//�M��LCM�B����k��
				i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]);  		//���"Input Code:"
				Flag=1; break;
			}
			default:
			{	if(Key<10) 
				{	LCMWrite(1,Key+'0');							//������
					ptr=(Flag) ? InputCode : SaveCode;				//�]�wptr���V�}�C
					*ptr=Key; ptr++;								//�x�s���
					if(Get3Keys(ptr))								//���U�M����?
					{	LCMWrite(0,0x8B); 							//��в��ܦC1��12
						i=0; while(i++<4) LCMWrite(1,' ');			//�M��4�Ӧ�m
						LCMWrite(0,0x8B); 							//��в��ܦC1��12
						break;												
					}
					if(Flag) 										//Flag=1,�K�X��J�Ҧ�
					{	I2C_SeqRandomRead(0,SaveCode,4);			//��EEPROMŪ�^�K�X
						Verify(InputCode,SaveCode);					//�i��K�X���
					}
					else											//Flag=0,�K�X�]�w�Ҧ�
					{	I2C_PageWrite(0,SaveCode,4);				//�K�X�s���EEPROM
						LCMWrite(0,0xC0); i=0;						//��в��ܦC2��0
						while(Str5[i]!=0) LCMWrite(1,Str5[i++]);	//���"Save OK!"
						_tm0al=(u8)1000; _tm0ah=1000>>8;			//�]�w���k�X�g��=500us
						_t0on=1; Delayms(200); _t0on=0;				//�W�v=1/(500us*2)=1KHz,0.2��
					}
					Delayms(2000);									//���T/���~�T�����2��
					Flag=1; LCMWrite(0,1);							//�M��LCM�B����k��
					i=0; while(Str1[i]!=0) LCMWrite(1,Str1[i++]);	//���"Input Code:"
				}
			}
		}
		do Key=ScanKey(); while (Key==16);							//���ݫ�������
		Delayms(15); while(ScanKey()!=16); Delayms(15);				//���ݫ�������
	} while(1);
}
u8 Get3Keys(u8 *ptr)
{	u8 key, i=0;
	while(1)
	{	do key=ScanKey(); while (key==16);			   				//���ݫ�������
		if(key<10 && i<3)											//��J"0" ~ "9"
		{	*ptr=key; ptr++; i++;					   				//�x�s�ƭ�
			LCMWrite(1,key+'0');									//��ܸ��
		}
		Delayms(15); while(ScanKey()!=16); Delayms(15);				//���ݫ�������
		if(key==0x0F && i==3) return 0;								//�� F ��A������J
		if(key==0x0E) return 1;										//�� E ��A���s��J
	}
}
void Verify(u8 *ptr1,u8 *ptr2)
{	u8 i,flag=0;
	for(i=0;i<4;i++)												//�i��K�X���
	{	if(*ptr1++ != *ptr2++) flag++;
	}
	LCMWrite(0,0xC0);  												//�]�wLCD�C�G�B��0
	if(flag)														//flag!=0,�����~
	{	i=0; while(Str4[i]!=0) LCMWrite(1,Str4[i++]);  				//���"Sorry!!"
		_tm0al=(u8)2000%256; _tm0ah=2000>>8;						//�]�w���k�X�g��=1ms
		_t0on=1; Delayms(1000); _t0on=0; 							//�W�v=1/(1ms*2)=500Hz
	}
	else															//flag=0,��勵�T
	{	i=0; while(Str3[i]!=0) LCMWrite(1,Str3[i++]);  				//���"Good Job"
		for(i=0;i<2;i++)													
		{	_tm0al=(u8)500; _tm0ah=500>>8;							//�]�w���k�X�g��=250us
			_t0on=1; Delayms(200); _t0on=0; Delayms(100);			//�W�v=1/(250us*2)=2KHz
		}	
	}
}
void I2C_START(void)
{	SCL=0; SDA=1;													//�]�w SCL=0, SDA=1
	SCLC=0; SDAC=0; 					   							//SCL/SDA����X�Ҧ�
	SCL=1; 															//SCL=1, SDA=1
	GCC_DELAY(1);
	SDA=0;															//SDA=0 			     						
	GCC_DELAY(1);
	SCL=0;								      						//SCL=0	
}
void I2C_STOP(void)
{	SDA=0; SDAC=0;							   						// SDA=0,SDA ����X�Ҧ�
	SCL=1;															//SCL=1
	GCC_DELAY(1);
	SDA=1;								    						//SDA=1
	GCC_DELAY(1);
	SCL=0; 															//SCL=0	
}
void CheckACK(void)
{	SDAC=1; 										      			//SDA ����J�Ҧ�
	SCL=1; 	GCC_DELAY(1);							      			//�]�w SCL=1, 
	while(SDA);										    			//���� ACK(Low)
	SCL=0;					   										//�]�w SCL=0
}
void I2C_DeviceSelect(_Bool FG_RW)
{	WriteByte(DeviceID|FG_RW);										//���XDeviceID�PRW�줸
	CheckACK();		
} 
void I2C_SetAddress(u16 I2CAddress)
{	WriteByte(I2CAddress>>8);										//1'st Word Address
	CheckACK();
	WriteByte((u8)I2CAddress);										//2'nd Word Address
	CheckACK();
}
void I2C_SeqRandomRead(u16 Address,u8 *ptr,u8 Count)
{	u8 i;
	I2C_START();
	I2C_DeviceSelect(0);				      						//Device ID/A2~A0/Write
	I2C_SetAddress(Address);					      				//�]�w a11~a0
	I2C_START();
	I2C_DeviceSelect(1);				      						//Device ID/A2~A0/Read
	for(i=0;i<Count;i++)
	{	*ptr++=ReadByte();
		if(i==(Count-1)) SDA=1; else SDA=0;							//�Y���̥��줸��NO_ACK,�_�hACK
		SDAC=0;
		SCL=1;  SCL=0; 		
	}
	I2C_STOP();										         		//STOP 
}
void I2C_PageWrite(u16 Address,u8 *ptr,u8 Count)
{	u8 i;
	I2C_START();
	I2C_DeviceSelect(0);				      						//Device ID/A2~A0/Write
	I2C_SetAddress(Address);					      				//�]�w a11~a0
	for(i=0;i<Count;i++)
	{	WriteByte(*ptr++);							     			//�e�X�@��Byte
		CheckACK();	
	}
	I2C_STOP();										         		//STOP 
	Delayms(5);									         			//Delay 5ms for tW	
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SCL=0; SDAC=0;									         		//SCL=0, SDA����X�Ҧ�
	do
	{	SDA=(I2CData & temp)?1:0; //Delay5us();				   		//�]�w SDA �Ǧ�é��� 5us
		SCL=1; GCC_DELAY(1); 
		SCL=0; GCC_DELAY(1);	   									//���� SCL Clock
		temp>>=1;									         		//�U�@�줸
	} while (temp!=0);
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				         		//�]�w SDA ����J�Ҧ�
	do
	{	SCL=1; GCC_DELAY(1);							      		//�]�w SCL=1, Delay 5us
		if(SDA==1) I2CData|=temp;						      		//�����줸�� **
		SCL=0; GCC_DELAY(1);							      		//�]�w  SCL=0, Delay 5us
		temp>>=1;										         	//�U�@�줸
	} while (temp!=0);
	return I2CData;
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					      			//�]�wEN/RW/RS Pin��0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      			//�]�wEN/RW/RS ����X�Ҧ�
	Delayms(40);									         		//LCM Power-On Time
	LCMWrite(0,0x38);								         		//8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);								         		//Display/Cursor Blinking On
	LCMWrite(0,0x06);								         		//Increment, Not Shift
	LCMWrite(0,0x01);								         		//Clear LCM Display
}
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;										//�W��Port����J�Ҧ�
	LCM_RS=0; LCM_RW=1;												//RS=0,RW=1 (Read IR)
	GCC_NOP(); 
	do
	{	LCM_EN=1; GCC_NOP();										//EN=1
		BusyAC=LCM_DataPort;										//Loop Until BF=0
		LCM_EN=0;													//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;												//�W��Port����X�Ҧ�
	LCM_RW=0;														//RW=0 (Write)
	LCM_RS=DCFlag;													//Set RS State By DCFlag
	LCM_DataPort=CD;												//Sent Command or Data
	LCM_EN=1; GCC_NOP(); LCM_EN=0;								    //EN=1
	return BusyAC;	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;					   				//��X/��J�W���íP�ണ�ɹq��
	KeyPort=0b11111110;								      			//��l���y�X
	for(i=0;i<=3;i++)
	{	if(!(KeyPort & 1<<7)) break;				      			//�ˬd��1��
		key++;
		if(!(KeyPort & 1<<6)) break;				      			//�ˬd��2��
		key++;
		if(!(KeyPort & 1<<5)) break;				      			//�ˬd��3��
		key++;
		if(!(KeyPort & 1<<4)) break;				      			//�ˬd��4��
		key++;
		KeyPort<<=1; KeyPort|=0b00000001;			   				//���ͤU�@�C���y�X
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;															//@fSYS=8MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}