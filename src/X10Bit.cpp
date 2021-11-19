#include "X10Bit.hpp"

static int s_data;

static X10Bit* X10Ptr = 0;

ISR(INT2_vect)
{
	if ((1 & s_data) == 1) 
	{
		PORTB |= 0b00000001;
	}
	else
	{
		PORTB &= 0b11111110;
	}
	
	s_data = s_data >> 1;
	X10Ptr->test();

}

X10Bit::X10Bit() 
{
	EIMSK |= (1<<INT2);
	EICRA |= (1<<ISC21);
	X10Ptr = this;
}

void X10Bit::write(int data) 
{
	//s_data = data;
	onRecieve();
}

void X10Bit::onRecieve() const
{
	//PORTB ^= 0b10000000;
}

void X10Bit::test() const
{
	onRecieve();
}