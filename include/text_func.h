#ifndef TEXT_FUNC_
#define TEXT_FUNC_

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

#define ORIGINAL_TEXT_NAME 1

#define MAX_WORD_SIZE 32
#define MIN_WORD_SIZE 2

FILE *text_format (const char *text);
void put_each_word_in_buffer_on_separate_line (char *buffer, size_t text_size);
char *read_word_from_file (FILE *file);
char *read_file (const char *text_file);

#endif