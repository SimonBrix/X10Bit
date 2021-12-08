#pragma once

#include "X10Bit.hpp"

class Coder : public X10Bit
{
public:
	Coder();
	~Coder();

	void onReceiveBit(const bool bit) override;
};
