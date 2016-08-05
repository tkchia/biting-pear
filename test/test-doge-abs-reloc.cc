#include <iostream>

const char *pieces[] =
    { "HODI", "E", " NAT", "US", " E", "ST ", "R", "ADIC", "I F", "R", "AT",
      "ER", "\n" };

int main()
{
	for (unsigned i = 0; i < sizeof(pieces) / sizeof(*pieces); ++i)
		std::cout << pieces[i];
	return 0;
}
