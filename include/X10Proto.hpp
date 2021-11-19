#pragma once

#include "X10Bit.hpp"

class X10Proto : public X10Bit
{
public:
	X10Proto();
	~X10Proto();
	virtual void write(int data) override;
	virtual void onRecieve() const override;
};
