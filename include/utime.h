#ifndef NEWLIBGLUE_UTIME_H
#define NEWLIBGLUE_UTIME_H

#include <sys/types.h>

struct utimbuf {
	time_t actime;
	time_t modtime;
};

int utime(const char *path, const struct utimbuf *times);

#endif /* NEWLIBGLUE_TIME_H */
