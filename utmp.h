#ifndef _UTMP_H
#define _UTMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <utmpx.h>

#define ACCOUNTING 9
#define UT_NAMESIZE 32
#define UT_HOSTSIZE 256

struct lastlog {
	time_t ll_time;
	char ll_line[UT_LINESIZE];
	char ll_host[UT_HOSTSIZE];
};

#define ut_time ut_tv.tv_sec
#define ut_name ut_user
#define ut_exit __ut_exit
#define e_termination __e_termination
#define e_exit __e_exit
#define utmp utmpx
#define utmpname(x) (-1)

void         endutent(void);
struct utmp *getutent(void);
struct utmp *getutid(const struct utmp *);
struct utmp *getutline(const struct utmp *);
struct utmp *pututline(const struct utmp *);
void         setutent(void);

void updwtmp(const char *, const struct utmp *);

#define _PATH_UTMP "/dev/null"
#define _PATH_WTMP "/dev/null"

#ifdef __cplusplus
}
#endif

#endif
