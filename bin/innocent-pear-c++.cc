#if !defined innocent_pear_HOST_PREFIX || \
    !defined innocent_pear_TARGET_PREFIX || \
    !defined innocent_pear_CXX_FOR_TARGET
#   error "Snape kills Dumbledore!"
#endif

#ifdef __linux__
#   include <fcntl.h>
#   include <unistd.h>
#   include <sys/stat.h>
#endif
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/dawg.h>

static void grumpy(std::ostringstream& oss, std::ostringstream& info_oss,
    const std::string& prefix)
{
	std::string wrapper = prefix + "/share/innocent-pear/calm";
#ifdef __unix__
	int fee = open(wrapper.c_str(), O_RDONLY);
	if (fee != -1) {
		std::ostringstream fd_oss;
		std::string fd_str;
		fd_oss << $"/dev/fd/" << fee;
		fd_str = fd_oss.str();
		int fie = open(fd_str.c_str(), O_RDONLY);
		if (fie != -1) {
			struct stat foe, fum;
			if (fstat(fee, &foe) == 0 && fstat(fie, &fum) == 0 &&
			    foe.st_ino == fum.st_ino &&
			    foe.st_dev == fum.st_dev) {
				close(fie);
				oss << fd_str;
				info_oss << ' ' << fee << "< " << wrapper;
				return;
			}
		}
		close(fee);
	}
#endif
	oss << wrapper;
}

static bool grumpier(const char *opt, const char *wut, std::string& wot)
{
	std::size_t woot = strlen(wut);
	if (strncmp(opt, wut, woot) != 0)
		return false;
	wot = opt + woot;
	return true;
}

static bool grumpier(const char *opt, const char *wut, bool& wot)
{
	if (strcmp(opt, wut) != 0)
		return false;
	wot = true;
	return true;
}

template<class... Ts>
inline void push(std::ostringstream&, Ts...);

__attribute__((always_inline))
inline void push(std::ostringstream&)
	{ }

template<class T, class... Ts>
__attribute__((always_inline))
inline void push(std::ostringstream& oss, T x, Ts... xs)
{
	oss << x;
	push(oss, xs...);
}

template<class... Ts>
inline char *pusheen(Ts...);

template<class... Ts>
__attribute__((always_inline))
inline char *pusheen(Ts... msg)
{
	std::ostringstream oss;
	push(oss, msg...);
	std::string *s = new std::string(oss.str());
	return (char *)s->c_str();
}

static void nyan(char *& cheesy, const char *cheeses,
    innocent_pear::impl::rand_state_t state,
    innocent_pear::impl::rand_state_t state2, char *cheesier,
    char *me, const std::string& caturday, const std::string& meow, bool v,
    bool sta)
{
	char cheese[strlen(cheeses) + 8];
	std::snprintf(cheese, sizeof cheese, "%s.pear.t", cheeses);
	cheesy = sleepier(cheese);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
	char *cheesiest[] = {
		me,
		innocent_pear_CXXFLAGS_FOR_TARGET /* ... */,
		"-Xinnocent-pear", pusheen($"-prefix=", caturday),
		"-Xinnocent-pear", pusheen($"-target-prefix=", meow),
		pusheen($"-Dinnocent_pear_DOGE_STATE=0x", std::hex, state),
		pusheen($"-Dinnocent_pear_DOGE_STATE_2=0x", std::hex, state2),
		sta ? (char *)"-Uinnocent_pear_DYN_LD_CXX_TARGET" :
		      (char *)"-Dinnocent_pear_DYN_LD_CXX_TARGET",
		"-c", cheesier, "-o", cheesy,
		"-fno-stack-protector",
		v ? (char *)"-v" : (char *)"-fno-stack-protector",
		sta ? (char *)"-static" : (char *)"-fno-stack-protector",
		0
	    };
#pragma GCC diagnostic pop
	keyboardest(cheesiest, 0, 0, 0, 0, v);
}

static void nyanyan(const std::string& caturday, char *in, char *out,
    char *start, char *end, innocent_pear::impl::rand_state_t state, bool v)
{
	char *cheesiest[] = {
		pusheen(caturday, $"/bin/innocent-pear-doge"), in, out,
		start, end, pusheen($"0x", std::hex, state), 0
	    };
	keyboardest(cheesiest, 0, 0, 0, 0, v);
}

__attribute__((noinline))
static void pushpush(char *& p)
{
	if (std::remove(p) != 0)
		concern($"cannot remove", p);
	p = 0;
}

