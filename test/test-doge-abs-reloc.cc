#include <iostream>

const char *pieces[] =
    { "HODI", "E", " NAT", "US", " E", "ST ", "R", "ADIC", "I F", "R", "AT",
      "ER", "\n" };
const char * const c_pieces[] =
    { "HON", "I ", "SO", "IT", " ", "LA", " VACHE ", "QU", "I ", "R", "IT",
      "\n" };

int main()
{
	for (unsigned i = 0; i < sizeof(pieces) / sizeof(*pieces); ++i)
		std::cout << pieces[i];
	for (unsigned i = 0; i < sizeof(c_pieces) / sizeof(*c_pieces); ++i)
		std::cout << c_pieces[i];
	return 0;
}
