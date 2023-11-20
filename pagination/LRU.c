#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 4

typedef struct Page{
    char pagename;
    int age;
    int refs;
} Page;

Page pageframe[FRAME_SIZE];
int count = 0;

void init(){
    for(int i = 0; i < FRAME_SIZE; i++){
        pageframe[i].age = 0;
        pageframe[i].pagename = 0;
        pageframe[i].refs = -1;
    }
}

void display(){
    for(int i = 0; i < FRAME_SIZE; i++){
        printf("%c\n", pageframe[i].pagename);
    }
}

void increment(){
    for(int i = 0; i < FRAME_SIZE; i++){
        pageframe[i].age++;
    }
}

int search(Page page){
    for(int i = 0; i < FRAME_SIZE; i++){
        if(page.pagename == pageframe[i].pagename)
            return i;
    }

    return -1;
}

int find_most_useless(){
    Page min = pageframe[0];
    int mdx = 0;
    for(int i = 1; i < FRAME_SIZE; i++){
        if(pageframe[i].refs < min.refs){
            min = pageframe[i];
            mdx = i;
        } else if(pageframe[i].refs == min.refs){
            if(pageframe[i].age > min.age){
                min = pageframe[i];
                mdx = i;
            }
        }
    }
    return mdx;
}

void lru_paging(Page page){
    increment();
    int pos = search(page);
    if(pos == -1){
        count++;
        int i = find_most_useless();
        pageframe[i] = page;
    } else{
        pageframe[pos].refs++;
    }
}

int main(){
    init();
    char c;
    for(int i = 0; i < 10; i++){
        c = getchar();
        getchar();
        Page temp = {c, 0, 0};
        lru_paging(temp);
    }

    printf("%d page faults\n" ,count);
    display();
    return 0;
}
