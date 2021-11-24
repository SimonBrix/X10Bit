#include "X10Proto.hpp"

X10Proto::X10Proto() 
: X10Bit()
{
	X10Bit::test();
}

void X10Proto::write(int data) 
{
	X10Bit::write(data);
}

void X10Proto::onRecieve() const 
{
	PORTB ^= 0b10000000;
}
