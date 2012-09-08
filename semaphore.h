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
/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SEMAPHORE_H
#define	_SEMAPHORE_H

#include <sys/feature_tests.h>
#include <sys/types.h>
#include <sys/fcntl.h>

__BEGIN_DECLS

typedef struct {
	/* this structure must be the same as sema_t in <synch.h> */
	uint32_t	sem_count;	/* semaphore count */
	uint16_t	sem_type;
	uint16_t	sem_magic;
	upad64_t	sem_pad1[3];	/* reserved for a mutex_t */
	upad64_t 	sem_pad2[2];	/* reserved for a cond_t */
} sem_t;

#define	SEM_FAILED	((sem_t *)(-1))

/*
 * function prototypes
 */
int	sem_init(sem_t *, int, unsigned int);
int	sem_destroy(sem_t *);
sem_t	*sem_open(const char *, int, ...);
int	sem_close(sem_t *);
int	sem_unlink(const char *);
int	sem_wait(sem_t *);
/*
 * Inclusion of <time.h> breaks X/Open and POSIX namespace.
 * The timespec structure while allowed in XPG6 and POSIX.1003d-1999,
 * is not permitted in prior POSIX or X/Open specifications even
 * though functions beginning with sem_* are allowed.
 */
#if !defined(__XOPEN_OR_POSIX) || defined(_XPG6) || defined(__EXTENSIONS__)
struct timespec;
int	sem_timedwait(sem_t *__restrict,
		const struct timespec *__restrict);
int	sem_reltimedwait_np(sem_t *__restrict,
		const struct timespec *__restrict);
#endif	/* !defined(__XOPEN_OR_POSIX) || defined(_XPG6) ... */
int	sem_trywait(sem_t *);
int	sem_post(sem_t *);
int	sem_getvalue(sem_t *__restrict, int *__restrict);

__END_DECLS

#endif	/* _SEMAPHORE_H */
