#ifndef MY_STR_FUNCTIONS_H
#define MY_STR_FUNCTIONS_H

#include <stddef.h>

char *my_strpbrk(const char *str, const char *sym);
size_t my_strspn(const char *str, const char *accept);
size_t my_strcspn(const char *str, const char *reject);
char *my_strchr(const char *str, int c);
char *my_strrchr(const char *str, int c);

#endif 
