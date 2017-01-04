#include <iostream>
#include <locale>
#include <innocent-pear/yodawg.h>

int main()
{
	std::locale::global(std::locale(""));
	std::wcout << $$L"Ave, " << $L"munde!\n";
	return 0;
}
