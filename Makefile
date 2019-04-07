all: main.x

main.x:
	gcc src/main.c src/defs.c -I./inc -o artist_manager

sigblock:
	gcc part_2/hw3_3_shell.c -o shell
	gcc part_2/hw3_3_child.c -o child

fib:
	gcc part_2/hw3_1.c -o fib -lm

sshell:
	gcc part_2/hw3_2.c -o simple_shell

clean:
	rm fib simple_shell shell child artist_manager
