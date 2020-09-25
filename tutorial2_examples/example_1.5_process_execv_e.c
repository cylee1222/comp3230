#include <unistd.h>
#include <stdio.h>


int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	char *envp[]={"PATH=/tmp/path", NULL};
	char *arg_vec[]={"env", NULL};

	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		execve("/usr/bin/env", arg_vec, envp);
		printf("I am the child process.\n");
	}
	else
	{
		printf("I am the parent process.\n");
	}

	printf("This is the END of grogram.\n\n");
	return 0;
}
