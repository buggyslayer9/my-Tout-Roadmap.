#include <stdio.h>

int main(int argc , char *argv[]){
    if(argc < 2){
        printf("Usage: ./echo_chamber <text to echo>\n");
    }else{
        printf("%s\n",argv[1]);
    }
    return 0;
}