#include <cerrno>
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

static void cheshire(int fd)
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
		ssize_t wr = write(fd, buf, BUFSIZ);
#ifdef EINTR
		while (wr < 0 && errno == EINTR)
			wr = write(fd, buf, BUFSIZ);
#endif
		if (wr >= 0)
			sz -= wr;
		else
			break;		/* erm... */
	}
#ifdef innocent_pear_HAVE_FUNC_FDATASYNC
	fdatasync(fd);
#else
	fsync(fd);
#endif
#ifdef EINTR
	while (ftruncate(fd, (off_t)0) < 0 && errno == EINTR);
#else
	ftruncate(fd, (off_t)0);
#endif
	fsync(fd);
}

static void cheshire(const char *y)
{
	int fd = open(y, O_WRONLY);
	cheshire(fd);
	if (fd != -1)
		close(fd);
}

void sleepier_t::sleepier(const char *x)
{
	std::size_t ys = strlen(x) + 8;
	char *y = new char[ys];
	std::snprintf(y, ys, "%s.XXXXXX", x);
	int fd = mkstemp(y);
	if (fd == -1)
		concern("cannot create temporary file with pattern ", x,
			".XXXXXX");
	fchmod(fd, 0600);
	close(fd);
	y_ = y;
}

void sleepier_t::operator()(const char *x)
{
	if (y_)
		many("in vino veritas");
	sleepier(x);
}

void sleepier_t::cheshire()
{
	if (!y_)
		return;
	::cheshire(y_);
}

void sleepier_t::sleepiest()
{
	if (!y_)
		return;
	char *y = y_, yy[std::strlen(y) + 1];
	y_ = 0;
	std::strcpy(yy, y);
	delete[] y;
	::cheshire(yy);
	errno = 0;
	if (unlink(yy) != 0 && errno != ENOENT)
		concern("cannot remove ", yy);
}

void sleepier_t::sleepiest(const char *z)
{
	if (!y_)
		many("ex nihilo nihil fit");
	char *y = y_, yy[std::strlen(y) + 1];
	y_ = 0;
	std::strcpy(yy, y);
	delete[] y;
	if (std::rename(yy, z) != 0)
		concern("cannot rename ", yy, " to ", z);
}
