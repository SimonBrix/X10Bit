#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

/// <summary> Utilizes timers and interrupts to send X10 data </summary>
class X10Bit
{
public:
	/// <summary> Constructs a new X10Bit object </summary>
	X10Bit();
	~X10Bit();
	void write(uint64_t , uint8_t);
	bool isSending();
	//void simulate(Data bits);
	virtual void onReceiveBit(bool bit);
private:
	bool isSending_flag;
};
