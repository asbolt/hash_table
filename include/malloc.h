#include <stdlib.h>

#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)
#define strlen(str) mystrlen(str)
#define memcpy(dest, source, count) mymemcpy(dest, source, count)
#define memset(buf, ch, count) mymemset(buf, ch, count)
#define strcmp(str1, str2) mystrcmp(str1, str2)

void *mymalloc(int size);
void myfree(void *ptr);
size_t mystrlen(const char *str);
void *mymemcpy(void *dest, const void *source, size_t count);
void *mymemset(void *buf, int ch, size_t count);
int mystrcmp(const char *str1, const char *str2);

