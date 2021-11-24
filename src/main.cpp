#include <avr/io.h>
#include <avr/interrupt.h>

#include "X10Proto.hpp"

extern "C" {
  void __cxa_pure_virtual(void) {};
}

int main()
{
	sei();

	DDRB = 0xff;
	PORTB = 0x00;

	X10Proto x10;
	//x10.write(0b111001010);
	while(1)
	{}
}