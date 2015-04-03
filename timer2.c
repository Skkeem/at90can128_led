#include "timer2.h"
#include "serial.h"

static int interval;
static volatile int tick;

void initTimer2 (int msec)
{
	//ASSR(AS2)�� TCNT2, OCR2A, TCCR2A���� ���� �Ǿ�� ��. 0���� �ؾ���. EXCLCK�� 0

	//TIMSK�� ��� OCIE�� 1�� �ؾ� compare match interrupt�Ͼ TOIE�� 1���ؾ� overflow interrupt

	//TIFR�� OCF, TOV�� ���ͷ�Ʈ ������ �Ǵ� 1�� ���� ������

	//GTCCR�� PSR2 bit�� prescaler�� reset��. �ϵ��� �ٷ� ����. �ٵ� TSM�� 1�̸� �ϵ��� ó������.
	//GTCCR�� TSM. 0���� ����

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
