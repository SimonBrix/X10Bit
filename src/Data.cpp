#include "Data.hpp"

Data::Data(void* dataPtr, uint8_t bitCount) 
{
	setData(dataPtr, bitCount);
}

void Data::setData(void* dataPtr, uint8_t bitCount) 
{
	dataPtr_ = dataPtr;
	bitCount_ = bitCount;
}

const void* Data::getData() const
{
	return dataPtr_;
}

uint8_t Data::getBitCount() const
{
	return bitCount_;
}
