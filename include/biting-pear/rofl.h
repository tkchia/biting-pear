#ifndef biting_pear_H_ROFL
#define biting_pear_H_ROFL

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <type_traits>
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
		{ return sizeof(x) > sizeof(uintptr_t) || wutwut(xs...); }
	template<class T>
	__attribute__((always_inline))
	static uintptr_t re_arg(T x)
	{
		if (std::is_integral<T>::value || std::is_enum<T>::value)
			return (uintptr_t)x;
		union {
			uintptr_t up;
			T x;
		} u = { 0, };
		u.x = x;
		return u.up;
	}
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
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (re_arg(x1))
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
		    : "0" (re_scno(scno)), "b" (re_arg(x1)), "c" (re_arg(x2))
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
		    : "0" (re_scno(scno)), "b" (re_arg(x1)), "c" (re_arg(x2)),
		      "d" (re_arg(x3))
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
		    : "0" (re_scno(scno)), "b" (re_arg(x1)), "c" (re_arg(x2)),
		      "d" (re_arg(x3)), "S" (re_arg(x4))
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
		__asm __volatile("int $0x80"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "b" (re_arg(x1)), "c" (re_arg(x2)),
		      "d" (re_arg(x3)), "S" (re_arg(x4)), "D" (re_arg(x5))
		    : "memory", "cc");
		return re_rv(rv);
	}
#   elif defined __amd64__
    public:
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		long rv;
		__asm __volatile("syscall"
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
		__asm __volatile("syscall"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "D" (re_arg(x1))
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
		__asm __volatile("syscall"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "D" (re_arg(x1)), "S" (re_arg(x2))
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
		__asm __volatile("syscall"
		    : "=a" (rv)
		    : "0" (re_scno(scno)), "D" (re_arg(x1)), "S" (re_arg(x2)),
		      "d" (re_arg(x3))
		    : "memory", "cc");
		return re_rv(rv);
	}
#   elif defined __arm__ && defined __thumb__
    public:
		/*
		 * It will be good if I can use the __asm("r0") style of
		 * register variables to specify exactly which values go
		 * where.  Alas, PR 15089 (https://gcc.gnu.org/bugzilla/
		 * show_bug.cgi?id=15089), which was _supposedly_ fixed in
		 * gcc 4, for some reason still crops up under g++ 5.3.1, so
		 * an __asm("r0") does not actually guarantee that a value
		 * will go into r0 (!).
		 *
		 * To work around this, I use operand constraints, combined
		 * with clobber lists, to force the compiler to assign
		 * values to registers the way I want.
		 *
		 * g++ 5 has a semi-documented "Cs" (caller saves)
		 * constraint which we can use to distinguish between r0--r3
		 * and r4--r7.  g++ 4 does not have "Cs" though, so I
		 * arrange to put the syscall number in a high register
		 * (r8--r12) before moving it into r7, which is not very
		 * optimal.
		 *
		 * A side effect of using clobber lists, is that many
		 * registers which are not touched at all by the syscall are
		 * considered by the compiler to be clobbered.
		 */
#	define biting_pear_ASM_REG_CHK(rx, ry) \
		".ifnc " rx ", " ry "; " \
		".error \"biting_pear::rofl_impl_syscall<...>: " \
		    "line " biting_pear_STRINGIZE(__LINE__) ": " \
		    "value meant for " ry " goes to " rx "!\"; " \
		".endif; "
#	if __GNUC__ >= 5
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		typedef unsigned long long RP;
		long rscno = re_scno(scno), rv;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 biting_pear_ASM_REG_CHK("%1", "r7")
				 "svc #0"
		    : "=Cs" (rv), "=l" (rscno)
		    : "1" (rscno)
		    : "r1", "r2", "r3", "r4", "r5", "r6", "ip",
		      "memory", "cc");
		return re_rv(rv);
	}
	template<class T1>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1)
	{
		typedef unsigned long long RP;
		if (wutwut(x1))
			return use_libc_syscall(scno, x1);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1);
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 biting_pear_ASM_REG_CHK("%1", "r7")
				 "svc #0"
		    : "=Cs" (z1), "=l" (rscno)
		    : "0" (z1), "1" (rscno)
		    : "r1", "r2", "r3", "r4", "r5", "r6", "ip",
		      "memory", "cc");
		return re_rv((long)z1);
	}
	template<class T1, class T2>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2)
	{
		typedef unsigned long long RP;
		if (wutwut(x1, x2))
			return use_libc_syscall(scno, x1, x2);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1), z2 = re_arg(x2);
		RP z1z2 = (RP)z1 | (RP)z2 << 32;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 biting_pear_ASM_REG_CHK("%1", "r7")
				 "svc #0"
		    : "=Cs" (z1z2), "=l" (rscno)
		    : "0" (z1z2), "1" (rscno)
		    : "r2", "r3", "r4", "r5", "r6", "ip", "memory", "cc");
		return re_rv((long)z1z2);
	}
	template<class T1, class T2, class T3>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3)
	{
		typedef unsigned long long RP;
		if (wutwut(x1, x2, x3))
			return use_libc_syscall(scno, x1, x2, x3);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1), z2 = re_arg(x2), z3 = re_arg(x3);
		RP z1z2 = (RP)z1 | (RP)z2 << 32;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 biting_pear_ASM_REG_CHK("%1", "r2")
				 biting_pear_ASM_REG_CHK("%2", "r7")
				 "svc #0"
		    : "=Cs" (z1z2), "=Cs" (z3), "=l" (rscno)
		    : "0" (z1z2), "1" (z3), "2" (rscno)
		    : "r3", "r4", "r5", "r6", "ip", "memory", "cc");
		return re_rv((long)z1z2);
	}
