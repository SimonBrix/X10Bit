#include "Data.h"

#include <cstdlib>

Data::Data() {
	pointer_ = nullptr;
	pointerBitCount_ = 0;
	byteCount_ = 0;
	pointerCapacity_ = 0;
}

Data::Data(const uint8_t& bitCount)
	: Data() {
	resize(bitCount, false);
}
Data::Data(const Data& data)
	: Data(data.pointer_, data.pointerBitCount_) {
}
Data::Data(const void* const& pointer, const uint8_t& bitCount)
	: Data() {
	setData(pointer, bitCount);
}
Data::Data(const void* const& pointer, const uint8_t& copyBitCount, const uint8_t& bitCount)
	: Data() {
	resize(bitCount);
	setData(pointer, (copyBitCount < bitCount) ? copyBitCount : bitCount);
	resize(bitCount);
}

Data::~Data() {
	if (pointerCapacity_ > 0) free(pointer_);
}

const void* Data::getData() const {
	return pointer_;
}
void* Data::getChangeableData() {
	return pointer_;
}

uint8_t Data::getBitCount() const {
	return pointerBitCount_;
}
uint8_t Data::getByteCountCeiled() const {
	return byteCount_;
}
uint8_t Data::getByteCountFloored() const {
	return pointerBitCount_ / 8;
}

void Data::setData(const void* const& pointer, const uint8_t& bitCount) {
	resize(bitCount, false);

	for (uint8_t byteI = 0; byteI < byteCount_; byteI++)
	{
		(pointer_)[byteI] = ((uint8_t*)pointer)[byteI];
	}
}

void Data::resize(const uint8_t& newBitCount, const bool& keepValues) {
	const uint8_t newByteCount = (newBitCount + 7) / 8;

	if (newByteCount > pointerCapacity_) {
		uint8_t* const newPointer = (uint8_t*)malloc(newByteCount);
		
		//Delete old pointer
		if (pointerCapacity_ > 0) {
			if (keepValues) {
				uint8_t copyByteCount = (pointerCapacity_ < newByteCount) ? pointerCapacity_ : newByteCount;
				for (uint8_t i = 0; i < copyByteCount; i++) {
					newPointer[i] = pointer_[i];
				}
			}
			free(pointer_);
		}

		pointer_ = newPointer;
		pointerCapacity_ = newByteCount;
	}

	pointerBitCount_ = newBitCount;
	byteCount_ = newByteCount;
}

void Data::concatenate(const Data& additionalData) {
	const uint8_t oldBitSize = getBitCount();
	const uint8_t bitSizeChange = additionalData.getBitCount();

	resize(oldBitSize + bitSizeChange);

	uint8_t* const destinationBytes = getChangeableData<uint8_t>() + (oldBitSize / 8);
	const uint8_t* const copyBytes = additionalData.getData<uint8_t>();
	const uint8_t copyByteBitShift = oldBitSize % 8;

	if (copyByteBitShift == 0) {
		const uint8_t byteSizeChangeCeiled = additionalData.getByteCountCeiled();
		//Copy full bytes (and treat last byte as full byte)
		for (uint8_t byteI = 0; byteI < byteSizeChangeCeiled; byteI++) {
			destinationBytes[byteI] = copyBytes[byteI];
		}
	}
	else {
		const uint8_t byteSizeChangeFloored = additionalData.getByteCountFloored();
		//Copy full bytes
		destinationBytes[0] &= (0xFF << (8 - copyByteBitShift));
		for (uint8_t byteI = 0; byteI < byteSizeChangeFloored; byteI++) {
			destinationBytes[byteI] |= (copyBytes[byteI] >> copyByteBitShift);
			destinationBytes[byteI + 1] = (copyBytes[byteI] << (8 - copyByteBitShift));
		}
		//Copy last (not-full) byte
		const uint8_t lastByteBitSize = bitSizeChange % 8;
		if (lastByteBitSize > 0) {
			destinationBytes[byteSizeChangeFloored] |= (copyBytes[byteSizeChangeFloored] >> copyByteBitShift);
			if (lastByteBitSize > 8 - copyByteBitShift) {
				destinationBytes[byteSizeChangeFloored + 1] = (copyBytes[byteSizeChangeFloored] << (8 - copyByteBitShift));
			}
		}
	}
}

