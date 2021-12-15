#include <avr/io.h>
#include <avr/interrupt.h>

#include "X10Bit.hpp"
#define F_CPU 16000000
#include <util/delay.h>


extern "C" {
  void __cxa_pure_virtual(void) {};
}

int main()
{
	sei();
	
	DDRE |= (1<<PE4)|(1<<PE3);
	PORTE &= ~((1<<PE4)|(1<<PE3)); 
	
	X10Bit X10;
	
	//uint64_t x = 0b11000111;
	//uint64_t x = 0b1100010110000111101010101001100110000111101010101001100110001111;
//	uint64_t x = 9113429;
	uint64_t x = 0xaaaaaaaaaaaaaaaa;

	
	X10.write(x, 64);
	while(1)
	{	}
}