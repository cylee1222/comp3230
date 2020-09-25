#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void RecuresiveFunc2(int i){
	int temp = 100;
	printf("Addresses which fall into:\n");
	printf("1) temp = %p.\n", &temp);
	
	printf("i is %d.\n\n", i);
	if(i > 7){
		RecuresiveFunc2(--i);
	}
	else{
		while(1){
			printf("[while loop] Process ID: %d.\n", getpid());
			sleep(100);
		}
	}
}

int main(int argc, char *argv[])
{
	int i = 10;
	RecuresiveFunc2(i);
	return 0;
}




