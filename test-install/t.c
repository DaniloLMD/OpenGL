#include <stdio.h>

#define func(a, b) a++, b++;

int main(){

    int flag = 0;

    int x = 5;
    int y = 10;

    if(flag)
        func(x,y);
    


    printf("x = %d\n", x);
    printf("y = %d\n", y);

    return 0;
}