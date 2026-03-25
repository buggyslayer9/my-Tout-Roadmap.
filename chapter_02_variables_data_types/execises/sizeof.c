#include <stddef.h>
#include <stdio.h>
size_t process_array(int arr[],size_t arr_length) {
    // DANGER! BUG!
    // arr looks like an array, but it's actually just an int pointer here.
    // sizeof(arr) will return 8 (size of a pointer).
    // 8 / 4 = 2. You think the array only has 2 elements!
    size_t length = sizeof(arr_length) / sizeof(arr[0]); 
    return length;
}

int main(void) {
    int data[100];
    printf("%zu",process_array(data,sizeof(data)));
    return 0;
}