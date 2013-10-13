#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/interrupt.h>

#include "led.h"
#include "spk.h"
#include "pins.h"


void power_setup() {
//	power_adc_disable();
//	power_timer0_disable();
//	power_timer1_disable();
//	power_usi_disable();

	power_all_disable();
}

void sleep() {
	sei();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();
	sleep_disable();
	cli();
}

void init_interupts() {
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(BUZ) | _BV(BTN);
}

ISR(PCINT0_vect) {
}

int main(void)
{

	led_setup();
	led_flash(1);




	spk_setup();


	BTN_SETUP;
	BUZ_SETUP;

		
	init_interupts();

	power_setup();

    for(;;){
    	led_fadein();
	_delay_ms(100);
	led_fadeout();
 	sleep();
        while (! BTN_READ ) {
		led_on();
		spk_beep(200);
		_delay_ms(100);
		led_off();
        }	
        while (! BUZ_READ ) {
		led_on();
		spk_beep(200);
		_delay_ms(100);
		led_on();
        }	

    }
    return 0;   /* never reached */
}
