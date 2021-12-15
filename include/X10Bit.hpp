#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

class X10Bit
{
public:
	
	X10Bit();
	~X10Bit();
	void write(uint64_t , uint8_t);
	bool isSending();
	//void simulate(Data bits);
	virtual void onReceiveBit(bool bit);
private:
	bool isSending_flag;
};
