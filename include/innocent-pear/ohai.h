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
	T b_[N];
    public:
	__attribute__((always_inline))
	operator T *()
		{ return b_; }
	__attribute__((always_inline))
	~ohai()
	{
		int c;
		__asm __volatile("" : "=g" (c));
		std::memset(b_, (int)(unsigned char)c, N * sizeof(T));
	}
};

} // innocent_pear::impl

using impl::ohai;

} // innocent_pear

#endif
