#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <innocent-pear/rofl.h>

int main(void)
{
	using innocent_pear::ops::allow_for_startup;
	const unsigned char PAT = 0xf6;
	std::size_t psz = innocent_pear::rofl?<allow_for_startup>::
	    getpagesize();
	void *pm = innocent_pear::rofl?<allow_for_startup>::mmap(0, psz,
	    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);
	if (!pm) {
		std::cout << "not OK: mmap " << errno << '\n';
		return 1;
	}
	std::memset(pm, PAT, psz);
	unsigned char c = 0;
	while (!std::memchr(pm, c, psz))
		++c;
	if (c != PAT) {
		std::cout << "not OK: memchr\n";
		return 1;
	}
#if defined __linux__ && (defined __i386__ || defined __amd64__)
	int nb = innocent_pear::rofl?<allow_for_startup>::modify_ldt(0, pm,
	    psz);
	if (nb < 0 || (std::size_t)nb > psz) {
		std::cout << "not OK: modify_ldt\n";
		return 1;
	}
	std::memset((char *)pm + nb, 0, psz - nb);
	if (!std::memchr(pm, 0, psz)) {
		std::cout << "not OK: memchr #2\n";
		return 1;
	}
#endif
	if (innocent_pear::rofl?<allow_for_startup>::munmap(pm, psz) != 0) {
		std::cout << "not OK: munmap " << errno << '\n';
		return 1;
	}
	std::cout << "OK\n";
	return 0;
}
