/*
 * Chapter 9 — File I/O (Text and Binary)
 * Compile: gcc -Wall -Wextra -std=c11 file_io.c -o file_io
 * Run:     ./file_io
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int  grade;
} Student;

int main(void) {
    // === Write Text File ===
    printf("=== Writing text file ===\n");
    FILE *fp = fopen("/tmp/demo_output.txt", "w");
    if (fp == NULL) {
        perror("fopen write");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Name: Ayman\n");
    fprintf(fp, "Course: C Programming\n");
    fprintf(fp, "Year: 2025\n");
    fclose(fp);
    printf("Wrote /tmp/demo_output.txt\n");

    // === Read Text File ===
    printf("\n=== Reading text file ===\n");
    fp = fopen("/tmp/demo_output.txt", "r");
    if (fp == NULL) {
        perror("fopen read");
        return EXIT_FAILURE;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("  %s", line);
    }
    fclose(fp);

    // === Write Binary File ===
    printf("\n=== Writing binary file ===\n");
    Student students[] = {
        {"Alice", 95},
        {"Bob", 82},
        {"Carol", 91},
    };
    int count = sizeof(students) / sizeof(students[0]);

    fp = fopen("/tmp/students.bin", "wb");
    if (fp == NULL) {
        perror("fopen binary write");
        return EXIT_FAILURE;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
    printf("Wrote %d students to /tmp/students.bin\n", count);

    // === Read Binary File ===
    printf("\n=== Reading binary file ===\n");
    fp = fopen("/tmp/students.bin", "rb");
    if (fp == NULL) {
        perror("fopen binary read");
        return EXIT_FAILURE;
    }
    int loaded_count;
    fread(&loaded_count, sizeof(int), 1, fp);
    printf("Found %d students:\n", loaded_count);

    Student loaded;
    for (int i = 0; i < loaded_count; i++) {
        fread(&loaded, sizeof(Student), 1, fp);
        printf("  %-10s %d\n", loaded.name, loaded.grade);
    }
    fclose(fp);

    // Cleanup temp files
    remove("/tmp/demo_output.txt");
    remove("/tmp/students.bin");
    printf("\nTemp files cleaned up.\n");

    return EXIT_SUCCESS;
}
