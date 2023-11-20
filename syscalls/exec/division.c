#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("%d / %d = %0.2f", a, b, (float)a/b);
    return 0;
}
