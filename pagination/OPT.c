#include <stdio.h>

void printFrames(int frame[], int capacity) {
    printf("Frames: ");
    for (int i = 0; i < capacity; i++) {
        if (frame[i] == -1) {
            printf("- ");
        } else if(frame[i]>1000||frame[i]<-1000)
        {
        }
        else
         {
            printf("%d ", frame[i]);
        }
    }
    printf("\n");
}

int findOptimal(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int frame[capacity];
    int frameIndex = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int farthest = i;
            int replaceIndex = 0;

            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        break;
                    }
                }
                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = pages[i];
            pageFaults++;
        }

        printf("Page Reference: %d\n", pages[i]);
        printFrames(frame, capacity);
    }

    return pageFaults;
}

int main() {
    int n, capacity;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the capacity of memory: ");
    scanf("%d", &capacity);

    printf("\nOptimal Page Replacement Algorithm:\n");
    int optimalFaults = findOptimal(pages, n, capacity);

    printf("\nPage Faults:\n");
    printf("Optimal: %d\n", optimalFaults);

    return 0;
}
