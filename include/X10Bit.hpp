#pragma once
#include "Data.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>

class X10Bit
{
public:
	X10Bit(int inf);
	~X10Bit();
	void write(int data);
	virtual void onRecieve(bool bit) const;
};
