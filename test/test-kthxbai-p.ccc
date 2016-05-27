#include <cstdio>
#include <innocent-pear/kthxbai.h>

int main(void)
{
	using innocent_pear::ops::allow_all;
	typedef innocent_pear_decltype(&std::printf) pft;
	innocent_pear::kthxbai?<pft, allow_all> f1(std::printf);
	f1("Hello ");
	innocent_pear::kthxbai?<pft, allow_all> f2(std::printf);
	f2("%s!", "world");
	innocent_pear::kthxbai?<pft, allow_all> f3(std::printf);
	f3("%c", '\n');
	return 0;
}
