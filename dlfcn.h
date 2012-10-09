#ifndef	_DLFCN_H
#define	_DLFCN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define RTLD_LAZY     0x00001
#define RTLD_NOW      0x00002
#define RTLD_NOLOAD   0x00004
#define RTLD_GLOBAL   0x00100
#define RTLD_LOCAL    0x00000
#define RTLD_PARENT   0x00200
#define RTLD_GROUP    0x00400
#define RTLD_WORLD    0x00800
#define RTLD_NODELETE 0x01000
#define RTLD_FIRST    0x02000

#define RTLD_NEXT    ((void *)-1)
#define RTLD_DEFAULT ((void *)-2)
#define RTLD_SELF    ((void *)-3)
#define RTLD_PROBE   ((void *)-4)

int    dlclose(void *);
char  *dlerror(void);
void  *dlopen(const char *, int);
void  *dlsym(void *__restrict, const char *__restrict);

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
typedef struct {
	const char *dli_fname;
	void *dli_fbase;
	const char *dli_sname;
	void *dli_saddr;
} Dl_info;
int dladdr(void *, Dl_info *);
#endif

#ifdef __cplusplus
}
#endif

#endif
