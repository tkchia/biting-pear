#ifndef innocent_pear_H_DAWG
#define innocent_pear_H_DAWG

#include <climits>
#include <cstdlib>
#include <ostream>
#include <type_traits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/teh.h>

namespace innocent_pear
{

namespace impl
{

template<impl::rand_state_t State, class T, ops_flags_t Flags,
    unsigned Levels>
class kthxbai;  // forward

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT Ch>
class dawg_impl_1;  // forward

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT... Chs>
class dawg_impl_2;

template<rand_state_t State, class CT, ops_flags_t Flags, CT Ch>
class dawg_impl_1<State, CT, Flags, ~0u, Ch> : public nowai
	{ };

template<rand_state_t State, class CT, ops_flags_t Flags, CT Ch>
class dawg_impl_1<State, CT, Flags, 0u, Ch>
{
	typedef typename std::make_unsigned<CT>::type UCT;
	static constexpr rand_state_t
	    State2 = update_inner(State),
	    NewState = update_outer(State2, 4u);
    public:
	innocent_pear_always_inline
	static CT wut()
	{
		constexpr UCT Frob = pick_hi<UCT>(State2);
		volatile const UCT& x = teh<NewState, UCT, (UCT)Ch ^ Frob>::x;
		return (CT)(x ^ Frob);
	}
};

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT Ch>
class dawg_impl_1
{
	typedef innocent_pear_decltype(1u | (CT)1 << 0u) PCT; // N3797 5.8.2
	typedef typename std::make_unsigned<CT>::type UCT;
	static constexpr rand_state_t
	    State2 = update_inner(State),
	    State3 = update_inner(State2),
	    State4 = update_inner(State3),
	    NewState = update_outer(State2, Levels > 4u ? Levels : 4u);
    public:
	innocent_pear_always_inline
	static CT wut()
	{
		constexpr unsigned Sublevels = ((State ^ NewState) >> 48) % 2;
		if (!Sublevels)
			return dawg_impl_1<State, CT, Flags, 0u, Ch>::wut();
		if (sizeof(CT) == sizeof(char))
			return (CT)(PCT)
			    kthxbai<NewState, PCT, Flags, Sublevels>(
				(pick_hi<PCT>(State3 ^ State4) &
				    ~(PCT)UCHAR_MAX) |
				 ((PCT)Ch & UCHAR_MAX));
		else
			return (CT)(PCT)kthxbai<NewState, PCT, Flags,
			    Sublevels>(Ch);
	}
};

template<rand_state_t State, class CT, ops_flags_t Flags, CT... Chs>
class dawg_impl_2<State, CT, Flags, ~0u, Chs...> : public nowai
	{ };

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels>
class dawg_impl_2<State, CT, Flags, Levels>
{
    public:
	innocent_pear_always_inline
	dawg_impl_2()
		{ }
	innocent_pear_always_inline
	dawg_impl_2(const dawg_impl_2<State, CT, Flags, Levels>& x)
		{ }
	innocent_pear_always_inline
	static CT front()
		{ __builtin_unreachable(); }
	innocent_pear_always_inline
	CT operator[](std::size_t i) const
		{ __builtin_unreachable(); }
	innocent_pear_always_inline
	static std::size_t size()
		{ return 0; }
	innocent_pear_always_inline
	void operator>>(CT *b)
		{ }
};

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT Ch, CT... Chs>
class dawg_impl_2<State, CT, Flags, Levels, Ch, Chs...>
{
	static constexpr rand_state_t
	    State2 = update_inner(State),
	    State3 = update_inner(State2),
	    State4 = update_inner(State3);
	typedef dawg_impl_2<State4, CT, Flags, Levels, Chs...> rest_type;
    public:
	innocent_pear_always_inline
	dawg_impl_2()
		{ }
	innocent_pear_always_inline
	dawg_impl_2(const dawg_impl_2<State, CT, Flags, Levels, Ch, Chs...>& x)
		{ }
	innocent_pear_always_inline
	static CT front()
		{ return dawg_impl_1<State, CT, Flags, Levels, Ch>::wut(); }
	innocent_pear_always_inline
	static rest_type rest()
		{ return rest_type(); }
	innocent_pear_always_inline
	CT operator[](std::size_t i) const
		{ return i == 0 ? front() : rest()[i - 1]; }
	innocent_pear_always_inline
	static std::size_t size()
		{ return 1u + sizeof...(Chs); }
	innocent_pear_always_inline
	void operator>>(CT *b)
	{
		CT x;
		switch ((State3 ^ State4) % 0x100000001u % 3) {
		    case 0:
			rest() >> (b + 1);
			*b = front();
			break;
		    case 1:
			*b = front();
			rest() >> (b + 1);
			break;
		    default:
			x = front();
			rest() >> (b + 1);
			*b = x;
		}
	}
};

template<class CT, innocent_pear::impl::rand_state_t State,
    innocent_pear::ops_flags_t Flags, unsigned Levels>
innocent_pear_always_inline
std::basic_ostream<CT>& operator<<(std::basic_ostream<CT>& os,
    const innocent_pear::impl::dawg_impl_2<State, CT, Flags, Levels>& s)
{
	return os;
}

template<class CT, innocent_pear::impl::rand_state_t State,
    innocent_pear::ops_flags_t Flags, unsigned Levels, CT Ch>
innocent_pear_always_inline
std::basic_ostream<CT>& operator<<(std::basic_ostream<CT>& os,
    const innocent_pear::impl::dawg_impl_2<State, CT, Flags, Levels, Ch>& s)
{
	if (!Ch)
		return os;
	constexpr innocent_pear::impl::rand_state_t
	    State2 = innocent_pear::impl::update_inner(State),
	    State3 = innocent_pear::impl::update_inner(State2),
	    NewState2 = innocent_pear::impl::update_outer(State3, 3u);
	typedef std::basic_ostream<CT>& FT(std::basic_ostream<CT>&, CT);
	innocent_pear::impl::kthxbai<NewState2, FT *, Flags, 1u>
	    f(static_cast<FT *>(&std::operator<<));
	return f(os, s.front());
}

template<class CT, innocent_pear::impl::rand_state_t State,
    innocent_pear::ops_flags_t Flags, unsigned Levels,
    CT Ch0, CT Ch1, CT... Chs>
innocent_pear_always_inline
std::basic_ostream<CT>& operator<<(std::basic_ostream<CT>& os,
    const innocent_pear::impl::dawg_impl_2<State, CT, Flags, Levels,
    Ch0, Ch1, Chs...>& s)
{
	constexpr innocent_pear::impl::rand_state_t
	    State2 = innocent_pear::impl::update_inner(State),
	    State3 = innocent_pear::impl::update_inner(State2),
	    NewState2 = innocent_pear::impl::update_outer(State3, 3u);
	typedef std::basic_ostream<CT>& FT(std::basic_ostream<CT>&, CT);
	innocent_pear::impl::kthxbai<NewState2, FT *, Flags, 1u>
	    f(static_cast<FT *>(&std::operator<<));
	return f(os, s.front()) << s.rest();
}

template<rand_state_t State, ops_flags_t Flags, char... Chs>
using dawg = dawg_impl_2<State, char, Flags, 2u, Chs...>;

} // innocent_pear::impl

using impl::dawg;

} // innocent_pear

#endif
