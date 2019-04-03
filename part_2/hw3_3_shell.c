// Shell that runs child
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zconf.h>
#include <signal.h>

int main (int argc, char** argv)
{
	int exit_status = 0;
	char input_line[255];
	pid_t pid;
	
	do{
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if (strcmp(input_line, "exit") == 0){
			exit_status = 1;
			exit(0);
		}

		else if (strcmp(input_line, "run") == 0){
			if ((pid = fork()) == 0){
				char* args[] = {./hw_2/hw3_3_child, NULL};
				execve("./hw_2/hw3_3_child",args);
			}
			else{
				signal(SIGINT,SIG_IGN);
				wait(NULL);
			}				

		}

		else{
			printf("Please enter a correct command\n");
		}

	} while(exit_status == 0)

}
