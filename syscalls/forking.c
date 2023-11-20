#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sum(int a[], int n){
	int sum = 0;
	for(int i = 0;i < n;i++)
		sum+=a[i];
	printf("sum:%d\n",sum);
}

void mean(int a[], int n){
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum+=a[i];
	}
	float mean = sum/n;
	printf("mean:%f\n",mean);
}

void max(int a[], int n){
	int max = a[0];
	for(int i = 1; i < n; i++){
		if(max > a[i]) max = a[i];
	}
	printf("max:%d\n",max);
}

void (*p[3]) (int a[], int n);

int main(){

	
	int array[3];
	for(int i = 0; i < 3; i++){
		scanf("%d", &array[i]);
	}
		
	pid_t pid1, pid2, pid3;
	pid_t cpid1, cpid2, cpid3;
	int status;
	
	if((pid1 = fork()) == 0){
		sum(array, 3);
	}
	 else if((pid2 = fork()) == 0){
	 	mean(array, 3);
	 }
 	 else if((pid3 = fork()) == 0){
 	 	max(array, 3);
	}	 
	else {
 		if(cpid1 = wait(&status) == pid1){
 			printf("Child %d returned\n", pid1);
 		}
 		if(cpid2 = wait(&status) == pid2){
 			printf("Child %d returned\n", pid2);
 		}
 		if(cpid3 = wait(&status) == pid3){
 			printf("Child %d returned\n", pid3);
 		}
 	}
 	return 0;
}
