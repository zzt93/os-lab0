#ifndef __STRING_H__
#define __STRING_H__

#include "common.h"

char *itoa(int);
int itoa_s(int, char*, int);
int itoh_s(int, char*, int);
void memcpy(void *, const void *, size_t);
void memset(void *, int, size_t);
size_t strlen(const char *);
void strcpy(char *d, const char *s);
void print_str(void (*printer)(char), char *);

#endif
