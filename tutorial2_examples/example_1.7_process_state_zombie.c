#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	
	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		printf("I am the child process with ID %d.\n",getpid());
		printf("Exit now.\n\n");
	}
	else
	{
		//wait(NULL);
		printf("I am the parent process with ID %d.\n",getpid());
		printf("I will sleep 100 seconds.\n\n");
		sleep(100);
			
	}

	printf("This is the END of program.\n\n");
	return 0;
}
