#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
  
int main(int argc, char* argv[])
{
    printf("This is the BEGINNING of the program.\n\n");
    if(argc-1 != 3){
        printf("Error: The number of input integers now is %d. Please input 3 integers.\n",argc-1);
        return -1;
    }// Don't modify this Error Checking part
        
    {
        // Write your code in this brace
    int* differ;
    int size_data = 3 * sizeof(int);
    int shmid = shmget(IPC_PRIVATE, size_data, 0666 | IPC_CREAT);

    pid_t fpid = fork();
    
    if(fpid == 0){

      differ = shmat(shmid, 0, 0);
      printf("Receive a SIGCONT.\n");
      printf("Child process B ID: %d.\n", getpid());
      if(differ[2] > 0)
        printf("The 3rd argument is larger than the 1st argument.\n\n");
      else if(differ[2] == 0)
        printf("The 3rd argument is equal to the 1st argument.\n\n");
      else
        printf("The 3rd argument is smaller than the 1st argument.\n\n");
      shmdt(differ);
      exit(0);
      
    }else{

      pid_t fpid1 = fork();
      if(fpid1 < 0) exit(0);
      else if(fpid1 == 0){

        differ = shmat(shmid, 0, 0);
        differ[2] = differ[0] + differ[1];
        printf("Receive a SIGCONT.\n");
        printf("Child process A ID: %d.\n", getpid());
        printf("Sum of differences: %d.\n", differ[2]);
        printf("Send a SIGCONT to process %d.\n\n", fpid);
        shmdt(differ);
        kill(fpid, SIGCONT);
        exit(0);

      }else{
        kill(fpid, SIGSTOP);
        kill(fpid1, SIGSTOP);
        int count = 0;
        int v1 = atoi(argv[1]), v2 = atoi(argv[2]), v3 = atoi(argv[3]);
        differ = shmat(shmid, 0, 0);
        differ[0] = v2 - v1;
        differ[1] = v3 - v2;
        printf("Apply %d bytes.\n", size_data);
        printf("Parent process ID: %d.\n", getpid());
        printf("Differences: %d, %d.\n", differ[0], differ[1]);
        printf("Send a SIGCONT to process %d.\n\n", fpid1);

        kill(fpid1, SIGCONT);
        pid_t pid;
        
        pid = wait(NULL);
        printf("Exited Process ID: %d; Count: %d.\n", pid, ++count);

        pid = wait(NULL);
        printf("Exited Process ID: %d; Count: %d.", pid, ++count);

        shmdt(differ);
        shmctl(shmid, IPC_RMID, NULL);

      }

    }
        
    
    }
    printf("\nThis is the END of the program.\n");
    return 0;
}


// Plase use the following lines to print related information if needed.
/*
sleep(0.001);  // which you may need for registration of signal handlers in child process,
               //only allowd at the beginning of the parent process after fork();
printf ("Apply %d bytes.\n",***);
printf("Child process A ID: %d.\n", getpid());
printf("Child process B ID: %d.\n", getpid());
printf("Sum of differences: %d.\n\n", ***);
printf("Send a SIGCONT to Process %d.\n\n", ***);
printf("Parent process ID: %d.\n");
printf("Differences: %d, %d.\n", ***,***);
printf("Send a SIGCONT to process %d.\n\n", ***);
printf("Exited Process ID: %d.\n", **);
printf("Receive a SIGCONT.\n");
printf("Receive a SIGSTOP.\n");


printf("Exited Process ID: %d; Count: %d.\n", *, **);
printf("The 3rd argument is larger than the 1st argument.\n");
printf("The 3rd argument is smaller than the 1st argument.\n");
printf("The 3rd argument is equal to the 1st argument.\n");
*/
