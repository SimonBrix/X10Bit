#pragma once
#include "Data.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>

class X10Bit
{
public:
	X10Bit();
	~X10Bit();
	virtual void write(int data);
	virtual void onRecieve() const;
	void test() const;

};
