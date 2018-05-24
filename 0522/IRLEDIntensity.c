// PROGRAM	: IRLedIntensity.c							2017.07.01
// FUNCTION	: LED Control By IR Remote Controller(NEC)	By Steven
//            Software PWM By Using Timer/Counter Operation
/* Note		: When Increase PWM Channels, The IRDevoder() may
			  Fault Due to the ISR Execution Cycles. Changing
			  the TM3 Comapre-match Time to 200us and Period	   
	            to 1000 could solve this problem! */ 
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
void LED(u16);
#define	Period 200											//PWM�P���`��
volatile u8 PCnt,Bcnt[4]={10,10,10,10};
void main()
  {	u16 adrs,cmd;
	u8 state,i;
	_wdtc=0b10101111;										//�����ݪ����p�ɾ�
	LEDPort|=0x0F; LEDPortC&=0xF0;							//***
	_tm0c0=0; _tm0c1=0b00110001;							//TM0���k�X��X 
	_tm0al=500&0xFF; _tm0ah=500>>8;							//�]�w���k�X�g��=250us
	_pcs2=0x20;												//���TP0�\���PC5��{
	_tm2c0=0;									  			//TM2: STM fINT=fSYS/4
	_ifs2=0b00000000;									  	//TP2I -> PC3
	PCnt=Period; 	
	_tm3c0=0x08; _tm3c1=0b11000001;							//TM3�p��/�p�ƼҦ� 
	_tm3al=200%256; _tm3ah=200>>8;							//�]�w���k�X�g��=100us
	_t3ae=1; _mf2e=1; _emi=1;
	LCMInit();
	LCMWrite(0,0x80); i=0;									//Select Row 1
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);				//���STR1[]�r��
	LCMWrite(0,0xC0);i=0;									//Select Row 2
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);				//���STR2[]�r��
	while(1)
	{	state=IRDecoder(&adrs,&cmd);						//Ū��IR�H��
		if(state==2 && adrs==CID)
		{	_t0on=1; LED(cmd); 
			LCMWrite(0,0x89); Display(&adrs);				//Select Row 1
			LCMWrite(0,0xC9); Display(&cmd);				//Select Row 2
			Delayms(20); 									//��X2KHz��i
		}
		else if(state==1 && adrs==CID)
		{	_t0on=1; LED(cmd);								//��X2KHz��i
			LCMWrite(0,0x90); LCMWrite(1,'R');
			 Delayms(15);									
		}	
		LCMWrite(0,0x90); LCMWrite(1,' ');
		_t0on=0;
	}
}
void LED(u16 cmd)
{	switch(cmd)
	{	case LED0:
			if(Bcnt[0]<Period) Bcnt[0]+=5;
			break;
		case LED1:
			if(Bcnt[1]<Period) Bcnt[1]+=5;
			break;
		case LED2:
			if(Bcnt[2]<Period) Bcnt[2]+=5;
			break;
		case LED3:
			if(Bcnt[3]<Period) Bcnt[3]+=5;
			break;			
		case LED0_:
			if(Bcnt[0]>=5) Bcnt[0]-=5;
			break;
		case LED1_:
			if(Bcnt[1]>=5) Bcnt[1]-=5;
			break;
		case LED2_:
			if(Bcnt[2]>=5) Bcnt[2]-=5;
			break;
		case LED3_:
			if(Bcnt[3]>=5) Bcnt[3]-=5;;
			break;					
	}
}
DEFINE_ISR(ISR_TM3,0x20)
{	static u8 cnt[4];								//�ոխY���[static���G�p��?
	if(PCnt--==0)									//�P�_PWM�P���O�_�w����
	{	PCnt=Period; 								//�O�A�٭�Ҧ���
		cnt[0]=Bcnt[0]; cnt[1]=Bcnt[1];
		cnt[2]=Bcnt[2]; cnt[3]=Bcnt[3];
		pLED0=(Bcnt[0]==0)? 1 : 0;					//��Duty�]�w�}���l���A
		pLED1=(Bcnt[1]==0)? 1 : 0;					//��Duty�]�w�}���l���A
		pLED2=(Bcnt[2]==0)? 1 : 0;					//��Duty�]�w�}���l���A
		pLED3=(Bcnt[3]==0)? 1 : 0;					//��Duty�]�w�}���l���A
	}
	else
	{	if(cnt[0]!=0) cnt[0]-- ; else pLED0=1; 		//�P�_Duty�Y�O�����]�w���}��0
		if(cnt[1]!=0) cnt[1]-- ; else pLED1=1;
		if(cnt[2]!=0) cnt[2]-- ; else pLED2=1;
		if(cnt[3]!=0) cnt[3]-- ; else pLED3=1;
	}
	_t3af=0;				  						//�M��T3AF�X��
}
void Display(u16 *ptr)
{	u16	x=0xF000;
	u8 tmp,i=3;
	do
	{	tmp=(*ptr & x)>>(4*i--);
		tmp=(tmp>9)? tmp+'7': tmp+'0';
		LCMWrite(1,tmp);
		if(i==1) LCMWrite(1,' ');
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
	{	if(_t2pf) {_t2on=0; return 0; }						//�Y�W�L�̤j�p�ƭ���A�^��0
	}
	_t2on=0; _t2af=0; _t2pf=0;  							//����TM2, �M��T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//���oSTART�H�����ɶ�����
	if(TCnt<16000) {_emi=1; return 0;}						//�YStart<8ms�A�^��0
	_tm2c1=0b01010000;										//��J�����Ҧ�(�t�t)
	_t2on=1; 
	while(!_t2af)											//����SYNC�H������
	{	if(_t2pf) {_t2on=0; return 0; }						//�Y�W�L�̤j�p�ƭ���A�^��0
	}
	_t2on=0; _t2af=0; _t2pf=0; 								//����TM2, �M��T2AF
	TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;						//���oSYNC�H�����ɶ�����
	if(TCnt<4000 || TCnt>9600) return 0;					//�YSYNC<2ms �� >4.8ms�A�^��0
	if(TCnt<5200)  return 1;								//�Y2ms<SYNC<2.6ms�����ƽX�A�^��1
	while(temp1!=0)											//������Ʀ줸
	{	_t2on=1;											//�Ұʭp��
		while(!_t2af);										//���ݦ줸�ɶ�����;
		TCnt=_tm2ah; TCnt=(TCnt<<8)|_tm2al;					//���o�줸�ɶ�
		_t2on=0; _t2af=0;									//����TM2, �M��T2AF
		if(TCnt>3000) temp=temp|temp1;						//�Y�줸�ɶ�>1500us,�h�줸��1 
		temp1<<=1; 
	}	 
	_t2on=0; 												//����TM2 
	*ptradrs=(u16)temp;										//���oCustom Code
	*ptrcmd=(temp & 0xFFFF0000)>>16; 						//���oCommand
	return 2;												//Command���T�A�^��2
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	            			//�]�wEN/RW/RS�}�쬰�C�q��
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	         			//�]�wEN/RW/RS�}�쬰��X�Ҧ�
	GCC_DELAY(50000);							         	//LCM Power-On Time
	LCMWrite(0,0x38);							      		//COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);						         		//COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);							      		//COMD:Increment, Not Shift
	LCMWrite(0,0x01);							      		//COMD:Clear LCM Display
}	
u8 LCMWrite(_Bool DCFlag,u8 CD)
{	u8 BusyAC;
	LCM_DataPortC=0b11111111;								//�W��Port����J�Ҧ�
	LCM_RS=0; LCM_RW=1;										//RS=0,RW=1 (Read IR)
	_nop(); 
	do
	{	LCM_EN=1; _nop();							   		//EN=1
		BusyAC=LCM_DataPort;						   		//Loop Until BF=0
		LCM_EN=0;									   		//EN=0	
	} while (BusyAC&0b10000000);
	LCM_DataPortC=0;								   		//�W��Port����X�Ҧ�
	LCM_RW=0;										   		//RW=0 (Write)
	LCM_RS=DCFlag;									   		//Set RS State By DCFlag
	LCM_DataPort=CD;								   		//Sent Command or Data
	LCM_EN=1; _nop(); LCM_EN=0;			      				//EN=1
	return BusyAC;	
}
void Delayms(u16 del)
{	u16 i;													//@fSYS=8MH,����del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}
