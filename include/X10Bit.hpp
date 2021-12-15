#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

/// <summary> Utilizes timers and interrupts to send X10 data </summary>
class X10Bit
{
public:
	/// <summary> Constructs a new X10Bit object </summary>
	X10Bit();
	/// <summary> writes a data object to the X10-line </summary>
	/// <param name="bitData"> Reference to a Data-object containing the data to transmit</param>
	void write(Data &bitData);
	/// <summary> Returns status on whether or not X10Bit is sending</summary>
	/// <returns> true if not finished sending and false if finished sending</returns>
	bool isSending();
	/// <summary> Get function for attribute isSending_flag </summary>
	bool getisSending_flag();
	/// <summary> Set function for attribute isSending_flag </summary>
	void setisSending_flag(bool flag);
	/// <summary> Is called every time X10-bit recieves a bit </summary>
	/// <param name="bit"> true if a 1 is recieved false if a 0 is recieved </param>
	virtual void onReceiveBit(bool bit);
private:
	/// <summary> SW-flag for status about sending </summary>
	bool isSending_flag;
};
