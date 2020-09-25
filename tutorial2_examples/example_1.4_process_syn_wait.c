#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	
	pid_t pid_wait;
	int status;
	
	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		printf("I am the child process with ID %d. \n\n", getpid());
	}
	else
	{
		pid_wait=wait(&status);
		printf("The ID of exited process is %d.\n", pid_wait); 
		printf("I am the parent process with ID %d. \n", getpid());
	}

	printf("This is the END of program.\n\n");
	return 0;
}



