#include "X10Bit.hpp"

static uint64_t s_data;

static uint8_t dataLeft;

static X10Bit* X10Ptr = 0;

// ZeroCross
ISR(INT5_vect) 
{
	PORTK ^= 0x0F;
	
	// 1ms delay => Sending bit
	
	if(dataLeft != 0)
	{
		if (s_data & ((uint64_t)1 << (dataLeft-1)))
		{
			// Enable CTC-signal
			TCCR5A |= (1 << COM1A0);

            // Enable stop-sending-interrupt
			TIFR4 = (1 << OCF4A);
			OCR4A = TCNT4 + 16000; // 1 ms
			TIMSK4 |= (1 << OCIE4A);
		}
		dataLeft--;
	}
	
	
    // 0.5ms delay => Recieving bit
	TIFR4 = (1 << OCF4B);
	OCR4B = TCNT4 + 8000; // 0.5 ms
	TIMSK4 |= (1 << OCIE4B);
	
}

//Stop sending
ISR(TIMER4_COMPA_vect)
{
	// Disable CTC-signal
    TCCR5A &= ~(1 << COM1A0);
	
	TIMSK4 &= ~(1 << OCIE4A);
}

//Read from X10
ISR(TIMER4_COMPB_vect)
{
	X10Ptr->onReceiveBit((PINL >> 6) & 1);
	TIMSK4 &= ~(1 << OCIE4B);
}

X10Bit::X10Bit() 
{	
	DDRK = 0xFF;
	
	PORTK = 0x00;
	
	X10Ptr = this;
	
	// Init timers and interupts
    // DDRL |= (1 << 6);
	DDRL = 0b10111111;

	EIMSK |= (1 << INT5);
	EICRB |= (1 << ISC50);

    // Init Timer 4
        // Normal mode and Prescaler = 1
        TCCR4A = 0b00000000;
        TCCR4B = 0b00000001;
		TIMSK4 = 0x00;
        
	
	// Init Timer 5
		// CTC mode, Toggle OC5A and Prescaler = 1
		TCCR5A = 0b01000000;
		TCCR5B = 0b00001001;
		OCR5A = 66; // 120 kHz
		TCCR5A &= ~(1 << COM1A0);

}

X10Bit::~X10Bit() 
{
	
}

void X10Bit::write(uint64_t x, uint8_t bits) 
{
    // Save bitData to variable
	//s_data = *(bitData.getData<uint64_t>());

	//dataLeft = bitData.getBitCount();
    
	s_data = x;
	dataLeft = bits;
    // Set internal flag;
    isSending_flag = 1;
}

bool X10Bit::isSending() 
{
	return isSending_flag;
}

/*void X10Bit::simulate(Data bits) 
{
	
}*/

void X10Bit::onReceiveBit(bool bit) 
{
	if (bit == true)
	{
		PORTK |= 0xF0;
	}
	else
	{
		PORTK &= ~0xF0;
	}
}
