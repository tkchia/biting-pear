#ifndef innocent_pear_H_TEH
#define innocent_pear_H_TEH

namespace innocent_pear
{

namespace impl
{

template<class T, T V>
struct
#ifdef __ELF__
__attribute__((visibility("hidden")))
#endif
teh
{
	static T x;
};

template<class T, T V>
T teh<T, V>::x = V;

} // innocent_pear::impl

} // innocent_pear

#endif
