#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

class X10Bit
{
public:
	X10Bit();
	~X10Bit();
	void write(int, int);
	bool isSending();
	//void simulate(Data bits);
	virtual void onReceiveBit(bool bit);
private:
	bool isSending_flag;
};
