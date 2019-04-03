// Shell 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	char *envp[] = {(char*)"PATH=/bin", 0};

	do{
		i = 0;
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if(strcmp(input_line, "exit") == 0){
			exit_status = 1;
		}

		found = strtok(input_line, " ");
		while (found){
			array[i++] = strdup(found);
			found = strtok(NULL," ");
		}
		strcpy(command, array[0]);

		if (i>1){
			for(int j = 0; j<i; j++)
				parameters[j] = array[j+1];
			parameters[i] = NULL;
		}
		
		else{
			parameters[0] = NULL;
		}

		if(fork() != 0){
			wait(NULL);
		}
		else {
			printf("Array[0]: %s\n", array[0]);
			printf("Command: %s\n", command);
			printf("Parameters[0]: %s\n", parameters[0]);
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
		}

	} while (exit_status == 0);

	return 0;
}