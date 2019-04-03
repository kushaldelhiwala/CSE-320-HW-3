#include <stdio.h>
#include "defs.h"

int main(void) {
	//char* msg = "Hello, world!\n";
    	//cse320_print(msg);
	
	int exit_flag = 0;
	char input_line[255];

	do{
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");

		if (strcmp(input_line, "help")==0){
			printf("Here are the functions of the various commands\n");
			printf("Date: Prints out the current date/time\n");
			printf("Hire: You can hire artists\n");
			printf("Fire: You can fire artists\n");
			printf("FireAll: You can fire all artists\n");
			printf("Assign: Assign a job to artists\n");
			printf("Withdraw: Withdraw a job to artists\n");
			printf("List: List all the artists PIDs\n");
			printf("Exit: Exit the program\n");
		}	
		else if(strcmp(input_line, "date")==0){
			if (pid == 0) {
	                        // Child process
                       		 if (execvp("date", "date") == -1) {
                               		 perror("lsh");
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
	
		}	
		else if(strcmp(input_line, "hire")==0){
			int num_of_processes = 0;
			sscanf(input_line, "*%s %d", num_of_processes);
			int i = 0;
			pid_t pid;
			
			while(i < num_of_processes){
				pid = fork();
				i++;
			}	
			
		}
		else if(strcmp(input_line, "fire")==0){
			int num_of_processes = 0;
			sscanf(input_line, "*%s %d", num_of_processes);
			
		}
		else if(strcmp(input_line, "fireall")==0){}
		else if(strcmp(input_line, "assign")==0){}
		else if(strcmp(input_line, "withdraw")==0){}
		else if(strcmp(input_line, "list")==0){}
		else if(strcmp(input_line, "exit")==0){
			exit_flag == 1;
		}
		else{
			printf("Please enter a valid command\n");
		}
	
	}while(exit_flag==0);


    return 0;
}
