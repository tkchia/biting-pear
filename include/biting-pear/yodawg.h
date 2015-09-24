#ifndef biting_pear_H_YODAWG
#define biting_pear_H_YODAWG

#include <cstddef>
#include <biting-pear/dawg.h>

namespace biting_pear
{

template<impl::rand_state_t State, impl::ops_flags_t Flags, wchar_t... Chs>
    using yodawg = impl::dawg_impl<State, wchar_t, Flags, Chs...>;

} // biting_pear

#endif
