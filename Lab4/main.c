//#include <avr/io.h>
//#include <avr/interrupt.h>
//
//ISR(USART_RX_vect)
//{
	//PORTB = UDR0;
//}
//
//int main(void)
//{
	//
	//DDRB = 0xFF;
	//UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
	//UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	//UBRR0L = 0x33;
	//sei();
    //while (1);
	//return 0;
//}
//

#define F_CPU 1600000000ul
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#define USART_BAUDRATE 4800
#define UBRR_VALUE (((F_CPU/(USART_BAUDRATE * 16UL)))-1)

void usart_init(){
	// initialize USART (must call this before using it)
	//UBRR0 = UBRR_VALUE; // set baud rate
	UCSR0B |= (1 << TXEN0); //enable TX
	UCSR0B |= (1 << RXEN0); //enable RX
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // no parity, 1 stop bit, 8-bit data
}

void usart_send(unsigned char data) {
	// send a single character via USART
	while(!(UCSR0A&(1<<UDRE0))){}; //wait while previous byte is completed
	UDR0 = data; // Transmit data
}

int main(void){
	char str[] = "We are ready";
	unsigned char strLength = 10;
	unsigned char i = 0;

	usart_init();

	while(1) {
		usart_send(str[i++]);
		if (i >= strLength) {
			i = 0;
			break;
		}
	}

	return 0;
}