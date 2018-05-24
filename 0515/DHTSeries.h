#include "HT66F70A.h"
#include "Mytype.h"
#define	fSYS		8000000					//System Frequency
#define DHT22								//Mark this Line When DHT11 is Used!!								
#ifdef 	DHT22
	#define DHTStartTC	(1*(fSYS/(4*1000)))	//DHT22 Start Signal Time Constant :1ms
#else	
	#define DHTStartTC	(20*(fSYS/(4*1000)))//DHT11 Start Signal Time Constant :20ms
#endif
	
#define DHTSSDTC	(160*(fSYS/(4*1000000)))//DHT Start Send Data Signal Time Constant:160us
#define DHTBit0TC	(80*(fSYS/(4*1000000)))	//DHT Data=0 Signal Time Constant:80us

#define	pDHT		_pd1					//Connect to DHT Signal Pin	
#define	pDHTC		_pdc1
#define	pDHTPU		_pdpu1

#define LCM_EN			_ph2	//PE.0
#define LCM_ENC			_phc2	//PEC.0
#define LCM_RW			_ph1	//PE.1
#define LCM_RWC			_phc1	//PEC.1
#define LCM_RS			_ph0	//PE.2
#define LCM_RSC			_phc0	//PEC.2
#define LCM_DataPort	_pg
#define LCM_DataPortC	_pgc
