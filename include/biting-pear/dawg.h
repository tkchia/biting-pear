#ifndef biting_pear_H_DAWG
#define biting_pear_H_DAWG

#include <climits>
#include <cstdlib>
#include <ostream>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

#ifndef biting_pear_HAVE_CXX_VAR_TPLS
#   error "this header needs support for C++11 variadic templates"
#endif

namespace biting_pear
{

namespace impl
{

template<rand_state_t State, class CT, ops_flags_t Flags, CT... Chs>
class dawg_impl;

template<rand_state_t State, class CT, ops_flags_t Flags>
class dawg_impl<State, CT, Flags>
{
    public:
	__attribute__((always_inline))
	dawg_impl()
		{ }
	__attribute__((always_inline))
	dawg_impl(const dawg_impl<State, CT, Flags>& x)
		{ }
	__attribute__((always_inline))
	static CT front()
		{ __builtin_unreachable(); }
	__attribute__((always_inline))
	CT operator[](std::size_t i) const
		{ __builtin_unreachable(); }
	__attribute__((always_inline))
	static std::size_t size()
		{ return 0; }
};

template<rand_state_t State, class CT, ops_flags_t Flags, CT Ch, CT... Chs>
class dawg_impl<State, CT, Flags, Ch, Chs...>
{
	typedef biting_pear_decltype(1u | (CT)1 << 0u) PCT; // N3797 5.8.2
	static constexpr rand_state_t State2 = update_inner(State);
	static constexpr rand_state_t State3 = update_inner(State2);
	static constexpr rand_state_t State4 = update_inner(State3);
	static constexpr rand_state_t NewState = update_outer(State2);
	typedef dawg_impl<State4, CT, Flags, Chs...> rest_type;
    public:
	__attribute__((always_inline))
	dawg_impl()
		{ }
	__attribute__((always_inline))
	dawg_impl(const dawg_impl<State, CT, Flags, Ch, Chs...>& x)
		{ }
	__attribute__((always_inline))
	static CT front()
	{
		static constexpr unsigned Levels =
		    ((State ^ NewState) >> 48 & 7) <= 2 ? 2u : 1u;
		if (sizeof(CT) == sizeof(char))
			return (CT)(PCT)kthxbai<NewState, PCT, Flags, Levels>
			    ((pick_hi<PCT>(State3^State4) & ~(PCT)UCHAR_MAX) |
				((PCT)Ch & UCHAR_MAX));
		else
			return (CT)(PCT)kthxbai<NewState, PCT, Flags, Levels>
			    (Ch);
	}
	__attribute__((always_inline))
	static rest_type rest()
		{ return rest_type(); }
	__attribute__((always_inline))
	CT operator[](std::size_t i) const
		{ return i == 0 ? front() : rest()[i - 1]; }
	__attribute__((always_inline))
	static std::size_t size()
		{ return 1u + sizeof...(Chs); }
};

} // biting_pear::impl

template<impl::rand_state_t State, impl::ops_flags_t Flags, char... Chs>
    using dawg = impl::dawg_impl<State, char, Flags, Chs...>;

} // biting_pear

template<class CT, biting_pear::impl::rand_state_t State,
    biting_pear::impl::ops_flags_t Flags>
__attribute__((always_inline))
inline std::basic_ostream<CT>& operator<<(std::basic_ostream<CT>& os,
    const biting_pear::impl::dawg_impl<State, CT, Flags>& s)
{
	return os;
}

template<class CT, biting_pear::impl::rand_state_t State,
    biting_pear::impl::ops_flags_t Flags, CT Ch, CT... Chs>
__attribute__((always_inline))
inline std::basic_ostream<CT>& operator<<(std::basic_ostream<CT>& os,
    const biting_pear::impl::dawg_impl<State, CT, Flags, Ch, Chs...>& s)
{
	constexpr biting_pear::impl::rand_state_t
	    State2 = biting_pear::impl::update_inner(State),
	    State3 = biting_pear::impl::update_inner(State2),
	    NewState2 = biting_pear::impl::update_outer(State3);
	typedef std::basic_ostream<CT>& FT(std::basic_ostream<CT>&, CT);
	biting_pear::impl::kthxbai<NewState2, FT *, Flags, 1u>
	    f(static_cast<FT *>(&std::operator<<));
	return f(os, s.front()) << s.rest();
}

#endif
