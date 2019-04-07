#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t assign_id = -1;
pid_t withdraw_id = -1;
void handler1(int sig);
void handler2(int sig);
void cse320_print(char* message);

int main(void) {
	//char* msg = "Hello, world!\n";
    	//cse320_print(msg);
	
	int exit_flag = 0;
	char input_line[255];
	pid_t child_pid[500];
	pid_t assigned_processes[500];
	int assigned_counter = 0;
	int pos = 0;
	char* found;
	char* array[100];
	char command[255];
	char input_find[255];
	//pid_t assign_id = -1;

	do{
		printf("shell> ");
		fgets(input_line, 255, stdin);
		strtok(input_line, "\n");
		
		strcpy(input_find, input_line);	
		found = strtok(input_find, " ");
		array[0] = strdup(found);
		array[1] = NULL;
		printf("Array[0]: %s\n", array[0]);

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
		else if(strcmp(array[0], "date")==0){
			pid_t pid;
			pid_t wpid;
			int status;
			char* args[50];
			const char* s1 = "/bin/date";
			args[0] = strdup(s1);
			args[1] = NULL;
			
			pid = fork();
			
			if (pid == 0) {
                       		 if (execvp(args[0], args) == -1) {
                               		 printf("Failed to execute date\n");
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
		else if(strcmp(array[0], "hire")==0){
			int num_of_processes = 0;
			//printf("Input Line: %s\n", input_line);
			sscanf(input_line, "%*s %d", &num_of_processes);
			//printf("Num of Processes: %d\n", num_of_processes);
			int i = 0;
			pid_t pid;
			
			for (int i = 0; i < num_of_processes; i++){
				pid = fork();
				if (pid < 0){printf("Error in forking\n");}
				else if (pid == 0){
					signal(SIGUSR1, handler1);
					signal(SIGUSR2, handler2);
					while(1);
				}
				else{
					child_pid[pos] = pid;
					printf("Child Pos[i]: %d\n", pid);
					pos++;
				}
			}	
			
		}
		else if(strcmp(array[0], "fire")==0){
			pid_t terminate_pid = 0;
			sscanf(input_line, "%*s %d", &terminate_pid);
			printf("Terminate PID: %d\n", terminate_pid);
			int k = 0;
			int match_found = 0;
			int has_assignment = 0;
			
			for (k = 0; k < pos; k++){
				if (child_pid[k] == terminate_pid){
					match_found = 1;
					child_pid[k] = 0;
				}
			}
		
			for (int p = 0; p < assigned_counter; p++){
				if (assigned_processes[p] == terminate_pid){
					has_assignment = 1;
				}
			}
			
			if (has_assignment == 1){
				kill(terminate_pid, SIGUSR2);
				sleep(1);
			}
		
			if (match_found == 1){
				kill(terminate_pid, SIGTERM);	
				wait(NULL);
			}
			
			else{
				printf("Match not found for ID\n");
			}
			
		}
		else if(strcmp(array[0], "fireall")==0){
			int has_assignment = 0;
			for (int k = 0; k < pos; k++){
				if(child_pid[k] > 0){
					for (int j = 0; j < assigned_counter; j++){
						if (child_pid[k] == assigned_processes[j]){
							kill(child_pid[k], SIGUSR2);
							sleep(1);
						}	
					
					}	
					kill(child_pid[k], SIGTERM);
					child_pid[k] = 0;
					wait(NULL);
				}
				
			}
		}
		else if(strcmp(array[0], "assign")==0){
			sscanf(input_line, "%*s %d", &assign_id);
			//printf("Assign PID: %d\n", assign_id);
			int match_found = 0;
			int already_assigned = 0;

			for (int k = 0; k < pos; k++){
				if (child_pid[k] == assign_id){
					match_found = 1;
				}
			}
		
			for (int k = 0; k < assigned_counter; k++){
				if (assigned_processes[k] == assign_id){
					already_assigned = 1;
				}
			}			
			if (match_found == 1 && already_assigned == 0){
				assigned_processes[assigned_counter] = assign_id;
				assigned_counter++;

				kill(assign_id, SIGUSR1);
				sleep(1);
				//printf("ARIST %d IS ASSIGNED TO A JOB\n", assign_id);
			}
		
			else if (match_found == 1 && already_assigned == 1){
				printf("Artist has already been assigned job\n");
			}
			
			else{
				printf("Artist ID not found\n");
			}
		
		}	
		else if(strcmp(array[0], "withdraw")==0){
			sscanf(input_line, "%*s %d", &withdraw_id);
			printf("Withdraw PID: %d\n", withdraw_id);
			int match_found = 0;
			int never_assigned = 0;
	
			for (int k = 0; k < pos; k++){
				if (child_pid[k] == withdraw_id){
					match_found = 1;
				}
			}
			
			for (int k = 0; k < assigned_counter; k++){
				if (assigned_processes[k] == withdraw_id){
					never_assigned = 1;
					assigned_processes[k] = 0;
				}
			}
			
			if(match_found == 1 && never_assigned == 1){
				kill(withdraw_id, SIGUSR2);
				sleep(1);
				//printf("ARTIST %d IS WITHDRAWN FROM JOB\n", withdraw_id);
			}
			
			else{
				printf("Match not found for ID, or Artist has never been assigned a job\n");
			}
		}
		else if(strcmp(array[0], "list")==0){
			int has_assignment = 0;

			for (int i = 0; i < pos; i++){
				has_assignment = 0;
				if (child_pid[i] > 0){
					printf("%d\t", child_pid[i]);
				}
				if (child_pid[i] >0){
					for (int j = 0; j < assigned_counter; j++){
						if (assigned_processes[j] == child_pid[i]){
							has_assignment = 1;
						}
					}
				
					if (has_assignment == 0){
						printf("WAITING\n");
					}	
				
					else{
						printf("ASSIGNED\n");
					}
				}
			}
		}
		else if(strcmp(array[0], "exit")==0){
			exit_flag = 1;
		}
		else{
			printf("Please enter a valid command\n");
		}
	
	} while(exit_flag==0);


    return 0;
}

void handler1(int sig){
	char buffer1[255];
	sprintf(buffer1, "ARIST %d IS ASSIGNED TO A JOB\n", getpid());
	cse320_print(buffer1);

}

void handler2(int sig){
	char buffer2[255];
	sprintf(buffer2, "ARTIST %d IS WITHDRAWN FROM A JOB\n", getpid());
	cse320_print(buffer2);
}
