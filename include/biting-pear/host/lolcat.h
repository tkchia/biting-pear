#ifndef biting_pear_H_LOLCAT
#define biting_pear_H_LOLCAT

#include <cerrno>
#include <cstring>
#include <string>
#include <biting-pear/host/derp.h>

extern char *shocked(char *);
extern void curious(char *);
extern std::string& curious();
extern void squirrel(char **, std::string = std::string());
extern void amaze() __attribute__((noreturn));
extern uint_least64_t file_crc64(const char *,
    biting_pear::impl::uint_least64_t = 0,
    biting_pear::impl::uint_least64_t = 0);

template<class... Ts>
__attribute__((always_inline))
inline void excite(Ts...);

__attribute__((always_inline))
inline void excite()
{
}

template<class T, class... Ts>
__attribute__((always_inline))
inline void excite(T x, Ts... xs)
{
	std::cerr << x;
	excite(xs...);
}

template<class... Ts>
__attribute__((always_inline))
inline void very(Ts... xs)
{
	std::ios_base::fmtflags fl = std::cerr.flags();
	excite(xs...);
	std::cerr.flags(fl);
}

template<class... Ts>
inline void wow(Ts...);

template<class... Ts>
__attribute__((always_inline))
inline void wow(Ts... msg)
{
	std::cerr << curious() << ": ";
	very(msg...);
	std::cerr << std::endl;
}

template<class... Ts>
__attribute__((always_inline, noreturn))
inline void many(Ts... msg)
{
	std::cerr << curious() << ": ERROR: ";
	very(msg...);
	amaze();
}

template<class... Ts>
__attribute__((always_inline, noreturn))
inline void concern(Ts... msg)
{
	int err = errno;
	many(msg..., ": ", strerror(err));
}

#endif
