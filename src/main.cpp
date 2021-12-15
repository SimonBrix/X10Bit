#include <avr/io.h>
#include <avr/interrupt.h>

#include "X10Bit.hpp"


extern "C" {
  void __cxa_pure_virtual(void) {};
}

int main()
{
	sei();
	
	X10Bit X10;
	
	uint64_t x = 0b1100010110000111101010101001100110000111101010101001100110001111;
//	uint64_t x = 9113429;

	
	X10.write(x, 64);
	while(1)
	{ }
}