#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../inc/data.h"

void hire (pid_t transfer_pid){
	child_pid[pos] = transfer_pid;
	pos++;
}

void fire (int transfer_k){
	child_pid[transfer_k] = 0;
}

void assign(pid_t transfer_pid){
	assigned_processes[assigned_counter] = transfer_pid;
        assigned_counter++;
}

void withdraw(int transfer_k){
        assigned_processes[transfer_k] = 0;              
}
