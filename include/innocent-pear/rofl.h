#ifndef innocent_pear_H_ROFL
#define innocent_pear_H_ROFL

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <type_traits>
#include <sys/mman.h>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/omg.h>
/*
 * <sys/ptrace.h> pollutes the macro (and enum) namespace a bit, but we
 * include it since it is non-trivial to guess the correct prototype for
 * ptrace(...)...
 */
#ifdef innocent_pear_HAVE_FUNC_PTRACE
#   include <unistd.h>
#   include <sys/ptrace.h>
#endif
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#   ifdef __linux__
#	include <linux/prctl.h>
#   endif
#endif

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg;  // forward

template<rand_state_t State, unsigned Levels>
class rofl_impl_base
{
    protected:
	static constexpr rand_state_t
	    NewState = update_outer(State, Levels),
	    State2 = update_inner(State),
	    NewState2 = update_outer(State2, Levels),
	    State3 = update_inner(State2),
	    NewState3 = update_outer(State3, Levels),
	    State4 = update_inner(State3),
	    NewState4 = update_outer(State4, Levels),
	    State5 = update_inner(State4),
	    NewState5 = update_outer(State5, Levels),
	    NewState6 = update_outer(NewState5, Levels),
	    NewState7 = update_outer(NewState6, Levels),
	    NewState8 = update_outer(NewState7, Levels),
	    NewState9 = update_outer(NewState8, Levels);
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
#define innocent_pear_STRINGIZE(x) innocent_pear_STRINGIZE_1(x)
#define innocent_pear_STRINGIZE_1(x) #x
extern long libc_syscall(long scno, ...)
    __asm(innocent_pear_STRINGIZE(__USER_LABEL_PREFIX__) "syscall");
/*
 * Also do not include <sys/ioctl.h> if we do not have to, since this file
 * greatly pollutes the macro namespace with all its ioctl numbers. 
 * Similarly for <sys/termios.h>, which defines tcflow(...).
 */
extern int libc_ioctl(int fd, unsigned long request, ...)
    __asm(innocent_pear_STRINGIZE(__USER_LABEL_PREFIX__) "ioctl");
extern int libc_tcflow(int fd, int action)
    __asm(innocent_pear_STRINGIZE(__USER_LABEL_PREFIX__) "tcflow");

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_syscall : virtual public rofl_impl_base<State, Levels>
{
	typedef rofl_impl_base<State, Levels> super;
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
		typedef rofl_impl_base<State, Levels> super;
		kthxbai<super::NewState, unsigned long, Flags, Levels>
		    no(scno);
		return (long)(unsigned long)no;
	}
	template<class... Ts>
	__attribute__((always_inline))
	static syscall_ret use_libc_syscall(long scno, Ts... xs)
	{
		typedef rofl_impl_base<State, Levels> super;
		kthxbai<super::NewState, long (*)(long, ...), Flags, Levels>
		    scf(libc_syscall);
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
		if (std::is_integral<T>::value || std::is_enum<T>::value ||
		    std::is_pointer<T>::value)
			return (uintptr_t)x;
		union {
			uintptr_t up;
			T x;
		} u = { 0, };
		u.x = x;
		return u.up;
	}
#   if defined __i386__ && !defined __clang__ && __GNUC__ < 5
#	pragma message \
	    "may emit inferior code, as g++ < 5 cannot spill %ebx"
#   elif defined __i386__ && (defined __clang__ || __GNUC__ >= 5)
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
#	ifndef __clang__
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
#	else
	/*
	 * clang++ may run out of registers when compiling rofl<...>::ptrace
	 * (PT_TRACE_ME, ...), which has 4 arguments.  Fall back on using the
	 * library routine...
	 */
#	endif
#   elif defined __amd64__
    public:
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		long rv;
		__asm __volatile("syscall"
		    : "=a" (rv)
		    : "0" (re_scno(scno))
		    : "rcx", "r11", "memory", "cc");
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
		    : "rcx", "r11", "memory", "cc");
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
		    : "rcx", "r11", "memory", "cc");
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
		    : "rcx", "r11", "memory", "cc");
		return re_rv(rv);
	}
