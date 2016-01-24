#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

char *shocked(char *s)
{
	char *ss = std::strrchr(s, (int)(unsigned char)'/');
	if (!ss)
		return s;
	return ss + 1;
}

void curious(std::string& x, char *y)
{
	struct stat z;
	if (stat(y, &z) != 0 || !S_ISLNK(z.st_mode)) {
		x = shocked(y);
		return;
	}
	std::size_t w = z.st_size;
	if ((off_t)w < 0 || (off_t)w != (off_t)z.st_size) {
		x = shocked(y);
		return;
	}
	char v[w + 1];
	ssize_t ww = readlink(y, v, w);
	if (ww < 0 || (std::size_t)ww > w)
		x = shocked(y);
	else {
		v[ww] = 0;
		x = shocked(v);
	}
}
