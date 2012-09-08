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


#ifndef	_SIGINFO_H
#define	_SIGINFO_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/siginfo.h>

__BEGIN_DECLS

struct siginfolist {
	int nsiginfo;
	char **vsiginfo;
};

extern const char * _sys_illlist[];
extern const char * _sys_fpelist[];
extern const char * _sys_segvlist[];
extern const char * _sys_buslist[];
extern const char * _sys_traplist[];
extern const char * _sys_cldlist[];
extern const struct siginfolist *_sys_siginfolistp;
#define	_sys_siginfolist	_sys_siginfolistp
extern void psignal(int, const char *);
extern void psiginfo(siginfo_t *, char *);

__END_DECLS

#endif	/* _SIGINFO_H */