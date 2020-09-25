#include <unistd.h>
#include <stdio.h>


int main()
{
	printf("This is the beginning of the program!\n\n");

	for(int i=0;i<3;i++)
	{
		pid_t fpid;
		fpid=fork();
		if (fpid==0) 
			printf("I am %d. My parent is %d. \n", getpid(), getppid());
	}

	printf("This is the END of program.\n\n");
	return 0;
}
