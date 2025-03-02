#include <stdint.h>
#include "registers.h"
void delay(unsigned len)
{
	while(len--);
}
void initPorts()
{
	// LED's are on P1.0 and P1.1
	// So make these push-pull outputs
	P1_IOCR0 = (1 << 15) + (1 << 7) + (1 << 23);
	P0_IOCR0 = (1 << 15) + (1 << 7);
	P2_IOCR8 = (1 << 31);
}
int main(void)
{
	initPorts();
	while(1)
	{
	
		P1_OUT = 0x00;
		
		delay(1800000);
		
		P1_OUT |= (1 << 0);
		delay(1800000);
		
		P1_OUT |= (1 << 1);
		delay(1800000);
		
		P1_OUT |= (1 << 2);
    delay(1800000);
		P1_OUT = 0x00;
		
	};
}