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
/*	wctype.h	1.13 89/11/02 SMI; JLE	*/
/*	from AT&T JAE 2.1			*/
/*	definitions for international functions	*/

/*
 * Copyright 2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_WCTYPE_H
#define	_WCTYPE_H

#include <iso/wctype_iso.h>
#if !defined(__XOPEN_OR_POSIX) && !defined(_STRICT_STDC) || defined(__EXTENSIONS__)
#include <ctype.h>
#include <wchar.h>
#endif

#include <iso/wctype_c99.h>

__BEGIN_DECLS

/* do not allow any of the following in a strictly conforming application */
#if !defined(__XOPEN_OR_POSIX) && !defined(_STRICT_STDC) || \
	defined(__EXTENSIONS__)

/*
 * data structure for supplementary code set
 * for character class and conversion
 */
struct	_wctype {
	wchar_t	tmin;		/* minimum code for wctype */
	wchar_t	tmax;		/* maximum code for wctype */
	unsigned char  *index;	/* class index */
	unsigned int   *type;	/* class type */
	wchar_t	cmin;		/* minimum code for conversion */
	wchar_t	cmax;		/* maximum code for conversion */
	wchar_t *code;		/* conversion code */
};


#ifdef	_ILLUMOS_PRIVATE
extern	int __iswrune(wint_t);
extern	wint_t __nextwctype(wint_t, wctype_t);
#define	iswrune(c)		__iswrune(c)
#define	nextwctype(c, t)	__nextwctype(c, t)
#endif

/* character classification functions */

/* iswascii is still a macro */
#define	iswascii(c)	isascii(c)

/* isw*, except iswascii(), are not macros any more.  They become functions */
extern	unsigned _iswctype(wchar_t, int);
extern	wchar_t _trwctype(wchar_t, int);
/* is* also become functions */
extern	int isphonogram(wint_t);
extern	int isideogram(wint_t);
extern	int isenglish(wint_t);
extern	int isnumber(wint_t);
extern	int isspecial(wint_t);

#define	iscodeset0(c)	isascii(c)
#define	iscodeset1(c)	(((c) & WCHAR_CSMASK) == WCHAR_CS1)
#define	iscodeset2(c)	(((c) & WCHAR_CSMASK) == WCHAR_CS2)
#define	iscodeset3(c)	(((c) & WCHAR_CSMASK) == WCHAR_CS3)

#endif /* !defined(__XOPEN_OR_POSIX)... */

__END_DECLS

#endif	/* _WCTYPE_H */
