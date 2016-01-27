all: runCommand shell shell2

runCommand: runCommand.o
	gcc -g runCommand.o -o runCommand

runCommand.o: runCommand.c
	gcc -g -c runCommand.c

shell: shell.o
	gcc -g shell.o -o shell

shell.o: shell.c
	gcc -g -c shell.c

shell2: shell2.o
	gcc -g shell2.o -o shell2

shell2.o: shell2.c
	gcc -g -c shell2.c

clean:
	rm -f runCommand.o runCommand shell.o shell shell2.o shell2

