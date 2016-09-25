#include <cstdlib>
#include <limits>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/host/moar.h>

using innocent_pear::impl::uint64_t;

void moar_t::feed(const unsigned char *b, std::size_t n)
{
	static constexpr unsigned UIM = std::numeric_limits<unsigned>::max();
	while (n >= UIM) {		/* unlikely but possible case... */
		KeccakWidth1600_SpongePRG_Feed(&g_, b, UIM);
		b += UIM;
		n -= UIM;
	}
	KeccakWidth1600_SpongePRG_Feed(&g_, b, (unsigned)n);
}

uint64_t moar_t::fetch()
{
	static constexpr std::size_t NB = sizeof(uint64_t);
	static constexpr uint64_t UCM =
	    (uint64_t)std::numeric_limits<unsigned char>::max();
	unsigned char o[NB];
	uint64_t x = 0;
	KeccakWidth1600_SpongePRG_Fetch(&g_, o, NB);
	for (std::size_t i = 0; i < NB; ++i) {
		x *= UCM + 1;
		x += o[i];
	}
	return x;
}
