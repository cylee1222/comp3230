#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	int status;
	
	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		printf("I am the child process with ID %d. \n", getpid());
		printf("The ID of parent process is %d. \n", getppid());
	}
	else
	{
		wait(&status);
		printf("I am the parent process with ID %d. \n", getpid());
		printf("The ID of parent process is %d. \n", getppid());
	}

	printf("This is the END of program.\n\n");
	return 0;
}
