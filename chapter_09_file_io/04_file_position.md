# 9.4 File Position: Seeking and Telling

When you read or write to a file, C maintains an internal cursor — the **file position indicator**. It starts at byte 0 and advances with every read/write. You can manually move this cursor to jump around inside the file.

## The Navigation Functions

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("data.bin", "rb");
    if (fp == NULL) { perror("fopen"); return 1; }
    
    // ftell: "Where is the cursor right now?"
    long current_pos = ftell(fp);
    printf("Current position: %ld bytes\n", current_pos);  // 0
    
    // fseek: "Move the cursor to a specific location."
    // SEEK_SET = from the beginning of the file.
    // SEEK_CUR = from the current position.
    // SEEK_END = from the end of the file.
    fseek(fp, 0, SEEK_END);  // Jump to the very end.
    
    long file_size = ftell(fp);  // Now ftell returns the total file size!
    printf("File size: %ld bytes\n", file_size);
    
    // rewind: Shortcut for fseek(fp, 0, SEEK_SET)
    rewind(fp);  // Cursor back to byte 0.
    
    fclose(fp);
    return 0;
}
```

## Practical Use Case: Reading the Nth Record

If your binary file contains an array of fixed-size structs, you can jump directly to any record without reading everything before it:

```c
typedef struct {
    char name[50];
    int  score;
} Record;

// Jump directly to the 5th record (index 4), skipping records 0-3.
fseek(fp, 4 * sizeof(Record), SEEK_SET);

Record fifth;
fread(&fifth, sizeof(Record), 1, fp);
printf("5th record: %s — %d\n", fifth.name, fifth.score);
```

This is how simple databases and save-game systems work — random access via calculated byte offsets.