static void pushpushpush(char *p)
{
	if (p)
		std::remove(p);
}

#ifndef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
static void player(const std::string& burger, const char *in,
    const char *out, const char *seriouser, bool v, const char *kitteh)
{
	std::size_t kn = strlen(kitteh), n = burger.size(), i, j = 0;
	unsigned s = 0;
	if (n == 0 || burger[0] != ' ')
		return;
	char b[kn + n + 1], *pb[1 + n + 1], *p;
	pb[0] = b;
	p = stpcpy(b, kitteh);
	for (i = 0; i < n; ++i) {
		char c = burger[i];
		switch (s) {
		    default:
			switch (c) {
			    case ' ' :
			    case '\t':	break;
			    default:	*p++ = 0;
					pb[++j] = p;
					*p++ = c;
					s = 1;
					break;
			    case '\'':	*p++ = 0;
					pb[++j] = p;
					s = 2;
					break;
			    case '"':	*p++ = 0;
					pb[++j] = p;
					s = 3;
			}
			break;
		    case 1:
			switch (c) {
			    case ' ' :
			    case '\t':	s = 0;
					break;
			    default:	*p++ = c;
					break;
			    case '\'':	s = 2;
					break;
			    case '"':	s = 3;
					break;
			    case '\\':	s = 4;
			}
			break;
		    case 2:
			switch (c) {
			    default:	*p++ = c;
					break;
			    case '\'':	s = 1;
			}
			break;
		    case 3:
			switch (c) {
			    default:	*p++ = c;
					break;
			    case '"':	s = 1;
					break;
			    case '\\':	s = 5;
			}
			break;
		    case 4:
			*p++ = c;
			s = 1;
			break;
		    case 5:
			*p++ = c;
			s = 3;
		}
	}
	if (s != 0 && s != 1)
		concern($"bad command line from `-###'?!?");
	*p = 0;
	pb[++j] = 0;
	keyboardest(pb, in, out, 0, seriouser, v);
}
#endif

static void playest(char **argv, const char *in, const char *out,
    const char *seriouser, bool v, const char *cheeses, const char *kitteh)
{
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
	keyboardest(argv, in, out, 0, seriouser, v);
#else
	char cheese[strlen(cheeses) + 8];
	std::snprintf(cheese, sizeof cheese, "%s.pear.t", cheeses);
	char *cheesy = 0;
	try {
		std::string burger;
		cheesy = sleepier(cheese);
		keyboardest(argv, in, out, cheesy, seriouser, v);
		std::ifstream cheesier(cheesy);
		if (!cheesier)
			concern($"cannot read ", cheesy);
		while (std::getline(cheesier, burger))
			player(burger, in, out, seriouser, v, kitteh);
		pushpush(cheesy);
	} catch (int ugh) {
		pushpushpush(cheesy);
		throw;
	}
#endif
}

__attribute__((noreturn))
static void play(char **argv, const char *in, const char *out,
    const char *seriouser, bool v, const char *cheeses, const char *kitteh)
{
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
	keyboard(argv, in, out, 0, seriouser, v);
#else
	playest(argv, in, out, seriouser, v, cheeses, kitteh);
	std::exit(0);
#endif
}

