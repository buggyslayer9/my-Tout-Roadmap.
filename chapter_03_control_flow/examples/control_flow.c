/*
 * Chapter 3 — Control Flow (if/else, switch, loops)
 * Compile: gcc -Wall -Wextra -std=c11 control_flow.c -o control_flow
 * Run:     ./control_flow
 */
#include <stdio.h>

int main(void) {
    // === If / Else ===
    int score = 85;
    printf("Score: %d → ", score);
    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else if (score >= 70) {
        printf("Grade: C\n");
    } else {
        printf("Grade: F\n");
    }

    // === Ternary ===
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    printf("Max of %d and %d is %d\n", a, b, max);

    // === Switch ===
    char grade = 'B';
    printf("Grade %c: ", grade);
    switch (grade) {
        case 'A': printf("Excellent!\n"); break;
        case 'B': printf("Good job!\n"); break;
        case 'C': printf("Average.\n"); break;
        default:  printf("Invalid.\n"); break;
    }

    // === For Loop — Multiplication Table ===
    printf("\n=== Multiplication Table (1-5) ===\n");
    printf("%4s", "");
    for (int c = 1; c <= 5; c++) printf("%4d", c);
    printf("\n");

    for (int row = 1; row <= 5; row++) {
        printf("%4d", row);
        for (int col = 1; col <= 5; col++) {
            printf("%4d", row * col);
        }
        printf("\n");
    }

    // === Break and Continue ===
    printf("\nOdd numbers < 10 (using continue): ");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