#	else /* if instead __GNUC__ < 5... */
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		typedef unsigned long long RP;
		long rscno = re_scno(scno), rv;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 "mov r7, %1; svc #0"
		    : "=l" (rv), "=h" (rscno)
		    : "1" (rscno)
		    : "r1", "r2", "r3", "r4", "r5", "r6", "r7",
		      "memory", "cc");
		return re_rv(rv);
	}
	template<class T1>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1)
	{
		typedef unsigned long long RP;
		if (wutwut(x1))
			return use_libc_syscall(scno, x1);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1);
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 "mov r7, %1; svc #0"
		    : "=l" (z1), "=h" (rscno)
		    : "0" (z1), "1" (rscno)
		    : "r1", "r2", "r3", "r4", "r5", "r6", "r7",
		      "memory", "cc");
		return re_rv((long)z1);
	}
	template<class T1, class T2>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2)
	{
		typedef unsigned long long RP;
		if (wutwut(x1, x2))
			return use_libc_syscall(scno, x1, x2);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1), z2 = re_arg(x2);
		RP z1z2 = (RP)z1 | (RP)z2 << 32;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 "mov r7, %1; svc #0"
		    : "=l" (z1z2), "=h" (rscno)
		    : "0" (z1z2), "1" (rscno)
		    : "r2", "r3", "r4", "r5", "r6", "r7", "memory", "cc");
		return re_rv((long)z1z2);
	}
	template<class T1, class T2, class T3>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3)
	{
		typedef unsigned long long RP;
		if (wutwut(x1, x2, x3))
			return use_libc_syscall(scno, x1, x2, x3);
		long rscno = re_scno(scno);
		uintptr_t z1 = re_arg(x1), z2 = re_arg(x2), z3 = re_arg(x3);
		RP z1z2 = (RP)z1 | (RP)z2 << 32;
		__asm __volatile(biting_pear_ASM_REG_CHK("%0", "r0")
				 biting_pear_ASM_REG_CHK("%1", "r2")
				 "mov r7, %2; svc #0"
		    : "=l" (z1z2), "=l" (z3), "=h" (rscno)
		    : "0" (z1z2), "1" (z3), "2" (rscno)
		    : "r3", "r4", "r5", "r6", "r7", "memory", "cc");
		return re_rv((long)z1z2);
	}
#	endif
#	undef biting_pear_ASM_REG_CHK
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
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(125, addr, len, prot);
#elif defined __linux__ && defined __amd64__
		return super::syscall(10, addr, len, prot);
#else
		int rv = (kthxbai<NewState2, biting_pear_decltype(&mprotect),
		    Flags, Levels>(mprotect))(addr, len, prot);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_clear_cache :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret
	clear_cache(void *start, void *end)
	{
#if defined __linux__ && defined __arm__
		biting_pear::kthxbai<super::NewState, unsigned, Flags, Levels>
		    zero(0);
		return super::syscall(0xf0002, start, end, (unsigned)zero);
#else
		__builtin___clear_cache(start, end);
		return typename super::syscall_ret(0, 0);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_memset :
    virtual public rofl_impl_base<State>,
    virtual public rofl_impl_clear_cache<State, Flags, Levels>
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
		typedef rofl_impl_base<State> super1;
		typedef rofl_impl_clear_cache<State, Flags, Levels> super2;
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
		biting_pear::kthxbai<super1::NewState, unsigned, Flags, Levels>
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
		super2::clear_cache(s, foo);
#   undef biting_pear_T16_INSN
#else
		biting_pear::kthxbai<NewState,
		    biting_pear_decltype(&std::memset),
		    Flags, Levels> f(std::memset);
		/* A rather slippery method.  But it works.  So far. */
		f(s, 0, (char *)&&foo - (char *)s);
	    foo:
		super2::clear_cache(s, &&foo);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags = 0, unsigned Levels = 2u>
class rofl : virtual public rofl_impl_memset<State, Flags, Levels>,
	     virtual public rofl_impl_mprotect<State, Flags, Levels>,
	     virtual public rofl_impl_clear_cache<State, Flags, Levels>
	{ };

#undef biting_pear_STRINGIZE
#undef biting_pear_STRINGIZE_1

} // biting_pear::impl

using impl::rofl;

} // biting_pear

#endif
