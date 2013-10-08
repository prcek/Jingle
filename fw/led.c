#include <avr/io.h>
#include <util/delay.h>


#include "led.h"
#include "pins.h"

void led_setup() {
	LED_SETUP;
}
void led_flash(int count) {
	while((count--)>0) {
		LED_ON;
		_delay_ms(50);
		LED_OFF;
		_delay_ms(50);
	}
}
void led_on() {
	LED_ON;
}

void led_off(){
	LED_OFF;
}

void led_fadein() {
	LED_ON; //TODO
}

void led_fadeout() {
	LED_OFF; //TODO
}

void led_fadeflash(int count) {
	while((count--)>0) {
		led_fadein();
		_delay_ms(50);
		led_fadeout();
		_delay_ms(50);
	}

}
