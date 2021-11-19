#include <avr/io.h>
#include <avr/interrupt.h>


#include "X10Bit.hpp"

int main()
{
	sei();

	DDRB = 0xff;
	PORTB = 0x00;

	X10Bit x10(10);
	x10.write(0b10101);
	while(1)
	{}
}