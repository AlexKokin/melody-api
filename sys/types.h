#ifndef	_SYS_TYPES_H
#define	_SYS_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_ino_t
#define __NEED_dev_t
#define __NEED_uid_t
#define __NEED_gid_t
#define __NEED_mode_t
#define __NEED_nlink_t
#define __NEED_off_t
#define __NEED_pid_t
#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_time_t
#define __NEED_timer_t
#define __NEED_clockid_t

#define __NEED_int8_t
#define __NEED_int16_t
#define __NEED_int32_t
#define __NEED_int64_t

#define __NEED___uint16_t
#define __NEED___uint32_t
#define __NEED___uint64_t

#define __NEED_blkcnt_t
#define __NEED_fsblkcnt_t
#define __NEED_fsfilcnt_t

#define __NEED_id_t
#define __NEED_key_t
#define __NEED_clock_t
#define __NEED_suseconds_t
#define __NEED_blksize_t

#define __NEED_pthread_t
#define __NEED_pthread_attr_t
#define __NEED_pthread_mutexattr_t
#define __NEED_pthread_condattr_t
#define __NEED_pthread_rwlockattr_t
#define __NEED_pthread_barrierattr_t
#define __NEED_pthread_mutex_t
#define __NEED_pthread_cond_t
#define __NEED_pthread_rwlock_t
#define __NEED_pthread_barrier_t
#define __NEED_pthread_spinlock_t
#define __NEED_pthread_key_t
#define __NEED_pthread_once_t

#define __NEED_uintptr_t

#include <bits/alltypes.h>

typedef enum boolean { B_FALSE, B_TRUE } boolean_t;

typedef unsigned char u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;

typedef unsigned char   uchar_t;
typedef unsigned short  ushort_t;
typedef unsigned int    uint_t;
typedef unsigned long   ulong_t;

typedef unsigned char   lock_t;
typedef long long       hrtime_t;

typedef int64_t         pad64_t;
typedef __uint64_t        upad64_t;

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
typedef char *caddr_t;
typedef unsigned char u_char;
typedef unsigned short u_short, ushort;
typedef unsigned u_int, uint;
typedef unsigned long u_long, ulong;
typedef long long quad_t;
typedef unsigned long long u_quad_t;
typedef long register_t;
#include <endian.h>
#include <sys/select.h>
#include <sys/sysmacros.h>
#endif

#if defined(_LARGEFILE64_SOURCE) || defined(_GNU_SOURCE)
#define blksize64_t blksize_t
#define blkcnt64_t blkcnt_t
#define fsblkcnt64_t fsblkcnt_t
#define fsfilcnt64_t fsfilcnt_t
#define ino64_t ino_t
#define off64_t off_t
#endif

#ifdef __cplusplus
}
#endif
#endif


