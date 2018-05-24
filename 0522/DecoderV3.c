// PROGRAM	: IR_testV3.c							      	2017.0701
// FUNCTION	: NEC IR Decoder Demo Program					By Steven
//          : PC5->Buzzer, PC3-> FM9038 O/P
#include "HT66F70A.h"
#include "MyType.H"
#include "Decoder.H"
u8 IRDecoder(u16*,u16*);
void Delayms(u16 del);
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void Display(u16*);
const u8 STR1[]={"CUS. ID:"};
const u8 STR2[]={"Command:"};
void main()
{	u16 adrs, cmd; u8 state,i;
	_wdtc=0b10101111;										//�����ݪ����p�ɾ�
	_tm0c0=0; _tm0c1=0b00110001;							//TM0���k�X��X 
	_tm0al=500&0xFF; _tm0ah=500>>8;							//�]�w���k�X�g��=250us
	_pcs2=0x20;												//���TP0�\���PC6��{
	_tm2c0=0;									  			//TM2: STM fINT=fSYS/4  0.5s
	_ifs2=0b00000000;										//���TP2I�\���PC3��{
	LCMInit();
	LCMWrite(0,0x80); i=0;									//Select Row 1
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);				//���STR1[]�r��
	LCMWrite(0,0xC0);i=0;									//Select Row 2
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);				//���STR2[]�r��
	while(1)
	{	state=IRDecoder(&adrs,&cmd);						//Ū��IR�H��
		switch (state)
		{	case 2:
				LCMWrite(0,0x89); Display(&adrs);			//Select Row 1
				LCMWrite(0,0xC9); Display(&cmd);			//Select Row 2
				break;
			case 1:
				LCMWrite(0,0x8F); LCMWrite(1,'R');
				break;	
			case 0: 
				LCMWrite(0,0xCF); LCMWrite(1,'.');
				break;
		}	
		_t0on=1; Delayms(25); _t0on=0; Delayms(15);			//��X2KHz��i�ú���0.25��
		_t0on=1; Delayms(25); _t0on=0; Delayms(50);			//��X2KHz��i�ú���0.25��
		LCMWrite(0,0x8F); LCMWrite(1,' ');
		LCMWrite(0,0xCF); LCMWrite(1,' ');
	}
}
void Display(u16* ptr)
{	u16	x=0xF000;
	char tmp,i=3;
	do
	{	tmp=(*ptr & x)>>(4*i--);
		tmp=(tmp>9)? tmp+'7': tmp+'0';
		LCMWrite(1,tmp);
	} while((x>>=4)!=0);		
}		
u8 IRDecoder(u16 *ptradrs,u16 *ptrcmd)
{	u32 temp=0,temp1=1;
	u16 TCnt;												//Time Tick Counter, Address
	_tm2rp=80;												//256*80*fINT=10240us(�p�Ƴ̤j����)
	_tm2c1=0b01000000;										//��J�����Ҧ�(���t)
	_t2pf=0; _t2af=0;										//�M��T2AF�BT2PF�X��
//	while(!IR_Pin);											//����SPACE
	while(IR_Pin);											//����Start Bit
	_t2on=1;												//�}�l�p��
	while(!_t2af)											//����STRAT�H������
	{	if(_t2pf) {_t2on=0;	return 0; }						//�Y�W�L�̤j�p�ƭ���A�^��0
	}
	_t2on=0; _t2af=0; _t2pf=0;  							//����TM2, �M��T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//���oSTART�H�����ɶ�����
	if(TCnt<16000) return 0;								//�YStart<8ms�A�^��0 �]���t�X�w��n�٦��� �i�ण�|��9ms �̭��i���RC�_���� ��í�w
	_tm2c1=0b01010000;										//��J�����Ҧ�(�t�t)
	_t2on=1; 
	while(!_t2af)											//����SYNC�H������
	{	if(_t2pf) {_t2on=0;	return 0; }						//�Y�W�L�̤j�p�ƭ���A�^��0
	}
	_t2on=0; _t2af=0; _t2pf=0; 								//����TM2, �M��T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//���oSYNC�H�����ɶ�����
	if(TCnt<4000 || TCnt>9600) return 0; 					//�YSYNC<2ms �� >4.8ms�A�^��0
	if(TCnt<5200) return 1;									//�Y2ms<SYNC<2.6ms�����ƽX�A�^��1
	while(temp1!=0)											//������Ʀ줸
	{	_t2on=1;											//�Ұʭp��
		while(!_t2af);										//���ݦ줸�ɶ�����;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;					//���o�줸�ɶ�
		_t2on=0; _t2af=0;									//����TM2, �M��T2AF
		if(TCnt>3000) temp|=temp1;							//�Y�줸�ɶ�>1500us,�h�줸��1 
		temp1<<=1; 											//����32��bit  �C�K���K�줸�OADDRESS  �U�@�ӧC�K���K �OCOMMAND
		
	}	 
	_t2on=0; 												//����TM2 
	*ptradrs=(u16)temp;									//���oCustom Code
	*ptrcmd=(temp & 0xFFFF0000)>>16; 						//���oCommand
	return 2;												//Command���T�A�^��2
}

void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;					      	//�]�wEN/RW/RS Pin��0
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;				      	//�]�wEN/RW/RS ����X�Ҧ�
	Delayms(40);									    	//LCM Power-On Time
	LCMWrite(0,0x38);								        //8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);								        //Display/Cursor Blinking On
	LCMWrite(0,0x06);								        //Increment, Not Shift
	LCMWrite(0,0x01);								        //Clear LCM Display
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
	LCM_EN=1; GCC_NOP(); LCM_EN=0;							//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=8MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}