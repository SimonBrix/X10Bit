#include "X10Bit.hpp"

static long s_data;

static uint8_t dataLeft;

static X10Bit* X10Ptr = 0;

ISR(INT4_vect)
{
	// 1ms delay => Sending bit
	if(dataLeft != 0)
	{
		if (s_data & (1 << dataLeft-1))
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
	X10Ptr = this;
	
	// Init timers and interupts
    DDRL |= (1 << 6);
	sei();

    // Init Timer 4
        // Normal mode and Prescaler = 1
        TCCR4A = 0b00000000;
        TCCR4B = 0b00000001;
        
	
	// Init Timer 5
		// CTC mode and Prescaler = 1
		TCCR5A = 0b00000000;
		TCCR5B = 0b00001001;
		OCR5A = 66; // 120 kHz
}

X10Bit::~X10Bit() 
{
	
}

void X10Bit::write(Data bitData) 
{
    // Save bitData to variable
	s_data = *(bitData.getData<long>());

	dataLeft = bitData.getBitCount();
    
    // Set internal flag;
    isSending_flag = 1;
}

bool X10Bit::isSending() 
{
	return isSending_flag;
}

void X10Bit::simulate(Data bits) 
{
	
}

void X10Bit::onReceiveBit(bool bit) 
{
	
}
