#include "timer2.h"

void initTimer2 (int msec)
{
	//turn off timer irq
	//set global variable to msec
	//stop timer initialize TCCR2A
	//set waveform generation mode
	//set normal port operation
	//clear async register
	//select clock from io clock
	//turn on timer irq, slow down io clock by prescaler
	//clear timercnt
	//set tccr2a0 to set timer in msec
}
