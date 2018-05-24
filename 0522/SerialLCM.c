// PROPGRAM : SerialLCM.C 						2017.1031
// FUNCTION	: LCM Library for PCF8574 			By Steven
//   Note   : Suit for Hardware Configure as follows:
//			PCF8574           1602A LCMRead
//			 4(P0)				 4(RS)
//			 5(P1)				 5(RW)
//			 6(P2)				 6(EN)
//			 7(P3)				  LCM Back Light(8050)
//			 9(P4)				11(D4)
//			10(P5)				12(D5)
//			11(P6)				13(D6)
//			12(P7)				14(D7)
#include <HT66F70A.h>
#include "MyType.h"
#include "SerialLCM.h"
u8 LCMWrite(_Bool fgCD,u8 CD)
{	volatile u8 BusyAC,tmp,i=1;
	do
	{	BusyAC=LCMRead(0);						//Ū��LCM IR
	} while (BusyAC & 1<<7);					//�YLCM���L,�A��Ū��
	I2C_START();								//START Condition
	WriteByte(PCF8574ID|0);	CheckACK();			//Write
	tmp=(fgCD) ? 0x09 : 0x08;					//P3=1,EN=0,RW=0,RS=fgCD	
	tmp|=(CD & 0xF0);							//Get Hi-nibble 
	if((tmp & 0b00110001)== 0x20) i=2;			//If Function Set is Issued
	while(i--)
	{	WriteByte(tmp); CheckACK();				//Write Hi-nibble
		tmp|=(1<<2);							//Set P2(->EN)=1
		WriteByte(tmp);	CheckACK();
		tmp&=(~(1<<2));							//Set P2(->EN)=0
		WriteByte(tmp);	CheckACK();
	}
	tmp&=0x0F;									//Keep Lo-nibble Unchanged
	tmp|=(CD<<4);								//Get Lo-nibble
	WriteByte(tmp); CheckACK();					//Write Lo-nibble
	tmp|=(1<<2);								//Set P2(->EN)=1
	WriteByte(tmp);	CheckACK();							
	tmp&=(~(1<<2));								//Set P2(->EN)=0
	WriteByte(tmp); CheckACK();								
	I2C_STOP();									//STOP Condition
	return BusyAC;								//�^��Address Counter
}
u8 LCMRead(_Bool fgCD)							//Read Busy AC or CGRAM/DDRAM
{	volatile u8 BusyAC,tmp;
	I2C_START();								//START Condition
	WriteByte(PCF8574ID|0);	CheckACK();			//Write
	if(fgCD) tmp=0xFB;else tmp=0xFA;			//Set P0(->RS) if fgCD=1
	WriteByte(tmp);	CheckACK();					//Write to Port
	tmp|=(1<<2);								//Set P2(->EN)=1
	WriteByte(tmp);	CheckACK();							
	I2C_STOP();									//STOP Condition

	I2C_START();								//START Condition
	WriteByte(PCF8574ID|1);	CheckACK();			//Read
	BusyAC=ReadByte();							//Ū��Hi-Nibble
	SDA=1; SDAC=0; 								//�e�XNo_ACK�H��
	SCL=1; GCC_NOP(); SCL=0; 	
	I2C_STOP();									//�e�XI2C STOP�H��

	I2C_START();								//START Condition
	WriteByte(PCF8574ID|0);	CheckACK();			//Write
	tmp&=~(1<<2);								//Set P2(->EN)=0
	WriteByte(tmp);	CheckACK();					//Write to Port
	tmp|=(1<<2);								//Set P2(->EN)=1
	WriteByte(tmp);	CheckACK();							
	I2C_STOP();									//STOP Condition

	I2C_START();								//START Condition
	WriteByte(PCF8574ID|1);	CheckACK();			//Read
	BusyAC&=0xF0;
	BusyAC|=(ReadByte()>>4);					//Ū��Lo-Nibble
	SDA=1; SDAC=0; 								//�e�XNo_ACK�H��
	SCL=1; GCC_NOP(); SCL=0; 	
	I2C_STOP();									//�e�XI2C STOP�H��

	I2C_START();								//START Condition
	WriteByte(PCF8574ID|0);	CheckACK();			//Write
	tmp&=~(1<<2);								//Set P2(->EN)=0
	WriteByte(tmp);	CheckACK();					//Write to Port
	I2C_STOP();									//STOP Condition
	return BusyAC;								//�^��Address Counter
}
void I2C_START(void)
{	SCL=0; SDA=1;								//�]�w SCL=0, SDA=1
	SCLC=0; SDAC=0; 					   		//SCL/SDA����X�Ҧ�
	SCL=1; pause();								//SCL=1, SDA=1
	SDA=0;										//SDA=0 			     						
	SCL=0;								      	//SCL=0	
}
void I2C_STOP(void)
{	SCL=0; SDA=0;								//�]�w SCL=0, SDA=0
	SDAC=0;								   		//SDA ����X�Ҧ�
	SCL=1;pause();						      	//SCL=1
	SDA=1;pause();						    	//SDA=1
	SCL=0; 										//SCL=0	
}
void CheckACK(void)
{	SDAC=1;							     		//SDA ����J�Ҧ�
	SCL=1; 							     		//�]�w SCL=1
	while(SDA);									//���� ACK(Low)
	SCL=0;					   					//�]�w SCL=0
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SDAC=0;										//SDA����X�Ҧ�
	while(temp!=0)								//�ǰe8�Ӧ줸				
	{	SDA=(I2CData & temp)?1:0; pause();		//�]�w SDA �Ǧ�
		SCL=1; pause(); SCL=0;    				//���� SCL Clock
		temp>>=1;								//�U�@�줸
	}					
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 			//�]�w SDA ����J�Ҧ�
	while(temp!=0)								//����8�Ӧ줸
	{	SCL=1; pause();							//�]�w SCL=1
		if(SDA) I2CData|=temp;					//�����줸��
		SCL=0;									//�]�w SCL=0
		temp>>=1;								//�U�@�줸
	} 
	return I2CData;
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}