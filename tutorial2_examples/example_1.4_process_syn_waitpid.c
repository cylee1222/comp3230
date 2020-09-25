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
		sleep(5);
		printf("End of child process.\n");
	}
	else
	{		
		pid_wait=waitpid(fpid, &status, WNOHANG); // with para WNOHANG, process won't be blocked
		while(pid_wait==0)
		{
			pid_wait=waitpid(fpid, &status, WNOHANG); 
			if(pid_wait==0)
			{
				printf("There is no exited process.\n");
			}
			sleep(1);
		}
		
		printf("I am the parent process with ID %d. \n", getpid());	
		printf("The ID of exited process is %d.\n", pid_wait); 
	}

	printf("This is the END of program.\n\n");
	return 0;
}

