/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
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
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SIGNAL_H
#define	_SIGNAL_H

#include <sys/cdefs.h>
#include <sys/feature_tests.h>

#if defined(__EXTENSIONS__) || !defined(_STRICT_STDC) || \
	defined(__XOPEN_OR_POSIX)
#include <sys/types.h>	/* need pid_t/uid_t/size_t/clock_t/caddr_t/pthread_t */
#endif

#include <iso/signal_iso.h>
#include <sys/signal.h>

__BEGIN_DECLS

extern const char	**_sys_siglistp;	/* signal descriptions */
extern const int	_sys_siglistn;		/* # of signal descriptions */

#if defined(__EXTENSIONS__) || !defined(__XOPEN_OR_POSIX)
#define	_sys_siglist	_sys_siglistp
#define	_sys_nsig	_sys_siglistn
#endif

#if defined(__EXTENSIONS__) || !defined(_STRICT_STDC) || \
	defined(__XOPEN_OR_POSIX)
extern int kill(pid_t, int);
extern int sigaction(int, const struct sigaction *__restrict,
	struct sigaction *__restrict);
#ifndef	_KERNEL
extern int sigaddset(sigset_t *, int);
extern int sigdelset(sigset_t *, int);
extern int sigemptyset(sigset_t *);
extern int sigfillset(sigset_t *);
extern int sigismember(const sigset_t *, int);
#endif
extern int sigpending(sigset_t *);
extern int sigprocmask(int, const sigset_t *__restrict,
	sigset_t *__restrict);
extern int sigsuspend(const sigset_t *);
#endif /* defined(__EXTENSIONS__) || !defined(_STRICT_STDC)... */

#if defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && \
	!defined(__XOPEN_OR_POSIX))
#include <sys/procset.h>
extern int gsignal(int);
extern int (*ssignal(int, int (*)(int)))(int);
extern int sigsend(idtype_t, id_t, int);
extern int sigsendset(const procset_t *, int);
extern int sig2str(int, char *);
extern int str2sig(const char *, int *);
#define	SIG2STR_MAX	32
#endif /* defined(__EXTENSIONS__) || (!defined(_STRICT_STDC)... */

#if defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && \
	!defined(__XOPEN_OR_POSIX)) || defined(_XPG4_2)
extern void (*bsd_signal(int, void (*)(int)))(int);
extern int killpg(pid_t, int);
extern int siginterrupt(int, int);
extern int sigaltstack(const stack_t *__restrict, stack_t *__restrict);
extern int sighold(int);
extern int sigignore(int);
extern int sigpause(int);
extern int sigrelse(int);
extern void (*sigset(int, void (*)(int)))(int);
#endif /* defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && ... */

/* Marked as LEGACY in SUSv2 and removed in SUSv3 */
#if defined(__EXTENSIONS__) || \
	(!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	(defined(_XPG4_2) && !defined(_XPG6))
extern int sigstack(struct sigstack *, struct sigstack *);
#endif

#if defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && \
	!defined(__XOPEN_OR_POSIX)) || (_POSIX_C_SOURCE > 2)
#include <sys/siginfo.h>
#include <time.h>
extern int pthread_kill(pthread_t, int);
extern int pthread_sigmask(int, const sigset_t *__restrict,
	sigset_t *__restrict);
extern int sigwaitinfo(const sigset_t *__restrict,
	siginfo_t *__restrict);
extern int sigtimedwait(const sigset_t *__restrict,
	siginfo_t *__restrict, const struct timespec *__restrict);
extern int sigqueue(pid_t, int, const union sigval);
#endif /* defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && */

/*
 * sigwait() prototype is defined here.
 */

#if	defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) && \
	!defined(__XOPEN_OR_POSIX)) || (_POSIX_C_SOURCE - 0 >= 199506L) || \
	defined(_POSIX_PTHREAD_SEMANTICS)

#if	(_POSIX_C_SOURCE - 0 >= 199506L) || defined(_POSIX_PTHREAD_SEMANTICS)

extern int __posix_sigwait(const sigset_t *__restrict,
    int *__restrict);

sigwait(const sigset_t *__restrict __setp, int *__restrict __signo)
{
	return (__posix_sigwait(__setp, __signo));
}

#else  /* (_POSIX_C_SOURCE - 0 >= 199506L) || ... */

extern int sigwait(sigset_t *);

#endif  /* (_POSIX_C_SOURCE - 0 >= 199506L) || ... */

#endif /* defined(__EXTENSIONS__) || (!defined(_STRICT_STDC) ... */

__END_DECLS

#endif	/* _SIGNAL_H */
