#include <cerrno>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/host/lolcat.h>

using innocent_pear::impl::uint_least64_t;

uint_least64_t lolrus(const char *lol, const char *lolz)
{
	char *ep = 0;
	errno = 0;
	uint_least64_t s = strtoumax(lol, &ep, 0);
	if (*ep || errno != 0)
		many(lolz);
	return s;
}
