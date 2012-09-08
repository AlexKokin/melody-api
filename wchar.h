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
 * Copyright (c) 1993, 2010, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	_WCHAR_H
#define	_WCHAR_H

#include <sys/cdefs.h>
#include <sys/feature_tests.h>
#include <iso/wchar_iso.h>
#include <iso/wchar_c99.h>

__BEGIN_DECLS

#if !defined(_STRICT_STDC) || defined(_XOPEN_SOURCE) || defined(__EXTENSIONS__)
#if !defined(_WCTYPE_T) || __cplusplus >= 199711L
#define	_WCTYPE_T
typedef	int	wctype_t;
#endif
#endif /* !defined(_STRICT_STDC) || defined(_XOPEN_SOURCE)... */

/*
 * XPG6 requires that va_list be defined as defined in <stdarg.h>,
 * however, inclusion of <stdarg.h> breaks Standard C namespace.
 */
#if defined(_XPG6) && !defined(_VA_LIST)
#define	_VA_LIST
typedef __va_list va_list;
#endif  /* defined(_XPG6) && !defined(_VA_LIST) */

#if !defined(_STRICT_STDC) || defined(_XOPEN_SOURCE) || defined(__EXTENSIONS__)
extern int iswalpha(wint_t);
extern int iswupper(wint_t);
extern int iswlower(wint_t);
extern int iswdigit(wint_t);
extern int iswxdigit(wint_t);
extern int iswalnum(wint_t);
extern int iswspace(wint_t);
extern int iswpunct(wint_t);
extern int iswprint(wint_t);
extern int iswgraph(wint_t);
extern int iswcntrl(wint_t);
extern int iswctype(wint_t, wctype_t);
extern wint_t towlower(wint_t);
extern wint_t towupper(wint_t);
extern wchar_t *wcswcs(const wchar_t *, const wchar_t *);
extern int wcswidth(const wchar_t *, size_t);
extern int wcwidth(wchar_t);
extern wctype_t wctype(const char *);
#endif /* !defined(_STRICT_STDC) || defined(_XOPEN_SOURCE)... */

#if defined(__EXTENSIONS__) || \
	(!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX))
	/* || defined(_XPG7) */
extern wchar_t *wcsdup(const wchar_t *);
extern size_t wcsnlen(const wchar_t *, size_t);
extern wchar_t *wcpcpy(wchar_t *__restrict, const wchar_t *__restrict);
extern wchar_t *wcpncpy(wchar_t *__restrict, const wchar_t *__restrict,
    size_t);
extern int wcscasecmp(const wchar_t *, const wchar_t *);
extern int wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
#endif

__END_DECLS

#endif	/* _WCHAR_H */
