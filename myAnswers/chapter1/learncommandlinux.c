#include <stdio.h>
#include <string.h>
int main(int argc,char *argv[])
{
    if(argc < 2){
        printf("No Argument Here\n");
    }else if(strcmp(argv[1],"--gui") ==0){
        printf("The Gui App Is Opened \n");
    }
    return 0;
}