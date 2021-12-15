#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Data.hpp"

class X10Bit
{
public:
	X10Bit();
	~X10Bit();
	
	void write(Data &bitData);
	bool isSending();
	//void simulate(Data bits);
	bool getisSending_flag();
	void setisSending_flag(bool flag);
	virtual void onReceiveBit(bool bit);
private:
	bool isSending_flag;
};
