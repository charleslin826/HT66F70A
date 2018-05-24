#include "MyType.h"	
//#define TinyRGB						//RGB模組若是大顆的，註解此行

#ifdef TinyRGB
	enum {Green=1, Red, Blue, Alpha};   //此行不管 因為這是硬體設計不同時才用的 
#else
	enum {Red=1, Green, Blue, Alpha};
#endif

#define  KeyPort	_pe
#define  KeyPortC	_pec
#define  KeyPortPU	_pepu

#define	_TX			_pa1			//連接至藍芽RX (Yellow)
#define	_TXC		_pac1
#define	_RX			_pa3			//連接至藍芽TX (Blue)
#define	_RXC		_pac3			
#define	fSYS		8000000	
#define	BaudRate	19200	
#define	BITC		(fSYS/BaudRate)	//Bit Interval Time Constant
