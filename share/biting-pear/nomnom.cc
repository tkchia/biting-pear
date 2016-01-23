#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <biting-pear/host/derp.h>

#define DEFAULT_POLY	0x42f0e1eba9ea3693u

using namespace std;
using biting_pear::impl::uint_least64_t;

static void make_crc_table(uint_least64_t crc_table[256], uint_least64_t poly)
{
	unsigned n, k;
	uint_least64_t c;
	for (n = 0; n < 256; ++n) {
		c = (uint_least64_t)n;
		for (k = 0; k < 8; ++k)
			c = c & 1 ? poly ^ (c >> 1) : c >> 1;
		crc_table[n] = c;
	}
}

static uint_least64_t update_crc(uint_least64_t crc, const uint8_t *buf,
    size_t n, const uint_least64_t crc_table[256])
{
	crc = ~crc;
	while (n-- != 0) {
		crc = crc_table[(uint8_t)crc ^ *buf] ^ (crc >> 8);
		++buf;
	}
	return ~crc;
}

uint_least64_t file_crc64(const char *fn, uint_least64_t poly)
{
	uint_least64_t crc_table[256];
	uint8_t buf[65536];
	uint_least64_t curr_crc = 0;
	if (poly == 0)
		poly = DEFAULT_POLY;
	int fd = open(fn, O_RDONLY);
	if (fd == -1)
		return 0;
	make_crc_table(crc_table, poly);
	ssize_t r;
	while ((r = read(fd, buf, sizeof buf)) > 0)
		curr_crc = update_crc(curr_crc, buf, (size_t)r, crc_table);
	close(fd);
	return curr_crc;
}
