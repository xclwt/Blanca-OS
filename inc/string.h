#ifndef _INC_STRING_H
#define _INC_STRING_H

#include <inc/types.h>

int	strlen(const char *s);
char *	strcpy(char *dst, const char *src);
char *	strncpy(char *dst, const char *src, size_t size);
char *	strcat(char *dst, const char *src);
int	strcmp(const char *str1, const char *str2);
int	strncmp(const char *str1, const char *str2, size_t size);
char *strstr(const char *haystack, const char *needle);


void *	memmove(void *dst, const void *src, size_t len);
void *	memset(void *dst, uint8_t c, size_t len);


#endif /* not JOS_INC_STRING_H */
