/*
 * Chapter 5 — Arrays, Strings, and Secure Input
 * Compile: gcc -Wall -Wextra -std=c11 arrays_strings.c -o arrays_strings
 * Run:     ./arrays_strings
 */
#include <stdio.h>
#include <string.h>

void print_array(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    // === Arrays ===
    int numbers[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int len = sizeof(numbers) / sizeof(numbers[0]);

    printf("Array: ");
    print_array(numbers, len);
    printf("Length: %d\n", len);

    // === Multidimensional Array ===
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("\nMatrix:\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            printf("%3d ", matrix[r][c]);
        }
        printf("\n");
    }

    // === Strings ===
    char name[] = "Ayman";
    char greeting[100];

    printf("\nName: %s (length: %zu)\n", name, strlen(name));

    // Safe string operations
    snprintf(greeting, sizeof(greeting), "Hello, %s! Welcome to C.", name);
    printf("%s\n", greeting);

    // String comparison
    if (strcmp(name, "Ayman") == 0) {
        printf("Name matches 'Ayman'\n");
    }

    // === Secure Input with fgets ===
    char input[50];
    printf("\nEnter a message: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';
        printf("You typed: '%s'\n", input);
        printf("Length: %zu\n", strlen(input));
    }

    return 0;
}
