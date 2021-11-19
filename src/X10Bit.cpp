#include "X10Bit.hpp"

static int s_data;

ISR(INT2_vect)
{
	PORTB = (1 & s_data);
	s_data = s_data >> 1;
}

X10Bit::X10Bit(int inf) 
{
	EIMSK |= (1<<INT2);
	EICRA |= (1<<ISC21);
}

void X10Bit::write(int data) 
{
	s_data = data;
}