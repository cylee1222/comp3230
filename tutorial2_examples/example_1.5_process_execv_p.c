#include <unistd.h>
#include <stdio.h>


int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	char *argv_vec[]={"env", NULL};

	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		execvp("env", argv_vec);
		printf("I am the child process.\n");
	}
	else
	{
		printf("I am the parent process.\n");
	}

	printf("This is the END of program.\n\n");
	return 0;
}
