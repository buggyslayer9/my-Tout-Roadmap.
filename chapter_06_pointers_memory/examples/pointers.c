/*
 * Chapter 6 — Pointers and Memory
 * Compile: gcc -Wall -Wextra -std=c11 pointers.c -o pointers
 * Run:     ./pointers
 */
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_min_max(int *arr, int len, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void reverse_array(int *arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);
    }
}

void print_array(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    // === Basic Pointer Demo ===
    int x = 42;
    int *p = &x;

    printf("=== Pointer Basics ===\n");
    printf("x = %d\n", x);
    printf("&x = %p\n", (void *)&x);
    printf("p = %p\n", (void *)p);
    printf("*p = %d\n", *p);

    *p = 100;
    printf("After *p = 100: x = %d\n", x);

    // === Swap ===
    int a = 5, b = 10;
    printf("\n=== Swap ===\n");
    printf("Before: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("After:  a=%d, b=%d\n", a, b);

    // === Find Min/Max ===
    int data[] = {5, 2, 8, 1, 9, 3};
    int len = sizeof(data) / sizeof(data[0]);
    int min, max;
    find_min_max(data, len, &min, &max);
    printf("\n=== Min/Max ===\n");
    printf("Array: ");
    print_array(data, len);
    printf("Min: %d, Max: %d\n", min, max);

    // === Reverse ===
    printf("\n=== Reverse ===\n");
    printf("Before: ");
    print_array(data, len);
    reverse_array(data, len);
    printf("After:  ");
    print_array(data, len);

    // === Double Pointer ===
    int **pp = &p;
    printf("\n=== Double Pointer ===\n");
    printf("**pp = %d\n", **pp);

    return 0;
}
