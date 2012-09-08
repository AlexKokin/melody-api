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

/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * Copyright (c) 2011 by Delphix. All rights reserved.
 */

#ifndef _SPAWN_H
#define	_SPAWN_H

#include <sys/cdefs.h>
#include <sys/feature_tests.h>
#include <sys/types.h>
#include <signal.h>
#include <sched.h>

__BEGIN_DECLS

/*
 * flags for posix_spawnattr_setflags()
 */
#define POSIX_SPAWN_RESETIDS            0x0001
#define POSIX_SPAWN_SETPGROUP           0x0002
#define POSIX_SPAWN_SETSIGDEF           0x0004
#define POSIX_SPAWN_SETSIGMASK          0x0008
#define POSIX_SPAWN_SETSCHEDPARAM       0x0010
#define POSIX_SPAWN_SETSCHEDULER        0x0020
/*
 * non-portable extensions
 */
#if defined(__EXTENSIONS__)
#define POSIX_SPAWN_SETSIGIGN_NP        0x0800
#define POSIX_SPAWN_NOSIGCHLD_NP        0x1000
#define POSIX_SPAWN_WAITPID_NP          0x2000
#define POSIX_SPAWN_NOEXECERR_NP        0x4000
#endif  /* !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) */

typedef struct {
        void *__spawn_attrp;    /* implementation-private */
} posix_spawnattr_t;

typedef struct {
        void *__file_attrp;     /* implementation-private */
} posix_spawn_file_actions_t;

extern int posix_spawn(
	pid_t *__restrict pid,
	const char *__restrict path,
	const posix_spawn_file_actions_t *file_actions,
	const posix_spawnattr_t *__restrict attrp,
	char *const [],
	char *const []);

extern int posix_spawnp(
	pid_t *__restrict pid,
	const char *__restrict file,
	const posix_spawn_file_actions_t *file_actions,
	const posix_spawnattr_t *__restrict attrp,
	char *const [],
	char *const []);

extern int posix_spawn_file_actions_init(
	posix_spawn_file_actions_t *file_actions);

extern int posix_spawn_file_actions_destroy(
	posix_spawn_file_actions_t *file_actions);

extern int posix_spawn_file_actions_addopen(
	posix_spawn_file_actions_t *__restrict file_actions,
	int filedes,
	const char *__restrict path,
	int oflag,
	mode_t mode);

extern int posix_spawn_file_actions_addclose(
	posix_spawn_file_actions_t *file_actions,
	int filedes);

extern int posix_spawn_file_actions_adddup2(
	posix_spawn_file_actions_t *file_actions,
	int filedes,
	int newfiledes);

extern int posix_spawnattr_init(
	posix_spawnattr_t *attr);

extern int posix_spawnattr_destroy(
	posix_spawnattr_t *attr);

extern int posix_spawnattr_setflags(
	posix_spawnattr_t *attr,
	short flags);

extern int posix_spawnattr_getflags(
	const posix_spawnattr_t *__restrict attr,
	short *__restrict flags);

extern int posix_spawnattr_setpgroup(
	posix_spawnattr_t *attr,
	pid_t pgroup);

extern int posix_spawnattr_getpgroup(
	const posix_spawnattr_t *__restrict attr,
	pid_t *__restrict pgroup);

extern int posix_spawnattr_setschedparam(
	posix_spawnattr_t *__restrict attr,
	const struct sched_param *__restrict schedparam);

extern int posix_spawnattr_getschedparam(
	const posix_spawnattr_t *__restrict attr,
	struct sched_param *__restrict schedparam);

extern int posix_spawnattr_setschedpolicy(
	posix_spawnattr_t *attr,
	int schedpolicy);

extern int posix_spawnattr_getschedpolicy(
	const posix_spawnattr_t *__restrict attr,
	int *__restrict schedpolicy);

extern int posix_spawnattr_setsigdefault(
	posix_spawnattr_t *__restrict attr,
	const sigset_t *__restrict sigdefault);

extern int posix_spawnattr_getsigdefault(
	const posix_spawnattr_t *__restrict attr,
	sigset_t *__restrict sigdefault);

/*
 * non-portable extensions
 */
#if defined(__EXTENSIONS__) 

extern int posix_spawn_pipe_np(
	pid_t *__restrict pidp,
	int *__restrict fdp,
	const char *__restrict cmd,
	boolean_t write,
	posix_spawn_file_actions_t *__restrict fact,
	posix_spawnattr_t *__restrict attr);

extern int posix_spawn_file_actions_addclosefrom_np(
	posix_spawn_file_actions_t *file_actions,
	int lowfiledes);

extern int posix_spawnattr_setsigignore_np(
	posix_spawnattr_t *__restrict attr,
	const sigset_t *__restrict sigignore);

extern int posix_spawnattr_getsigignore_np(
	const posix_spawnattr_t *__restrict attr,
	sigset_t *__restrict sigignore);

#endif	/* !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) */

extern int posix_spawnattr_setsigmask(
	posix_spawnattr_t *__restrict attr,
	const sigset_t *__restrict sigmask);

extern int posix_spawnattr_getsigmask(
	const posix_spawnattr_t *__restrict attr,
	sigset_t *__restrict sigmask);


__END_DECLS

#endif	/* _SPAWN_H */
