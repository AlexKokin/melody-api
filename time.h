/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/


/*
 * Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 * Copyright 2010 Nexenta Systems, Inc.  Al rights reserved.
 */

#ifndef _TIME_H
#define	_TIME_H

#include <sys/cdefs.h>
#include <sys/feature_tests.h>
#include <iso/time_iso.h>
#if (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	(_POSIX_C_SOURCE > 2) || defined(__EXTENSIONS__)
#include <sys/types.h>
#include <sys/time_impl.h>
#endif /* (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) ... */

__BEGIN_DECLS

#ifndef _CLOCKID_T
#define	_CLOCKID_T
typedef int	clockid_t;
#endif

#ifndef _TIMER_T
#define	_TIMER_T
typedef int	timer_t;
#endif

#if defined(__EXTENSIONS__) || \
	(!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	(_POSIX_C_SOURCE - 0 >= 199506L) || defined(_REENTRANT)
extern struct tm *gmtime_r(const time_t *__restrict,
			struct tm *__restrict);
extern struct tm *localtime_r(const time_t *__restrict,
			struct tm *__restrict);
#endif

#if (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	defined(_XPG4) || defined(__EXTENSIONS__)

#ifdef _STRPTIME_DONTZERO
extern char *__strptime_dontzero(const char *, const char *, struct tm *);
#define	strptime	__strptime_dontzero
#endif	/* _STRPTIME_DONTZERO */

extern char *strptime(const char *__restrict, const char *__restrict,
		struct tm *__restrict);

#endif /* (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX))... */

#if (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	(_POSIX_C_SOURCE > 2) || defined(__EXTENSIONS__)
/*
 * Neither X/Open nor POSIX allow the inclusion of <signal.h> for the
 * definition of the sigevent structure.  Both require the inclusion
 * of <signal.h> and <time.h> when using the timer_create() function.
 * However, X/Open also specifies that the sigevent structure be defined
 * in <time.h> as described in the header <signal.h>.  This prevents
 * compiler warnings for applications that only include <time.h> and not
 * also <signal.h>.  The sigval union and the sigevent structure is
 * therefore defined both here and in <sys/siginfo.h> which gets included
 * via inclusion of <signal.h>.
 */
#ifndef	_SIGVAL
#define	_SIGVAL
union sigval {
	int	sival_int;	/* integer value */
	void	*sival_ptr;	/* pointer value */
};
#endif	/* _SIGVAL */

#ifndef	_SIGEVENT
#define	_SIGEVENT
struct sigevent {
	int		sigev_notify;	/* notification mode */
	int		sigev_signo;	/* signal number */
	union sigval	sigev_value;	/* signal value */
	void		(*sigev_notify_function)(union sigval);
	pthread_attr_t	*sigev_notify_attributes;
	int		__sigev_pad2;
};
#endif	/* _SIGEVENT */

extern int clock_getres(clockid_t, struct timespec *);
extern int clock_gettime(clockid_t, struct timespec *);
extern int clock_settime(clockid_t, const struct timespec *);
extern int timer_create(clockid_t, struct sigevent *__restrict,
		timer_t *__restrict);
extern int timer_delete(timer_t);
extern int timer_getoverrun(timer_t);
extern int timer_gettime(timer_t, struct itimerspec *);
extern int timer_settime(timer_t, int, const struct itimerspec *__restrict,
		struct itimerspec *__restrict);

extern int nanosleep(const struct timespec *, struct timespec *);
extern int clock_nanosleep(clockid_t, int,
	const struct timespec *, struct timespec *);

#endif /* (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX))... */

#if !defined(_STRICT_STDC) || defined(__XOPEN_OR_POSIX) || \
	defined(__EXTENSIONS__)

extern void tzset(void);
extern char *tzname[2];

/* CLK_TCK marked as LEGACY in SUSv2 and removed in SUSv3 */
#if !defined(_XPG6) || defined(__EXTENSIONS__)
#ifndef CLK_TCK
extern long _sysconf(int);	/* System Private interface to sysconf() */
#define	CLK_TCK	((clock_t)_sysconf(3))	/* clock ticks per second */
				/* 3 is _SC_CLK_TCK */
#endif
#endif /* !defined(_XPG6) || defined(__EXTENSIONS__) */

#if (!defined(_STRICT_STDC) && !defined(_POSIX_C_SOURCE)) || \
	defined(_XOPEN_SOURCE) || defined(__EXTENSIONS__)
extern long timezone;
extern int daylight;
#endif

#endif /* !defined(_STRICT_STDC) || defined(__XOPEN_OR_POSIX)... */

#if (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	defined(__EXTENSIONS__)
extern time_t timegm(struct tm *);
extern int cftime(char *, char *, const time_t *);
extern int ascftime(char *, const char *, const struct tm *);
extern long altzone;
#endif

#if (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	defined(_XPG4_2) || defined(__EXTENSIONS__)
extern struct tm *getdate(const char *);
#ifdef	_REENTRANT
#undef getdate_err
#define	getdate_err *(int *)_getdate_err_addr()
extern int *_getdate_err_addr(void);
#else
extern int getdate_err;
#endif /* _REENTRANT */
#endif /* (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX))... */

/*
 * ctime_r() & asctime_r() prototypes are defined here.
 */

/*
 * Previous releases of Solaris, starting at 2.3, provided definitions of
 * various functions as specified in POSIX.1c, Draft 6.  For some of these
 * functions, the final POSIX 1003.1c standard had a different number of
 * arguments and return values.
 *
 * The following segment of this header provides support for the standard
 * interfaces while supporting applications written under earlier
 * releases.  The application defines appropriate values of the feature
 * test macros _POSIX_C_SOURCE and _POSIX_PTHREAD_SEMANTICS to indicate
 * whether it was written to expect the Draft 6 or standard versions of
 * these interfaces, before including this header.  This header then
 * provides a mapping from the source version of the interface to an
 * appropriate binary interface.  Such mappings permit an application
 * to be built from libraries and objects which have mixed expectations
 * of the definitions of these functions.
 *
 * For applications using the Draft 6 definitions, the binary symbol is the
 * same as the source symbol, and no explicit mapping is needed.  For the
 * standard interface, the function func() is mapped to the binary symbol
 * _posix_func().  The preferred mechanism for the remapping is a compiler
 * #pragma.  If the compiler does not provide such a #pragma, the header file
 * defines a static function func() which calls the _posix_func() version;
 * this has to be done instead of #define since POSIX specifies that an
 * application can #undef the symbol and still be bound to the correct
 * implementation.  Unfortunately, the statics confuse lint so we fallback to
 * #define in that case.
 *
 * NOTE: Support for the Draft 6 definitions is provided for compatibility
 * only.  New applications/libraries should use the standard definitions.
 */

#if	defined(__EXTENSIONS__) || defined(_REENTRANT) || \
	(!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	(_POSIX_C_SOURCE - 0 >= 199506L) || defined(_POSIX_PTHREAD_SEMANTICS)

#if	(_POSIX_C_SOURCE - 0 >= 199506L) || defined(_POSIX_PTHREAD_SEMANTICS)

static char *
asctime_r(const struct tm *__restrict __tm, char *__restrict __buf)
{
	return (__posix_asctime_r(__tm, __buf));
}

static char *
ctime_r(const time_t *__time, char *__buf)
{
	return (__posix_ctime_r(__time, __buf));
}

#else  /* (_POSIX_C_SOURCE - 0 >= 199506L) || ... */

extern char *asctime_r(const struct tm *, char *, int);
extern char *ctime_r(const time_t *, char *, int);

#endif  /* (_POSIX_C_SOURCE - 0 >= 199506L) || ... */

#endif /* defined(__EXTENSIONS__) || defined(_REENTRANT)... */

__END_DECLS

#endif	/* _TIME_H */
