#include <cstdio>
#include <innocent-pear/kthxbai.h>

int main(void)
{
	using innocent_pear::kthxbai;
	using innocent_pear::ops::allow_for_startup;
	typedef innocent_pear_decltype(&std::printf) pft;
	kthxbai?<pft, allow_for_startup> f1(std::printf);
	f1("Hello ");
	kthxbai?<pft, allow_for_startup> f2(std::printf);
	f2("%s!", static_cast<const char *>
	    (kthxbai?<const char *, allow_for_startup>("world", 3)));
	kthxbai?<pft, allow_for_startup> f3(std::printf);
	f3("%c", '\n');
	return 0;
}
