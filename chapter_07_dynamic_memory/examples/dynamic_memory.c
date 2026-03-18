/*
 * Chapter 7 — Dynamic Memory Allocation
 * Compile: gcc -Wall -Wextra -std=c11 dynamic_memory.c -o dynamic_memory
 * Run:     ./dynamic_memory
 * Check:   valgrind --leak-check=full ./dynamic_memory
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 5;

    // === malloc ===
    printf("=== malloc (uninitialized) ===\n");
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "malloc failed!\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // === realloc ===
    printf("\n=== realloc (grow to 8 elements) ===\n");
    int new_n = 8;
    int *temp = (int *)realloc(arr, new_n * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "realloc failed!\n");
        free(arr);  // Original still valid!
        return EXIT_FAILURE;
    }
    arr = temp;
    for (int i = n; i < new_n; i++) {
        arr[i] = (i + 1) * 10;
    }
    for (int i = 0; i < new_n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // === calloc ===
    printf("\n=== calloc (zero-initialized) ===\n");
    int *zeros = (int *)calloc(5, sizeof(int));
    if (zeros == NULL) {
        fprintf(stderr, "calloc failed!\n");
        free(arr);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 5; i++) {
        printf("zeros[%d] = %d\n", i, zeros[i]);  // All 0
    }

    // === Compute mean ===
    printf("\n=== Mean Calculation ===\n");
    double sum = 0;
    for (int i = 0; i < new_n; i++) {
        sum += arr[i];
    }
    double mean = sum / new_n;
    printf("Mean: %.1f\n", mean);
    printf("Above mean: ");
    for (int i = 0; i < new_n; i++) {
        if (arr[i] > mean) printf("%d ", arr[i]);
    }
    printf("\n");

    // === Free everything ===
    free(arr);
    arr = NULL;
    free(zeros);
    zeros = NULL;

    printf("\nAll memory freed. Run with valgrind to verify!\n");
    return EXIT_SUCCESS;
}
