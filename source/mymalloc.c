#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <immintrin.h>

void *mymalloc(size_t size)
{
    void *ptr = malloc(size);
    printf("malloc(%d)=%p\n", (int)size, ptr);
    return ptr;
}

void myfree(void *ptr)
{
    free(ptr);
    printf("free(%p)\n", ptr);
}

int mystrlen(const char *str)
{
    int size = strlen (str);
    printf("size: %d\n", size);
    return size;
}

void *mymemcpy(void *dest, const void *source, size_t count)
{
    memcpy (dest, source, count);
    printf ("dest: %p, source: %p\n", dest, source);
}

void *mymemset(void *buf, int ch, size_t count)
{
    memset (buf, ch, count);
    printf ("memset %ld symbols\n", count);
    return buf;
}

int mystrcmp(const char *str1, const char *str2)
{
    __m256i st2 = _mm256_set_epi8 ( str2[31], str2[30], str2[29], str2[28], str2[27], str2[26], str2[25],
                                    str2[24], str2[23], str2[22], str2[21], str2[20], str2[19], str2[18], 
                                    str2[17], str2[16], str2[15], str2[14], str2[13], str2[12], str2[11], 
                                    str2[10], str2[9], str2[8], str2[7], str2[6], str2[5], str2[4], str2[3], 
                                    str2[2], str2[1], str2[0]);
    __m256i st1 = _mm256_set_epi8 ( str1[31], str1[30], str1[29], str1[28], str1[27], str1[26], str1[25],
                                    str1[24], str1[23], str1[22], str1[21], str1[20], str1[19], str1[18], 
                                    str1[17], str1[16], str1[15], str1[14], str1[13], str1[12], str1[11], 
                                    str1[10], str1[9], str1[8], str1[7], str1[6], str1[5], str1[4], str1[3], 
                                    str1[2], str1[1], str1[0]);

    __m256i sub = _mm256_sub_epi8(st1, st2);
    int cmp = _mm256_movemask_epi8(sub);

    return cmp;
}

#endif