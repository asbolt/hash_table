#ifndef HASH_TABLE_FUNC_
#define HASH_TABLE_FUNC_

#include "text_func.h"
//extern int hash_word (const char *word);

#define WORD_MAX_SIZE 32
#define HASH_TABLE_SIZE 128
#define CHECK_AMOUNT 500

struct Node
{
    char *value;
    int amount;
    struct Node *next;
};

struct Node *node_ctor();
void node_dtor (struct Node *node);
struct Node **hash_table_ctor();
void hash_table_dtor (struct Node **hash_table);
int word_counter (const char *buffer, int buffer_size);
void fill_hash_table (struct Node **hash_table, const char *formatted_text);
void hash_table_check_element (const char *word, struct Node **hash_table);
void hash_table_add_element (const char *word, struct Node *node);
void hash_table_find_element (const char *word, struct Node **hash_table);

#endif