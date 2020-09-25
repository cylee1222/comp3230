#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>


int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	char *arg_vec[]={"./para_sum","5","6","7", NULL};

	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		sleep(2);
		execv("./para_sum", arg_vec);
		printf("I am the child process.\n");
	}
	else
	{
		printf("I am the parent process.\n");
	}

	printf("This is the END of program.\n\n");
	return 0;
}
