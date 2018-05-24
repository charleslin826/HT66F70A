//Lab02_10    
/*   Basic C Program 
     switch case Demo*/
#include <HT66F70A.h>					     
#include "MyType.h"
#define LED_Port	_pc					//Port C Data Register
#define LED_PortC	_pcc				//Port C Control Register		
void main()
{	u8 x=0;
	_wdtc=0b10101111;
	LED_Port=0; LED_PortC=0;   //0000 0000全亮  設定PCC方向
	while(1)
	{	switch (x)
		{	case 1: LED_Port=~0x01; // ( ~是取反向/補數的意思  就是0000 0000 變成 1111 1111 )(!是邏輯反向 真變假 假變真) 
		/*   ~0x01  = 0000 0001取反向 = 1111 1110 >>>只亮第1顆 */
					break;
			case 2: LED_Port=~0x02;
		/*   ~0x02  = 0000 0010取反向 = 1111 1101>>>只亮第2顆 */
					break;					
			case 3: LED_Port=~0x04;
		/*   ~0x04  = 0000 0100取反向 = 1111 1011>>>只亮第3顆 */
					break;
			case 4: LED_Port=~(1<<3);	//將1左移三位元
		/*   ~0x04  = 0000 0001左移三位元 = 1111 0111>>>只亮第4顆 */
					break;
			case 5: LED_Port=~(1<<4);
					break;
			case 6: LED_Port=~(1<<5);
					break;
			case 7: LED_Port=~(1<<6);
					break;
			case 8: LED_Port=~(1<<7);
					break;
			default:					//x!=1~8時執行本段
					x=0;
		}
		x+=1;
		GCC_DELAY(263690);		//延遲0~263690個指令週期 此為盛群自定義的 可看build-in.h
	}
}	