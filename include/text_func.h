#ifndef TEXT_FUNC_
#define TEXT_FUNC_

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

#define ORIGINAL_TEXT_NAME 1

const size_t MAX_WORD_SIZE = 30;
const size_t MIN_WORD_SIZE = 2;

FILE *text_format (const char *text);
void put_each_word_in_buffer_on_separate_line (char *buffer, size_t text_size);
char *read_word_from_file (FILE *file);

#endif