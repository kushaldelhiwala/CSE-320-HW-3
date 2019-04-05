// Shell 
// Used some code from  https://brennan.io/2015/01/16/write-a-shell-in-c/ for the waiting part
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char** argv)
{
	// First read the line 
	// Parse the info from it 
	// Take some action 
	int exit_status = 0;
	char input_line [255];
	char command[255];
	char cmd[100];
	char *parameters[20];
	char* found;
	int i = 0;
	char *array[100];
	char *envp[] = {(char*)"PATH=/", 0};
	pid_t pid;
	pid_t wpid;
	int status;

	do{
		i = 0;
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if(strcmp(input_line, "exit") == 0){
			exit_status = 1;
			exit(0);
			printf("Exit\n");
		}

		found = strtok(input_line, " ");
		while (found){
			array[i++] = strdup(found);
			found = strtok(NULL," ");
		}
		array[i] = NULL;

		pid = fork();
  		
		if (pid == 0) {
    			// Child process
    			if (execvp(array[0], array) == -1) {
      				printf("Failed to execute %s\n", array[0]);
    			}
    			exit(EXIT_FAILURE);
  		}
		else if(pid < 0){
			printf("Error forking\n");
		}
		else{
			do {
      				wpid = waitpid(pid, &status, WUNTRACED);
     			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}

	} while (exit_status == 0);

	return 0;
}
