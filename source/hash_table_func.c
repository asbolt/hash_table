#include "hash_table_func.h"
extern int hash_word (const char *word);

struct Node *node_ctor()
{
    struct Node *node = (struct Node *)calloc (1, sizeof (struct Node));
    if (!node)
    {
        return NULL;
    }

    node->value = (char *)calloc (WORD_MAX_SIZE, sizeof (char));
    if (!node->value)
    {
        return NULL;
    }

    node->amount = 0;

    return node;
}

void node_dtor (struct Node *node)
{
    assert (node);
    free (node);
}

struct Node **hash_table_ctor ()
{
    struct Node **hash_table = (struct Node **)calloc (HASH_TABLE_SIZE, sizeof (struct Node *));
    if (!hash_table)
    {
        return NULL;
    }

    for (int element = 0; element < HASH_TABLE_SIZE; element++)
    {
        hash_table[element] = node_ctor();
    }

    return hash_table;
}

void hash_table_dtor (struct Node **hash_table)
{
    assert (hash_table);

    for (int element = 0; element < HASH_TABLE_SIZE; element++)
    {
        node_dtor (hash_table[element]);
    }

    free (hash_table);
}

int word_counter (const char *buffer, int buffer_size)
{
    int words_amount = 0;
    for (int symbol = 0; symbol < buffer_size; symbol++)
    {
        if (buffer[symbol] == '\n')
        {
            words_amount++;
        }
    }

    return words_amount;
}

void fill_hash_table (struct Node **hash_table, const char *formatted_text)
{
    assert (hash_table);
    assert (formatted_text);

    char *buffer = read_file (formatted_text);
    int text_size = strlen (buffer);

    int words_amount = word_counter (buffer, text_size);
    char *word = (char *)calloc (WORD_MAX_SIZE, sizeof (char));
    if (!word)
    {
        return;
    }

    int current_symbol = 0;
    int start_point = 0;
    for (int word_number = 0; word_number < words_amount; word_number++)
    {
        while (buffer[current_symbol] != '\n')
        {
            current_symbol++;
        }
        
        if (current_symbol == start_point)
        {
            current_symbol++;
            start_point = current_symbol;
            continue;
        }

        memset (word, 0, MAX_WORD_SIZE);
        memcpy (word, buffer + start_point, current_symbol - start_point);
        current_symbol++;
        start_point = current_symbol;
        hash_table_check_element (word, hash_table);
    }
    
}

void hash_table_check_element (const char *word, struct Node **hash_table)
{
    int block_number = hash_word (word);
    if (hash_table[block_number]->amount == 0)
    {
        hash_table_add_element (word, hash_table[block_number]);
        for (int cycle = 0; cycle < CHECK_AMOUNT; cycle++)
        {
            hash_table_find_element (word, hash_table);
        }
        return;
    } 

    struct Node *current_node = hash_table[block_number];
    while (strcmp (word, current_node->value) != 0)
    {
        if (current_node->next == NULL)
        {
            break;
        }
        current_node = current_node->next;
    }

    if (current_node->next == NULL)
    {
        current_node->next = node_ctor();
        current_node = current_node->next;
        hash_table_add_element (word, current_node);
    } else {
        (current_node->amount)++;
    }

    for (int cycle = 0; cycle < CHECK_AMOUNT; cycle++)
    {
        hash_table_find_element (word, hash_table);
    }
}

void hash_table_add_element (const char *word, struct Node *node)
{
    int word_size = strlen (word); 
    printf ("%p\n", node->value);
    memcpy (node->value, word, word_size);
    (node->amount)++;
    return;
}

void hash_table_find_element (const char *word, struct Node **hash_table)
{
    int block_number = hash_word (word);
    struct Node *current_node = hash_table[block_number];

    while (strcmp (word, current_node->value) != 0)
    {
        current_node = current_node->next;
    }

    printf ("-----------------------------------------\n");
    printf ("Word: \"%s\" \n", word);
    printf ("Block number: %d\n", block_number);
    printf ("Amount in text: %d\n", current_node->amount);
    printf ("-----------------------------------------\n");
}