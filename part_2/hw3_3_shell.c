// Shell that runs child
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char** argv)
{
	int exit_status = 0;
	char input_line[255];
	
	do{
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if (strcmp(input_line, "exit") == 0){
			exit_status = 1;
		}

		else if (strcmp(input_line, "run") == 0){
			

		}

		else{
			printf("Please enter a correct command\n");
		}

	} while(exit_status==0)











}