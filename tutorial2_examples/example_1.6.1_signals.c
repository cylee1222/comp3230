#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
void sighup(int sig);  // function declaration 
void sigint(int sig); 
void sigquit(int sig); 
  
int main() 
{ 
	int pid; 
	if ((pid = fork()) < 0) { 
		exit(1); 
	} 
  
	if (pid == 0) { /* child */
		signal(SIGHUP, sighup); 
		signal(SIGINT, sigint); 
		signal(SIGQUIT, sigquit); 
		while(1);
	} 
	else { /* parent */
		printf("\nPARENT: sending SIGHUP\n"); 
		kill(pid, SIGHUP); 
  
		sleep(3); /* pause for 3 secs */
		printf("\nPARENT: sending SIGINT\n"); 
		kill(pid, SIGINT); 
  
		sleep(3); /* pause for 3 secs */
		printf("\nPARENT: sending SIGQUIT\n"); 
		kill(pid, SIGQUIT); 
		sleep(3); 
	}
	
	printf("\nThis is the END of program.\n\n");
	return 0;
} 
  
// sighup() function definition 
void sighup(int sig){ 
	printf("CHILD: I have received a SIGHUP\n"); 
	signal(SIGHUP, SIG_DFL); /* reset signal */
} 
  
// sigint() function definition 
void sigint(int sig){ 
	printf("CHILD: I have received a SIGINT\n"); 
	signal(SIGINT, SIG_DFL); /* reset signal */
} 
  
// sigquit() function definition 
void sigquit(int sig){ 
	printf("My DADDY has Killed me!!!\n"); 
	exit(0); 
}







