#if !defined innocent_pear_HOST_PREFIX || \
    !defined innocent_pear_TARGET_PREFIX || \
    !defined innocent_pear_CC_FOR_TARGET || \
    !defined innocent_pear_CXX_FOR_TARGET || \
    !defined innocent_pear_STRIP_FOR_TARGET
#   error "Snape kills Dumbledore!"
#endif

#ifdef __linux__
#   include <fcntl.h>
#   include <unistd.h>
#   include <sys/stat.h>
#endif
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/host/moar.h>
#include <innocent-pear/dawg.h>

#undef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
#if defined innocent_pear_FRONT_END_CXX ? \
	defined innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER : \
	defined innocent_pear_CC_FOR_TARGET_HAVE_OPT_WRAPPER
#    define innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
#endif
#undef innocent_pear_COMPILER_FOR_TARGET_DECOUPLE_AS
#if defined innocent_pear_FRONT_END_CXX ? \
	defined innocent_pear_CXX_FOR_TARGET_DECOUPLE_AS : \
	defined innocent_pear_CC_FOR_TARGET_DECOUPLE_AS
#    define innocent_pear_COMPILER_FOR_TARGET_DECOUPLE_AS
#endif
#undef innocent_pear_DYN_LD_COMPILER_TARGET
#if defined innocent_pear_FRONT_END_CXX ? \
	defined innocent_pear_DYN_LD_CXX_TARGET : \
	defined innocent_pear_DYN_LD_CC_TARGET
#    define innocent_pear_DYN_LD_COMPILER_TARGET
#endif

typedef struct {
	innocent_pear::impl::rand_state_t z, i, ii, iii, iv, v,
	    vi, vii, viii, ix, x;
} states_t;

static const char * const doge_i_tags[] =
    { "01", "02", "03", "04", "05", "06", "07", "45" };
static const char * const doge_n_tags[] = { "98", "99" };
static constexpr std::size_t
    NumDogeIParts = sizeof(doge_i_tags) / sizeof(*doge_i_tags),
    NumDogeNParts = sizeof(doge_n_tags) / sizeof(*doge_n_tags);
static_assert(NumDogeIParts >= 2, "NumDogeIParts < 2 !");

