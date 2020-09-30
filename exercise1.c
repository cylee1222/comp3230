#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
  printf("This is the beginning of the program!\n\n");
	
  pid_t fpid21 = fork();
  if(fpid21 < 0) exit(0);
  else if(fpid21 == 0){
    pid_t fpid32 = fork();
    if(fpid32 < 0) exit(0);
    else if(fpid32 == 0)
      printf("The exited child process ID now is %d, whose parent process ID is %d.\n", getpid(), getppid());
    else{
      wait(NULL);
      printf("The exited child process ID now is %d, whose parent process ID is %d.\n", getpid(), getppid());
    }
  }else{
    wait(NULL);
    pid_t fpid41 = fork();
    if(fpid41 < 0) exit(0);
    else if(fpid41 == 0)
      printf("The exited child process ID now is %d, whose parent process ID is %d.\n", getpid(), getppid());
    else{
      wait(NULL);
      printf("The final exited process ID now is %d.\n\n", getpid());
      printf("This is the END of program!\n");
    }
  }

  return 0;
}

