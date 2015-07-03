#ifndef biting_pear_H_LOLWUT
#define biting_pear_H_LOLWUT

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

namespace biting_pear
{

namespace impl
{

template<rand_state_t State, class T, unsigned Levels>
struct kthxbai_impl;  // forward

template<rand_state_t State, class T, unsigned Levels = 6u>
class lolwut
{
	static constexpr rand_state_t State2 = impl::update_inner(State);
	static constexpr rand_state_t NewState = impl::update_outer(State);
	static constexpr unsigned Disp =
	    impl::pick_hi<unsigned>(State2 ^ NewState) / 2u;
	static constexpr bool Sign =
	    impl::pick_hi<unsigned>(State2 ^ NewState) % 2u != 0;
	static constexpr rand_state_t State3 = impl::update_inner(State2);
	static constexpr rand_state_t State4 = impl::update_inner(State3);
#ifdef __amd64__
	static constexpr unsigned Disp2 = Disp > 2 ?
	    impl::pick_hi<unsigned>(State2 ^ State3) % (Disp / 2) : 0;
#endif
	static constexpr unsigned Disp3 =
	    impl::pick_hi<unsigned>(State3 ^ State4) / 2u;
	char *p_;
    protected:
	void advance_chars(std::ptrdiff_t n)
		{ p_ += n; }
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
			 * Address of a g++ label.  We use the `%a' operand
			 * modifier to remove the `$' from the constant
			 * displacements.  See locklessinc.com/articles/
			 * gcc_asm/ .
			 *
			 * -- 20150703
			 *
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
			if (Disp < 0x70000000u && State2 > NewState) {
				if (Sign)
					__asm("leaq -%a1+%l2(%%rip), %0"
					    : "=r" (p_)
					    : "n" (Disp), "p" (v));
				else
					__asm("leaq %a1+%l2(%%rip), %0"
					    : "=r" (p_)
					    : "n" (Disp), "p" (v));
			} else {
				if (Sign) {
					__asm("leaq -%a1+%l2(%%rip), %0; "
					    : "=r" (p_)
					    : "n" (Disp2),
					      "p" (v)
					    : "cc");
					p_ -= Disp - Disp2;
				} else {
					__asm("leaq %a1+%l2(%%rip), %0; "
					    : "=r" (p_)
					    : "n" (Disp2),
					      "p" (v)
					    : "cc");
					p_ += Disp - Disp2;
				}
			}
			break;
#   if defined __ELF__ && (defined __pic__ || defined __pie__)
		    case 2:
			/*
			 * On Linux/x86-64 and possibly other ELF platforms
			 * (?), an assembly operand of the form
			 *
			 *	"X" (printf)
			 *
			 * will yield "printf(%rip)" for "%a1", and
			 * "$printf" for "%1".  This can be considered a
			 * glitch in g++, so we do not rely on it.
			 *
			 * If the above trick works, then something like
			 *
			 *	leaq	printf(%rip), %rdi
			 *
			 * will point %rdi to the _PLT stub_ for printf.  We
			 * can modify this to
			 *
			 *	leaq	some_constant+printf(%rip), %rdi
			 *
			 * to obscure the reference to `printf'.
			 *
			 * -- 20150703
			 */
			if (Sign) {
				__asm(	".ifc \"$%a1\", \"%1(%%rip)\"; "
						"leaq -%a2+%a1, %0; "
					".else; "
						"movq %1, %0; "
						"subq %2, %0; "
					".endif"
				    : "=&r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ -= Disp - Disp2;
			} else {
				__asm(	".ifc \"$%a1\", \"%1(%%rip)\"; "
						"leaq %a2+%a1, %0; "
					".else; "
						"movq %1, %0; "
						"addq %2, %0; "
					".endif"
				    : "=&r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ += Disp - Disp2;
			}
			break;
#   endif
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
		impl::kthxbai_impl<NewState, unsigned, Levels>(disp, Disp);
		if (Sign)
			return reinterpret_cast<T *>(p_ + disp);
		else	return reinterpret_cast<T *>(p_ - disp);
	}
};

} // biting_pear::impl

} // biting_pear

#endif
