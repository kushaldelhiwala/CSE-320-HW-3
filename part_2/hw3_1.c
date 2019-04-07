//Read number from command line, find the last digit of that fibonacci number 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int calculate_fibonacci(int n);
void handler(int sig);

int fib_last = 0;
pid_t pid;
int print_fib = -1;

int main (int argc, char** argv)
{
  int input_num = 0;
  long long fibonacci_input = 0;
 
  if (argc != 2){
	printf("Enter arguments correctly\n");
	exit(-1);
  }
  char* arg_i = *(argv+1);
  input_num = atoi(arg_i);
  signal(SIGCHLD, handler);
  
  if ((pid = fork()) == 0){
    input_num = input_num % 60;
    fibonacci_input = calculate_fibonacci(input_num);
    fib_last = fibonacci_input % 10;
    exit(fib_last);
  }

  //int result;
  //wait(&result);
  while (print_fib == -1);
  printf("Print Fib: %d\n", print_fib);
  return 0;

}

void handler(int sig)
{
  int status; 
  waitpid(pid, &status, 0);
  if (WIFEXITED(status)){
    print_fib = WEXITSTATUS(status);
  }

}

int calculate_fibonacci(int n)
{
  double phi = (1 + sqrt(5)) / 2; 
  double phi_1 = (1 - sqrt(5)) / 2; 

  if (n>0){
    return round(pow(phi, n) / sqrt(5));
  }
  else{
    return round(pow(phi_1, n) / sqrt(5));
  }

}
