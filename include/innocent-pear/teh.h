#ifndef innocent_pear_H_TEH
#define innocent_pear_H_TEH

#include <type_traits>
#include <innocent-pear/bbq.h>

namespace innocent_pear
{

namespace impl
{

template<class T, T V, unsigned WhichBin>
struct
#ifdef __ELF__
__attribute__((visibility("hidden")))
#endif
teh_impl
{
	static T x __attribute__((nocommon));
};

template<class T, T V, unsigned WhichBin>
T teh_impl<T, V, WhichBin>::x = V;

template<rand_state_t State, class T, T V>
using teh = teh_impl<
    typename std::conditional<
	creal(State, (rand_state_t)V) % 317u % 2u != 0,
	const T, T >::type,
    V, crealf(State, cpow((rand_state_t)V)) % 19u >;

} // innocent_pear::impl

} // innocent_pear

#endif
