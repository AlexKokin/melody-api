#ifndef	_STRINGS_H
#define	_STRINGS_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif


int bcmp (const void *, const void *, size_t);
void bcopy (const void *, void *, size_t);
void bzero (void *, size_t);

int ffs (int);

char *index (const char *, int);
char *rindex (const char *, int);

int strcasecmp (const char *, const char *);
int strncasecmp (const char *, const char *, size_t);

int strcasecmp_l (const char *, const char *, locale_t);
int strncasecmp_l (const char *, const char *, size_t, locale_t);

#ifdef __cplusplus
}
#endif

#endif
