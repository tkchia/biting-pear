#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define DEFAULT_POLY	0x42f0e1eba9ea3693u

using namespace std;

static void make_crc_table(uint64_t crc_table[256], uint64_t poly)
{
	unsigned n, k;
	uint64_t c;
	for (n = 0; n < 256; ++n) {
		c = (uint64_t)n;
		for (k = 0; k < 8; ++k)
			c = c & 1 ? poly ^ (c >> 1) : c >> 1;
		crc_table[n] = c;
	}
}

static uint64_t update_crc(uint64_t crc, const uint8_t *buf, size_t n,
    const uint64_t crc_table[256])
{
	crc = ~crc;
	while (n-- != 0) {
		crc = crc_table[(uint8_t)crc ^ *buf] ^ (crc >> 8);
		++buf;
	}
	return ~crc;
}

int main(int argc, char **argv)
{
	uint64_t poly, crc_table[256], curr_crc;
	uint8_t buf[65536];
	ssize_t n;
	switch (argc) {
	    case 1:
		poly = DEFAULT_POLY;  break;
	    case 2:
		poly = (uint64_t)strtoumax(argv[1], NULL, 0);  break;
	    default:
		fprintf(stderr, "bad arguments\n");
		return 1;
	}
	make_crc_table(crc_table, poly);
	curr_crc = 0;
	while ((n = fread(buf, 1, sizeof buf, stdin)) > 0)
		curr_crc = update_crc(curr_crc, buf, (size_t)n, crc_table);
	if (n < 0) {
		fprintf(stderr, "error: %s\n", strerror(errno));
		return 2;
	}
	printf("0x%016" PRIx64 "\n", curr_crc);
	return 0;
}
