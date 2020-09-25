#include <unistd.h>
#include <stdio.h>


int main()
{
	printf("This is the beginning of the program!\n\n");
	
	pid_t fpid;   //fpid, return value of fork function
	int count=0;
	
	fpid = fork();
	if (fpid < 0)
		printf("Error in executing fork!");
	else if (fpid == 0)
	{
		printf("I am the child process.\n");
	}
	else
	{
		printf("I am the parent process.\n");
	}

	printf("This is the END of program with count value %d.\n\n",++count);
	return 0;
}
