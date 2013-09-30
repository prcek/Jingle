#include <avr/io.h>
#include <util/delay.h>


#define BUZ 0
#define LED 1
#define SPK 2
#define BTN 3

void flash_led(int count) {
	while((count--)>0) {
    	PORTB |= _BV(LED);
		_delay_ms(50);
    	PORTB &= ~_BV(LED);
		_delay_ms(50);
	}
}

#define LED_ON PORTB |= _BV(LED)
#define LED_OFF PORTB &= ~_BV(LED)

#define SPK_ON PORTB |= _BV(SPK)
#define SPK_OFF PORTB &= ~_BV(SPK)


void beep(int f, int d) {
	while((d--)>0) {
		SPK_ON;
		int f2 = f;
		while(f2--) _delay_ms(1);
		SPK_OFF;
		f2 = f;
		while(f2--) _delay_ms(1);
	}
}


int main2(void)
{
    DDRB |= _BV(LED);
    LED_ON;
}
int main(void)
{
    DDRB |= _BV(LED);

    flash_led(5);


    DDRB &= ~_BV(BTN); //INPUT
    PORTB |= _BV(BTN); //PULLUP

    DDRB &= ~_BV(BUZ); //INPUT
    PORTB |= _BV(BUZ); //PULLUP

   	
    DDRB |= _BV(SPK); //OUT


    for(;;){
	LED_OFF;
        if (PINB & _BV(BTN)) {
	//	LED_ON;
        } else {
    		flash_led(2);
		beep(1,5);
    		flash_led(2);
        }	
        if (PINB & _BV(BUZ)) {
	//	LED_ON;
        } else {
		LED_ON;
		beep(1,5);
		LED_OFF;
		beep(1,5);
        }	
 
    }
    return 0;   /* never reached */
}
