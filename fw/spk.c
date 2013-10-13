#include <avr/io.h>
#include <util/delay.h>
#include "pins.h"
#include "spk.h"
#include "spk_pitches.h"

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



void spk_beep(long ms) {
	ms = (ms * 440) / 1000;
 	 for (long i=0; i < ms; i++){ 
  	 	SPK_ON;
		_delay_us(1136);
   		SPK_OFF;
		_delay_us(1136);
 	 }
 
}

void spk_buzz(long frequency, long length) {


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
void spk_setup() {
	SPK_SETUP;
}



#include "melody_bond.h"


void spk_play() {
	for (int thisNote = 0; thisNote < size; thisNote++) {

       		int noteDuration = 1000/tempo[thisNote];

	      	spk_buzz(melody[thisNote],noteDuration);

       	//	int pauseBetweenNotes = noteDuration * 1.30;
       	//	delay(pauseBetweenNotes);

	}
}



