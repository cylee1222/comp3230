#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int data1;
void RecuresiveFunc1(int i)
{
    data1 = 1; 
    int data2 = 1;    
	int data3[2] = {1,1};
	int *data4 = malloc(1000*sizeof(int));
	data4[0]=data4[1]=1;
	static int data5 = 1;  
	
	printf("Addresses which fall into:\n");
	printf("1) data1 = %p.\n", &data1);
	printf("2) data2 = %p.\n", &data2);
	printf("3) data3 = %p.\n", &data3);	
	printf("4) data4 = %p.\n", &data4);
	printf("5) data4[0] = %p.\n", &data4[0]);	
	printf("6) data5 = %p.\n", &data5);
	
	printf("i is %d.\n\n", i);	
	if(i < 2){
		RecuresiveFunc1(++i);
	}
	else{
		while(1){
			printf("[while loop] Process ID: %d.\n", getpid());
			sleep(100);
		}
	}
	free(data4);
}

int main(int argc, char *argv[])
{
	int i = 0;
	RecuresiveFunc1(i);
	return 0;
}







