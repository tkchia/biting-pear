#ifndef innocent_pear_H_YODAWG
#define innocent_pear_H_YODAWG

#include <cstddef>
#include <innocent-pear/dawg.h>

namespace innocent_pear
{

template<impl::rand_state_t State, impl::ops_flags_t Flags, wchar_t... Chs>
    using yodawg = impl::dawg_impl<State, wchar_t, Flags, Chs...>;

} // innocent_pear

#endif
