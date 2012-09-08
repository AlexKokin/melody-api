/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)cdefs.h	8.8 (Berkeley) 1/9/95
 * $FreeBSD$
 */
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
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_CDEFS_H_
#define	_SYS_CDEFS_H_

#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif

/*
 * This code has been put in place to help reduce the addition of
 * compiler specific defines in FreeBSD code.  It helps to aid in
 * having a compiler-agnostic source tree.
 */

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#if __GNUC__ >= 3 || defined(__INTEL_COMPILER)
#define __GNUCLIKE_ASM 3
#define __GNUCLIKE_MATH_BUILTIN_CONSTANTS
#else
#define __GNUCLIKE_ASM 2
#endif
#define __GNUCLIKE___TYPEOF 1
#define __GNUCLIKE___OFFSETOF 1
#define __GNUCLIKE___SECTION 1

#ifndef __INTEL_COMPILER
# define __GNUCLIKE_CTOR_SECTION_HANDLING 1
#endif

#define __GNUCLIKE_BUILTIN_CONSTANT_P 1
# if defined(__INTEL_COMPILER) && defined(__cplusplus) \
    && __INTEL_COMPILER < 800
#  undef __GNUCLIKE_BUILTIN_CONSTANT_P
# endif

#if (__GNUC_MINOR__ > 95 || __GNUC__ >= 3) && !defined(__INTEL_COMPILER)
# define __GNUCLIKE_BUILTIN_VARARGS 1
# define __GNUCLIKE_BUILTIN_STDARG 1
# define __GNUCLIKE_BUILTIN_VAALIST 1
#endif

#if defined(__GNUC__)
# define __GNUC_VA_LIST_COMPATIBILITY 1
#endif

#ifndef __INTEL_COMPILER
# define __GNUCLIKE_BUILTIN_NEXT_ARG 1
# define __GNUCLIKE_MATH_BUILTIN_RELOPS
#endif

#define __GNUCLIKE_BUILTIN_MEMCPY 1

/* XXX: if __GNUC__ >= 2: not tested everywhere originally, where replaced */
#define __CC_SUPPORTS_INLINE 1
#define __CC_SUPPORTS___INLINE 1
#define __CC_SUPPORTS___INLINE__ 1

#define __CC_SUPPORTS___FUNC__ 1
#define __CC_SUPPORTS_WARNING 1

#define __CC_SUPPORTS_VARADIC_XXX 1 /* see varargs.h */

#define __CC_SUPPORTS_DYNAMIC_ARRAY_INIT 1

#endif /* __GNUC__ || __INTEL_COMPILER */

