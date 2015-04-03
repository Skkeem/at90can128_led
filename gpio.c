#include "gpio.h"
#include <avr/io.h>

void initGpio (void)
{
	/* Set the initial value of PE3 as 1 */
	PORTE |= 1 << PE3;
	/* Set the direction of PE3 as output */
	DDRE |= 1 << DD3;
}
