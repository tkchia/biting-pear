#include <cstdio>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>

__attribute__((section(".innocent_pear.test")))
char msg[] = "SCIENTIA EST LVX LVCIS\n";

int main()
{
	innocent_pear::kthxbai?<unsigned char *> p((unsigned char *)msg, 3);
	innocent_pear::orly<STATE, unsigned char, false, true>().wut(p,
	    p + sizeof msg);
	std::fputs(msg, stdout);
	return 0;
}
