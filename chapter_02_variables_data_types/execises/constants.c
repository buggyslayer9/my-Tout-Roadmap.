#include <stdio.h>
#define PI 3.14

int main(void){
    const char *SERVERNAME = "ngix";
    enum{
        Banana = 0,
        Apple =1,
        Babies = 20
    };
    printf("%.2f\n",PI);
    printf("%s",SERVERNAME);
    printf("%d",Banana);
}