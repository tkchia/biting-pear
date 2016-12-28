#ifndef innocent_pear_H_TEH
#define innocent_pear_H_TEH

#include <innocent-pear/bbq.h>

namespace innocent_pear
{

namespace impl
{

template<class T, T V, rand_state_t State>
struct
#ifdef __ELF__
__attribute__((visibility("hidden")))
#endif
teh
{
	static T x;
};

template<class T, T V, rand_state_t State>
T teh<T, V, State>::x = V;

} // innocent_pear::impl

} // innocent_pear

#endif