#   elif defined __arm__ && defined __thumb__
    private:
	typedef omg<super::NewState5, uintptr_t, Flags,
	    Levels ? Levels - 1 : 0> omg5;
	typedef omg<super::NewState6, uintptr_t, Flags,
	    Levels ? Levels - 1 : 0> omg6;
	typedef omg<super::NewState7, uintptr_t, Flags,
	    Levels ? Levels - 1 : 0> omg7;
	typedef omg<super::NewState8, uintptr_t, Flags,
	    Levels ? Levels - 1 : 0> omg8;
	typedef omg<super::NewState9, uintptr_t, Flags,
	    Levels ? Levels - 1 : 0> omg9;
    public:
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		constexpr unsigned Which =
		    pick_hi<unsigned>(super::State2 ^ super::State3) % 3;
		long rv;
		uintptr_t x1;
		switch (Which) {
		    case 0:
			__asm __volatile("movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno))
			    : "r0", "r7", "memory");
			return re_rv(rv);
#	if __GNUC__ >= 5
		    case 1:
			__asm __volatile("movs r7, %1; "
					 "svc #0; "
			    : "=Cs" (rv)
			    : "rI" (re_scno(scno))
			    : "r1", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
#	endif
		    default:
			{ omg5 zomg(x1); }
			return syscall(scno, x1);
		}
	}
	template<class T1>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1)
	{
		constexpr unsigned Which =
		    pick_hi<unsigned>(super::State2 ^ super::State3) % 3;
		if (wutwut(x1))
			return use_libc_syscall(scno, x1);
		long rv;
		uintptr_t x2;
		switch (Which) {
		    case 0:
			__asm __volatile("movs r0, %2; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1))
			    : "r0", "r7", "memory");
			return re_rv(rv);
#	if __GNUC__ >= 5
		    case 1:
			__asm __volatile("movs r7, %1; "
					 "svc #0"
			    : "=Cs" (rv)
			    : "rI" (re_scno(scno)), "0" (re_arg(x1))
			    : "r1", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
#	endif
		    default:
			{ omg6 zomg(x2); }
			return syscall(scno, x1, x2);
		}
	}
	template<class T1, class T2>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2)
	{
		constexpr unsigned Which =
		    pick_hi<unsigned>(super::State2 ^ super::State3) % 6;
		if (wutwut(x1, x2))
			return use_libc_syscall(scno, x1, x2);
		long rv;
		uintptr_t x3;
		switch (Which) {
		    case 0:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2))
			    : "r0", "r1", "r7", "memory");
			return re_rv(rv);
#	if __GNUC__ >= 5
		    case 1:
			__asm __volatile("movs r1, %3; "
					 "movs r7, %1; "
					 "svc #0"
			    : "=Cs" (rv)
			    : "rI" (re_scno(scno)), "0" (re_arg(x1)),
			      "rI" (re_arg(x2))
			    : "r1", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 2:
		    case 3:
			__asm __volatile("movs r0, %2; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "Cs" (re_arg(x2))
			    : "r0", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
#	endif
		    default:
			{ omg7 zomg(x3); }
			return syscall(scno, x1, x2, x3);
		}
	}
	template<class T1, class T2, class T3>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3)
	{
		constexpr unsigned Which =
		    pick_hi<unsigned>(super::State2 ^ super::State3) % 9;
		if (wutwut(x1, x2, x3))
			return use_libc_syscall(scno, x1, x2, x3);
		long rv;
		uintptr_t x4;
		switch (Which) {
		    case 0:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r2, %4; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2)), "rI" (re_arg(x3))
			    : "r0", "r1", "r2", "r7", "memory");
			return re_rv(rv);
#	if __GNUC__ >= 5
		    case 1:
			__asm __volatile("movs r1, %3; "
					 "movs r2, %4; "
					 "movs r7, %1; "
					 "svc #0"
			    : "=Cs" (rv)
			    : "rI" (re_scno(scno)), "0" (re_arg(x1)),
			      "rI" (re_arg(x2)), "rI" (re_arg(x3))
			    : "r1", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 2:
			__asm __volatile("movs r0, %2; "
					 "movs r2, %4; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "Cs" (re_arg(x2)), "rI" (re_arg(x3))
			    : "r0", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 3:
		    case 4:
		    case 5:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2)), "Cs" (re_arg(x3))
			    : "r0", "r1", "r3", "r7", "ip", "memory");
			return re_rv(rv);
