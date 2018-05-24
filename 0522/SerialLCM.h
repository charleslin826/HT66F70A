// 2017.1023    By Steven
#define	 SCL		_pa6						//SCL -> PA6
#define	 SDA		_pa7						//SDA -> PA7
#define	 SCLC		_pac6						//PAC6
#define	 SDAC		_pac7						//PAC7
//#define	 PCF8574ID	(0x27<<1)				//I2C 裝置位址(for 8574 with A2A1A0=111)
#define	 PCF8574ID	(0x3F<<1)					//I2C 裝置位址(for 8574A with A2A1A0=111)
#define pause()	GCC_NOP() //GCC_DELAY(25)
u8 LCMWrite(_Bool fgCD,u8 CD);
u8 LCMRead(_Bool fgCD);
void I2C_START(void);
void I2C_STOP(void);
void CheckACK(void);
void WriteByte(u8);
u8 ReadByte(void);
void Delayms(u16 del);