#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/power.h>

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
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();
	sleep_disable();
}


int main(void)
{

	led_setup();
	led_flash(5);




	spk_setup();

	BTN_SETUP;
	BUZ_SETUP;

	power_setup();

    for(;;){
    	led_fadein();
		led_fadeout();
        if (! BTN_READ ) {
			led_flash(2);
			spk_play();
    		led_flash(2);
        }	
        if (! BUZ_READ ) {
			led_on();
			spk_play();
			led_fadeout();
        }	
 		sleep();

    }
    return 0;   /* never reached */
}
