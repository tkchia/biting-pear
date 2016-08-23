#ifndef innocent_pear_H_ROFL
#define innocent_pear_H_ROFL

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <sys/mman.h>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
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
#endif

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai;  // forward

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
	    NewState4 = update_outer(State4, Levels);
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
#	if __GNUC__ >= 5
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
		 * and r4--r7.  g++ 4 does not have "Cs" though. :-(
		 *
		 * A side effect of using clobber lists, is that many
		 * registers which are not touched at all by the syscall are
		 * considered by the compiler to be clobbered.
		 */
	__attribute__((always_inline))
	static long syscall_raw(uintptr_t x1, uintptr_t x2, uintptr_t x3,
	    long scno)
	{
		typedef unsigned long long RP;
		RP x1x2 = (RP)x1 | (RP)x2 << 32, rv;
		__asm __volatile("mov r2, %2; svc #0"
		    : "=Cs" (rv)
		    : "0" (x1x2), "h" (x3), "l" (scno)
		    : "r2", "r3", "r4", "r5", "r6", "memory", "cc");
		return (long)rv;
	}
#	else	/* __GNUC__ < 5 */
	__attribute__((noinline, naked))
	static long syscall_raw(uintptr_t x1, uintptr_t x2, uintptr_t x3,
	    long scno)
	{
		/* assume Thumb support means `bx lr' support... */
		__asm("push {r7, lr}; "
		      "mov r7, r3; "
		      "svc #0; "
		      "pop {r7, lr}; "
		      "bx lr");
	}
#	endif
    public:
	__attribute__((always_inline))
	static syscall_ret syscall(long scno)
	{
		uintptr_t x1, x2, x3;
		__asm("" : "=r" (x1), "=r" (x2), "=r" (x3));
		return re_rv(syscall_raw(x1, x2, x3, re_scno(scno)));
	}
	template<class T1>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1)
	{
		uintptr_t x2, x3;
		if (wutwut(x1))
			return use_libc_syscall(scno, x1);
		__asm("" : "=r" (x2), "=r" (x3));
		return re_rv(syscall_raw(re_arg(x1), x2, x3, re_scno(scno)));
	}
	template<class T1, class T2>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2)
	{
		uintptr_t x3;
		if (wutwut(x1, x2))
			return use_libc_syscall(scno, x1, x2);
		__asm("" : "=r" (x3));
		return re_rv(syscall_raw(re_arg(x1), re_arg(x2), x3,
		    re_scno(scno)));
	}
	template<class T1, class T2, class T3>
	__attribute__((always_inline))
	static syscall_ret syscall(long scno, T1 x1, T2 x2, T3 x3)
	{
		if (wutwut(x1, x2, x3))
			return use_libc_syscall(scno, x1, x2, x3);
		return re_rv(syscall_raw(re_arg(x1), re_arg(x2), re_arg(x3),
		    re_scno(scno)));
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
		std::fprintf(stderr, "mprotect(%p, %#zx, %#x)\n", addr,
		    len, (unsigned)prot);
#endif
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(125, addr, len, prot);
#elif defined __linux__ && defined __amd64__
		return super::syscall(10, addr, len, prot);
#else
		int rv = (kthxbai<super::NewState2,
		    innocent_pear_decltype(&mprotect),
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
		kthxbai<super::NewState, unsigned, Flags, Levels> zero(0);
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
		long rv = (kthxbai<super::NewState2,innocent_pear_decltype(&ptrace), Flags, Levels>
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
#if defined innocent_pear_DEBUG
		if (req == PT_TRACE_ME) {
			static volatile bool traced = false;
			std::fprintf(stderr, "ptrace(%ld, %ld, %p, %p) = ",
			    (long)req, (long)pid, addr, data);
			if (!traced) {
				std::fprintf(stderr, "0\n");
				std::fflush(stderr);
				traced = true;
				return typename super::syscall_ret(0, 0);
			} else {
				std::fprintf(stderr, "-1; EPERM\n");
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
			    Levels>((unsigned)fd);
		if (__builtin_constant_p(req))
			req = kthxbai<super::NewState3, unsigned long,
			    Flags, Levels>(req);
#if defined __linux__ && (defined __i386__ || defined __arm__)
		return super::syscall(54, fd, req, args...);
#elif defined __linux__ && defined __amd64__
		return super::syscall(16, fd, req, args...);
#else
		int rv = (kthxbai<super::NewState2,
		    int (*)(int, unsigned long, ...), Flags, Levels>
		    (libc_ioctl))(fd, req, args...);
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
    defined innocent_pear_HAVE_CONST_TCOOFF && \
    defined innocent_pear_HAVE_CONST_TCOON
		if (action == innocent_pear_VAL_CONST_TCOOFF ||
		    action == innocent_pear_VAL_CONST_TCOON) {
			std::fprintf(stderr, "tcflow(%d, %d)\n", fd, action);
			return typename super::syscall_ret(0, 0);
		}
#endif
#ifdef innocent_pear_HAVE_CONST_TCXONC
		if (__builtin_constant_p(action))
			action = kthxbai<super::NewState4, unsigned, Flags,
			    Levels>((unsigned)action);
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
			    Levels>((unsigned)fd);
		int rv = (kthxbai<super::NewState2, int (*)(int, int),
		    Flags, Levels>(libc_tcflow))(fd, action);
		return typename super::syscall_ret(rv, errno);
#   else
		return typename super::syscall_ret(-1, ENOSYS);
#   endif
#endif
	}
};

template<rand_state_t State, ops_flags_t Flags = 0, unsigned Levels = 2u>
class rofl : virtual public rofl_impl_mprotect<State, Flags, Levels>,
	     virtual public rofl_impl_clear_cache<State, Flags, Levels>,
	     virtual public rofl_impl_memset<State, Flags, Levels>,
	     virtual public rofl_impl_ptrace<State, Flags, Levels>,
	     virtual public rofl_impl_getpid<State, Flags, Levels>,
	     virtual public rofl_impl_getppid<State, Flags, Levels>,
	     virtual public rofl_impl_kill<State, Flags, Levels>,
	     virtual public rofl_impl_ioctl<State, Flags, Levels>,
	     virtual public rofl_impl_tcflow<State, Flags, Levels>
	{ };

#undef innocent_pear_STRINGIZE
#undef innocent_pear_STRINGIZE_1

} // innocent_pear::impl

using impl::rofl;

} // innocent_pear

#endif
