#include <avr/io.h>
#include <avr/interrupt.h>


#include "X10Proto.hpp"

/*__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" {
  int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
  void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
  void __cxa_guard_abort (__guard *) {};
}*/

/*extern "C" {
  void __cxa_pure_virtual(void) {};
}*/

int main()
{
	sei();

	DDRB = 0xff;
	PORTB = 0x00;

	X10Proto x10;
	x10.write(0b10101);
	while(1)
	{}
}