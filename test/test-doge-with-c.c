#include <stdio.h>

unsigned new = 3, private = 1, public = 2;

int main(void)
{
	int catch = 0;
	printf("%u %u %u\n", private, public, new);
	return catch;
}
