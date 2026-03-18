/*
 * Chapter 4 — Functions, Recursion, Scope
 * Compile: gcc -Wall -Wextra -std=c11 functions.c -o functions -lm
 * Run:     ./functions
 */
#include <stdio.h>
#include <math.h>

// Function prototypes
int add(int a, int b);
int factorial(int n);
int is_prime(int n);
int power(int base, int exp);

// Static variable demo
void count_calls(void) {
    static int count = 0;
    count++;
    printf("  Called %d time(s)\n", count);
}

int main(void) {
    // Basic function
    printf("add(3, 4) = %d\n", add(3, 4));

    // Recursion
    printf("factorial(5) = %d\n", factorial(5));
    printf("power(2, 10) = %d\n", power(2, 10));

    // Prime numbers 1-50
    printf("\nPrimes from 1 to 50:\n");
    for (int i = 2; i <= 50; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Static variable
    printf("\nStatic variable demo:\n");
    count_calls();
    count_calls();
    count_calls();

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
