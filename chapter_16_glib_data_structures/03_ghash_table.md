# 16.3 GHashTable: Key-Value Storage

Dictionary, Map, Hash Table — whatever you call it, `GHashTable` is how you store key-value pairs in GLib.

## Using a Hash Table

```c
#include <glib.h>

int main() {
    // 1. Create the table
    // For string keys, use g_str_hash and g_str_equal.
    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

    // 2. Insert data
    g_hash_table_insert(table, "name", "Alice");
    g_hash_table_insert(table, "role", "Admin");
    g_hash_table_insert(table, "status", "Active");

    // 3. Lookup data
    char *val = g_hash_table_lookup(table, "name");
    g_print("Name: %s\n", val ? val : "Not Found");

    // 4. Check existence (without fetching the value)
    if (g_hash_table_contains(table, "role")) {
        g_print("User has a role defined.\n");
    }

    // 5. Remove an item
    g_hash_table_remove(table, "status");

    // 6. Iterate through the table
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("%s : %s\n", (char *)key, (char *)value);
    }

    // 7. Cleanup
    g_hash_table_destroy(table);
    
    return 0;
}
```

## Memory Management (Advanced Create)

If you dynamically allocate your keys and values (`g_strdup`, `g_new`, etc.), you don't want to manually free them when removing items. Tell the hash table how to free them automatically:

```c
// When an item is replaced or removed, g_free is called on both key and value.
GHashTable *table = g_hash_table_new_full(
    g_str_hash, 
    g_str_equal, 
    g_free,    // key destroy function
    g_free     // value destroy function
);
```