static void grumpy(std::ostringstream& oss, std::ostringstream& info_oss,
    const std::string& eprefix, int& close_fd)
{
	std::string wrapper = eprefix + "/share/innocent-pear/calm";
	close_fd = -1;
#ifdef __unix__
	int fee = open(wrapper.c_str(), O_RDONLY);
	if (fee != -1) {
		char om[9 + (2 + sizeof(int) * CHAR_BIT) / 3];
		std::snprintf(om, sizeof om, "/dev/fd/%d", fee);
		int fie = open(om, O_RDONLY);
		if (fie != -1) {
			struct stat foe, fum;
			if (fstat(fee, &foe) == 0 && fstat(fie, &fum) == 0 &&
			    foe.st_ino == fum.st_ino &&
			    foe.st_dev == fum.st_dev) {
				close(fie);
				oss << om;
				info_oss << ' ' << fee << "< " << wrapper;
				close_fd = fee;
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

template<class... Ts>
__attribute__((always_inline))
inline void plush(std::string& s, Ts... msg)
{
	std::ostringstream oss;
	push(oss, msg...);
	s = oss.str();
}

static void nyan(sleepier_t& cheesy, const char *cheeses, states_t st,
    const char *cheez, const char *cheeez, const char *cheeeez,
    char *cheesier, char *cxx, const std::string& caturday,
    const std::string& ecaturday, const std::string& meow,
    const std::string& emeow, bool v, bool sta, bool debug_doge)
{
	char cheese[strlen(cheeses) + 8];
	std::snprintf(cheese, sizeof cheese, "%s.pear.t", cheeses);
	cheesy(cheese);
	std::string s1, s2, s3, s4, s5,
	    s6 = "-Uinnocent_pear_DOGE_TAG_NEXT",
	    s7 = "-Uinnocent_pear_DOGE_TAG_2_NEXT",
	    s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18;
	plush(s1,  "-prefix=", caturday);
	plush(s2,  "-exec-prefix=", ecaturday);
	plush(s3,  "-target-prefix=", meow);
	plush(s4,  "-target-exec-prefix=", emeow);
	plush(s5,  "-Dinnocent_pear_DOGE_TAG=\"", cheez, '"');
	if (cheeez)
		plush(s6, "-Dinnocent_pear_DOGE_TAG_NEXT=\"", cheeez, '"');
	if (cheeeez)
		plush(s7, "-Dinnocent_pear_DOGE_TAG_2_NEXT=\"", cheeeez, '"');
	plush(s8,  "-Dinnocent_pear_DOGE_STATE_0=0x",  std::hex, st.z);
	plush(s9,  "-Dinnocent_pear_DOGE_STATE_1=0x",  std::hex, st.i);
	plush(s10, "-Dinnocent_pear_DOGE_STATE_2=0x",  std::hex, st.ii);
	plush(s11, "-Dinnocent_pear_DOGE_STATE_3=0x",  std::hex, st.iii);
	plush(s12, "-Dinnocent_pear_DOGE_STATE_4=0x",  std::hex, st.iv);
	plush(s13, "-Dinnocent_pear_DOGE_STATE_5=0x",  std::hex, st.v);
	plush(s14, "-Dinnocent_pear_DOGE_STATE_6=0x",  std::hex, st.vi);
	plush(s15, "-Dinnocent_pear_DOGE_STATE_7=0x",  std::hex, st.vii);
	plush(s16, "-Dinnocent_pear_DOGE_STATE_8=0x",  std::hex, st.viii);
	plush(s17, "-Dinnocent_pear_DOGE_STATE_9=0x",  std::hex, st.ix);
	plush(s18, "-Dinnocent_pear_DOGE_STATE_10=0x", std::hex, st.x);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
	char *cheesiest[] = {
		cxx,
		innocent_pear_CXXFLAGS_FOR_TARGET /* ... */,
		"-Xinnocent-pear", (char *)s1.c_str(),
		"-Xinnocent-pear", (char *)s2.c_str(),
		"-Xinnocent-pear", (char *)s3.c_str(),
		"-Xinnocent-pear", (char *)s4.c_str(),
		"-Wa,--Xinnocent-pear=dogecoin=u",
		(char *)s5.c_str(),  (char *)s6.c_str(),  (char *)s7.c_str(),
		(char *)s8.c_str(),  (char *)s9.c_str(),  (char *)s10.c_str(),
		(char *)s11.c_str(), (char *)s12.c_str(), (char *)s13.c_str(),
		(char *)s14.c_str(), (char *)s15.c_str(), (char *)s16.c_str(),
		(char *)s17.c_str(), (char *)s18.c_str(),
		sta ? (char *)"-Uinnocent_pear_DYN_LD_CXX_TARGET" :
		      (char *)"-Dinnocent_pear_DYN_LD_CXX_TARGET",
		debug_doge ? (char *)"-Dinnocent_pear_DEBUG=1" :
			     (char *)"-Uinnocent_pear_DEBUG",
		"-c", cheesier, "-o", (char *)cheesy(),
		"-fno-toplevel-reorder",
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_WRITABLE_STRINGS
		"-fwritable-strings",
#endif
		"-fno-stack-protector",
		v ? (char *)"-v" : (char *)"-fno-stack-protector",
		v ? (char *)"-Wa,-v" : (char *)"-fno-stack-protector",
		sta ? (char *)"-static" : (char *)"-fno-stack-protector",
		0
	    };
#pragma GCC diagnostic pop
	keyboardest(cheesiest, 0, 0, 0, 0, v);
}

static void nyanyan(const std::string& ecaturday, const char *in,
    const char *out, const char *start, const char *end,
    innocent_pear::impl::rand_state_t state, bool v)
{
	std::string s1, s2;
	plush(s1, ecaturday, "/bin/innocent-pear-doge");
	plush(s2, "0x", std::hex, state);
	char *cheesiest[] = {
		(char *)s1.c_str(), (char *)in, (char *)out,
		(char *)start, (char *)end, (char *)s2.c_str(),
		v ? (char *)"-v" : 0, 0
	    };
	keyboardest(cheesiest, 0, 0, 0, 0, v);
}

static void nyanyanyan(const char *in, const char *out, bool v)
{
	char *cheesiest[] = {
		(char *)innocent_pear_STRIP_FOR_TARGET,
#ifdef innocent_pear_STRIP_FOR_TARGET_HAVE_OPT_STRIP_ALL
		(char *)"--strip-all",
#endif
		(char *)"-o", (char *)out,
		(char *)in,
		0
	    };
	keyboardest(cheesiest, 0, 0, 0, 0, v);
}

#ifndef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
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
		concern("bad command line from `-###'?!?");
	*p = 0;
	pb[++j] = 0;
	keyboardest(pb, in, out, 0, seriouser, v);
}
#endif

static void playest(char **argv, const char *in, const char *out,
    const char *seriouser, bool v, const char *cheeses, const char *kitteh)
{
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
	keyboardest(argv, in, out, 0, seriouser, v);
#else
	char cheese[strlen(cheeses) + 8];
	std::snprintf(cheese, sizeof cheese, "%s.pear.t", cheeses);
	sleepier_t cheesy(cheese);
	std::string burger;
	keyboardest(argv, in, out, cheesy(), seriouser, v);
	std::ifstream cheesier(cheesy());
	if (!cheesier)
		concern("cannot read ", cheesy());
	while (std::getline(cheesier, burger))
		player(burger, in, out, seriouser, v, kitteh);
#endif
}

__attribute__((noreturn))
static void play(char **argv, const char *in, const char *out,
    const char *seriouser, bool v, const char *cheeses, const char *kitteh)
{
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
	keyboard(argv, in, out, 0, seriouser, v);
#else
	playest(argv, in, out, seriouser, v, cheeses, kitteh);
	std::exit(0);
#endif
}

static int main_(int argc, char **argv)
{
	struct {
		unsigned moar : 1, pass : 1, caturday : 1, eleventy : 1,
			 grumpiest : 1, link : 1, starts : 1, o : 1,
			 dogecoin : 1, s : 1, eleven : 1, sta : 1;
	} is = { false, false, false, false, false, true, true, false,
		 false, false, true,
#ifdef innocent_pear_DYN_LD_COMPILER_TARGET
		 false
#else
		 true
#endif
		 };
	/*
	 * Why 15 + 9 * (NumDogeIParts + NumDogeNParts)?  We need
	 *
	 *   * 2 for `-wrapper' `...'
	 *   * 3 for `-no-integrated-cpp' `-fno-integrated-as'
	 *     `-Wa,--Xinnocent-pear=dogecoin=...'
	 *   * 4 for `-idirafter' `...' `-idirafter' `...'
	 *   * 3 for `-include', `.../doge.h', `-Wl,-T,(doge-i.ld),...'
	 *   * 9 * NumDogeIParts for (doge-01.o) `-lstdc++' `-latomic' `-lc'
	 *     `-lgcc' `-lgcc_eh' `-lc' `-lgcc' `-lgcc_eh', (doge-02.o) and
	 *     the same libraries, ...
	 *   * 0 (== 2 - 2) for `-x' `-none' minus `-Xinnocent-pear' `-doge'
	 *   * 9 * NumDogeNParts for ..., (doge-99.o) and the libraries
	 *   * and 3 for (doge-n.ld), and `-o' (doge-a).
	 *
	 * We also need a terminating null pointer, but since we do not pass
	 * our own *argv to execvp...
	 */
	char *burger[argc + 15 + 9 * (NumDogeIParts + NumDogeNParts)],
	    **cheese = burger, **cheeses = 0, *burgery[argc],
	    **cheesy = burgery, *ceiling, *real_a = 0;
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
	char *moar = 0;
#endif
	char *cc = 0, *cxx = 0;
	std::ostringstream shocked, serious;
	std::string kitteh, meowmeow, meowmeowmeow, seriouser,
	    caturday = innocent_pear_HOST_PREFIX,
	    ecaturday = innocent_pear_HOST_PREFIX,
	    meow = innocent_pear_TARGET_PREFIX,
	    emeow = innocent_pear_TARGET_PREFIX;
	bool doge = false, debug_doge = false;
	curious(*argv);
	ceiling = innocent_pear::impl::getenv("INNOCENT_PEAR_PREFIX");
	if (ceiling)
		caturday = ceiling;
	ceiling = innocent_pear::impl::getenv("INNOCENT_PEAR_EXEC_PREFIX");
	if (ceiling)
		ecaturday = ceiling;
#ifdef innocent_pear_FRONT_END_CXX
	*cheese++ = (char *)innocent_pear_CXX_FOR_TARGET;
#else
	*cheese++ = (char *)innocent_pear_CC_FOR_TARGET;
#endif
	for (int argh = 1; argh < argc; ++argh) {
		char *opt = argv[argh];
		if (is.moar) {
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
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
			    !grumpier(opt, "-exec-prefix=", ecaturday) &&
			    !grumpier(opt, "-target-prefix=", meow) &&
			    !grumpier(opt, "-target-exec-prefix=", emeow) &&
			    !grumpier(opt, "-doge", doge) &&
			    !grumpier(opt, "-debug-doge", debug_doge))
				many("unrecognized option `-Xinnocent-pear ",
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
			    case 's':
				/*
				 * We need to handle this separately in case
				 * `-Xinnocent-pear -doge' is in effect.
				 */
				is.s = true;  continue;
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
		  else if (strcmp(opt + 1, "nostartfiles") == 0)
			is.starts = false;
		  else if (strcmp(opt + 1, "nostdlib") == 0) {
			is.starts = false;
			is.eleven = false;
		} else if (strcmp(opt + 1, "nodefaultlibs") == 0)
			is.eleven = false;
		  else if (opt[1] == 'X' &&
			   (strcmp(opt + 2, "preprocessor") == 0 ||
			    strcmp(opt + 2, "assembler") == 0 ||
			    strcmp(opt + 2, "linker") == 0))
			is.pass = true;
		  else if (opt[1] == 'f' &&
			   (strcmp(opt + 2, "pic") == 0 ||
			    strcmp(opt + 2, "PIC") == 0 ||
			    strcmp(opt + 2, "pie") == 0 ||
			    strcmp(opt + 2, "PIE") == 0))
			is.dogecoin = true;
		  else if (strcmp(opt + 1, "arch") == 0 ||
			   strcmp(opt + 1, "aux-info") == 0 ||
			   strcmp(opt + 1, "-param") == 0)
			is.pass = true;
		  else if (strcmp(opt + 1, "wrapper") == 0) {
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
			is.moar = true;
#else
			is.pass = true;
#endif
			continue;
		} else if (strcmp(opt + 1, "###") == 0)
			many("`-###' not (yet) supported");
		  else if (strcmp(opt + 1, "Xinnocent-pear") == 0) {
			is.caturday = true;
			continue;
		} else if (strcmp(opt + 1, "nostdinc") == 0)
			is.eleventy = true;
#ifdef innocent_pear_DYN_LD_COMPILER_TARGET
		  else if (strcmp(opt + 1, "static") == 0)
			is.sta = true;
#endif
		  else if (strcmp(opt + 1, "pie") == 0)
			is.dogecoin = true;
		  else if (opt[1] == 'o') {
			/* Split `-ofoo' into `-o' `foo'. */
			*cheese++ = (char *)"-o";
			cheeses = cheese;
			*cheese++ = opt + 2;
			continue;
		} else if (strcmp(opt + 1, "fintegrated-as") == 0) {
			/*
			 * There is a high chance we will need the assembly
			 * pass to be decoupled from the compilation pass
			 * for everything to work properly, so...
			 */
			wow("ignoring `-fintegrated-as'");
			continue;
		}
		*cheese++ = opt;
	}
	int shocker;
	grumpy(shocked, serious, ecaturday, shocker);
	seriouser = serious.str();
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
	if (moar)
		shocked << ',' << moar;
#endif
	kitteh = shocked.str();
#ifdef innocent_pear_COMPILER_FOR_TARGET_HAVE_OPT_WRAPPER
	*cheese++ = (char *)"-wrapper";
	*cheese++ = (char *)kitteh.c_str();
#else
	*cheese++ = (char *)"-###";
#endif
	*cheese++ = (char *)"-no-integrated-cpp";
#ifdef innocent_pear_COMPILER_FOR_TARGET_DECOUPLE_AS
	*cheese++ = (char *)"-fno-integrated-as";
#endif
	meowmeow = meow + "/include";
	if (!is.eleventy) {		/* just in case... */
		*cheese++ = (char *)"-idirafter";
		*cheese++ = (char *)meowmeow.c_str();
		meowmeowmeow = emeow + "/include";
		*cheese++ = (char *)"-idirafter";
		*cheese++ = (char *)meowmeowmeow.c_str();
	}
	if (setenv("INNOCENT_PEAR_PREFIX", caturday.c_str(), 1) != 0)
		concern("cannot set INNOCENT_PEAR_PREFIX for "
		    innocent_pear_CXX_FOR_TARGET " process");
	if (setenv("INNOCENT_PEAR_EXEC_PREFIX", ecaturday.c_str(), 1) != 0)
		concern("cannot set INNOCENT_PEAR_EXEC_PREFIX for "
		    innocent_pear_CXX_FOR_TARGET " process");
#ifdef innocent_pear_FRONT_END_CXX
	cc = pusheen(ecaturday, "/bin/innocent-pear-cc");
	cxx = *argv;
#else
	cc = *argv;
	cxx = pusheen(ecaturday, "/bin/innocent-pear-c++");
#endif
	if (setenv("INNOCENT_PEAR_DRIVER_CC", cc, 1) != 0)
		concern("cannot set INNOCENT_PEAR_DRIVER_CC for "
		    innocent_pear_CXX_FOR_TARGET " process");
	if (setenv("INNOCENT_PEAR_DRIVER_CXX", cxx, 1) != 0)
		concern("cannot set INNOCENT_PEAR_DRIVER_CXX for "
		    innocent_pear_CXX_FOR_TARGET " process");
	states_t st;
	sleepier_t doge_i[NumDogeIParts], doge_n[NumDogeNParts],
	    doge_a, doge_b;
	if (doge) {
		{
			moar_t mor;
			while (cheesy != burgery) {
				--cheesy;
				int fd = open(*cheesy, O_RDONLY);
				if (fd == -1)
					continue;
				ssize_t n;
				unsigned char buf[4096];
				while ((n = read(fd, buf, sizeof buf)) > 0)
					mor.feed(buf, n);
				close(fd);
			}
			st.z = mor.fetch();
			st.i = mor.fetch();
			st.ii = mor.fetch();
			st.iii = mor.fetch();
			st.iv = mor.fetch();
			st.v = mor.fetch();
			st.vi = mor.fetch();
			st.vii = mor.fetch();
			st.viii = mor.fetch();
			st.ix = mor.fetch();
			st.x = mor.fetch();
			if (is.dogecoin)
				*cheese++ = pusheen("-Wa,"
				    "--Xinnocent-pear=dogecoin=0x",
				    std::hex, mor.fetch());
		}
		if (is.link && !cheeses) {
			*cheese++ = (char *)"-o";
			cheeses = cheese;
			*cheese++ = (char *)"a.out";
		}
		if (is.link && is.starts) {
			std::size_t s, t;
			for (s = 0; s < NumDogeIParts; ++s)
				nyan(doge_i[s], *cheeses, st, doge_i_tags[s],
				    s+1 < NumDogeIParts ? doge_i_tags[s+1] : 0,
				    s+2 < NumDogeIParts ? doge_i_tags[s+2] : 0,
				    pusheen(caturday, "/share/innocent-pear/"
					"doge-", doge_i_tags[s], ".cc"),
				    cxx, caturday, ecaturday, meow, emeow,
				    is.grumpiest, is.sta, debug_doge);
			for (s = 0; s < NumDogeNParts; ++s)
				nyan(doge_n[s], *cheeses, st, doge_n_tags[s],
				    s+1 < NumDogeNParts ? doge_n_tags[s+1] : 0,
				    s+2 < NumDogeNParts ? doge_n_tags[s+2] : 0,
				    pusheen(caturday, "/share/innocent-pear/"
					"doge-", doge_n_tags[s], ".cc"),
				    cxx, caturday, ecaturday, meow, emeow,
				    is.grumpiest,
				    is.sta, debug_doge);
			doge_a(*cheeses);
			doge_b(*cheeses);
			real_a = *cheeses;
			*cheeses = (char *)doge_a();
			std::size_t n_libs = 0;
			if (is.eleven) {
				n_libs = 4;
#ifdef innocent_pear_LIBSTDCXX_CXX_TARGET
				++n_libs;
#endif
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_LIB_ATOMIC
				++n_libs;
#endif
				if (is.sta)
					n_libs += 2;
			}
			std::memmove(burger + 4 + (n_libs + 1) * NumDogeIParts,
			    burger + 1,
			    (cheese - burger - 1) * sizeof(char *));
			cheese += 3 + (n_libs + 1) * NumDogeIParts;
			burger[1] = (char *)"-include";
			burger[2] = pusheen(meowmeow,
			    "/innocent-pear/doge.h");
			char *wl = pusheen("-Wl,-T,", caturday,
			    "/share/innocent-pear/doge-i.ld,-z,norelro");
#if defined __ELF__
			/*
			 * Nasty hack to work around a problem where some
			 * GNU indirect function resolvers (STT_GNU_IFUNC)
			 * end up in the scrambled portion of .text, and get
			 * called at runtime before they are unscrambled.
			 */
			if (is.eleven)
				wl = pusheen(wl, ",-u,stpncpy,-u,wmemcmp,"
				    "-u,wcschr,-u,wcscmp");
#endif
			burger[3] = wl;
			for (s = 0, t = 4; s < NumDogeIParts; ++s) {
				burger[t++] = (char *)doge_i[s]();
				if (is.eleven) {
#ifdef innocent_pear_LIBSTDCXX_CXX_TARGET
					burger[t++] = (char *)"-lstdc++";
#endif
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_LIB_ATOMIC
					burger[t++] = (char *)"-latomic";
#endif
					burger[t++] = (char *)"-lc";
					burger[t++] = (char *)"-lgcc";
					if (is.sta)
						burger[t++] =
						    (char *)"-lgcc_eh";
					burger[t++] = (char *)"-lc";
					burger[t++] = (char *)"-lgcc";
					if (is.sta)
						burger[t++] =
						    (char *)"-lgcc_eh";
				}
			}
			*cheese++ = (char *)"-x";
			*cheese++ = (char *)"none";
			for (s = 0; s < NumDogeNParts; ++s) {
				*cheese++ = (char *)doge_n[s]();
				if (is.eleven) {
#ifdef innocent_pear_LIBSTDCXX_CXX_TARGET
					*cheese++ = (char *)"-lstdc++";
#endif
#ifdef innocent_pear_CXX_FOR_TARGET_HAVE_LIB_ATOMIC
					*cheese++ = (char *)"-latomic";
#endif
					*cheese++ = (char *)"-lc";
					*cheese++ = (char *)"-lgcc";
					if (is.sta)
						*cheese++ = (char *)"-lgcc_eh";
					*cheese++ = (char *)"-lc";
					*cheese++ = (char *)"-lgcc";
					if (is.sta)
						*cheese++ = (char *)"-lgcc_eh";
				}
			}
			*cheese++ = pusheen(caturday,
			    "/share/innocent-pear/doge-n.ld");
		} else {
			std::memmove(burger + 3, burger + 1,
			    (cheese - burger - 1) * sizeof(char *));
			cheese += 2;
			burger[1] = (char *)"-include";
			burger[2] = pusheen(meowmeow,
			    "/innocent-pear/doge.h");
		}
	} else if (is.s)
		*cheese++ = (char *)"-s";
	*cheese = 0;
	if (!doge_i[0])
		play(burger, 0, 0, seriouser.c_str(), is.grumpiest,
		    *cheeses, kitteh.c_str());
	else {
		playest(burger, 0, 0, seriouser.c_str(), is.grumpiest,
		    *cheeses, kitteh.c_str());
		if (shocker != -1)
			close(shocker);
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.dogecoin.start",
		    (char *)"_.innocent_pear.dogecoin.end",
		    st.x, is.grumpiest);
		doge_a.cheshire();
		nyanyan(ecaturday, doge_b(), doge_a(),
		    (char *)"_.innocent_pear.text.doge.07.start",
		    (char *)"_.innocent_pear.text.doge.45.start",
		    st.ix, is.grumpiest);
		doge_b.cheshire();
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.data.start",
		    (char *)"_.innocent_pear.data.end",
		    st.viii, is.grumpiest);
		doge_a.cheshire();
		nyanyan(ecaturday, doge_b(), doge_a(),
		    (char *)"_.innocent_pear.text.doge.06.start",
		    (char *)"_.innocent_pear.text.doge.07.start",
		    st.vii, is.grumpiest);
		doge_b.cheshire();
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.relro.start",
		    (char *)"_.innocent_pear.relro.end",
		    st.vi, is.grumpiest);
		doge_a.cheshire();
		nyanyan(ecaturday, doge_b(), doge_a(),
		    (char *)"_.innocent_pear.text.doge.05.start",
		    (char *)"_.innocent_pear.text.doge.06.start",
		    st.v, is.grumpiest);
		doge_b.cheshire();
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.rodata.start",
		    (char *)"_.innocent_pear.rodata.end",
		    st.iv, is.grumpiest);
		doge_a.cheshire();
		nyanyan(ecaturday, doge_b(), doge_a(),
		    (char *)"_.innocent_pear.text.doge.04.start",
		    (char *)"_.innocent_pear.text.doge.05.start",
		    st.iii, is.grumpiest);
		doge_b.cheshire();
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.text.start",
		    (char *)"_.innocent_pear.text.end",
		    st.ii, is.grumpiest);
		doge_a.cheshire();
		nyanyan(ecaturday, doge_b(), doge_a(),
		    (char *)"_.innocent_pear.text.doge.03.start",
		    (char *)"_.innocent_pear.text.doge.04.start",
		    st.i, is.grumpiest);
		doge_b.cheshire();
		nyanyan(ecaturday, doge_a(), doge_b(),
		    (char *)"_.innocent_pear.text.doge.02.start",
		    (char *)"_.innocent_pear.text.doge.03.start",
		    st.z, is.grumpiest);
		doge_a.cheshire();
		if (is.s) {
			nyanyanyan(doge_b(), doge_a(), is.grumpiest);
			doge_b.cheshire();
			doge_a.sleepiest(real_a);
		} else
			doge_b.sleepiest(real_a);
		return 0;
	}
}

int main(int argc, char **argv)
{
	try
		{ return main_(argc, argv); }
	catch (int ugh)
		{ return ugh; }
}
