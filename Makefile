all: main.x

main.x:
	gcc src/main.c src/defs.c -I./inc

fib:
	gcc part_2/hw3_1.c -o fib

sshell:
	gcc part_2/hw3_2.c -o simple_shell

clean:
	rm a.out
