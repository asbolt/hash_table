#include "hash_table_func.h"

int main (int argc, char *argv[])
{
    FILE *file = text_format (argv[ORIGINAL_TEXT_NAME]);
    Node **hash_table = hash_table_ctor();
    fill_hash_table (hash_table, "formatted_text.txt");
    hash_table_dtor (hash_table);

    return 0;
}