void Data::operator=(const Data& data) {
	setData(data.getData(), data.getBitCount());
}

void Data::operator^=(const Data& data) {
	const uint8_t bitCount1 = getBitCount();
	const uint8_t bitCount2 = data.getBitCount();
	const uint8_t bitCount = (bitCount1 < bitCount2) ? bitCount1 : bitCount2;
	const uint8_t byteCountFloored = bitCount / 8;
	const uint8_t extraBitCount = bitCount % 8;

	uint8_t* const resultBytes = (uint8_t*)getChangeableData();
	const uint8_t* const checkBytes = (const uint8_t*)data.getData();

	//XOR full bytes
	for (uint8_t byteI = 0; byteI < byteCountFloored; byteI++) {
		resultBytes[byteI] ^= checkBytes[byteI];
	}
	//XOR last (not-full) byte
	if (extraBitCount > 0) {
		uint8_t endCheckByte = checkBytes[byteCountFloored] & (0xFF << (8 - extraBitCount));
		resultBytes[byteCountFloored] ^= endCheckByte;
	}
}
void Data::operator&=(const Data& data) {
	const uint8_t bitCount1 = getBitCount();
	const uint8_t bitCount2 = data.getBitCount();
	const uint8_t bitCount = (bitCount1 < bitCount2) ? bitCount1 : bitCount2;
	const uint8_t byteCountFloored = bitCount / 8;
	const uint8_t extraBitCount = bitCount % 8;

	uint8_t* const resultBytes = (uint8_t*)getChangeableData();
	const uint8_t* const checkBytes = (const uint8_t*)data.getData();

	//AND full bytes
	for (uint8_t byteI = 0; byteI < byteCountFloored; byteI++) {
		resultBytes[byteI] &= checkBytes[byteI];
	}
	//AND last (not-full) byte
	if (extraBitCount > 0) {
		uint8_t endCheckByte = checkBytes[byteCountFloored] | ~(0xFF << (8 - extraBitCount));
		resultBytes[byteCountFloored] &= endCheckByte;
	}
}
void Data::operator|=(const Data& data) {
	const uint8_t bitCount1 = getBitCount();
	const uint8_t bitCount2 = data.getBitCount();
	const uint8_t bitCount = (bitCount1 < bitCount2) ? bitCount1 : bitCount2;
	const uint8_t byteCountFloored = bitCount / 8;
	const uint8_t extraBitCount = bitCount % 8;

	uint8_t* const resultBytes = (uint8_t*)getChangeableData();
	const uint8_t* const checkBytes = (const uint8_t*)data.getData();

	//OR full bytes
	for (uint8_t byteI = 0; byteI < byteCountFloored; byteI++) {
		resultBytes[byteI] |= checkBytes[byteI];
	}
	//OR last (not-full) byte
	if (extraBitCount > 0) {
		uint8_t endCheckByte = checkBytes[byteCountFloored] & (0xFF << (8 - extraBitCount));
		resultBytes[byteCountFloored] |= endCheckByte;
	}
}

