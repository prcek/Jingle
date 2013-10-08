#include <avr/io.h>
#include <util/delay.h>
#include "pitches.h"

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

//#include "melody_mario.h"
#include "melody_bond.h"

void delay_us(long d) {
	while(d>100) {
		_delay_us(100);
		d-=100;	
	}
	while(d>10) {
		_delay_us(10);
		d-=10;	
	}
	while(d>0) {
		_delay_us(1);
		d-=1;
	}
}
void buzz(long frequency, long length) {


  if (frequency) {
	  long delayValue = 1000000/frequency/2; 
	  long numCycles = frequency * length/ 1000; 
 	 for (long i=0; i < numCycles; i++){ 
  	  SPK_ON;
   	 delay_us(delayValue); 
   	 SPK_OFF;
   	 delay_us(delayValue); 
 	 }
 } else {
	  long numCycles = length; 
 	  for (long i=0; i < numCycles; i++){ 
		_delay_ms(1);
	  }
 }
}




void play() {
	for (int thisNote = 0; thisNote < size; thisNote++) {

       		int noteDuration = 1000/tempo[thisNote];

	      	buzz(melody[thisNote],noteDuration);

       	//	int pauseBetweenNotes = noteDuration * 1.30;
       	//	delay(pauseBetweenNotes);

	}
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
		play();
    		flash_led(2);
        }	
        if (PINB & _BV(BUZ)) {
	//	LED_ON;
        } else {
		LED_ON;
//		beep(1,5);
		play();
		LED_OFF;
//		beep(1,5);
        }	
 
    }
    return 0;   /* never reached */
}
