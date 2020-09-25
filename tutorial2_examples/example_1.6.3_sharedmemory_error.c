#include <stdio.h>
#include <sys/wait.h>  
#include <unistd.h>    
#include <string.h>  

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>  


int main() {
   int shmid;
   int *shmp, *shmc;
   
   int size_data = 1 * sizeof(int);
   printf ("Apply %d bytes.\n",size_data);
	
   // key_t key = ftok("example_1.6.3_sharedmemory.c",65);
   shmid = shmget(2020, size_data, 0666 | IPC_CREAT);   
   if(fork() == 0) {
      shmc = shmat(shmid, 0, 0);
	  
      *shmc =10;
	  printf ("Child wrote %d.\n",*shmc) ;
	  
      shmdt(shmc);
   }
   else {
      wait(NULL);
	  
      shmp = shmat(shmid, 0, 0);
	  
      printf ("Parent reads %d.\n",*shmp) ;
	  
      shmdt(shmp);
      shmctl(shmid, IPC_RMID, NULL);
   }
   return 0;
}





