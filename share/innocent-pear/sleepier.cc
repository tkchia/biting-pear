#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/dawg.h>

char *sleepier(const char *x)
{
	std::size_t ys = strlen(x) + 8;
	char *y = new char[ys];
	std::snprintf(y, ys, "%s.XXXXXX", x);
	if (!mkstemp(y))
		concern($"cannot create temporary file with pattern "
			 "`", y, $"'");
	return y;
}

static void sleepiest(int fd)
{
	if (fd == -1)
		return;
	struct stat sb;
	if (fstat(fd, &sb) == -1)
		return;
	off_t sz = sb.st_size;
	if (sz <= 0)
		return;
	char buf[BUFSIZ];
	memset(buf, 0xaa, BUFSIZ);
	while (sz > 0) {
		if (write(fd, buf, BUFSIZ) < 0);
		sz -= BUFSIZ;
	}
#ifdef innocent_pear_HAVE_FUNC_FDATASYNC
	fdatasync(fd);
#else
	fsync(fd);
#endif
	if (ftruncate(fd, (off_t)0) < 0);
	fsync(fd);
}

int sleepiest(const char *y)
{
	int fd = open(y, O_WRONLY);
	sleepiest(fd);
	if (fd != -1)
		close(fd);
	return unlink(y);
}
