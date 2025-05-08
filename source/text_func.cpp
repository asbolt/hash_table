#include "text_func.h"

FILE *text_format (const char *text)
{
    assert (text);

    FILE *original_text = fopen (text, "r");
    if (!original_text)
    {
        return NULL;
    }

    fseek (original_text, 0, SEEK_END);
    size_t text_size = ftell (original_text);
    fseek (original_text, 0, SEEK_SET);

    char *buffer = (char *)calloc (text_size + 1, sizeof (char));
    if (!buffer)
    {
        fclose (original_text);
        return NULL;
    }

    fread (buffer, sizeof (char), text_size, original_text);
    buffer[text_size] = '\n';
    fclose (original_text);

    put_each_word_in_buffer_on_separate_line (buffer, text_size);

    FILE *formatted_text = fopen ("formatted_text.txt", "wa");
    if (!formatted_text)
    {
        free (buffer);
        return NULL;
    }

    fwrite (buffer, sizeof (char), text_size + 1, formatted_text);
    free (buffer);
    fclose (formatted_text);

    formatted_text = fopen ("formatted_text.txt", "r");
    return formatted_text;
}

void put_each_word_in_buffer_on_separate_line (char *buffer, size_t text_size)
{
    assert (buffer);

    for (size_t symbol = 0; symbol < text_size; symbol++)
    {
        if (!isalpha (buffer[symbol]))
        {
            buffer[symbol] = '\n';
        }
    }
}

char *read_word_from_file (FILE *file)
{
    assert (file);

    char *word = (char *)calloc (MAX_WORD_SIZE, sizeof (char));
    while (strlen (word) < MIN_WORD_SIZE)
        fgets (word, MAX_WORD_SIZE, file);

    size_t last_symbol_number = strlen (word);
    word [last_symbol_number - 1] = 0;

    return word;
}