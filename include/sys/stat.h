#ifndef _NEWLIB_GLUE_SYS_STAT_H_
#define _NEWLIB_GLUE_SYS_STAT_H_

#ifdef __rtems__
#error "Unexpected definition of __rtems__. Please revisit this header wrapper."
#endif

#define __rtems__
#include_next <sys/stat.h>
#undef __rtems__

#define UTIME_NOW  0x3fffffff
#define UTIME_OMIT 0x3ffffffe

#endif
