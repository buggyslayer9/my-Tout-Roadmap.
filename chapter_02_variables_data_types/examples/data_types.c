/*
 * Chapter 2 — Data Types, Sizeof, and Operators
 * Compile: gcc -Wall -Wextra -std=c11 data_types.c -o data_types
 * Run:     ./data_types
 */
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // Integer types
    char      c  = 'A';
    short     s  = 32000;
    int       i  = 2147483;
    long      l  = 123456789L;
    long long ll = 9999999999LL;

    // Floating point
    float  f = 3.14f;
    double d = 3.14159265358979;

    // Boolean
    bool flag = true;

    // Print sizes
    printf("=== Type Sizes ===\n");
    printf("char:      %zu bytes\n", sizeof(char));
    printf("short:     %zu bytes\n", sizeof(short));
    printf("int:       %zu bytes\n", sizeof(int));
    printf("long:      %zu bytes\n", sizeof(long));
    printf("long long: %zu bytes\n", sizeof(long long));
    printf("float:     %zu bytes\n", sizeof(float));
    printf("double:    %zu bytes\n", sizeof(double));
    printf("bool:      %zu bytes\n", sizeof(bool));
    printf("pointer:   %zu bytes\n", sizeof(void *));

    // Arithmetic operators
    int a = 10, b = 3;
    printf("\n=== Arithmetic (%d, %d) ===\n", a, b);
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d (integer division!)\n", a / b);
    printf("a %% b = %d\n", a % b);

    // Integer vs floating-point division
    printf("\n=== Division Danger ===\n");
    printf("7 / 2   = %d  (integer: truncated!)\n", 7 / 2);
    printf("7.0 / 2 = %f  (floating-point: correct)\n", 7.0 / 2);
    printf("(double)7 / 2 = %f  (cast: correct)\n", (double)7 / 2);

    return 0;
}
