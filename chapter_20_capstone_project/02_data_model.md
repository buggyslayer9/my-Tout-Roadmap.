# 20.2 Capstone Data Model

Before you write a single line of UI code, you must define your data model. Good C programs are designed around their structs.

## The Core Struct

Here is the recommended data structure you should use for your task manager:

```c
#include <glib.h>

// Enums make priorities strictly typed and easier to sort/filter
typedef enum { 
    PRIORITY_LOW, 
    PRIORITY_MEDIUM, 
    PRIORITY_HIGH 
} Priority;

typedef struct {
    int       id;                 // Unique identifier for the task
    char      title[100];         // The main heading
    char      description[500];   // Detailed notes
    Priority  priority;           // Urgency
    char      due_date[11];       // String format "YYYY-MM-DD"
    gboolean  completed;          // Is it done? (Using GLib's boolean)
} Task;
```

## Why fixed-size character arrays?
Notice that `title` and `description` are `char[100]` instead of `char*`. 

While `char*` is standard for dynamic strings, using fixed-size arrays makes **binary file I/O** drastically easier. If the struct is a fixed size in memory (e.g., exactly 624 bytes), you can save an entire array of tasks directly to disk using a single `fwrite()` call, and load them all back with `fread()`.

If you use `char*`, the struct only stores the *memory address* (the pointer), not the text itself. Saving a pointer to disk is useless since that memory address will be invalid the next time you run the program!
