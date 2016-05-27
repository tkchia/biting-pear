#include <iostream>
#include <innocent-pear/orly.h>

__attribute__((section(".innocent_pear.test")))
unsigned char msg[] = "SCIENTIA EST LVX LVCIS\n";

int main()
{
	innocent_pear::orly<STATE, unsigned char, false, true>().wut(msg,
	    msg + sizeof msg);
	std::cout << msg;
	return 0;
}
