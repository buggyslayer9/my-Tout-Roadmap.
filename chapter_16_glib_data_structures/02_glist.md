# 16.2 GList: The Doubly Linked List

`GList` is GLib's doubly linked list implementation. It's heavily used throughout the GTK toolkit.

## Basic Usage

```c
#include <glib.h>

int main() {
    GList *list = NULL;  // A NULL pointer IS an empty list in GLib!

    // 1. Adding items
    // IMPORTANT: Always reassign the pointer! list = g_list_append(...)
    list = g_list_append(list, "Alice");
    list = g_list_append(list, "Bob");
    list = g_list_prepend(list, "Zara");  // Adds to the front.

    // 2. Iterating
    // l->data is a gpointer (void *), so we cast it.
    for (GList *l = list; l != NULL; l = l->next) {
        g_print("Item: %s\n", (char *)l->data);
    }

    // 3. Information
    g_print("List length: %d\n", g_list_length(list));

    // 4. Searching
    GList *found = g_list_find(list, "Bob");
    if (found) {
        g_print("Found: %s\n", (char *)found->data);
    }

    // 5. Memory Management
    // Frees the list nodes (but NOT the data they point to).
    g_list_free(list);

    return 0;
}
```

## Critical GLib List Rules

1. **Empty Lists:** In GLib, `NULL` represents an empty list. You don't allocate a "list header" object.
2. **Reassignment:** Functions like `g_list_append` might return a new head pointer (e.g., if the list was `NULL`). You **must** write `list = g_list_append(list, data);` entirely. Overwriting the pointer is required.
3. **Pointers Only:** Lists store `gpointer` (void pointers). If you want to store integers, you either use the macro tricks `GINT_TO_POINTER()` / `GPOINTER_TO_INT()`, or allocate integers on the heap.
4. **`g_list_free` vs Data:** `g_list_free(list)` frees the structural nodes. It *doesn't* free the strings or structs your nodes point to. If you dynamically allocated the contents, use `g_list_free_full()` passing a free function.
