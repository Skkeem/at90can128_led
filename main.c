#include "serial.h"
#include "timer2.h"
#include <avr/interrupt.h>

#define BAUD 9600
#define UBRR_VAL (F_CPU / (16UL * BAUD)) - 1

#define INTERVAL_MSEC 250

int main(void)
{
    initUart(UBRR_VAL);
	initTimer2(INTERVAL_MSEC);
	sei();

	while (1)
		;

	return -1;
}
