#ifndef _NEWLIB_GLUE_SYS_STAT_H_
#define _NEWLIB_GLUE_SYS_STAT_H_

/* define __rtems__ only if not previously defined */
#ifndef __rtems__
/* A definition only for this header */
#define __undef_rtems___NEWLIB_GLUE_SYS_STAT_H_
#define __rtems__
#endif

#include_next <sys/stat.h>

/* cleanup __rtems__ */
#ifdef __undef_rtems___NEWLIB_GLUE_SYS_STAT_H_
#undef __rtems__
#undef __undef_rtems___NEWLIB_GLUE_SYS_STAT_H_
#endif

#define UTIME_NOW  0x3fffffff
#define UTIME_OMIT 0x3ffffffe

#endif
