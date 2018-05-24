// PROGRAM	: ADC12WithCal.c					2017.0601
// FUNCTION	: ADC VBG Calibration 				By Steven
#include <HT66F70A.h>
#include "MyType.h"
const u16 VBG=1250;								//Babgap Voltage 1.25V
const u16 VDD=5000;								//Babgap Voltage 5.00V
#define	 SCL		_ph0						//e-Display SCL -> PH0
#define	 SDA		_ph1						//e-Display SDA -> PH1
#define	 SCLC		_phc0						//PH7
#define	 SDAC		_phc1						//PH6
#define	 RES		_ph2						//e-Display RES -> PH2
#define	 RESC		_phc2
#define	 DeviceID	(0x2D<<1)					//e-Display I2C �˸m��}
enum { cmdASC=1,cmdRET,cmdDOT,cmdCLR,cmdPIC,	//e-Display�R�O�w�q			
	   eBUSY=0x55};
enum { White=0xFFFF,Black=0x0000,Red=0xF800, 	//e-Display�C��w�q
	   Green=0x07E0,Blue=0x001F,Yellow=0xFFE0,
	   Magenta=0xF81F,Cyanh=0x7FFF}; 
#define pause()	GCC_DELAY(25)
void I2C_START(void);
void I2C_STOP(void);
void CheckACK(void);
void eDisplayReset(void);
u8 e_Read(void);
void e_Command(u8*);
void eDisplayRet(u8,u8,u8,u8,u16);
void eDisplayPic(u8,u8,u8,u8,const u16* );
void eDisplayASC(u8,u8,u8*,u16);
void VoltDisplay(u8 x,u8 y,u16 ADR,u16 color,_Bool fg);
void e_DataRAM(u8*,u8);
void WriteByte(u8);
u8 ReadByte(void);
void Delayms(u16);	
void main()
{	u16 ADR,ADRVBG,Volt;
	u8 i;
	_wdtc=0b10101111;							//�����ݪ����p�ɾ�
	eDisplayReset();							//Reset eDisplay
	eDisplayRet(0,128,0,128,Blue);				//ø�s�x�ΰϰ�	
	eDisplayASC(15,5,"ADC VBG Test", Black);
	_adcr1=0b01100110;							//VBGEN=1,fSYS/64,VREFS=0,ADRFS=1
	_pas2=0x03;									//�]�wPA4��AN4�\��
	while(1)
	{	_adcr0=0x10;							//ADOFF=0,���VBG 
		_start=1; _start=0;						//�Ұ�AD�ഫ 
		while(_eocb);		
		ADRVBG=((u16)_adrh<<8)+_adrl;			//VBG �|��^5V �άO 3.3V
		_adcr0=0x04;							//ADOFF=0,���AN4	
		for(i=0;i<200;i++)
		{	_start=1; _start=0;					//�Ұ�AD�ഫ
			while(_eocb);						//Wait Conversion Complete
			ADR=((u16)_adrh<<8)+_adrl;			//AN4  �|�ܰ� 0~1024				
			VoltDisplay(20,30,ADR,Blue,0);
			Volt=((u32)ADR*VDD)>>12;			//Volt=(Result*VDD)/4096; VDD=5000
			VoltDisplay(20,50,Volt,Red,1);		
			Volt=((u32)ADR*VBG)/ADRVBG;			//Volt=(VBG*ADR2)/ADR1; VBG=1250  / ADRVBG=_adrh<<8)+_adrl
			VoltDisplay(20,70,Volt,Blue,1);
		}
	}
}
void VoltDisplay(u8 x,u8 y,u16 ADR,u16 color, _Bool fg)
{	u8	temp[10], *ptr;
	ptr=temp;
	*ptr++=ADR/1000+'0'; ADR%=1000;
	if(fg)
	{	*ptr++='.';
		eDisplayASC(x+40,y," volt",color);		//���
	}
	*ptr++=ADR/100+'0'; ADR%=100;
	*ptr++=ADR/10+'0'; *ptr++=ADR%10+'0';
	*ptr=0;
	eDisplayASC(x,y,temp,color);				//���
}
void eDisplayReset(void)
{	RES=0; RESC=0;
	Delayms(10);
	RES=1;
	Delayms(3000);
}
void eDisplayClear(u8 x,u8 xSize,u8 y,u8 ySize)
{	u8 Buffer[8]={cmdCLR,0,4,0,0,0,0,0};			//�˸��R�O
	e_Command(Buffer);								//�e�Xe-Display�M���R�O
	Buffer[0]=x; Buffer[1]=xSize;					//�˸��Ѽ�
	Buffer[2]=y; Buffer[3]=ySize;
	e_DataRAM(Buffer,4);							//�e�Xx/y�y�а_�I�Ϊ���
	I2C_STOP();										//�e�XI2C STOP�H�� 
}
void eDisplayASC(u8 x, u8 y,u8 *ptr, u16 color)
{	u8 i=6,Buffer[22];
	while(*ptr) {Buffer[i]=*ptr++;i++;};
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=i;		//�˸��R�O
	e_Command(Buffer);								//�e�X�R�O
	Buffer[0]=x; Buffer[1]=y;						//�˸��Ѽ�
	Buffer[2]=color>>8;	Buffer[3]=(u8)color;
	Buffer[4]=0xFF;	Buffer[5]=0xFF;
	e_DataRAM(Buffer,i);							//�e�X�Ѽ�
	I2C_STOP();										//�e�XI2C STOP�H�� 
}
void eDisplayRet(u8 x, u8 xSize,u8 y, u8 ySize, u16 color)
{	u8 Buffer[8]={cmdRET,0,6,0,0,0,0,0};		//�˸��R�O
	e_Command(Buffer);							//�e�X�R�O
	Buffer[0]=x; Buffer[1]=xSize;				//�˸��Ѽ�
	Buffer[2]=y; Buffer[3]=ySize;
	Buffer[4]=color>>8;	Buffer[5]=(u8)color;	
	e_DataRAM(Buffer,6);						//�e�X�Ѽ�
	I2C_STOP();									//�e�XI2C STOP�H�� 
}
void e_Command(u8* ptr)
{	u8 i;
	while(e_Read()==eBUSY); 						//�ˬde-Display���L���A	
	I2C_START();
	WriteByte(DeviceID|0); CheckACK();				//�e�XDeviceID_W�õ��ݦ^��ACK
	for(i=0;i<8;i++)								//e-Display�R�O���שT�w��8
	{	WriteByte(*ptr++); CheckACK();				//�vByte�e�X�R�O�õ��ݦ^��ACK
	}
}
void e_DataRAM(u8* ptr,u8 Length)
{	u8 i;
	for(i=0;i<Length;i++)
	{	WriteByte(*ptr++); CheckACK();				//�vByte�e�XRAM��ƨõ��ݦ^��ACK
	}
}
u8 e_Read(void)
{	u8 retval;
	I2C_START();									//�e�XI2C START�H�� 
	WriteByte(DeviceID|1); CheckACK();				//�e�XDeviceID_R�õ��ݦ^��ACK
	retval=ReadByte();								//Ū���˸m�^�ǭ�
	SDA=1; SDAC=0; 									//�e�XNO_ACK�H��
	SCL=1; pause(); SCL=0; 	
	I2C_STOP();										//�e�XI2C STOP�H��
	return retval;
}
void I2C_START(void)
{	SCL=0; SDA=0;									//�]�w SCL=0, SDA=0
	SCLC=0; SDAC=0; 					   			//SCL/SDA����X�Ҧ�
	SCL=1; SDA=1; pause();							//SCL=1, SDA=1
	SDA=0;											//SDA=0 			     						
	SCL=0;								      		//SCL=0	
}
void I2C_STOP(void)
{	SCL=0; SDA=0;									//�]�w SCL=0, SDA=0
	SDAC=0;								   			//SDA ����X�Ҧ�
	SCL=1;								      		//SCL=1
	SDA=1;								    		//SDA=1
	SCL=0; 											//SCL=0	
}
void CheckACK(void)
{	SDAC=1;							     			//SDA ����J�Ҧ�
	SCL=1; 							     			//�]�w SCL=1,
	while(SDA);										//���� ACK(Low)
	SCL=0;					   						//�]�w SCL=0
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SCL=0; SDAC=0;									//SCL=0, SDA����X�Ҧ�
	do								
	{	SDA=(I2CData & temp)?1:0; pause();			//�]�w SDA �Ǧ�
		SCL=1; pause(); SCL=0;    					//���� SCL Clock
		temp>>=1;									//�U�@�줸
	} while (temp!=0);								//�ǰe8�Ӧ줸
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				//�]�w SDA ����J�Ҧ�
	do
	{	SCL=1; pause();								//�]�w SCL=1
		if(SDA) I2CData|=temp;						//�����줸��
		SCL=0;										//�]�w SCL=0
		temp>>=1;									//�U�@�줸
	} while (temp!=0);								//����8�Ӧ줸
	return I2CData;
}
void Delayms(u16 del)								//@fSYS=8MH,����del*ms				
{	u16 i;							
	for(i=0;i<del;i++) GCC_DELAY(2000);				//����del*2000���O�g��			
}
