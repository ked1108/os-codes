#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define FRAGMENTS 5
int memoryblocks[FRAGMENTS];

int allocate(int size){
    int max = INT_MIN;
    for(int i = 0; i < FRAGMENTS; i++){
        if(memoryblocks[i] > max && memoryblocks[i] > size){
            max = memoryblocks[i];
        }
    }
    for(int i = 0; i < FRAGMENTS; i++){
        if(memoryblocks[i] == max){
            memoryblocks[i] -= size;
            return i;
        }
    }

    return -1;
}

int main(){

    for(int i = 0; i < FRAGMENTS; i++){
        scanf("%d", &memoryblocks[i]);
    }

    int flag, procsize;
    do {
        scanf("%d", &procsize);
        flag = allocate(procsize);
        if(flag != -1)
            printf("%d Block Allocated\n", flag+1);
        else
            printf("No Block Allocated, no more space left");
    } while (flag > 0); 

    return 0;
}
