// Child Program 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main (int argc, char** argv)
{
	signal(SIGINT,SIG_DFL);

	sigset_t mask, prev_mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);	
	
	sigprocmask(SIG_BLOCK, &mask, &prev_mask);
	
	printf("1\n");
	sleep(1);
	printf("2\n");
	sleep(1);
	printf("3\n");
	sleep(1);
	printf("4\n");
	sleep(1);
	printf("5\n");
	
	sigprocmask(SIG_SETMASK, &prev_mask, NULL);

	printf("6\n");
	sleep(1);
	printf("7\n");
	sleep(1);	
	printf("8\n");
	sleep(1);
	printf("9\n");
	sleep(1);
	printf("10\n");
	
	exit(0);
	
}
