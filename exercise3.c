#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void swap(int* a, int* b){
  int c = *a;
  *a = *b;
  *b = c;
}

void sort(int* a, int* b, int* c){
  if (*a > *c) swap(a, c);
  if (*a > *b) swap(a, b);
  if (*b > *c) swap(b, c);
}

int main(int argc,char* argv[]){
	if(argc-1 != 3){
		printf("Error: The number of input integers now is %d. Please input 3 integers", argc-1);
	}

  int size_data = 2 * sizeof(int);
  int shmid = shmget(IPC_PRIVATE, size_data, 0666 | IPC_CREAT);
  int* shmc;
  int* shmp;
  int a, b, c;

  pid_t fpid21 = fork();
  if(fpid21 < 0) exit(0);
  else if(fpid21 == 0){
    a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]);
    sort(&a, &b, &c);
    shmc = shmat(shmid, 0, 0);
    *shmc = a;
    *(shmc + 1) = b;
    printf("Child process ID: %d; Sorting results: %d, %d, %d.\n\n", getpid(), a, b, c);
  }else{
    wait(NULL);
    shmp = shmat(shmid, 0, 0);
    char arg1[10];
    char arg2[10];
    sprintf(arg1, "%d", *shmp);
    sprintf(arg2, "%d", *(shmp+1));
    char* arg_v[] = {"./para_sum", arg1, arg2, NULL};
    printf("Parent process ID: %d; Calculate the sum of the two smallest arguments: %d, %d.\n", getpid(), *shmp, *(shmp+1));
    execv("./para_sum", arg_v);

    shmdt(shmp);
    shmctl(shmid, IPC_RMID, NULL);
  }

  return 0;
}

