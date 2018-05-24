#include "MyType.h"
#define	 LCM_RS			_ph0			//PH0
#define  LCM_RW			_ph1			//PH1
#define  LCM_EN			_ph2			//PH2
#define  LCM_RSC		_phc0			//PHC0
#define  LCM_RWC		_phc1			//PHC1
#define  LCM_ENC		_phc2			//PHC2
#define  LCM_DataPort	_pg
#define  LCM_DataPortC	_pgc

#define  KeyPort		_pe				//4x4 Keypad -> PE[7:0]
#define	 KeyPortC		_pec			//PEC
#define	 KeyPortPU		_pepu			//PEPU

#define	 SCL			_pa6			//HT24LC32 SCL -> PA6
#define	 SDA			_pa7			//HT24LC32 SDA -> PA7
#define	 SCLC			_pac6			//PAC6
#define	 SDAC			_pac7			//PAC7

#define	 A210			0b000			//須與AMAEB上的設定吻合
#define	 DeviceID		0xA0|(A210<<1)	//I2C 裝置位址

const u8 Str1[]={"Input Code:"};
const u8 Str2[]={"Save  Code:"};
const u8 Str3[]={"Good Job!"};
const u8 Str4[]={"Sorry!!"};
const u8 Str5[]={"Save OK!"};
void LCMInit(void);
u8 LCMWrite(_Bool,u8);
u8 ScanKey(void);
u8 Get3Keys(u8*);
void Verify(u8*,u8*);
void I2C_START(void);
void I2C_STOP(void);
void CheckACK(void);
void I2C_DeviceSelect(_Bool);
void I2C_SetAddress(u16);
void I2C_SeqRandomRead(u16,u8*,u8);
void I2C_PageWrite(u16,u8*,u8);
void WriteByte(u8);
u8 ReadByte(void);
void Delayms(u16);