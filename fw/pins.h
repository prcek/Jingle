
#define BUZ 0
#define LED 1
#define SPK 2
#define BTN 3

#define LED_ON PORTB |= _BV(LED)
#define LED_OFF PORTB &= ~_BV(LED)
#define LED_SETUP DDRB |= _BV(LED) 


#define SPK_ON PORTB |= _BV(SPK)
#define SPK_OFF PORTB &= ~_BV(SPK)
#define SPK_SETUP DDRB |= _BV(SPK)


#define BTN_READ (PINB & _BV(BTN))
#define BTN_SETUP  DDRB &= ~_BV(BTN); PORTB |= _BV(BTN)


#define BUZ_READ (PINB & _BV(BUZ))
#define BUZ_SETUP DDRB &= ~_BV(BUZ); PORTB |= _BV(BUZ)