#	endif
		    default:
			{ omg8 zomg(x4); }
			return syscall(scno, x1, x2, x3, x4);
		}
	}
	template<class T1, class T2, class T3, class T4>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3, T4 x4)
	{
		constexpr unsigned Which =
		    pick_hi<unsigned>(super::State2 ^ super::State3) % 12;
		if (wutwut(x1, x2, x3, x4))
			return use_libc_syscall(scno, x1, x2, x3, x4);
		long rv;
		uintptr_t x5;
		switch (Which) {
		    case 0:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r2, %4; "
					 "movs r3, %5; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2)), "rI" (re_arg(x3)),
			      "rI" (re_arg(x4))
			    : "r0", "r1", "r2", "r7", "memory");
			return re_rv(rv);
#	if __GNUC__ >= 5
		    case 1:
			__asm __volatile("movs r1, %3; "
					 "movs r2, %4; "
					 "movs r3, %5; "
					 "movs r7, %1; "
					 "svc #0"
			    : "=Cs" (rv)
			    : "rI" (re_scno(scno)), "0" (re_arg(x1)),
			      "rI" (re_arg(x2)), "rI" (re_arg(x3)),
			      "rI" (re_arg(x4))
			    : "r1", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 2:
			__asm __volatile("movs r0, %2; "
					 "movs r2, %4; "
					 "movs r3, %5; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "Cs" (re_arg(x2)), "rI" (re_arg(x3)),
			      "rI" (re_arg(x4))
			    : "r0", "r2", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 3:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r3, %5; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2)), "Cs" (re_arg(x3)),
			      "rI" (re_arg(x4))
			    : "r0", "r1", "r3", "r7", "ip", "memory");
			return re_rv(rv);
		    case 4:
		    case 5:
		    case 6:
		    case 7:
			__asm __volatile("movs r0, %2; "
					 "movs r1, %3; "
					 "movs r2, %4; "
					 "movs r7, %1; "
					 "svc #0; "
					 "movs %0, r0"
			    : "=r" (rv)
			    : "rI" (re_scno(scno)), "rI" (re_arg(x1)),
			      "rI" (re_arg(x2)), "rI" (re_arg(x3)),
			      "Cs" (re_arg(x4))
			    : "r0", "r1", "r2", "r7", "ip", "memory");
			return re_rv(rv);
#	endif
		    default:
			{ omg9 zomg(x5); }
			return syscall(scno, x1, x2, x3, x4, x5);
		}
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
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "mprotect(%p, %#zx, %#x)", addr,
		    len, (unsigned)prot);
#endif
		if (__builtin_constant_p(prot))
			prot = kthxbai<super::NewState3, unsigned, Flags,
			    Levels ? Levels - 1 : 0>((unsigned)prot);
#if defined __linux__ && (defined __i386__ || defined __arm__)
		typename super::syscall_ret ret
		    (super::syscall(125, addr, len, prot));
#elif defined __linux__ && defined __amd64__
		typename super::syscall_ret ret
		    (super::syscall(10, addr, len, prot));
#else
		int rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&mprotect),
		    Flags, Levels>(mprotect))(addr, len, prot);
		typename super::syscall_ret ret(rv, errno);
#endif
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, " = %ld; %d\n", (long)ret, ret.err());
#endif
		return ret;
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
		kthxbai<super::NewState, unsigned, Flags,
		    Levels ? Levels - 1 : 0> zero(0);
		return super::syscall(0xf0002, start, end, (unsigned)zero);
#else
		__builtin___clear_cache((char *)start, (char *)end);
		return typename super::syscall_ret(0, 0);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_memset :
    virtual public rofl_impl_base<State, Levels>,
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
		typedef rofl_impl_base<State, Levels> super1;
		typedef rofl_impl_clear_cache<State, Flags, Levels> super2;
		void *x, *y, *foo;
		/*
		 * Should work under ARM, Thumb-16, and Thumb-32 modes.  The
		 * difference between "divided" and "unified" Thumb-16
		 * syntax is a pain to handle...
		 */
