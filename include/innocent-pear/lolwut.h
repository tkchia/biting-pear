#ifndef innocent_pear_H_LOLWUT
#define innocent_pear_H_LOLWUT

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
struct kthxbai_impl;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class lolwut_impl
{
    protected:
	static constexpr rand_state_t State2 = impl::update_inner(State);
	static constexpr rand_state_t NewState =
	    impl::update_outer(State, Levels);
	static constexpr rand_state_t NewNewState =
	    impl::update_outer(NewState, Levels);
	static constexpr unsigned Disp =
	    impl::pick_hi<unsigned>(State2 ^ NewState) / 2u;
	static constexpr bool Sign =
	    impl::pick_hi<unsigned>(State2 ^ NewState) % 2u != 0;
	static constexpr rand_state_t State3 = impl::update_inner(State2);
	/*
	 * (1) On x86-64, `Disp2' is used as a random displacement to be
	 *     added or subtracted to (ASLR-slid) static addresses in `leaq'
	 *     instructions.
	 *
	 *     In the unlikely case that the offset-from-%rip does not fit
	 *     into a signed 32-bit operand, we still need to output valid
	 *     machine instructions.  We thus split the +/- displacement
	 *     `Disp' into two parts, `Disp2' which can be stashed along
	 *     with the static address into the `leaq', and `Disp' - `Disp2'
	 *     which is applied in a separate instruction.
	 *
	 *     If `Disp' is small enough, then we (sometimes) just stash the
	 *     whole displacement into the `leaq', i.e.  set `Disp2' ==
	 *     `Disp'.
	 *
	 * (2) `clang++ -static' targeting x86-64 may produce a 32-bit
	 *     absolute relocation (R_X86_64_32) with +Disp2 or -Disp2 as
	 *     part of its addend, which leads to build errors if the
	 *     resulting address cannot fit into unsigned 32 bits.
	 *
	 *     To reduce the chances of this happening, for now we make
	 *     `Disp2' no larger than the minimum page size (0x1000) -- this
	 *     assumes that no static code or data will ever end up at the
	 *     addresses 0...0xfff or 0xfffff000...0xffffffff.
	 *
	 *     (Obviously, this workaround is less than ideal.  It would
	 *     help a bit if clang++ defines macros which tell us which code
	 *     model it is using, like g++ does (e.g.  __code_model_medium__
	 *     for `-mcmodel=medium'), but clang++ does not do so...)
	 *
	 * (3) On ARM without Thumb mode, when compiling under g++ 4.7, we
	 *     do a similar splitting exercise to work around a compiler
	 *     bug:
	 *
	 *	"test/test-dawg.ccc:13:1: error: unrecognizable insn:
	 *	 (insn 2833 1723 2834 17 (set (reg:SI 2195)
	 *		   (const_int -2540681723 [0xffffffff68904605]))
	 *			./include/biting-pear/lolwut.h:240 -1
	 *		(nil))
	 *	 test/test-dawg.ccc:13:1: internal compiler error: in
	 *	 extract_insn, at recog.c:2123"
	 *
	 * (4) On x86-32, `Disp2' is a displacement for the global offset
	 *     table (GOT) entry of the target item.  We make sure that
	 *     `Disp2' can _not_ be expressed as an 8-bit sign-extended
	 *     offset.
	 */
#if defined __amd64__
#   if !defined __clang__ || defined __pic__ || defined __pie__
	static constexpr unsigned Disp2 =
	    Disp < 0x60000000u && State2 > NewState ? Disp :
		(Disp > 2 ?
		 impl::pick_hi<unsigned>(State2 ^ State3) % (Disp / 2) : 0);
#   else
	static constexpr unsigned Disp2 =
	    Disp <= 0x1000u ? Disp :
		impl::pick_hi<unsigned>(State2 ^ State3) % 0x1001u;
#   endif
#elif defined __i386__
	static constexpr unsigned Disp2 =
	    ((State2 ^ State3) >> 20) % 0xffffff00u + 0x80u;
#elif defined __arm__ && !defined __thumb__ && !defined __clang__ && \
      __GNUC__ == 4 && __GNUC_MINOR__ <= 7
	static constexpr unsigned Disp2 = Disp > 2 ?
	    impl::pick_hi<unsigned>(State2 ^ State3) % (Disp / 2) : 0;
#endif
	static constexpr rand_state_t State4 = impl::update_inner(State3);
#if defined __arm__ && defined __thumb2__
	static constexpr rand_state_t State5 = impl::update_inner(State4);
	static constexpr unsigned Subsxn =
	    impl::pick_hi<unsigned>(State3 ^ State4) % 4096u + 1u;
	static constexpr unsigned Disp3 =
	    impl::pick_hi<unsigned>(State4 ^ State5);
#endif
	static constexpr unsigned Levels2 = Levels ? Levels - 1 : 0;
	char *p_;
	void advance_chars(std::ptrdiff_t n)
		{ p_ += n; }
	__attribute__((always_inline))
	lolwut_impl()
		{ }
	__attribute__((always_inline))
	void set(T *v, int mode = 0)
	{
		switch (mode) {
#if defined __amd64__
		    case 1:
			/*
			 * Address of a g++ label.  We use the `%a' operand
			 * modifier to remove the `$' from the constant
			 * displacements.  See locklessinc.com/articles/
			 * gcc_asm/ .
			 *
			 * -- 20150703
			 */
			if (Sign) {
				__asm("leaq -%a1+%l2(%%rip), %0"
				    : "=r" (p_)
				    : "n" ((unsigned long)Disp2), "p" (v));
				p_ -= Disp - Disp2;
			} else {
				__asm("leaq %a1+%l2(%%rip), %0"
				    : "=r" (p_)
				    : "n" ((unsigned long)Disp2), "p" (v));
				p_ += Disp - Disp2;
			}
			break;
#   if defined __ELF__ && (defined __pic__ || defined __pie__)
		    case 2:
			/*
			 * Address of a named function.  On Linux/x86-64 and
			 * possibly other ELF platforms (?), an assembly
			 * operand of the form
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
			 *
			 * Dang, apparently this no longer works: ld says
			 * stuff like
			 *
			 *	relocation R_X86_64_PC32 against undefined
			 *	symbol `_ZStlsISt11char_traitsIcEERSt
			 *	13basic_ostreamIcT_ES5_c@@GLIBCXX_3.4' can
			 *	not be used when making a shared object;
			 *	recompile with -fPIC
			 *
			 * To work around this, make the PLT explicit:
			 *
			 *	leaq	some_constant+printf@PLT(%rip), %rdi
			 *
			 * -- 20160214
			 */
#	ifndef __clang__
			if (Sign) {
				__asm("leaq -%a2+%P1(%%rip), %0"
				    : "=r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ -= Disp - Disp2;
			} else {
				__asm("leaq %a2+%P1(%%rip), %0"
				    : "=r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ += Disp - Disp2;
			}
#	else
			if (Sign) {
				__asm("leaq -%a2+%c1@PLT(%%rip), %0"
				    : "=r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ -= Disp - Disp2;
			} else {
				__asm("leaq %a2+%c1@PLT(%%rip), %0"
				    : "=r" (p_)
				    : "X" (v), "n" ((unsigned long)Disp2));
				p_ += Disp - Disp2;
			}
#	endif
			break;
#	ifndef __clang__
		    case 3:
			/* Address of a static variable.  -- 20160225 */
			if (Sign) {
				__asm("leaq -%a1+%a2, %0"
				    : "=r" (p_)
				    : "n" ((unsigned long)Disp2), "X" (v));
				p_ -= Disp - Disp2;
			} else {
				__asm("leaq %a1+%a2, %0"
				    : "=r" (p_)
				    : "n" ((unsigned long)Disp2), "X" (v));
				p_ += Disp - Disp2;
			}
			break;
#	endif
#   endif
#elif defined __i386__ && !defined __clang__
		    case 1:
		    case 3:
			__asm("" : "=r" (p_) : "0" (&&qux));
			__asm("addl $%a3+%p4-%p2, %0"
			    : "=r" (p_)
			    : "0" (p_), "X" (&&qux),
			      "n" (Sign ? -Disp : Disp), "X" (v)
			    : "cc");
		    qux:
			break;
#   ifdef __ELF__
		    case 2:
			/*
			 * On gcc 5.3.1:
			 *
			 * (1) The `[...]' grouping must be there.  Without
			 *     it, GNU `as' computes the wrong offset.
			 *
			 * (2) It might seem easier to get the PLT stub's
			 *     address via %eip-relative computations. 
			 *     Alas, the PLT stubs assume that %ebx points
			 *     to the GOT, and gcc 5+ outputs code that
			 *     breaks this assumption.
			 */
			{
				unsigned disp;
				impl::kthxbai_impl<State4, unsigned, Flags,
				    Levels2>(disp, Disp);
				__asm("" : "=r" (p_) : "0" (&&quux));
				__asm(".ifc \"$%P3\", \"%3@PLT\"; "
					"addl $_GLOBAL_OFFSET_TABLE_" \
					    "+[%p4+(.-%p2)], %0; "
				      ".endif"
				    : "=r" (p_)
				    : "0" (p_), "X" (&&quux), "X" (v),
				      "n" (Disp2)
				    : "cc");
				__asm(".ifc \"$%P2\", \"%2@PLT\"; "
					".reloc 1f-4, R_386_GOT32, %p2; "
					"movl %p3(%1), %0; "
					"1: ; "
				      ".else; "
					"movl %2, %0; "
				      ".endif"
				    : "=r" (p_)
				    : "r" (p_), "X" (v), "n" (-Disp2));
				if (Sign)
					p_ -= disp;
				else	p_ += disp;
			}
		    quux:
			break;
#   endif
#elif defined __arm__ && defined __thumb2__ && defined __OPTIMIZE__
		    case 1:
			{
				uintptr_t scratch;
				__asm("" : "=r" (p_) : "0" (&&qux));
				__asm("movw %1, #:lower16:(%a4+%a5-%a3); "
				      "movt %1, #:upper16:(%a4+%a5-%a3); "
				      "add %0, %0, %1"
				    : "=r" (p_), "=&r" (scratch)
				    : "0" (p_), "X" (&&qux),
				      "n" (Sign ? -Disp : Disp), "X" (v));
			}
		    qux:
			break;
#   ifdef __ELF__
		    case 2:
		    case 3:
			{
				unsigned disp3, scratch;
				impl::kthxbai_impl<State5, unsigned, Flags,
				    Levels2>(disp3, Disp3);
				__asm(".ifc \"#%a2\", \"\%2\"; "
					".subsection %a3; "
					".balign 4; "
					".reloc ., R_ARM_GOT_PREL, %a2; "
					"1: "
					".long %a4; "
					".previous; "
					"movw %0, #:lower16:(1b-2f-4); "
					"movt %0, #:upper16:(1b-2f-4); "
					"2: "
					"add %0, %0, pc; "
					"ldr %1, [%0]; "
					"add %1, %1, %0; "
					"ldr %0, [%5, %1]; "
				      ".else; "  /* assume %2 is a reg...? */
					"mov %0, %2; "
				      ".endif"
				    : "=&r" (p_), "=&r" (scratch)
				    : "X" (v), "n" (Subsxn), "n" (-Disp3),
				      "r" (disp3));
				if (Sign)
					p_ -= Disp;
				else	p_ += Disp;
			}
			break;
#   endif
#endif
		    default:
#if defined __arm__ && !defined __thumb__ && !defined __clang__ && \
    (__GNUC__ == 4 && __GNUC_MINOR__ <= 7)
#   pragma message \
	"may emit inferior code to avoid g++ < 4.8 bug"
			if (Sign) {
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char*>(v)-Disp2));
				p_ -= Disp - Disp2;
			} else {
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char*>(v)+Disp2));
				p_ += Disp - Disp2;
			}
#elif defined __amd64__ && defined __clang__ && \
    !defined __pic__ && !defined __pie__
#   pragma message \
	"may emit inferior code to avoid clang -static issue on x86-64"
			if (Sign) {
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char*>(v)-Disp2));
				p_ -= Disp - Disp2;
			} else {
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char*>(v)+Disp2));
				p_ += Disp - Disp2;
			}
