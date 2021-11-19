#pragma once
#include <stdint.h>

class Data
{
public:
	Data(void* dataPtr, uint8_t bitCount);

	void setData(void* dataPtr, uint8_t bitCount);
	const void* getData() const;

	uint8_t getBitCount() const;

private:
	void* dataPtr_;
	uint8_t bitCount_;

};
