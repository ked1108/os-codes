#include <stdio.h>
#include <stdlib.h>

int allocated[5][4], max[5][4], need[5][4], running[5], avail[4], new_avail[4];

void need_calc(){
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int checkSafe(int proc[]){
    for (int i =0; i < 4; i++) {
        if(proc[i] > avail[i]){
            return 0;
        }
    }
    return 1;
}

int stillRunning(){
    for (int i =0; i < 4; i++) {
        if(running[i] == 0){
            return 1;
        }
    }
    return 0;
}

void bankers(){
    for (int i =0; i < 5; i++) {
        running[i] = 0;
    }

    while(stillRunning()){
        for (int i = 0; i < 5; i++) {
            if(running[i] == 0 && checkSafe(need[i])){
                running[i] = 1;
                for (int j = 0; j < 4; j++) {
                    avail[j] += allocated[i][j];
                }
                printf("Process P%d Finished\n", i);
                printf("New Avail:\n");
                for (int j = 0; j < 4; j++) {
                    printf("%d ", avail[j]);
                }
                printf("\n");
            }
        }
        int flag = 0;
        for(int i = 0; i < 5; i++){
            if(running[i] == 1){
                flag = 1;
            }
        }
        if(flag == 0){
            printf("No Safe Sequence Possible!");
            break;
        }
    }
}

int main(){
     for (int i = 0; i < 5; i++) {
         printf("Enter Allocated Resources for Process P%d:\n", i);
         for (int j = 0; j < 4; j++) {
             scanf("%d", &allocated[i][j]);
         }
     }
    
     for (int i = 0; i < 5; i++) {
         printf("Enter Maximum Resources for Process P%d:\n", i);
         for (int j = 0; j < 4; j++) {
             scanf("%d", &max[i][j]);
         }
     }
     printf("Enter Available Resources:\n");
     for (int j = 0; j < 4; j++) {
         scanf("%d", &avail[j]);
         new_avail[j] = avail[j];
     }

    need_calc();
    bankers();

    // ADDRESSING REQUESTS
    
    int req[4];
    printf("Enter Resource Request:\n");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &req[i]);
        new_avail[i] -= req[i];
        need[1][i] -= req[i];
        allocated[1][i] += req[i];
        if(new_avail[i] < 0){
            printf("Invalid Request!");
            return 0;
        }
        avail[i] = new_avail[i];
    }

    bankers();

    return 0;
}
