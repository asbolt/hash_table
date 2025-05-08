#ifndef HASH_TABLE_FUNC_
#define HASH_TABLE_FUNC_

#include "text_func.h"

const int WORD_MAX_SIZE   = 30;
const int HASH_TABLE_SIZE = 100;

struct Node
{
    char *value = NULL;
    int amount  = 0;
    Node *next  = NULL;
};

int hash_word (const char *word);
Node *node_ctor();
void node_dtor (Node *node);
Node **hash_table_ctor();
void hash_table_dtor (Node **hash_table);
int word_counter (const char *buffer, int buffer_size);
void fill_hash_table (Node **hash_table, const char *formatted_text);
void hash_table_check_element (const char *word, Node **hash_table);
void hash_table_add_element (const char *word, Node *node);
void hash_table_find_element (const char *word, Node **hash_table);

#endif