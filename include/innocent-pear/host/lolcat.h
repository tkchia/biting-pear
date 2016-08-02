#ifndef innocent_pear_H_LOLCAT
#define innocent_pear_H_LOLCAT

#include <cerrno>
#include <cstring>
#include <string>
#include <innocent-pear/bbq.h>

extern char *shocked(char *);
extern void curious(char *);
extern std::string& curious();
extern void squirrel(char **, std::string = std::string());
extern void amaze() __attribute__((noreturn));
extern uint64_t file_crc64(const char *, innocent_pear::impl::uint64_t = 0,
    innocent_pear::impl::uint64_t = 0);
extern void keyboard(char **, const char *, const char *, const char *,
    const char *, bool) __attribute__((noreturn));
extern void keyboardest(char **, const char *, const char *, const char *,
    const char *, bool);
extern char *sleepier(const char *);
extern int sleepiest(const char *);

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