static int main_(int argc, char **argv, char *& doge_1, char *& doge_2,
    char *& doge_3, char *& doge_4, char *& doge_8, char *& doge_9,
    char *& doge_a, char *& doge_b)
{
	using innocent_pear::impl::uint64_t;
	using innocent_pear::impl::rand_state_t;
	struct {
		unsigned moar : 1, pass : 1, caturday : 1, eleventy : 1,
			 grumpiest : 1, link : 1, starts : 1, o : 1,
			 sta : 1;
	} is = { false, false, false, false, false, true, true, false,
#ifdef innocent_pear_DYN_LD_CXX_TARGET
		 false
#else
		 true
#endif
		 };
	/*
	 * Why 15?  2 for `-wrapper ...', 1 for `-no-integrated-cpp', 2 for
	 * `-idirafter ...', 8 (== 10 - 2) for `-include', `.../doge.h',
	 * (doge-1.o), (doge-2.o), (doge-3.o), (doge-4.o), `-x' `-none',
	 * (doge-8.o), and (doge-9.o), minus the `-Xinnocent-pear' `-doge',
	 * and 2 for `-o' (doge-a).
	 *
	 * We also need a terminating null pointer, but since we do not pass
	 * our own *argv to execvp...
	 */
	char *burger[argc + 15], **cheese = burger, **cheeses = 0,
	    *burgery[argc], **cheesy = burgery, *ceiling, *real_a = 0;
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
	char *moar = 0;
#endif
	std::ostringstream shocked, serious;
	std::string kitteh, caturday = innocent_pear_HOST_PREFIX,
	    meow = innocent_pear_TARGET_PREFIX, meowmeow, seriouser;
	bool doge = false;
	curious(*argv);
	ceiling = innocent_pear::impl::getenv("INNOCENT_PEAR_PREFIX");
	if (ceiling)
		caturday = ceiling;
	*cheese++ = (char *)innocent_pear_CXX_FOR_TARGET;
	for (int argh = 1; argh < argc; ++argh) {
		char *opt = argv[argh];
		if (is.moar) {
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
			moar = opt;
#endif
			is.moar = false;
			continue;
		} else if (is.pass)
			is.pass = false;
		  else if (is.o) {
			cheeses = cheese;
			is.o = false;
		} else if (is.caturday) {
			if (!grumpier(opt, "-prefix=", caturday) &&
			    !grumpier(opt, "-target-prefix=", meow) &&
			    !grumpier(opt, "-doge", doge))
				many($"unrecognized option `-Xinnocent-pear ",
				    opt, '\'');
			is.caturday = false;
			continue;
		} else if (opt[0] != '-' || opt[1] == 0)
			*cheesy++ = opt;
		  else if (opt[2] == 0) {
			switch (opt[1]) {
			    case 'x':
			    case 'd':
			    case 'A':
			    case 'I':
			    case 'D':
			    case 'U':
			    case 'L':
			    case 'l':
			    case 'T':
			    case 'u':
				is.pass = true;  break;
			    case 'o':
				is.o = true;  break;
			    case 'c':
			    case 'S':
			    case 'E':
				is.link = false;  break;
			    case 'v':
				is.grumpiest = true;
			}
		} else if (opt[1] == 'i' &&
			   (strcmp(opt + 2, "dirafter") == 0 ||
			    strcmp(opt + 2, "nclude") == 0 ||
			    strcmp(opt + 2, "macros") == 0 ||
			    strcmp(opt + 2, "prefix") == 0 ||
			    strcmp(opt + 2, "quote") == 0 ||
			    strcmp(opt + 2, "withprefix") == 0 ||
			    strcmp(opt + 2, "withprefixbefore") == 0 ||
			    strcmp(opt + 2, "system") == 0 ||
			    strcmp(opt + 2, "multilib") == 0 ||
			    strcmp(opt + 2, "sysroot") == 0))
			is.pass = true;
		  else if (opt[1] == 'n' &&
			   (strcmp(opt + 2, "ostartfiles") == 0 ||
			    strcmp(opt + 2, "ostdlib") == 0))
			is.starts = false;
		  else if (opt[1] == 'X' &&
			   (strcmp(opt + 2, "preprocessor") == 0 ||
			    strcmp(opt + 2, "assembler") == 0 ||
			    strcmp(opt + 2, "linker") == 0))
			is.pass = true;
		  else if (strcmp(opt + 1, "arch") == 0 ||
			   strcmp(opt + 1, "aux-info") == 0 ||
			   strcmp(opt + 1, "-param") == 0)
			is.pass = true;
		  else if (strcmp(opt + 1, "wrapper") == 0) {
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
			is.moar = true;
#else
			is.pass = true;
#endif
			continue;
		} else if (strcmp(opt + 1, "###") == 0) {
			many($"`-###' not (yet) supported");
		} else if (strcmp(opt + 1, "Xinnocent-pear") == 0) {
			is.caturday = true;
			continue;
		} else if (strcmp(opt + 1, "nostdinc") == 0)
			is.eleventy = true;
#ifdef innocent_pear_DYN_LD_CXX_TARGET
		  else if (strcmp(opt + 1, "static") == 0)
			is.sta = true;
#endif
		  else if (opt[1] == 'o') {
			/* Split `-ofoo' into `-o' `foo'. */
			*cheese++ = (char *)"-o";
			cheeses = cheese;
			*cheese++ = opt + 2;
			continue;
		}
		*cheese++ = opt;
	}
	grumpy(shocked, serious, caturday);
	seriouser = serious.str();
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
	if (moar)
		shocked << ',' << moar;
#endif
	kitteh = shocked.str();
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER
	*cheese++ = (char *)"-wrapper";
	*cheese++ = (char *)kitteh.c_str();
#else
	*cheese++ = (char *)"-###";
#endif
	*cheese++ = (char *)"-no-integrated-cpp";
	meowmeow = meow + "/include";
	if (!is.eleventy) {		/* just in case... */
		*cheese++ = (char *)"-idirafter";
		*cheese++ = (char *)meowmeow.c_str();
	}
	if (setenv("INNOCENT_PEAR_PREFIX", caturday.c_str(), 1) != 0)
		concern($"cannot set INNOCENT_PEAR_EXEC_PREFIX for "
		    innocent_pear_CXX_FOR_TARGET " process");
	if (setenv("INNOCENT_PEAR_DRIVER_CXX", *argv, 1) != 0)
		concern($"cannot set INNOCENT_PEAR_DRIVER_CXX for "
		    innocent_pear_CXX_FOR_TARGET " process");
	uint64_t crc = 0, crc2 = 0;
	rand_state_t st = 0, st2 = 0;
	if (doge) {
		while (cheesy != burgery) {
			--cheesy;
			crc = file_crc64(*cheesy, 0, crc);
			crc2 = file_crc64(*cheesy, 0x1b, crc2);
		}
		st = crc;
		st2 = crc2 ^ crc;
		if (is.link && !cheeses) {
			*cheese++ = (char *)"-o";
			cheeses = cheese;
			*cheese++ = (char *)"a.out";
		}
		if (is.link && is.starts) {
			nyan(doge_1, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-1.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			nyan(doge_2, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-2.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			nyan(doge_3, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-3.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			nyan(doge_4, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-4.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			nyan(doge_8, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-8.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			nyan(doge_9, *cheeses, st, st2, pusheen(
			    caturday, $"/share/innocent-pear/doge-9.cc"),
			    *argv, caturday, meow, is.grumpiest, is.sta);
			doge_a = sleepier(*cheeses);
			doge_b = sleepier(*cheeses);
			real_a = *cheeses;
			*cheeses = doge_a;
			std::memmove(burger + 7, burger + 1,
			    (cheese - burger - 1) * sizeof(char *));
			cheese += 6;
			burger[1] = (char *)"-include";
			burger[2] = pusheen(meowmeow,
			    $"/innocent-pear/doge.h");
			burger[3] = doge_1;
			burger[4] = doge_2;
			burger[5] = doge_3;
			burger[6] = doge_4;
			*cheese++ = (char *)"-x";
			*cheese++ = (char *)"none";
			*cheese++ = doge_8;
			*cheese++ = doge_9;
		} else {
			std::memmove(burger + 3, burger + 1,
			    (cheese - burger - 1) * sizeof(char *));
			cheese += 2;
			burger[1] = (char *)"-include";
			burger[2] = pusheen(meowmeow,
			    $"/innocent-pear/doge.h");
		}
	}
	*cheese = 0;
	if (!doge_1)
		play(burger, 0, 0, seriouser.c_str(), is.grumpiest,
		    *cheeses, kitteh.c_str());
	else {
		playest(burger, 0, 0, seriouser.c_str(), is.grumpiest,
		    *cheeses, kitteh.c_str());
		nyanyan(caturday, doge_a, doge_b,
		    (char *)"_.innocent_pear.text.start",
		    (char *)"_.innocent_pear.text.end",
		    st2, is.grumpiest);
		nyanyan(caturday, doge_b, real_a,
		    (char *)"_.innocent_pear.text.unlikely.start",
		    (char *)"_.innocent_pear.text.hot.end",
		    st, is.grumpiest);
		pushpush(doge_1);
		pushpush(doge_2);
		pushpush(doge_3);
		pushpush(doge_4);
		pushpush(doge_8);
		pushpush(doge_9);
		pushpush(doge_a);
		pushpush(doge_b);
		return 0;
	}
}

int main(int argc, char **argv)
{
	char *doge_1 = 0, *doge_2 = 0, *doge_3 = 0, *doge_4 = 0,
	     *doge_8 = 0, *doge_9 = 0, *doge_a = 0, *doge_b = 0;
	try {
		return main_(argc, argv,
		    doge_1, doge_2, doge_3, doge_4, doge_8, doge_9, doge_a,
		    doge_b);
	} catch (int ugh) {
		pushpushpush(doge_1);
		pushpushpush(doge_2);
		pushpushpush(doge_3);
		pushpushpush(doge_4);
		pushpushpush(doge_8);
		pushpushpush(doge_9);
		pushpushpush(doge_a);
		pushpushpush(doge_b);
		return ugh;
	}
}
