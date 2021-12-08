#pragma once

#include <stdint.h>

/// <summary> Contains a specific amount of bits. </summary>
class Data {
private:
	/// <summary> Pointer to the bits contained by this. </summary>
	uint8_t* pointer_;
	/// <summary> The amount of bits contained by this. </summary>
	uint8_t pointerBitCount_;
	/// <summary> The amount of bytes this contains, rounded up. </summary>
	uint8_t byteCount_;
	/// <summary> The amount of bytes the pointer points to which is reserved by this. </summary>
	uint8_t pointerCapacity_;
public:
	/// <summary> Constructs a Data-object.
	/// <para /> This default constructor results in a Data-object containing 0 bits. </summary>
	Data();
	/// <param name="bitCount"> The amount of bits this should start out containing. The individuel bits' values are undefined. </param>
	Data(const uint8_t& bitCount);
	/// <param name="data"> The Data-object whose bits to copy into this. </param>
	Data(const Data& data);
	/// <param name="pointer"> A pointer to the data to copy into this. getData will return a pointer to a copy of this. </param>
	/// <param name="bitCount"> The amount of bits to copy from pointer. getBitCount will return this. </param>
	Data(const void* const& pointer, const uint8_t& bitCount);
	/// <param name="pointer"> A pointer to the data to copy into this. getData will return a pointer to a copy of this. </param>
	/// <param name="copyBitCount"> The amount of bits to copy from pointer. If bigger than bitCount, will be clamped to bitCount. If smaller, remaining bits will be undefined. </param>
	/// <param name="bitCount"> The amount of bits this should contain. getBitCount will return this. </param>
	Data(const void* const& pointer, const uint8_t& copyBitCount, const uint8_t& bitCount);
	~Data();

	/// <summary> Gets the bits currently contained by this. The data becomes undefined if setData is called after this. </summary>
	/// <returns> A pointer to the data. Use getBitCount to get the size of the data this points to. </returns>
	const void* getData() const;
	/// <summary> Like getData, but the pointer's values are changeable. </summary>
	/// <returns> A pointer to the data. Use getBitCount to get the size of the data this points to. </returns>
	void* getChangeableData();
	/// <summary> Gets the bits currently contained by this. The data becomes undefined if setData is called after this. </summary>
	/// <typeparam name="T"> The type to return the data as. </typeparam>
	/// <returns> A pointer to the data. Use getBitCount to get the size of the data this points to. </returns>
	template <class T>
	const T* getData() const { return (const T*)getData(); }
	/// <summary> Like getData, but the pointer's values are changeable. </summary>
	/// <typeparam name="T"> The type to return the data as. </typeparam>
	/// <returns> A pointer to the data. Use getBitCount to get the size of the data this points to. </returns
	template <class T>
	T* getChangeableData() { return (T*)getChangeableData(); }

	/// <summary> Returns the amount of bits contained by this. </summary>
	uint8_t getBitCount() const;
	/// <summary> Returns the amount of bytes contained by this, rounded up. </summary>
	uint8_t getByteCountCeiled() const;
	/// <summary> Returns the amount of bytes contained by this, rounded down. </summary>
	uint8_t getByteCountFloored() const;

	/// <summary> Overwrites the data this class contains. Makes the data from past getData-calls undefined. </summary>
	/// <param name="pointer"> A pointer to the data to copy into this. After this method, getData will return a pointer to a copy of this. </param>
	/// <param name="bitCount"> The amount of bits to copy from pointer. After this method, getBitCount will return this. </param>
	void setData(const void* const& pointer, const uint8_t& bitCount);
	/// <summary> Sets the amount of bits this contains. </summary>
	/// <param name="keepValues"> If true, keeps the bits this contains after being resized.
	/// <para /> If resized to be smaller, bits towards the end are removed first to make space.
	/// <para /> If resized to be larger, the new bits added are at the end. </param>
	void resize(const uint8_t& newBitCount, const bool& keepValues = true);
	/// <summary> Sets this to a larger collection of bits that first contains this' bits, and then contains additionalData's bits. </summary>
	void concatenate(const Data& additionalData);

public: // Operators:
	/// <summary> Sets the left-hand side to a copy of the right-hand side. </summary>
	void operator=(const Data&);

	/// <summary> XORs the left-hand side with the right-hand side.
	/// <para /> If the left-hand side has more bits, the extra bits does NOT get XORed.
	/// <para /> If the left-hand side has fewer bits, the right hand side's extra bits gets ignored. </summary>
	void operator^=(const Data&);
	/// <summary> ANDs the left-hand side with the right-hand side.
	/// <para /> If the left-hand side has more bits, the extra bits does NOT get ANDed.
	/// <para /> If the left-hand side has fewer bits, the right hand side's extra bits gets ignored. </summary>
	void operator&=(const Data&);
	/// <summary> ORs the left-hand side with the right-hand side.
	/// <para /> If the left-hand side has more bits, the extra bits does NOT get ORed.
	/// <para /> If the left-hand side has fewer bits, the right hand side's extra bits gets ignored. </summary>
	void operator|=(const Data&);

	/// <summary> Returns the XOR of the two Data-objects.
	/// <para /> If one Data-object has more bits than the other, the bigger one's right-most bits are ignored for this. </summary>
	Data operator^(const Data&) const;
	/// <summary> Returns the AND of the two Data-objects.
	/// <para /> If one Data-object has more bits than the other, the bigger one's right-most bits are ignored for this. </summary>
	Data operator&(const Data&) const;
	/// <summary> Returns the OR of the two Data-objects.
	/// <para /> If one Data-object has more bits than the other, the bigger one's right-most bits are ignored for this. </summary>
	Data operator|(const Data&) const;
	/// <summary> Returns a copy of the Data-object where its 0s and 1s have been inverted to 1s and 0s. </summary>
	Data operator~() const;

	/// <summary> Returns true if two Data-objects have the same amount of bits, and those bits are the same; else returns false. </summary>
	bool operator==(const Data&) const;
	/// <summary> Returns false if two Data-objects have the same amount of bits, and those bits are the same; else returns true. </summary>
	bool operator!=(const Data&) const;

	/// <summary> Bitshifts the Data's bits to the left. The new bits shifted in from the right are undefined. </summary>
	Data operator<<(const uint8_t&) const;
	/// <summary> Bitshifts the Data's bits to the right. The new bits shifted in from the left are undefined. </summary>
	Data operator>>(const uint8_t&) const;

	/// <summary> Returns the bit in the designated bit-position. </summary>
	const bool operator[](const uint8_t&) const;
};