#else
			if (Sign)
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char *>(v)-Disp));
			else
				__asm __volatile(""
				    : "=r" (p_)
				    : "0" (reinterpret_cast<char *>(v)+Disp));
#endif
		}
		__asm("" : "=g" (p_) : "0" (p_));
	}
};

template<rand_state_t State, class T, ops_flags_t Flags = 0,
    unsigned Levels = 3u>
class lolwut;

template<rand_state_t State, class T, ops_flags_t Flags>
class lolwut<State, T, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, ops_flags_t Flags>
class lolwut<State, T, Flags, 0u> : public lolwut_impl<State, T, Flags, 0u>
{
    public:
	__attribute__((always_inline))
	lolwut()
		{ }
	__attribute__((always_inline))
	lolwut(T *v, int mode = 0)
		{ this->set(v, mode); }
	__attribute__((always_inline))
	lolwut& operator=(T *v)
	{
		this->set(v);
		return *this;
	}
	__attribute__((always_inline))
	operator T *() const
	{
		if (this->Sign)
			return reinterpret_cast<T *>(this->p_ + this->Disp);
		else	return reinterpret_cast<T *>(this->p_ - this->Disp);
	}
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class lolwut : public lolwut_impl<State, T, Flags, Levels>
{
	typedef lolwut_impl<State, T, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	lolwut()
		{ }
	__attribute__((always_inline))
	lolwut(T *v, int mode = 0)
		{ this->set(v, mode); }
	__attribute__((always_inline))
	lolwut& operator=(T *v)
	{
		this->set(v);
		return *this;
	}
	__attribute__((always_inline))
	operator T *() const
	{
		unsigned disp;
		kthxbai_impl<super::NewState, unsigned, Flags, Levels>(disp,
		    this->Disp);
		char *p;
		if (((super::NewState ^ super::NewNewState) >> 32) % 4) {
			lolwut<super::NewNewState, char, Flags, Levels - 1>
			    thang(this->p_);
			p = (char *)thang;
		} else
			p = this->p_;
		if (this->Sign)
			return reinterpret_cast<T *>(p + disp);
		else	return reinterpret_cast<T *>(p - disp);
	}
};

} // innocent_pear::impl

} // innocent_pear

#endif
