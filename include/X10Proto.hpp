#pragma once

#include "X10Bit.hpp"

class X10Proto : protected X10Bit
{
public:
	X10Proto();
	~X10Proto();
	void write(int data) override;
	void onRecieve() const override;
};
