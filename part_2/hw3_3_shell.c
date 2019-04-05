// Shell that runs child
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (int argc, char** argv)
{
	int exit_status = 0;
	char input_line[255];
	pid_t pid;
	pid_t wpid;
	int status;
	
	do{
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if (strcmp(input_line, "exit") == 0){
			exit_status = 1;
			exit(0);
		}

		else if (strcmp(input_line, "run") == 0){
			pid = fork();

			if (pid == 0){
				signal(SIGINT,SIG_IGN);
				char* args[] = {"./child", NULL};
				if (execvp(args[0], args) == -1){
					printf("Failed to execute null\n");
				}
				exit(EXIT_FAILURE);
			}
			
			else if (pid < 0){
				printf("Error forking.\n");
			}
			else{
				do {
                               		 wpid = waitpid(pid, &status, WUNTRACED);
                         	} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			}				

		}

		else{
			printf("Please enter a correct command\n");
		}

	} while(exit_status == 0);

}
