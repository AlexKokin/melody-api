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

#ifndef _CTYPE_H
#define	_CTYPE_H

#include <sys/cdefs.h>
#include <iso/ctype_iso.h>
#include <iso/ctype_c99.h>

__BEGIN_DECLS

#if defined(__EXTENSIONS__) || \
	((!defined(_STRICT_STDC) && !defined(_POSIX_C_SOURCE)) || \
	defined(_XOPEN_SOURCE))

extern int isascii(int);
extern int toascii(int);
extern int _tolower(int);
extern int _toupper(int);

#endif /* defined(__EXTENSIONS__) || ((!defined(_STRICT_STDC) ... */

#if defined(__EXTENSIONS__) || \
	((!defined(_STRICT_STDC) && !defined(_POSIX_C_SOURCE)) || \
	defined(_XOPEN_SOURCE)) || defined(__XPG4_CHAR_CLASS__)
#define	isascii(c)	(!(((int)(c)) & ~0177))
#define	toascii(c)	(((int)(c)) & 0177)
#if defined(__XPG4_CHAR_CLASS__) || defined(_XPG4)
#define	_toupper(c)	(__trans_upper[(int)(c)])
#define	_tolower(c)	(__trans_lower[(int)(c)])
#else
#define	_toupper(c)	((__ctype + 258)[(int)(c)])
#define	_tolower(c)	((__ctype + 258)[(int)(c)])
#endif /* defined(__XPG4_CHAR_CLASS__) || defined(_XPG4) */

#endif /* defined(__EXTENSIONS__) || ((!defined(_STRICT_STDC) ... */

__END_DECLS

#endif	/* _CTYPE_H */
