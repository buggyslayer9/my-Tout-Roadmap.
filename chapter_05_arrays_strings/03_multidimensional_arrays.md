# 5.3 Multidimensional Arrays (Matrices)

Sometimes data is two-dimensional: mathematical matrices, chess boards, pixel grids. C allows you to create arrays of arrays, structured dynamically in memory as one continuous contiguous sequence.

## Creating a 2D Matrix

You declare a multidimensional array by chaining bracket limits. First `[Rows]`, then `[Columns]`.

```c
// Creating a 3x3 grid
int matrix[3][3] = {
    {1, 2, 3},  // Row 0
    {4, 5, 6},  // Row 1
    {7, 8, 9}   // Row 2
};

// Accessing the exact center of the grid 
// (Row index 1, Col index 1)
printf("Center: %d\n", matrix[1][1]);  // 5
```

## Navigating the Grid with Nested Loops

To print a 2D array, we must use a nested iteration. An outer loop counts down the Y-axis (Rows). An inner loop sweeps across the X-axis (Columns).

```c
#include <stdio.h>

int main(void) {
    int matrix[3][3] = {
        {1,  2,  3},
        {4,  5,  6},
        {7,  8,  9}
    };

    // R iterates complete rows (0, 1, 2)
    for (int r = 0; r < 3; r++) {
        
        // C sweeps across columns for the current row
        for (int c = 0; c < 3; c++) {
            // "%3d" forces each number to take exactly 3 characters of space
            // keeping our grid perfectly aligned.
            printf("%3d ", matrix[r][c]);
        }
        
        // At the end of every row, print a hard return.
        printf("\n");
    }
    
    return 0;
}
```

## How It's Actually Stored

Under the hood, RAM is not a 2D grid. RAM is a flat, one-dimensional ribbon. 
When you create `matrix[3][3]`, C flattens it out in memory like this:
`| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |`

C automatically translates your `[row][col]` request into a 1D offset using this formula:
`memory_location = start_address + (row * total_columns + col) * size_of_data`

You don't need to manually calculate this yet, but understanding the illusion is part of mastering systems architecture.