Data Data::operator^(const Data& data) const {
	if (data.getBitCount() < getBitCount()) {
		Data xorData(data);
		xorData ^= *this;
		return xorData;
	}
	else {
		Data xorData(*this);
		xorData ^= data;
		return xorData;
	}
}
Data Data::operator&(const Data& data) const {
	if (data.getBitCount() < getBitCount()) {
		Data andData(data);
		andData &= *this;
		return andData;
	}
	else {
		Data andData(*this);
		andData &= data;
		return andData;
	}
}
Data Data::operator|(const Data& data) const {
	if (data.getBitCount() < getBitCount()) {
		Data orData(data);
		orData |= *this;
		return orData;
	}
	else {
		Data orData(*this);
		orData |= data;
		return orData;
	}
}
Data Data::operator~() const {
	const uint8_t* sourceBytes = (const uint8_t*)getData();

	Data onesComplementData(getBitCount());
	uint8_t* const onesComplementBytes = (uint8_t*)onesComplementData.getChangeableData();
	const uint8_t byteCountCeiled = getByteCountCeiled();

	for (uint8_t byteI = 0; byteI < byteCountCeiled; byteI++) {
		onesComplementBytes[byteI] = ~sourceBytes[byteI];
	}

	return onesComplementData;
}

bool Data::operator==(const Data& data) const {
	if (data.getBitCount() != getBitCount()) return false;
	const uint8_t byteCountFloored = getByteCountFloored();
	const uint8_t* const dataBytes1 = (const uint8_t*)getData();
	const uint8_t* const dataBytes2 = (const uint8_t*)data.getData();

	for (uint8_t i = 0; i < byteCountFloored; i++) {
		if (dataBytes1[i] != dataBytes2[i]) return false;
	}

	const uint8_t extraBitCount = getBitCount() % 8;
	if (extraBitCount > 0) {
		const uint8_t filter = 0xFF << (8 - extraBitCount);
		if ((dataBytes1[byteCountFloored] & filter) != (dataBytes2[byteCountFloored] & filter)) return false;
	}

	return true;
}
bool Data::operator!=(const Data& data) const {
	return !(*this == data);
}

Data Data::operator<<(const uint8_t& shiftBitCount) const {
	const uint8_t totalBitCount = getBitCount();
	//If shifting all bits out of this
	if (shiftBitCount >= totalBitCount) return Data(totalBitCount);

	const uint8_t byteShift = shiftBitCount / 8;
	const uint8_t bitShift = shiftBitCount % 8;

	Data returnData(totalBitCount);
	uint8_t* const destinationBytes = returnData.getChangeableData<uint8_t>();
	const uint8_t* copyBytes = getData<uint8_t>() + byteShift;
	const uint8_t byteCountToCopy = getByteCountCeiled() - byteShift;

	//Copy full bytes (and treat last (not-full) byte as full byte)
	for (uint8_t byteI = 0; byteI < byteCountToCopy - 1; byteI++) {
		destinationBytes[byteI] = (copyBytes[byteI] << bitShift) | (copyBytes[byteI + 1] >> (8 - bitShift));
	}
	destinationBytes[byteCountToCopy - 1] = (copyBytes[byteCountToCopy - 1] << bitShift);

	return returnData;
}
Data Data::operator>>(const uint8_t& shiftBitCount) const {
	const uint8_t totalBitCount = getBitCount();
	//If shifting all bits out of this
	if (shiftBitCount >= totalBitCount) return Data(totalBitCount);

	const uint8_t byteShift = shiftBitCount / 8;
	const uint8_t bitShift = shiftBitCount % 8;

	Data returnData(totalBitCount);
	uint8_t* const destinationBytes = returnData.getChangeableData<uint8_t>() + byteShift;
	const uint8_t* const copyBytes = getData<uint8_t>();
	const uint8_t byteCountToCopy = getByteCountCeiled() - byteShift;

	//Copy full bytes (and treat last (not-full) byte as full byte)
	destinationBytes[0] = (copyBytes[0] >> bitShift);
	for (uint8_t byteI = 1; byteI < byteCountToCopy; byteI++) {
		destinationBytes[byteI] = (copyBytes[byteI] >> bitShift) | (copyBytes[byteI - 1] << (8 - bitShift));
	}

	return returnData;
}

const bool Data::operator[](const uint8_t& id) const {
	const uint8_t byteID = id / 8;
	const uint8_t bitPositionInByte = id % 8;

	return getData<uint8_t>()[byteID] & (0b10000000 >> bitPositionInByte);
}