/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__GNUC_PREREQ__(ma, mi)	\
	(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define	__GNUC_PREREQ__(ma, mi)	0
#endif

/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky to use if it must work in non-ANSI
 * mode -- there must be no spaces between its arguments, and for nested
 * __CONCAT's, all the __CONCAT's must be at the left.  __CONCAT can also
 * concatenate double-quoted strings produced by the __STRING macro, but
 * this only works with ANSI C.
 *
 * __XSTRING is like __STRING, but it expands any macros in its argument
 * first.  It is only available with ANSI C.
 */
#if defined(__STDC__) || defined(__cplusplus)
#define	__P(protos)	protos		/* full-blown ANSI C */
#define	__CONCAT1(x,y)	x ## y
#define	__CONCAT(x,y)	__CONCAT1(x,y)
#define	__STRING(x)	#x		/* stringify without expanding x */
#define	__XSTRING(x)	__STRING(x)	/* expand x, then stringify */

#define	__const		const		/* define reserved names to standard */
#define	__signed	signed
#define	__volatile	volatile
#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#else
#if !(defined(__CC_SUPPORTS___INLINE))
#define	__inline			/* delete GCC keyword */
#endif /* ! __CC_SUPPORTS___INLINE */
#endif /* !__cplusplus */

#else	/* !(__STDC__ || __cplusplus) */
#define	__P(protos)	()		/* traditional C preprocessor */
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"

#if !defined(__CC_SUPPORTS___INLINE)
#define	__const				/* delete pseudo-ANSI C keywords */
#define	__inline
#define	__signed
#define	__volatile
/*
 * In non-ANSI C environments, new programs will want ANSI-only C keywords
 * deleted from the program and old programs will want them left alone.
 * When using a compiler other than gcc, programs using the ANSI C keywords
 * const, inline etc. as normal identifiers should define -DNO_ANSI_KEYWORDS.
 * When using "gcc -traditional", we assume that this is the intent; if
 * __GNUC__ is defined but __STDC__ is not, we leave the new keywords alone.
 */
#ifndef	NO_ANSI_KEYWORDS
#define	const				/* delete ANSI C keywords */
#define	inline
#define	signed
#define	volatile
#endif	/* !NO_ANSI_KEYWORDS */
#endif	/* !__CC_SUPPORTS___INLINE */
#endif	/* !(__STDC__ || __cplusplus) */

/*
 * Compiler-dependent macros to help declare dead (non-returning) and
 * pure (no side effects) functions, and unused variables.  They are
 * null except for versions of gcc that are known to support the features
 * properly (old versions of gcc-2 supported the dead and pure features
 * in a different (wrong) way).  If we do not provide an implementation
 * for a given compiler, let the compile fail if it is told to use
 * a feature that we cannot live without.
 */
#if !__GNUC_PREREQ__(2, 5) && !defined(__INTEL_COMPILER)
#define	__dead2
#define	__pure2
#define	__unused
#endif
#if __GNUC__ == 2 && __GNUC_MINOR__ >= 5 && __GNUC_MINOR__ < 7 && !defined(__INTEL_COMPILER)
#define	__dead2		__attribute__((__noreturn__))
#define	__pure2		__attribute__((__const__))
#define	__unused
/* XXX Find out what to do for __packed, __aligned and __section */
#if __GNUC_PREREQ__(2, 7)
#define	__dead2		__attribute__((__noreturn__))
#define	__pure2		__attribute__((__const__))
#define	__unused	__attribute__((__unused__))
#define	__used		__attribute__((__used__))
#define	__packed	__attribute__((__packed__))
#define	__aligned(x)	__attribute__((__aligned__(x)))
#define	__section(x)	__attribute__((__section__(x)))
#endif
#if defined(__INTEL_COMPILER)
#define __dead2		__attribute__((__noreturn__))
#define __pure2		__attribute__((__const__))
#define __unused	__attribute__((__unused__))
#define __used		__attribute__((__used__))
#define __packed	__attribute__((__packed__))
#define __aligned(x)	__attribute__((__aligned__(x)))
#define __section(x)	__attribute__((__section__(x)))
#endif
#endif

#if !__GNUC_PREREQ__(2, 95)
#define	__alignof(x)	__offsetof(struct { char __a; x __b; }, __b)
#endif

/*
 * Keywords added in C11.
 */
#if defined(__cplusplus) && __cplusplus >= 201103L
#define	_Alignas(e)		alignas(e)
#define	_Alignof(e)		alignof(e)
#define	_Noreturn		[[noreturn]]
#define	_Static_assert(e, s)	static_assert(e, s)
/* FIXME: change this to thread_local when clang in base supports it */
/* Pretty sure that means now? */
#define	_Thread_local		__thread
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/* Do nothing.  They are language keywords. */
#else
/* Not supported.  Implement them using our versions. */
#define	_Alignas(x)		__aligned(x)
#define	_Alignof(x)		__alignof(x)
#define	_Noreturn		__dead2
#define	_Thread_local		__thread
#ifdef __COUNTER__
#define	_Static_assert(x, y)	__Static_assert(x, __COUNTER__)
#define	__Static_assert(x, y)	___Static_assert(x, y)
#define	___Static_assert(x, y)	typedef char __assert_ ## y[(x) ? 1 : -1]
#else
#define	_Static_assert(x, y)	struct __hack
#endif
#endif

/*
 * Emulation of C11 _Generic().  Unlike the previously defined C11
 * keywords, it is not possible to implement this using exactly the same
 * syntax.  Therefore implement something similar under the name
 * __generic().  Unlike _Generic(), this macro can only distinguish
 * between a single type, so it requires nested invocations to
 * distinguish multiple cases.
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define	__generic(expr, t, yes, no)					\
	_Generic(expr, t: yes, default: no)
#elif __GNUC_PREREQ__(3, 1) && !defined(__cplusplus)
#define	__generic(expr, t, yes, no)					\
	__builtin_choose_expr(						\
	    __builtin_types_compatible_p(__typeof(expr), t), yes, no)
#endif

#if __GNUC_PREREQ__(2, 96)
#define	__malloc_like	__attribute__((__malloc__))
#define	__pure		__attribute__((__pure__))
#else
#define	__malloc_like
#define	__pure
#endif

#if __GNUC_PREREQ__(3, 1) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 800)
#define	__always_inline	__attribute__((__always_inline__))
#else
#define	__always_inline
#endif

#if __GNUC_PREREQ__(3, 1)
#define	__noinline	__attribute__ ((__noinline__))
#else
#define	__noinline
#endif

#if __GNUC_PREREQ__(3, 3)
#define __nonnull(x)	__attribute__((__nonnull__(x)))
#else
#define __nonnull(x)
#endif

#if __GNUC_PREREQ__(3, 4)
#define	__fastcall	__attribute__((__fastcall__))
#else
#define	__fastcall
#endif

#if __GNUC_PREREQ__(4, 1)
#define	__returns_twice	__attribute__((__returns_twice__))
#else
#define	__returns_twice
#endif

/* XXX: should use `#if __STDC_VERSION__ < 199901'. */
#if !__GNUC_PREREQ__(2, 7) && !defined(__INTEL_COMPILER)
#define	__func__	NULL
#endif

#if (defined(__INTEL_COMPILER) || (defined(__GNUC__) && __GNUC__ >= 2)) && !defined(__STRICT_ANSI__) || __STDC_VERSION__ >= 199901
#define	__LONG_LONG_SUPPORTED
#endif

/* C++11 exposes a load of C99 stuff */
#if defined(__cplusplus) && __cplusplus >= 201103L
#define	__LONG_LONG_SUPPORTED
#ifndef	__STDC_LIMIT_MACROS
#define	__STDC_LIMIT_MACROS
#endif
#ifndef	__STDC_CONSTANT_MACROS
#define	__STDC_CONSTANT_MACROS
#endif
#endif

/*
 * GCC 2.95 provides `__restrict' as an extension to C90 to support the
 * C99-specific `restrict' type qualifier.  We happen to use `__restrict' as
 * a way to define the `restrict' type qualifier without disturbing older
 * software that is unaware of C99 keywords.
 */
#if !(__GNUC__ == 2 && __GNUC_MINOR__ == 95)
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901 
#define	__restrict
#else
#define	__restrict	restrict
#endif
#endif

/* This is here to maintain backwards compatibility */
#define _RESTRICT_KYWD __restrict

/*
 * GNU C version 2.96 adds explicit branch prediction so that
 * the CPU back-end can hint the processor and also so that
 * code blocks can be reordered such that the predicted path
 * sees a more linear flow, thus improving cache behavior, etc.
 *
 * The following two macros provide us with a way to utilize this
 * compiler feature.  Use __predict_true() if you expect the expression
 * to evaluate to true, and __predict_false() if you expect the
 * expression to evaluate to false.
 *
 * A few notes about usage:
 *
 *	* Generally, __predict_false() error condition checks (unless
 *	  you have some _strong_ reason to do otherwise, in which case
 *	  document it), and/or __predict_true() `no-error' condition
 *	  checks, assuming you want to optimize for the no-error case.
 *
 *	* Other than that, if you don't know the likelihood of a test
 *	  succeeding from empirical or other `hard' evidence, don't
 *	  make predictions.
 *
 *	* These are meant to be used in places that are run `a lot'.
 *	  It is wasteful to make predictions in code that is run
 *	  seldomly (e.g. at subsystem initialization time) as the
 *	  basic block reordering that this affects can often generate
 *	  larger code.
 */
#if __GNUC_PREREQ__(2, 96)
#define __predict_true(exp)     __builtin_expect((exp), 1)
#define __predict_false(exp)    __builtin_expect((exp), 0)
#else
#define __predict_true(exp)     (exp)
#define __predict_false(exp)    (exp)
#endif

#if __GNUC_PREREQ__(4, 2)
#define	__hidden	__attribute__((__visibility__("hidden")))
#define	__exported	__attribute__((__visibility__("default")))
#else
#define	__hidden
#define	__exported
#endif

/*
 * We define this here since <stddef.h>, <sys/queue.h>, and <sys/types.h>
 * require it.
 */
#if __GNUC_PREREQ__(4, 1)
#define __offsetof(type, field)	 __builtin_offsetof(type, field)
#else
#ifndef __cplusplus
#define	__offsetof(type, field) \
	((__size_t)(__uintptr_t)((const volatile void *)&((type *)0)->field))
#else
#define __offsetof(type, field)					\
  (__offsetof__ (reinterpret_cast <__size_t>			\
                 (&reinterpret_cast <const volatile char &>	\
                  (static_cast<type *> (0)->field))))
#endif
#endif
#define	__rangeof(type, start, end) \
	(__offsetof(type, end) - __offsetof(type, start))

/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly (old versions of gcc-2
 * didn't permit keeping the keywords out of the application namespace).
 */
#if !__GNUC_PREREQ__(2, 7) && !defined(__INTEL_COMPILER)
#define	__printflike(fmtarg, firstvararg)
#define	__scanflike(fmtarg, firstvararg)
#define	__format_arg(fmtarg)
#define	__strfmonlike(fmtarg, firstvararg)
#define	__strftimelike(fmtarg, firstvararg)
#else
#define	__printflike(fmtarg, firstvararg) \
	    __attribute__((__format__ (__printf__, fmtarg, firstvararg)))
#define	__scanflike(fmtarg, firstvararg) \
	    __attribute__((__format__ (__scanf__, fmtarg, firstvararg)))
#define	__format_arg(fmtarg)	__attribute__((__format_arg__ (fmtarg)))
#define	__strfmonlike(fmtarg, firstvararg) \
	    __attribute__((__format__ (__strfmon__, fmtarg, firstvararg)))
#define	__strftimelike(fmtarg, firstvararg) \
	    __attribute__((__format__ (__strftime__, fmtarg, firstvararg)))
#endif

/* Compiler-dependent macros that rely on FreeBSD-specific extensions. */
#if defined(__FreeBSD_cc_version) && __FreeBSD_cc_version >= 300001 && \
    defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__printf0like(fmtarg, firstvararg) \
	    __attribute__((__format__ (__printf0__, fmtarg, firstvararg)))
#else
#define	__printf0like(fmtarg, firstvararg)
#endif

#if defined(__GNUC__) || defined(__INTEL_COMPILER)
#ifndef __INTEL_COMPILER
#define	__strong_reference(sym,aliassym)	\
	extern __typeof (sym) aliassym __attribute__ ((__alias__ (#sym)))
#endif
#ifdef __STDC__
#define	__weak_reference(sym,alias)	\
	__asm__(".weak " #alias);	\
	__asm__(".equ "  #alias ", " #sym)
#define	__warn_references(sym,msg)	\
	__asm__(".section .gnu.warning." #sym);	\
	__asm__(".asciz \"" msg "\"");	\
	__asm__(".previous")
#define	__sym_compat(sym,impl,verid)	\
	__asm__(".symver " #impl ", " #sym "@" #verid)
#define	__sym_default(sym,impl,verid)	\
	__asm__(".symver " #impl ", " #sym "@@" #verid)
#else
#define	__weak_reference(sym,alias)	\
	__asm__(".weak alias");		\
	__asm__(".equ alias, sym")
#define	__warn_references(sym,msg)	\
	__asm__(".section .gnu.warning.sym"); \
	__asm__(".asciz \"msg\"");	\
	__asm__(".previous")
#define	__sym_compat(sym,impl,verid)	\
	__asm__(".symver impl, sym@verid")
#define	__sym_default(impl,sym,verid)	\
	__asm__(".symver impl, sym@@verid")
#endif	/* __STDC__ */
#endif	/* __GNUC__ || __INTEL_COMPILER */

#define	__GLOBL1(sym)	__asm__(".globl " #sym)
#define	__GLOBL(sym)	__GLOBL1(sym)

#if defined(__GNUC__) || defined(__INTEL_COMPILER)
#define	__IDSTRING(name,string)	__asm__(".ident\t\"" string "\"")
#else
/*
 * The following definition might not work well if used in header files,
 * but it should be better than nothing.  If you want a "do nothing"
 * version, then it should generate some harmless declaration, such as:
 *    #define __IDSTRING(name,string)	struct __hack
 */
#define	__IDSTRING(name,string)	static const char name[] __unused = string
#endif

#ifndef	__DECONST
#define	__DECONST(type, var)	((type)(__uintptr_t)(const void *)(var))
#endif

#ifndef	__DEVOLATILE
#define	__DEVOLATILE(type, var)	((type)(__uintptr_t)(volatile void *)(var))
#endif

#ifndef	__DEQUALIFY
#define	__DEQUALIFY(type, var)	((type)(__uintptr_t)(const volatile void *)(var))
#endif

/*-
 * The following definitions are an extension of the behavior originally
 * implemented in <sys/_posix.h>, but with a different level of granularity.
 * POSIX.1 requires that the macros we test be defined before any standard
 * header file is included.
 *
 * Here's a quick run-down of the versions:
 *  defined(_POSIX_SOURCE)		1003.1-1988
 *  _POSIX_C_SOURCE == 1		1003.1-1990
 *  _POSIX_C_SOURCE == 2		1003.2-1992 C Language Binding Option
 *  _POSIX_C_SOURCE == 199309		1003.1b-1993
 *  _POSIX_C_SOURCE == 199506		1003.1c-1995, 1003.1i-1995,
 *					and the omnibus ISO/IEC 9945-1: 1996
 *  _POSIX_C_SOURCE == 200112		1003.1-2001
 *  _POSIX_C_SOURCE == 200809		1003.1-2008
 *
 * In addition, the X/Open Portability Guide, which is now the Single UNIX
 * Specification, defines a feature-test macro which indicates the version of
 * that specification, and which subsumes _POSIX_C_SOURCE.
 *
 * Our macros begin with two underscores to avoid namespace screwage.
 */

/* Deal with IEEE Std. 1003.1-1990, in which _POSIX_C_SOURCE == 1. */
/* TODO: Reconcile this with Illumos */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 1
#undef _POSIX_C_SOURCE		/* Probably illegal, but beyond caring now. */
#define	_POSIX_C_SOURCE		199009
#endif

/* Deal with IEEE Std. 1003.2-1992, in which _POSIX_C_SOURCE == 2. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 2
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		199209
#endif

/* Deal with various X/Open Portability Guides and Single UNIX Spec. */
#ifdef _XOPEN_SOURCE
#if _XOPEN_SOURCE - 0 >= 700
#define	__XSI_VISIBLE		700
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		200809
#elif _XOPEN_SOURCE - 0 >= 600
#define	__XSI_VISIBLE		600
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		200112
#elif _XOPEN_SOURCE - 0 >= 500
#define	__XSI_VISIBLE		500
#undef _POSIX_C_SOURCE
#define	_POSIX_C_SOURCE		199506
#endif
#endif

/*
 * Deal with all versions of POSIX.  The ordering relative to the tests above is
 * important.
 */
#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define	_POSIX_C_SOURCE		198808 /* This breaks compatibility with Solaris */
#endif                                 /* which would define POSIX_C_SOURCE 1 */
#ifdef _POSIX_C_SOURCE
#if _POSIX_C_SOURCE >= 200809
#define	__POSIX_VISIBLE		200809
#define	__ISO_C_VISIBLE		1999
#elif _POSIX_C_SOURCE >= 200112
#define	__POSIX_VISIBLE		200112
#define	__ISO_C_VISIBLE		1999
#elif _POSIX_C_SOURCE >= 199506
#define	__POSIX_VISIBLE		199506
#define	__ISO_C_VISIBLE		1990
#elif _POSIX_C_SOURCE >= 199309
#define	__POSIX_VISIBLE		199309
#define	__ISO_C_VISIBLE		1990
#elif _POSIX_C_SOURCE >= 199209
#define	__POSIX_VISIBLE		199209
#define	__ISO_C_VISIBLE		1990
#elif _POSIX_C_SOURCE >= 199009
#define	__POSIX_VISIBLE		199009
#define	__ISO_C_VISIBLE		1990
#else
#define	__POSIX_VISIBLE		198808
#define	__ISO_C_VISIBLE		0
#endif /* _POSIX_C_SOURCE */
#else
/*-
 * Deal with _ANSI_SOURCE:
 * If it is defined, and no other compilation environment is explicitly
 * requested, then define our internal feature-test macros to zero.  This
 * makes no difference to the preprocessor (undefined symbols in preprocessing
 * expressions are defined to have value zero), but makes it more convenient for
 * a test program to print out the values.
 *
 * If a program mistakenly defines _ANSI_SOURCE and some other macro such as
 * _POSIX_C_SOURCE, we will assume that it wants the broader compilation
 * environment (and in fact we will never get here).
 */
#if defined(_ANSI_SOURCE)	/* Hide almost everything. */
#define	__POSIX_VISIBLE		0
#define	__XSI_VISIBLE		0
#define	__BSD_VISIBLE		0
#define	__ISO_C_VISIBLE		1990
#elif defined(_C99_SOURCE)	/* Localism to specify strict C99 env. */
#define	__POSIX_VISIBLE		0
#define	__XSI_VISIBLE		0
#define	__BSD_VISIBLE		0
#define	__ISO_C_VISIBLE		1999
#elif defined(_C11_SOURCE)	/* Localism to specify strict C11 env. */
#define	__POSIX_VISIBLE		0
#define	__XSI_VISIBLE		0
#define	__BSD_VISIBLE		0
#define	__ISO_C_VISIBLE		2011
#else				/* Default environment: show everything. */
#define	__POSIX_VISIBLE		200809
#define	__XSI_VISIBLE		700
#define	__BSD_VISIBLE		1
#define	__ISO_C_VISIBLE		2011
#endif
#endif

/*
 * The feature test macros __XOPEN_OR_POSIX, _STRICT_STDC, and _STDC_C99
 * are Sun implementation specific macros created in order to compress
 * common standards specified feature test macros for easier reading.
 * These macros should not be used by the application developer as
 * unexpected results may occur. Instead, the user should reference
 * standards(5) for correct usage of the standards feature test macros.
 *
 * __XOPEN_OR_POSIX     Used in cases where a symbol is defined by both
 *                      X/Open or POSIX or in the negative, when neither
 *                      X/Open or POSIX defines a symbol.
 *
 * _STRICT_STDC         __STDC__ is specified by the C Standards and defined
 *                      by the compiler. For Sun compilers the value of
 *                      __STDC__ is either 1, 0, or not defined based on the
 *                      compilation mode (see cc(1)). When the value of
 *                      __STDC__ is 1 and in the absence of any other feature
 *                      test macros, the namespace available to the application
 *                      is limited to only those symbols defined by the C
 *                      Standard. _STRICT_STDC provides a more readable means
 *                      of identifying symbols defined by the standard, or in
 *                      the negative, symbols that are extensions to the C
 *                      Standard. See additional comments for GNU C differences.
 *
 * _STDC_C99            __STDC_VERSION__ is specified by the C standards and
 *                      defined by the compiler and indicates the version of
 *                      the C standard. A value of 199901L indicates a
 *                      compiler that complies with ISO/IEC 9899:1999, other-
 *                      wise known as the C99 standard.
 */

#if defined(_XOPEN_SOURCE) || defined(_POSIX_C_SOURCE)
#define __XOPEN_OR_POSIX
#endif

/*
 * ISO/IEC 9899:1990 and it's revision, ISO/IEC 9899:1999 specify the
 * following predefined macro name:
 *
 * __STDC__     The integer constant 1, intended to indicate a conforming
 *              implementation.
 *
 * Furthermore, a strictly conforming program shall use only those features
 * of the language and library specified in these standards. A conforming
 * implementation shall accept any strictly conforming program.
 *
 * Based on these requirements, Sun's C compiler defines __STDC__ to 1 for
 * strictly conforming environments and __STDC__ to 0 for environments that
 * use ANSI C semantics but allow extensions to the C standard. For non-ANSI
 * C semantics, Sun's C compiler does not define __STDC__.
 *
 * The GNU C project interpretation is that __STDC__ should always be defined
 * to 1 for compilation modes that accept ANSI C syntax regardless of whether
 * or not extensions to the C standard are used. Violations of conforming
 * behavior are conditionally flagged as warnings via the use of the
 * -pedantic option. In addition to defining __STDC__ to 1, the GNU C
 * compiler also defines __STRICT_ANSI__ as a means of specifying strictly
 * conforming environments using the -ansi or -std=<standard> options.
 *
 * In the absence of any other compiler options, Sun and GNU set the value
 * of __STDC__ as follows when using the following options:
 *
 *                              Value of __STDC__  __STRICT_ANSI__
 *
 * cc -Xa (default)                     0             undefined
 * cc -Xt (transitional)                0             undefined
 * cc -Xc (strictly conforming)         1             undefined
 * cc -Xs (K&R C)                   undefined         undefined
 *
 * gcc (default)                        1             undefined
 * gcc -ansi, -std={c89, c99,...)       1              defined
 * gcc -traditional (K&R)           undefined         undefined
 *
 * The default compilation modes for Sun C compilers versus GNU C compilers
 * results in a differing value for __STDC__ which results in a more
 * restricted namespace when using Sun compilers. To allow both GNU and Sun
 * interpretations to peacefully co-exist, we use the following Sun
 * implementation _STRICT_STDC_ macro:
 */

#if (__STDC__ - 0 == 1 && !defined(__GNUC__)) || \
        (defined(__GNUC__) && defined(__STRICT_ANSI__))
#define _STRICT_STDC
#else
#undef  _STRICT_STDC
#endif

/*
 * Compiler complies with ISO/IEC 9899:1999
 */

#if __STDC_VERSION__ - 0 >= 199901L
#define _STDC_C99
#endif

/*
 * Large file interfaces:
 *
 *      _LARGEFILE_SOURCE
 *              1               large file-related additions to POSIX
 *                              interfaces requested (fseeko, etc.)
 *      _LARGEFILE64_SOURCE
 *              1               transitional large-file-related interfaces
 *                              requested (seek64, stat64, etc.)
 *
 * The corresponding announcement macros are respectively:
 *      _LFS_LARGEFILE
 *      _LFS64_LARGEFILE
 * (These are set in <unistd.h>.)
 *
 * Requesting _LARGEFILE64_SOURCE implies requesting _LARGEFILE_SOURCE as
 * well.
 *
 * The large file interfaces are made visible regardless of the initial values
 * of the feature test macros under certain circumstances:
 *    - If no explicit standards-conforming environment is requested (neither
 *      of _POSIX_SOURCE nor _XOPEN_SOURCE is defined and the value of
 *      __STDC__ does not imply standards conformance).
 *    - Extended system interfaces are explicitly requested (__EXTENSIONS__
 *      is defined).
 *    - Access to in-kernel interfaces is requested (_KERNEL or _KMEMUSER is
 *      defined).  (Note that this dependency is an artifact of the current
 *      kernel implementation and may change in future releases.)
 */
#if     (!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
                defined(_KERNEL) || defined(_KMEMUSER) || \
                defined(__EXTENSIONS__)
#undef  _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE     1
#endif
#if     _LARGEFILE64_SOURCE - 0 == 1
#undef  _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE       1
#endif

/*
 * Large file compilation environment control:
 *
 * The setting of _FILE_OFFSET_BITS controls the size of various file-related
 * types and governs the mapping between file-related source function symbol
 * names and the corresponding binary entry points.
 *
 * In the 32-bit environment, the default value is 32; if not set, set it to
 * the default here, to simplify tests in other headers.
 *
 * In the 64-bit compilation environment, the only value allowed is 64.
 */
#if defined(_LP64)
#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS       64
#endif
#if     _FILE_OFFSET_BITS - 0 != 64
#error  "invalid _FILE_OFFSET_BITS value specified"
#endif
#else   /* _LP64 */
/* We should probably never get here... */
#error  "Only _LP64 is supported"
#endif  /* _LP64 */


/*
 * Use of _XOPEN_SOURCE
 *
 * The following X/Open specifications are supported:
 *
 * X/Open Portability Guide, Issue 3 (XPG3)
 * X/Open CAE Specification, Issue 4 (XPG4)
 * X/Open CAE Specification, Issue 4, Version 2 (XPG4v2)
 * X/Open CAE Specification, Issue 5 (XPG5)
 * Open Group Technical Standard, Issue 6 (XPG6), also referred to as
 *    IEEE Std. 1003.1-2001 and ISO/IEC 9945:2002.
 *
 * XPG4v2 is also referred to as UNIX 95 (SUS or SUSv1).
 * XPG5 is also referred to as UNIX 98 or the Single Unix Specification,
 *     Version 2 (SUSv2)
 * XPG6 is the result of a merge of the X/Open and POSIX specifications
 *     and as such is also referred to as IEEE Std. 1003.1-2001 in
 *     addition to UNIX 03 and SUSv3.
 *
 * When writing a conforming X/Open application, as per the specification
 * requirements, the appropriate feature test macros must be defined at
 * compile time. These are as follows. For more info, see standards(5).
 *
 * Feature Test Macro                                Specification
 * ------------------------------------------------  -------------
 * _XOPEN_SOURCE                                         XPG3
 * _XOPEN_SOURCE && _XOPEN_VERSION = 4                   XPG4
 * _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED = 1           XPG4v2
 * _XOPEN_SOURCE = 500                                   XPG5
 * _XOPEN_SOURCE = 600  (or POSIX_C_SOURCE=200112L)      XPG6
 *
 * In order to simplify the guards within the headers, the following
 * implementation private test macros have been created. Applications
 * must NOT use these private test macros as unexpected results will
 * occur.
 *
 * Note that in general, the use of these private macros is cumulative.
 * For example, the use of _XPG3 with no other restrictions on the X/Open
 * namespace will make the symbols visible for XPG3 through XPG6
 * compilation environments. The use of _XPG4_2 with no other X/Open
 * namespace restrictions indicates that the symbols were introduced in
 * XPG4v2 and are therefore visible for XPG4v2 through XPG6 compilation
 * environments, but not for XPG3 or XPG4 compilation environments.
 *
 * _XPG3    X/Open Portability Guide, Issue 3 (XPG3)
 * _XPG4    X/Open CAE Specification, Issue 4 (XPG4)
 * _XPG4_2  X/Open CAE Specification, Issue 4, Version 2 (XPG4v2/UNIX 95/SUS)
 * _XPG5    X/Open CAE Specification, Issue 5 (XPG5/UNIX 98/SUSv2)
 * _XPG6    Open Group Technical Standard, Issue 6 (XPG6/UNIX 03/SUSv3)
 */

/* X/Open Portability Guide, Issue 3 */
#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE - 0 < 500) && \
        (_XOPEN_VERSION - 0 < 4) && !defined(_XOPEN_SOURCE_EXTENDED)
#define _XPG3
/* X/Open CAE Specification, Issue 4 */
#elif   (defined(_XOPEN_SOURCE) && _XOPEN_VERSION - 0 == 4)
#define _XPG4
#define _XPG3
/* X/Open CAE Specification, Issue 4, Version 2 */
#elif (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE_EXTENDED - 0 == 1)
#define _XPG4_2
#define _XPG4
#define _XPG3
/* X/Open CAE Specification, Issue 5 */
#elif   (_XOPEN_SOURCE - 0 == 500)
#define _XPG5
#define _XPG4_2
#define _XPG4
#define _XPG3
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE                 199506L
/* Open Group Technical Standard , Issue 6 */
#elif   (_XOPEN_SOURCE - 0 == 600) || (_POSIX_C_SOURCE - 0 == 200112L)
#define _XPG6
#define _XPG5
#define _XPG4_2
#define _XPG4
#define _XPG3
#undef  _POSIX_C_SOURCE
#define _POSIX_C_SOURCE                 200112L
#undef  _XOPEN_SOURCE
#define _XOPEN_SOURCE                   600
#endif

/*
 * _XOPEN_VERSION is defined by the X/Open specifications and is not
 * normally defined by the application, except in the case of an XPG4
 * application.  On the implementation side, _XOPEN_VERSION defined with
 * the value of 3 indicates an XPG3 application. _XOPEN_VERSION defined
 * with the value of 4 indicates an XPG4 or XPG4v2 (UNIX 95) application.
 * _XOPEN_VERSION  defined with a value of 500 indicates an XPG5 (UNIX 98)
 * application and with a value of 600 indicates an XPG6 (UNIX 03)
 * application.  The appropriate version is determined by the use of the
 * feature test macros described earlier.  The value of _XOPEN_VERSION
 * defaults to 3 otherwise indicating support for XPG3 applications.
 */
#ifndef _XOPEN_VERSION
#ifdef  _XPG6
#define _XOPEN_VERSION 600
#elif defined(_XPG5)
#define _XOPEN_VERSION 500
#elif   defined(_XPG4_2)
#define _XOPEN_VERSION  4
#else
#define _XOPEN_VERSION  3
#endif
#endif

/*
 * ANSI C and ISO 9899:1990 say the type long long doesn't exist in strictly
 * conforming environments.  ISO 9899:1999 says it does.
 *
 * The presence of _LONGLONG_TYPE says "long long exists" which is therefore
 * defined in all but strictly conforming environments that disallow it.
 */
#if !defined(_STDC_C99) && defined(_STRICT_STDC) && !defined(__GNUC__)
/*
 * Resist attempts to force the definition of long long in this case.
 */
#if defined(_LONGLONG_TYPE)
#error  "No long long in strictly conforming ANSI C & 1990 ISO C environments"
#endif
#else
#if !defined(_LONGLONG_TYPE)
#define _LONGLONG_TYPE
#endif
#endif

/*
 * It is invalid to compile an XPG3, XPG4, XPG4v2, or XPG5 application
 * using c99.  The same is true for POSIX.1-1990, POSIX.2-1992, POSIX.1b,
 * and POSIX.1c applications. Likewise, it is invalid to compile an XPG6
 * or a POSIX.1-2001 application with anything other than a c99 or later
 * compiler.  Therefore, we force an error in both cases.
 */
#if defined(_STDC_C99) && (defined(__XOPEN_OR_POSIX) && !defined(_XPG6))
#error "Compiler or options invalid for pre-UNIX 03 X/Open applications \
        and pre-2001 POSIX applications"
#elif !defined(_STDC_C99) && \
        (defined(__XOPEN_OR_POSIX) && defined(_XPG6))
#error "Compiler or options invalid; UNIX 03 and POSIX.1-2001 applications \
        require the use of c99"
#endif

/*
 * The following macro indicates header support for the ANSI C++
 * standard.  The ISO/IEC designation for this is ISO/IEC FDIS 14882.
 */
#define _ISO_CPP_14882_1998

/*
 * The following macro indicates header support for the C99 standard,
 * ISO/IEC 9899:1999, Programming Languages - C.
 */
#define _ISO_C_9899_1999

/*
 * The following macro indicates header support for DTrace. The value is an
 * integer that corresponds to the major version number for DTrace.
 */
#define _DTRACE_VERSION 1


#ifndef	__has_feature
#define	__has_feature(x) 0
#endif
#ifndef	__has_include
#define	__has_include(x) 0
#endif
#ifndef	__has_builtin
#define	__has_builtin(x) 0
#endif

#endif /* !_SYS_CDEFS_H_ */
