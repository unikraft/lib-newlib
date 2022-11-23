#ifndef _TIME_H_
#define _TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <uk/config.h>
#include <_ansi.h>
#include <sys/reent.h>

#define __NEED_size_t
#define __NEED_time_t
#define __NEED_clock_t
#define __NEED_struct_timespec
#define __NEED_clockid_t
#define __NEED_timer_t
#define __NEED_pid_t
#define __NEED_locale_t

#include <sys/types.h>
#include <xlocale.h>

#ifndef CONFIG_LIBNOLIBC
/* Allow custom definitions */
#include_next <time.h>
#endif

#if defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
#define __tm_gmtoff tm_gmtoff
#define __tm_zone tm_zone
#endif

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long __tm_gmtoff;
	const char *__tm_zone;
};

clock_t clock (void);
time_t time (time_t *);
double difftime (time_t, time_t);
time_t mktime (struct tm *);
size_t strftime (char *__restrict, size_t, const char *__restrict, const struct tm *__restrict);
struct tm *gmtime (const time_t *);
struct tm *localtime (const time_t *);
char *asctime (const struct tm *);
char *ctime (const time_t *);
int timespec_get(struct timespec *, int);

#define CLOCKS_PER_SEC 1000000L

#define TIME_UTC 1

size_t strftime_l (char *  __restrict, size_t, const char *  __restrict, const struct tm *  __restrict, locale_t);

struct tm *gmtime_r (const time_t *__restrict, struct tm *__restrict);
struct tm *localtime_r (const time_t *__restrict, struct tm *__restrict);
char *asctime_r (const struct tm *__restrict, char *__restrict);
char *ctime_r (const time_t *, char *);

void tzset (void);

struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};

#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3
#define CLOCK_MONOTONIC_RAW      4
#define CLOCK_REALTIME_COARSE    5
#define CLOCK_MONOTONIC_COARSE   6
#define CLOCK_BOOTTIME           7
#define CLOCK_REALTIME_ALARM     8
#define CLOCK_BOOTTIME_ALARM     9
#define CLOCK_SGI_CYCLE         10
#define CLOCK_TAI               11

#define TIMER_ABSTIME 1

int nanosleep (const struct timespec *, struct timespec *);
int clock_getres (clockid_t, struct timespec *);
int clock_gettime (clockid_t, struct timespec *);
int clock_settime (clockid_t, const struct timespec *);
int clock_nanosleep (clockid_t, int, const struct timespec *, struct timespec *);
int clock_getcpuclockid (pid_t, clockid_t *);

struct sigevent;
int timer_create (clockid_t, struct sigevent *__restrict, timer_t *__restrict);
int timer_delete (timer_t);
int timer_settime (timer_t, int, const struct itimerspec *__restrict, struct itimerspec *__restrict);
int timer_gettime (timer_t, struct itimerspec *);
int timer_getoverrun (timer_t);

extern char *tzname[2];

#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
char *strptime (const char *__restrict, const char *__restrict, struct tm *__restrict);
extern int daylight;
extern long timezone;
extern int getdate_err;
struct tm *getdate (const char *);
#endif


#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
int stime(const time_t *);
time_t timegm(struct tm *);
#endif

#ifdef __cplusplus
}
#endif

#if __POSIX_VISIBLE
_VOID      _EXFUN(tzset,	(_VOID));
#endif
_VOID      _EXFUN(_tzset_r,	(struct _reent *));

typedef struct __tzrule_struct
{
  char ch;
  int m;
  int n;
  int d;
  int s;
  time_t change;
  long offset; /* Match type of _timezone. */
} __tzrule_type;

typedef struct __tzinfo_struct
{
  int __tznorth;
  int __tzyear;
  __tzrule_type __tzrule[2];
} __tzinfo_type;

__tzinfo_type *_EXFUN (__gettzinfo, (_VOID));

#ifdef HAVE_GETDATE
#if __XSI_VISIBLE >= 4
#ifndef _REENT_ONLY
#define getdate_err (*__getdate_err())
int *_EXFUN(__getdate_err,(_VOID));

struct tm *	_EXFUN(getdate, (const char *));
/* getdate_err is set to one of the following values to indicate the error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allication failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification  */
#endif /* !_REENT_ONLY */
#endif /* __XSI_VISIBLE >= 4 */

#if __GNU_VISIBLE
/* getdate_r returns the error code as above */
int		_EXFUN(getdate_r, (const char *, struct tm *));
#endif /* __GNU_VISIBLE */
#endif /* HAVE_GETDATE */

/* defines for the opengroup specifications Derived from Issue 1 of the SVID.  */
#if __SVID_VISIBLE || __XSI_VISIBLE
extern __IMPORT long _timezone;
extern __IMPORT int _daylight;
#endif
#if __POSIX_VISIBLE
extern __IMPORT char *_tzname[2];

/* POSIX defines the external tzname being defined in time.h */
#ifndef tzname
#define tzname _tzname
#endif
#endif /* __POSIX_VISIBLE */


#endif