#   if defined __thumb__ && !defined __thumb2__
#	define innocent_pear_T16_INSN(insn, d, n) insn " " d ", " n "; "
#   else
#	define innocent_pear_T16_INSN(insn, d, n) insn "s " \
						  d ", " d ", " n "; "
#   endif
		kthxbai<super1::NewState, unsigned, Flags, Levels> three(3);
		__asm __volatile(
			innocent_pear_T16_INSN("bic", "%0", "%4")
			"adr %1, 2f; "
			innocent_pear_T16_INSN("sub", "%0", "%1")
			"beq 3f; "
			".balign 4; "
			"2: "
			"str %2, [%1, %0]; "
			innocent_pear_T16_INSN("add", "%0", "#4")
			"bne 2b; "
			"3: "
		    : "=l" (x), "=l" (foo), "=l" (y)
		    : "0" ((char *)s + 3), "l" ((unsigned)three)
		    : "memory", "cc");
		super2::clear_cache(s, foo);
#   undef innocent_pear_T16_INSN
#else
		innocent_pear::kthxbai<NewState,
		    innocent_pear_decltype(&std::memset),
		    Flags, Levels> f(std::memset);
		/* A rather slippery method.  But it works.  So far. */
		f(s, 0, (char *)&&foo - (char *)s);
	    foo:
		super2::clear_cache(s, &&foo);
#endif
	}
};

#ifdef innocent_pear_DEBUG
/*
 * This needs to be common to, and thus outside of, all template
 * instantiations.
 */
__attribute__((weak)) unsigned long ptrace_counter = 0;
#endif

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_ptrace :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
#ifdef innocent_pear_HAVE_FUNC_PTRACE
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret
	ptrace_lib(Ts... xs)
	{
		long rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&ptrace), Flags, Levels>
		    (ptrace))(xs...);
		return typename super::syscall_ret(rv, errno);
	}
#endif
    public:
#ifdef __linux__
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret
	ptrace_raw(Ts... xs)
	{
#   if defined __amd64__
		return super::syscall(101, xs...);
#   else
		return super::syscall(26, xs...);
#   endif
	}
#endif
	__attribute__((always_inline))
	static typename super::syscall_ret
	ptrace(
#ifdef innocent_pear_HAVE_CONST_PT_TRACE_ME
	    innocent_pear_decltype(PT_TRACE_ME)
#else
	    int
#endif
	    req, pid_t pid, void *addr, void *data)
	{
#ifdef innocent_pear_DEBUG
		if (req == PT_TRACE_ME) {
			unsigned long k = __atomic_fetch_add(&ptrace_counter,
			    1, __ATOMIC_SEQ_CST);
			if (k > 200)
				return typename super::syscall_ret(-1, EPERM);
			std::fprintf(stderr, "ptrace(%ld, %ld, %p, %p) = ",
			    (long)req, (long)pid, addr, data);
			if (!k) {
				std::fprintf(stderr, "0\n");
				std::fflush(stderr);
				return typename super::syscall_ret(0, 0);
			} else {
				std::fprintf(stderr, "-1; EPERM%s\n",
				    k == 200 ? " ..." : "");
				std::fflush(stderr);
				return typename super::syscall_ret(-1, EPERM);
			}
		}
#endif
#if defined __linux__ && \
    (defined __amd64__ || defined __i386__ || defined _arm__)
		if (
#   if defined innocent_pear_HAVE_CONST_PT_READ_D
		    req == PT_READ_D ||
#   endif
#   if defined innocent_pear_HAVE_CONST_PT_READ_I
		    req == PT_READ_I ||
#   endif
#   if defined innocent_pear_HAVE_CONST_PT_READ_U
		    req == PT_READ_U ||
#   endif
		    false) {
			long val;
			typename super::syscall_ret rv =
			    ptrace_raw(req, pid, addr, &val);
			if (rv == 0)
				return typename super::syscall_ret(val, 0);
			return rv;
		} else
			return ptrace_raw(req, pid, addr, data);
#elif defined innocent_pear_HAVE_FUNC_PTRACE
		return ptrace_lib(req, pid, addr, data);
#else
		return typename super::syscall_ret(-1, ENOSYS);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_getpid :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret getpid()
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(20);
#elif defined __linux__ && defined __amd64__
		return super::syscall(39);
#else
		int rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&getpid), Flags, Levels>(getpid))();
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_getppid :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret getppid()
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(64);
#elif defined __linux__ && defined __amd64__
		return super::syscall(110);
