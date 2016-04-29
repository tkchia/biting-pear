#ifndef biting_pear_H_ROFL
#define biting_pear_H_ROFL

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

namespace biting_pear
{

namespace impl
{

template<rand_state_t State>
class rofl_impl_base
{
    protected:
	static constexpr rand_state_t NewState = update_outer(State);
	static constexpr rand_state_t State2 = update_inner(State);
	static constexpr rand_state_t NewState2 = update_outer(State2);
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_memset : virtual public rofl_impl_base<State>
{
    public:
	__attribute__((always_inline))
	static void memset(void *s)
	{
#if defined __i386__
		void *edi, *ecx;
		__asm __volatile(
			"andl $-4, %%edi; "
			"call 1f; "
			"1: "
			"popl %%ecx; "
			"subl %%edi, %%ecx; "
			"addl $2f-1b, %%ecx; "
			"shrl $2, %%ecx; "
			".balign 4; "
			"2: "
			"rep; stosl"
		    : "=D" (edi), "=c" (ecx)
		    : "0" ((char *)s + 3) : "memory", "cc");
#elif defined __amd64__
		void *rdi, *rcx;
		__asm __volatile(
			"andq $-8, %%rdi; "
			"leaq 2f(%%rip), %%rcx; "
			"subq %%rdi, %%rcx; "
			"shrq $3, %%rcx; "
			".balign 8; "
			"2: "
			"rep; stosq; "		// .. 4 bytes
			"stosl"			// .:
		    : "=D" (rdi), "=c" (rcx)
		    : "0" ((char *)s + 7) : "memory", "cc");
#elif defined __arm__
		typedef rofl_impl_base<State> super;
		void *x, *y, *foo;
		/*
		 * Should work under ARM, Thumb-16, and Thumb-32 modes.  The
		 * difference between "divided" and "unified" Thumb-16
		 * syntax is a pain to handle...
		 */
#   if defined __thumb__ && !defined __thumb2__
#	define biting_pear_T16_INSN(insn, d, n) insn " " d ", " n "; "
#   else
#	define biting_pear_T16_INSN(insn, d, n) insn "s " d ", " d ", " n "; "
#   endif
		biting_pear::kthxbai<super::NewState, unsigned, Flags, Levels>
		    three(3);
		__asm __volatile(
			biting_pear_T16_INSN("bic", "%0", "%4")
			"adr %1, 2f; "
			biting_pear_T16_INSN("sub", "%0", "%1")
			"beq 3f; "
			".balign 4; "
			"2: "
			"str %2, [%1, %0]; "
			biting_pear_T16_INSN("add", "%0", "#4")
			"bne 2b; "
			"3: "
		    : "=l" (x), "=l" (foo), "=l" (y)
		    : "0" ((char *)s + 3), "l" ((unsigned)three)
		    : "memory", "cc");
		__builtin___clear_cache(s, foo);
#   undef biting_pear_T16_INSN
#else
		biting_pear::kthxbai<NewState,
		    biting_pear_decltype(&std::memset),
		    Flags, Levels> f(std::memset);
		/* A rather slippery method.  But it works.  So far. */
		f(s, 0, (char *)&&foo - (char *)s);
	    foo:
		__builtin___clear_cache(s, &&foo);
#endif
	}
};

/*
 * The Linux syscall(2) man page says to do this to get a declaration for
 * syscall(...):
 *
 *	#define _GNU_SOURCE
 *	#include <unistd.h>
 *	...
 *
 * However, doing so will force the caller to slurp in a bunch of
 * declarations for GNU extensions, whether the caller wants them or not.
 */
#define biting_pear_STRINGIZE(x) biting_pear_STRINGIZE_1(x)
#define biting_pear_STRINGIZE_1(x) #x
extern long libc_syscall(long scno, ...)
    __asm(biting_pear_STRINGIZE(__USER_LABEL_PREFIX__) "syscall");
#undef biting_pear_STRINGIZE
#undef biting_pear_STRINGIZE_1

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_syscall : virtual public rofl_impl_base<State>
{
    public:
	class syscall_ret
	{
		long rv_;
		int err_;
	    public:
		__attribute__((always_inline))
		syscall_ret(long rv, int err) : rv_(rv), err_(err)
			{ }
		__attribute__((always_inline))
		operator long()
			{ return rv_; }
		__attribute__((always_inline))
		int err()
			{ return err_; }
	};
    private:
	__attribute__((always_inline))
	static long re_scno(long scno)
	{
		typedef rofl_impl_base<State> super;
		kthxbai<super::NewState, unsigned long, Flags, Levels>
		    no(scno);
		return (long)(unsigned long)no;
	}
	template<class... Ts>
	__attribute__((always_inline))
	static syscall_ret use_libc_syscall(long scno, Ts... xs)
	{
		typedef rofl_impl_base<State> super;
		biting_pear::kthxbai<super::NewState, long (*)(long, ...),
		    Flags, Levels> scf(libc_syscall);
		long rv = scf(re_scno(scno), xs...);
		return syscall_ret(rv, errno);
	}
#ifdef __linux__
	__attribute__((always_inline))
	static syscall_ret re_rv(long rv)
	{
		if (rv < 0 && rv > -0x1000)
			return syscall_ret(-1, -rv);
		else
			return syscall_ret(rv, 0);
	}
	__attribute__((always_inline))
	static bool wutwut()
		{ return false; }
	template<class T, class... Ts>
	__attribute__((always_inline))
	static bool wutwut(T x, Ts... xs)
		{ return sizeof(x) > sizeof(long) || wutwut(xs...); }
#   if defined __i386__ && __GNUC__ < 5
#	pragma message \
	    "may emit inferior code, as g++ < 5 cannot spill %ebx"
#   elif defined __i386__ && __GNUC__ >= 5
    public:
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		long rv;
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno))
		    : "memory", "cc");
		return re_rv(rv);
	}
	template<class T1>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1)
	{
		if (wutwut(x1))
			return use_libc_syscall(scno, x1);
		long rv;
		__asm __volatile(
		    "int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (x1)
		    : "memory", "cc");
		return re_rv(rv);
	}
	template<class T1, class T2>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2)
	{
		if (wutwut(x1, x2))
			return use_libc_syscall(scno, x1, x2);
		long rv;
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (x1), "c" (x2)
		    : "memory", "cc");
		return re_rv(rv);
	}
	template<class T1, class T2, class T3>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3)
	{
		if (wutwut(x1, x2, x3))
			return use_libc_syscall(scno, x1, x2, x3);
		long rv;
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (x1), "c" (x2), "d" (x3)
		    : "memory", "cc");
		return re_rv(rv);
	}
	template<class T1, class T2, class T3, class T4>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		if (wutwut(x1, x2, x3, x4))
			return use_libc_syscall(scno, x1, x2, x3, x4);
		long rv;
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (x1), "c" (x2), "d" (x3),
		      "S" (x4)
		    : "memory", "cc");
		return re_rv(rv);
	}
	template<class T1, class T2, class T3, class T4, class T5>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3, T4 x4,
	T5 x5)
	{
		if (wutwut(x1, x2, x3, x4, x5))
			return use_libc_syscall(scno, x1, x2, x3, x4, x5);
		long rv;
		__asm __volatile("int $0x80" : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (x1), "c" (x2), "d" (x3),
		      "S" (x4), "D" (x5)
		    : "memory", "cc");
		return re_rv(rv);
	}
#   endif
#endif
    public:
	template<class... Ts>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, Ts... xs)
		{ return use_libc_syscall(scno, xs...); }
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_mprotect :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret
	mprotect(void *addr, std::size_t len, int prot)
	{
#ifdef __linux__
		return super::syscall(125, addr, len, prot);
#else
		int rv = (kthxbai<NewState2, biting_pear_decltype(&mprotect),
		    Flags, Levels>(mprotect))(addr, len, prot);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags = 0, unsigned Levels = 2u>
class rofl : public rofl_impl_memset<State, Flags, Levels>,
	     public rofl_impl_mprotect<State, Flags, Levels>
	{ };

} // biting_pear::impl

using impl::rofl;

} // biting_pear

#endif