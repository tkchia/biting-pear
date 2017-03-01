#include <iostream>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>

__attribute__((section(".innocent_pear.test")))
unsigned char msg[] = "SCIENTIA EST LVX LVCIS\n";

int main()
{
	innocent_pear::kthxbai?<unsigned char *> p(msg);
	innocent_pear::kthxbai?<unsigned char *> q(msg + sizeof msg);
	innocent_pear::orly<STATE, unsigned char, false, true>().wut(p, q);
	std::cout << msg;
	return 0;
}
