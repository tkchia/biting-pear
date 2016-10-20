#include <climits>
#include <cstdlib>
#include <limits>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/host/moar.h>

using innocent_pear::impl::uint_least64_t;

void moar_t::feed(const unsigned char *b, std::size_t n)
{
	/*
	 * It is unlikely, though not exactly impossible, for the buffer
	 * size to be this big.  We also subtract the size of the PRG
	 * structure to take into account a possible overflow in the Keccak
	 * code's internal calculations.
	 */
	static constexpr unsigned M =
	    std::numeric_limits<int>::max() - sizeof(g_);
	while (n >= M) {
		KeccakWidth1600_SpongePRG_Feed(&g_, b, M);
		b += M;
		n -= M;
	}
	KeccakWidth1600_SpongePRG_Feed(&g_, b, (unsigned)n);
}

uint_least64_t moar_t::fetch()
{
	static constexpr std::size_t NB = (64 + CHAR_BIT - 1) / CHAR_BIT;
	static constexpr uint_least64_t UCM =
	    (uint_least64_t)std::numeric_limits<unsigned char>::max();
	unsigned char o[NB];
	uint_least64_t x = 0;
	KeccakWidth1600_SpongePRG_Fetch(&g_, o, NB);
	for (std::size_t i = 0; i < NB; ++i) {
		x *= UCM + 1;
		x += o[i];
	}
	return innocent_pear::impl::clip(x);
}
