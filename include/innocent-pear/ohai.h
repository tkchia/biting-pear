#ifndef innocent_pear_H_OHAI
#define innocent_pear_H_OHAI

#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <innocent-pear/bbq.h>

namespace innocent_pear
{

namespace impl
{

template<class T, std::size_t N>
class ohai
{
	static_assert(std::is_pod<T>::value, "T in "
	    "innocent_pear::ohai<, T, ...> is not a \"plain old data\" type");
	enum { NP = ((N + 1) * sizeof(T) - 1) / sizeof(uintptr_t) };
	union {
		T t_[N];
		uintptr_t v_[NP];
	} u_;
    public:
	__attribute__((always_inline))
	operator T *()
		{ return u_.t_; }
	__attribute__((always_inline))
	~ohai()
	{
		uintptr_t x;
		std::size_t i;
		for (i = 0; i < NP; ++i) {
			__asm __volatile("" : "=g" (x));
			u_.v_[i] = x;
		}
	}
};

} // innocent_pear::impl

using impl::ohai;

} // innocent_pear

#endif
