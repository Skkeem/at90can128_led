#include "timer2.h"
#include "serial.h"

static int interval;
static volatile int tick;

void initTimer2 (int msec)
{
	//ASSR(AS2)가 TCNT2, OCR2A, TCCR2A보다 먼저 되어야 함. 0으로 해야함. EXCLCK도 0

	//TIMSK의 경우 OCIE를 1로 해야 compare match interrupt일어남 TOIE를 1로해야 overflow interrupt

	//TIFR의 OCF, TOV는 인터럽트 실행후 또는 1을 쓸때 없어짐

	//GTCCR의 PSR2 bit이 prescaler를 reset함. 하드웨어가 바로 없앰. 근데 TSM이 1이면 하드웨어가 처리안함.
	//GTCCR의 TSM. 0으로 놔둠

    /* Set interval to msec */
	interval = msec;
	
    /*
     * Clock source : Clk_io / 1024. This scales 16MHz down to 15625Hz (which is roughly 16KHz)
	 * OC2A disconnected
     * Run timer2 in CTC mode
	 * Output compare is set to 16 in order to tick output compare interrupt with 1KHz frequency, ie tick every 1ms.  
     * Enable output compare interrupt only
     */
	OCR2A = 16;
	TIMSK2 = 1 << OCIE2A; //0x02
	TCCR2A = (1 << WGM21) | (7 << CS20); //0x0f
}

ISR (TIMER2_COMP_vect)
{
	/* Increase the tick every 1ms */
	tick++;
	if (tick >= interval) {
		putChar('1');
		PINE |= 1 << PE3; // or PORTE ^= 1 << PE3;
		tick = 0;
	}
}
