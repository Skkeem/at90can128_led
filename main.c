#include "serial.h"
#include "timer2.h"

#define BAUD 9600
#define UBRR_VAL (F_CPU / (16UL * BAUD)) - 1

#define PERIOD 250

int main(void)
{
    initUart(UBRR_VAL);
	initTimer2(PERIOD);

	while (1)
		;

	return -1;
}
