#include "hash_table_func.h"

int main (int argc, char *argv[])
{
    int a = hash_word ("kkk");
    printf ("%d\n", a);
    FILE *file = text_format (argv[ORIGINAL_TEXT_NAME]);
    struct Node **hash_table = hash_table_ctor();
    fill_hash_table (hash_table, "formatted_text.txt");
    hash_table_dtor (hash_table);

    return 0;
}