#else
		int rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&getppid), Flags, Levels>
		    (getppid))();
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_kill :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret kill(pid_t pid, int sig)
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(37, pid, sig);
#elif defined __linux__ && defined __amd64__
		return super::syscall(62, pid, sig);
#else
		int rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&kill), Flags, Levels>(kill))
		    (pid, sig);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_ioctl :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret ioctl(int fd, unsigned long req,
	    Ts... args)
	{
		if (__builtin_constant_p(fd))
			fd = kthxbai<super::NewState4, unsigned, Flags,
			    Levels ? Levels - 1 : 0>((unsigned)fd);
		if (__builtin_constant_p(req))
			req = kthxbai<super::NewState3, unsigned long,
			    Flags, Levels ? Levels - 1 : 0>(req);
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(54, fd, req, args...);
#elif defined __linux__ && defined __amd64__
		return super::syscall(16, fd, req, args...);
#else
		int rv = (kthxbai<super::NewState2,
		    int (*)(int, unsigned long, ...), Flags, Levels>
		    (ioctl))(fd, req, args...);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_tcflow :
    virtual public rofl_impl_ioctl<State, Flags, Levels>
{
	typedef rofl_impl_ioctl<State, Flags, Levels> super;
    public:
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret tcflow(int fd, int action)
	{
#if defined innocent_pear_DEBUG && \
    defined innocent_pear_HAVE_CONST_TCOON
		if (action == innocent_pear_VAL_CONST_TCOON) {
			std::fprintf(stderr, "tcflow(%d, %d)\n", fd, action);
			return typename super::syscall_ret(0, 0);
		}
#endif
#if defined innocent_pear_DEBUG && \
    defined innocent_pear_HAVE_CONST_TCOOFF
		if (action == innocent_pear_VAL_CONST_TCOOFF) {
			static volatile unsigned long k_ = 0;
			unsigned long k = __atomic_fetch_add(&k_, 1,
			    __ATOMIC_SEQ_CST);
			if (k < 200)
				std::fprintf(stderr, "tcflow(%d, %d)\n", fd,
				    action);
			else if (k == 200)
				std::fprintf(stderr, "tcflow(%d, %d) ...\n",
				    fd, action);
			return typename super::syscall_ret(0, 0);
		}
#endif
#ifdef innocent_pear_HAVE_CONST_TCXONC
		if (__builtin_constant_p(action))
			action = kthxbai<super::NewState4, unsigned, Flags,
			    Levels ? Levels - 1 : 0>((unsigned)action);
		return super::ioctl(fd,innocent_pear_VAL_CONST_TCXONC,action);
#else
#   if defined innocent_pear_HAVE_CONST_TCOOFF && \
       defined innocent_pear_HAVE_CONST_TIOCSTOP
		if (__builtin_constant_p(action) &&
		    action == innocent_pear_VAL_CONST_TCOOFF)
			return super::ioctl(fd,
			    innocent_pear_VAL_CONST_TIOCSTOP);
#   endif
#   if defined innocent_pear_HAVE_CONST_TCOON && \
       defined innocent_pear_HAVE_CONST_TIOCSTART
		if (__builtin_constant_p(action) &&
		    action == innocent_pear_VAL_CONST_TCOON)
			return super::ioctl(fd,
			    innocent_pear_VAL_CONST_TIOCSTART);
#   endif
#   ifdef innocent_pear_HAVE_FUNC_TCFLOW
		if (__builtin_constant_p(fd))
			fd = kthxbai<super::NewState4, unsigned, Flags,
			    Levels ? Levels - 1 : 0>((unsigned)fd);
		int rv = (kthxbai<super::NewState2, int (*)(int, int),
		    Flags, Levels>(tcflow))(fd, action);
		return typename super::syscall_ret(rv, errno);
#   else
		return typename super::syscall_ret(-1, ENOSYS);
#   endif
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_open :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret open(const char *pathname,
	    int flags, Ts... args)
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(5, pathname, flags, args...);
#elif defined __linux__ && defined __amd64__
		return super::syscall(2, pathname, flags, args...);
#elif defined __linux__ && defined __aarch64__
		return super::syscall(1024, pathname, flags, args...);
#else
		int rv = (kthxbai<super::NewState2,
		    int (*)(int, unsigned long, ...), Flags, Levels>(open))
		    (pathname, flags, args...);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_close :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	template<class... Ts>
	__attribute__((always_inline))
	static typename super::syscall_ret close(int fd)
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(6, fd);
#elif defined __linux__ && defined __amd64__
		return super::syscall(3, fd);
#elif defined __linux__ && defined __aarch64__
		return super::syscall(57, fd);
#else
		int rv = (kthxbai<super::NewState2,
		    int (*)(int, unsigned long, ...), Flags, Levels>(close))
		    (fd);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_time :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret time(time_t *tp)
	{
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(13, tp);
#elif defined __linux__ && defined __amd64__
		return super::syscall(201, tp);
#elif defined __linux__ && defined __aarch64__
		return super::syscall(1062, tp);
#else
		int rv = (kthxbai<super::NewState2, time_t (*)(time_t *),
		    Flags, Levels>(time))(tp);
		return typename super::syscall_ret(rv, errno);
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl_impl_prctl :
    virtual public rofl_impl_syscall<State, Flags, Levels>
{
	typedef rofl_impl_syscall<State, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	static typename super::syscall_ret prctl(int option,
	    unsigned long arg2)
	{
		if (__builtin_constant_p(option))
			option = kthxbai<super::NewState3, unsigned, Flags,
			    Levels ? Levels - 1 : 0>((unsigned)option);
		if (__builtin_constant_p(arg2))
			arg2 = kthxbai<super::NewState4, unsigned long,
			    Flags, Levels ? Levels - 1 : 0>(arg2);
#if defined innocent_pear_DEBUG && defined __linux__
		if (option == PR_SET_DUMPABLE) {
			static volatile unsigned long k_ = 0;
			unsigned long k = __atomic_fetch_add(&k_, 1,
			    __ATOMIC_SEQ_CST);
			if (k < 200)
				std::fprintf(stderr, "prctl(%d, %lu)\n",
				    option, arg2);
			else if (k == 200)
				std::fprintf(stderr, "prctl(%d, %lu) ...\n",
				    option, arg2);
			return typename super::syscall_ret(0, 0);
		}
#endif
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(172, option, arg2);
#elif defined __linux__ && defined __amd64__
		return super::syscall(157, option, arg2);
#elif defined __linux__ && defined __aarch64__
		return super::syscall(167, option, arg2);
#elif defined innocent_pear_HAVE_FUNC_PRCTL
		int rv = (kthxbai<super::NewState2,
		    int (*)(int, unsigned long, ...), Flags, Levels>(prctl))
		    (option, arg2);
		return typename super::syscall_ret(rv, errno);
#else
		return typename super::syscall_ret(-1, ENOSYS);
#endif
	}
};

template<rand_state_t State,
    ops_flags_t Flags = innocent_pear::ops::allow_minimal,
    unsigned Levels = 3u>
class rofl : virtual public rofl_impl_mprotect<State, Flags, Levels>,
	     virtual public rofl_impl_clear_cache<State, Flags, Levels>,
	     virtual public rofl_impl_memset<State, Flags, Levels>,
	     virtual public rofl_impl_ptrace<State, Flags, Levels>,
	     virtual public rofl_impl_getpid<State, Flags, Levels>,
	     virtual public rofl_impl_getppid<State, Flags, Levels>,
	     virtual public rofl_impl_kill<State, Flags, Levels>,
	     virtual public rofl_impl_ioctl<State, Flags, Levels>,
	     virtual public rofl_impl_tcflow<State, Flags, Levels>,
	     virtual public rofl_impl_open<State, Flags, Levels>,
	     virtual public rofl_impl_close<State, Flags, Levels>,
	     virtual public rofl_impl_time<State, Flags, Levels>,
	     virtual public rofl_impl_prctl<State, Flags, Levels>
	{ };

#undef innocent_pear_STRINGIZE
#undef innocent_pear_STRINGIZE_1

} // innocent_pear::impl

using impl::rofl;

} // innocent_pear

#endif
