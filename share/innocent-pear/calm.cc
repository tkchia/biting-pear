#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/dawg.h>

using innocent_pear::impl::uint64_t;

static int main_(int argc, char **argv, char *& grumpy, char *& grumpier)
{
	const char *lulz = innocent_pear::impl::getenv("INNOCENT_PEAR_PREFIX");
	enum { UNKNOWN, CLANG, AS, CC1, CC1PLUS, LD } wut = UNKNOWN;
	struct {
		unsigned pass : 1, e : 1, v : 1, x : 1;
	} is = { false, false, false, false };
	curious(*argv);
	if (!lulz)
		many($"Snape kills Dumbledore!");
	std::string lolz = lulz;
	char *calm[argc + 2], **calmer = calm, **calmest = 0;
	for (int argh = 1; argh < argc; ++argh) {
		char *opt = argv[argh], *base;
		switch (wut) {
		    case UNKNOWN:
			base = shocked(opt);
			if (strcmp(base, "clang") == 0)
				wut = CLANG;
			else if (strcmp(base, "as") == 0)
				wut = AS;
			else if (strcmp(base, "cc1") == 0)
				wut = CC1;
			else if (strcmp(base, "cc1plus") == 0)
				wut = CC1PLUS;
			else if (strcmp(base, "collect2") == 0 ||
				 strcmp(base, "ld") == 0 ||
				 strcmp(base, "ld.gold") == 0)
				wut = LD;
			break;
		    case CLANG:
			if (strcmp(opt, "-cc1") == 0)
				wut = CC1;
			else if (strcmp(opt, "-cc1as") == 0)
				wut = AS;
			break;
		    case CC1:
		    case CC1PLUS:
			if (is.pass)
				is.pass = false;
			  else if (is.x) {
				if (strcmp(opt, "c++") == 0 ||
				    strcmp(opt, "c++-cpp-output") == 0)
					wut = CC1PLUS;
				is.x = false;
			} else if (opt[0] != '-' || opt[1] == 0)
				break;
			  else if (opt[2] == 0) {
				switch (opt[1]) {
				    case 'E':
					is.e = true;  break;
				    case 'o':
					calmest = calmer + 1;
					/* fall through */
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
				    case 'v':
					is.v = true;  break;
				    case 'x':
					is.x = true;  break;
				    default:
					;
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
			  else if (strcmp(opt + 1, "aux-info") == 0 ||
				   strcmp(opt + 1, "-param") == 0)
				is.pass = true;
			break;
		    default:
			;
		}
		*calmer++ = opt;
	}
	*calmer = 0;
	switch (wut) {
	    default:
		keyboard(calm, 0, 0, 0, 0, is.v);
	    case CC1PLUS:
		{
			if (!is.e)
				keyboard(calm, 0, 0, 0, 0, is.v);
			grumpy = sleepier(*calmest);
			if (calmest) {
				lulz = *calmest;
				*calmest = grumpy;
			} else {
				*calmer++ = (char *)"-o";
				*calmer++ = grumpy;
				*calmer = 0;
			}
			keyboardest(calm, 0, 0, 0, 0, is.v);
			if (calmest)
				grumpier = sleepier(lulz);
			lolz += "/share/innocent-pear/omnomnom";
			calm[0] = (char *)lolz.c_str();
			calm[1] = new char[19];
			snprintf(calm[1], 19, "%#16" PRIx64,
			    file_crc64(grumpy));
			calm[2] = 0;
			keyboardest(calm, grumpy, grumpier, 0, 0, is.v);
			if (std::remove(grumpy) != 0)
				concern($"cannot remove ", grumpy);
			grumpy = 0;
			if (!calmest)
				return 0;
			if (rename(grumpier, lulz) != 0)
				concern($"cannot rename ", grumpier, $" to ",
				    lulz);
			return 0;
		}
	}
}

int main(int argc, char **argv)
{
	char *grumpy = 0, *grumpier = 0;
	try
		{ return main_(argc, argv, grumpy, grumpier); }
	catch (int ugh) {
		if (grumpy)
			std::remove(grumpy);
		if (grumpier)
			std::remove(grumpier);
		return ugh;
	}
}