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
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_LWP_TIMER_IMPL_H
#define	_SYS_LWP_TIMER_IMPL_H

#include <sys/types.h>
#include <sys/thread.h>
#include <sys/lwp.h>
#include <sys/time.h>
#include <sys/systm.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
	kthread_t	*lwpt_thread;
	timespec_t	*lwpt_tsp;
	timespec_t	lwpt_rqtime;
	int		lwpt_timecheck;
	uint_t		lwpt_imm_timeout;
	int		lwpt_time_error;
	callout_id_t	lwpt_id;
} lwp_timer_t;

#ifdef _KERNEL
extern	int	lwp_timer_copyin(lwp_timer_t *, timespec_t *);
extern	int	lwp_timer_enqueue(lwp_timer_t *);
extern	clock_t	lwp_timer_dequeue(lwp_timer_t *);
extern	int	lwp_timer_copyout(lwp_timer_t *, int);
#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_LWP_TIMER_IMPL_H */
