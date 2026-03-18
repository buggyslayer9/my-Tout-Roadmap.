#include <stdio.h>

int main(void){
    #define WIDTH 56
    char name[]= "Ayman ";
    int yearOfExperience = 3;
    double coffee = 3.14;
    char lang[] = "C / Gtk";
    printf("╔========================================================╗\n");
    printf("║                      AGENT DOSSIER                     ║\n");
    printf("╠========================================================╣\n");
    printf("║ %-20s %s %30s\n","Alias:",name,"║");
    printf("║ %-20s %d %35s\n","Year EXP:",yearOfExperience,"║");
    printf("║ %-20s %.2f %32s\n","Coffee/Day:",coffee,"║");
    printf("║ %-20s %s %29s\n","Language:",lang,"║");
    printf("╚========================================================╝\n");
    return 0;
}