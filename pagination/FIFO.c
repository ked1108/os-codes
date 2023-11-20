#include <stdio.h>
#include <stdlib.h>

typedef struct Page{
    char pagename;
    int age;
} Page;

Page pageframe[4];
int count = 0;

void init(){
    for(int i = 0; i < 4; i++){
        pageframe[i].age = 0;
        pageframe[i].pagename = 0;
    }
}

void increment(){
    for(int i = 0; i < 4; i++){
        pageframe[i].age++;
    }
}

int search(Page page){
    for(int i = 0; i < 4; i++){
        if(page.pagename == pageframe[i].pagename)
            return i;
    }

    return -1;
}

int find_oldest(){
    Page max = pageframe[0];
    int mdx = 0;
    for(int i = 1; i < 4; i++){
        if(pageframe[i].age > max.age){
            max = pageframe[i];
            mdx = i;
        }
    }
    return mdx;
}

void fifo_paging(Page page){
    increment();
    int pos = search(page);
    if(pos == -1){
        count++;
        int i = find_oldest();
        pageframe[i] = page;
    }
}

int main(){
    init();
    char c;
    for(int i = 0; i < 10; i++){
        c = getchar();
        getchar();
        Page temp = {c, 0};
        fifo_paging(temp);
    }

    printf("%d page faults\n" ,count);
    for(int i = 0; i < 4; i++){
        printf("%c\n", pageframe[i].pagename);
    }
    return 0;
}
