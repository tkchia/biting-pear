#ifndef biting_pear_H_LOLWUT
#define biting_pear_H_LOLWUT

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include "biting-pear/bbq.h"
#include "biting-pear/kthxbai.h"

namespace biting_pear
{

namespace impl
{

template<uint_least64_t Seed, class T, unsigned Levels>
struct kthxbai_impl;  // forward

template<uint_least64_t Seed, class T, unsigned Levels = 6u>
class lolwut
{
	static constexpr uint_least64_t Seed2 = impl::update_inner(Seed);
	static constexpr uint_least64_t NewSeed = impl::update_outer(Seed);
	static constexpr unsigned Disp =
	    impl::pick_hi<unsigned>(Seed2 ^ NewSeed) / 2u;
	static constexpr bool Sign =
	    impl::pick_hi<unsigned>(Seed2 ^ NewSeed) % 2u != 0;
#ifdef __amd64__
	static constexpr uint_least64_t Seed3 = impl::update_inner(Seed2);
	static constexpr unsigned Disp2 = Disp > 2 ?
	    impl::pick_hi<unsigned>(Seed2 ^ Seed3) % (Disp / 2) : 0;
#endif
	char *p_;
    public:
	__attribute__((always_inline))
	lolwut()
		{ }
	__attribute__((always_inline))
	lolwut(T *v, int mode = 0)
	{
		switch (mode) {
#ifdef __amd64__
		    case 1:
			/*
			 * In the unlikely case that the offset-from-%rip
			 * does not fit into a signed 32-bit operand, we
			 * still need to output valid machine instructions.
			 * We switch from doing a single `leaq' to building
			 * up the offset inside a register in two parts.
			 *
			 * Sometimes, we do this even if the offset-from-
			 * -%rip _does_ fit into a signed 32-bit. :-)
			 *
			 * -- 20150614
			 */
			if (Disp < 0x7ffff000u && Seed2 > NewSeed) {
				if (Sign)
					__asm("leaq -%c1+%l2(%%rip), %0"
					    : "=r" (p_)
					    : "n" (Disp), "p" (v));
				else
					__asm("leaq %c1+%l2(%%rip), %0"
					    : "=r" (p_)
					    : "n" (Disp), "p" (v));
			} else {
				if (Sign)
					__asm("leaq -%c1+%l3(%%rip), %0; "
					      "subq %2, %0"
					    : "=r" (p_)
					    : "n" (Disp2),
					      "n" (Disp - Disp2),
					      "p" (v));
				else
					__asm("leaq %c1+%l3(%%rip), %0; "
					      "addq %2, %0"
					    : "=r" (p_)
					    : "n" (Disp2),
					      "n" (Disp - Disp2),
					      "p" (v));
			}
			break;
#endif
		    default:
			*this = v;
		}
	}
	__attribute__((always_inline))
	const lolwut& operator=(T *v)
	{
		if (Sign)
			p_ = reinterpret_cast<char *>(v) - Disp;
		else	p_ = reinterpret_cast<char *>(v) + Disp;
		return *this;
	}
	__attribute__((always_inline))
	operator T *() const
	{
		unsigned disp;
		impl::kthxbai_impl<NewSeed, unsigned, Levels>(disp, Disp);
		if (Sign)
			return reinterpret_cast<T *>(p_ + disp);
		else	return reinterpret_cast<T *>(p_ - disp);
	}
};

} // biting_pear::impl

} // biting_pear

#endif
