Ankit Kumar	akumar3@wpi.edu



The project contains the following files:
1) runCommand, runCommand.c
2) shell, shell.c
3) shell2, shell2.c
4) testcommand.txt, testprocesses
5) makefile


entering "make" will compile all the programs
==>make

1) runCommand is a simple program that executes a simple shell command only once
Eg: ==>./runCommand ls \home
will output whatever ls \home should output
Test case: ==>	ls

 backup	file.txt  makefile  runCommand	runCommand.c  runCommand.c~  runCommand.o  shell  shell2  shell2.c  shell2.c~  shell2.h  shell2.o  shell.c  shell.c~  shell.o  test  testcommand.txt  testing
----------------------------> CPU INFORMATION <-------------------------------------

Total elapsed wall-clock time taken by the program: 3 milliseconds 
Total user CPU time taken by the program: 0 milliseconds 
Total system CPU time taken by the program: 2 milliseconds 
Number of times the process was preempted involuntarily 7
Number of times the process gave up CPU voluntarily 1
Number of page faults 0
Number of page faults that could be satisfied by unreclaimed pages 340





2) shell is a shell version of runCommand, it can process multiple commands in one process
Eg: ==>./shell
    ==> ls /home
    (output) ankit
    ==> pwd
    /home/Ankit/Desktop/Project1

   My test case:
   a)

    pwd
    /home/ankit/Desktop/Project 1
    ----------------------------> CPU INFORMATION <-------------------------------------

    Total elapsed wall-clock time taken by the program: 1 milliseconds 
    Total user CPU time taken by the program: 0 milliseconds 
    Total system CPU time taken by the program: 1 milliseconds 
    Number of times the process was preempted involuntarily 1
    Number of times the process gave up CPU voluntarily 1
    Number of page faults 0
    Number of page faults that could be satisfied by unreclaimed pages 220

    ls
    backup	file.txt  makefile  runCommand	runCommand.c  runCommand.c~  runCommand.o  shell  shell2  shell2.c  shell2.c~  shell2.h  shell2.o  shell.c  shell.c~  shell.o  test  testcommand.txt  testing
    ----------------------------> CPU INFORMATION <-------------------------------------

    Total elapsed wall-clock time taken by the program: 3 milliseconds 
    Total user CPU time taken by the program: 0 milliseconds 
    Total system CPU time taken by the program: 2 milliseconds 
    Number of times the process was preempted involuntarily 7
    Number of times the process gave up CPU voluntarily 1
    Number of page faults 0
    Number of page faults that could be satisfied by unreclaimed pages 302

  b)
   	
 ./shell < testcommand.txt 
 /home/ankit/Desktop/Project 1
 ----------------------------> CPU INFORMATION <-------------------------------------

 Total elapsed wall-clock time taken by the program: 2 milliseconds 
 Total user CPU time taken by the program: 0 milliseconds 
 Total system CPU time taken by the program: 1 milliseconds 
 Number of times the process was preempted involuntarily 1
 Number of times the process gave up CPU voluntarily 1
 Number of page faults 0
 Number of page faults that could be satisfied by unreclaimed pages 219

 ankit
 ----------------------------> CPU INFORMATION <-------------------------------------

 Total elapsed wall-clock time taken by the program: 2 milliseconds 
 Total user CPU time taken by the program: 0 milliseconds 
 Total system CPU time taken by the program: 2 milliseconds 
 Number of times the process was preempted involuntarily 4
 Number of times the process gave up CPU voluntarily 1
 Number of page faults 0
 Number of page faults that could be satisfied by unreclaimed pages 297

 backup	file.txt  makefile  runCommand	runCommand.c  runCommand.c~  runCommand.o  shell  shell2  shell2.c  shell2.c~  shell2.h  shell2.o  shell.c  shell.c~  shell.o  test  testcommand.txt  testing
 ----------------------------> CPU INFORMATION <-------------------------------------

 Total elapsed wall-clock time taken by the program: 3 milliseconds 
 Total user CPU time taken by the program: 0 milliseconds 
 Total system CPU time taken by the program: 2 milliseconds 
 Number of times the process was preempted involuntarily 7
 Number of times the process gave up CPU voluntarily 1
 Number of page faults 0
 Number of page faults that could be satisfied by unreclaimed pages 303


 c)

 ankit@Jarvis:~/Desktop/Project 1$ ./shell
 cd test
 pwd
 /home/ankit/Desktop/Project 1/test
 ----------------------------> CPU INFORMATION <-------------------------------------

 Total elapsed wall-clock time taken by the program: 1 milliseconds 
 Total user CPU time taken by the program: 0 milliseconds 
 Total system CPU time taken by the program: 1 milliseconds 
 Number of times the process was preempted involuntarily 1
 Number of times the process gave up CPU voluntarily 1
 Number of page faults 0
 Number of page faults that could be satisfied by unreclaimed pages 220








3) The 3rd version is the closed version to a simple shell. It can run multiple processes at once including background and foreground process by '&'

./shell2 will execute the shell2



ankit@Jarvis:~/Desktop/Project 1$ ./shell2 
./testing 20 &
./testing 3 &
jobs
The current processes running are: 
2
Process id= 17059 ; Command= ./testing
Process id= 17061 ; Command= ./testing
Test: 3
Test: 20
ls
backup	file.txt  makefile  runCommand	runCommand.c  runCommand.c~  runCommand.o  shell  shell2  shell2.c  shell2.c~  shell2.h  shell2.o  shell.c  shell.c~  shell.o  test  testcommand.txt  testing
-----------------------------------------------------------------------
Finished process number 17079
----------------------------> CPU INFORMATION <-------------------------------------

Total elapsed wall-clock time taken by the program: 3 milliseconds 
Total user CPU time taken by the program: 0 milliseconds 
Total system CPU time taken by the program: 2 milliseconds 
Number of times the process was preempted involuntarily 1
Number of times the process gave up CPU voluntarily 1
Number of page faults 0
Number of page faults that could be satisfied by unreclaimed pages 298

-----------------------------------------------------------------------
The process number 17059 finished with command ./testing
----------------------------> CPU INFORMATION <-------------------------------------

Total elapsed wall-clock time taken by the program: 129658 milliseconds 
Total user CPU time taken by the program: 0 milliseconds 
Total system CPU time taken by the program: 1 milliseconds 
Number of times the process was preempted involuntarily 3
Number of times the process gave up CPU voluntarily 4
Number of page faults 0
Number of page faults that could be satisfied by unreclaimed pages 444

-----------------------------------------------------------------------
The process number 17061 finished with command ./testing
----------------------------> CPU INFORMATION <-------------------------------------

Total elapsed wall-clock time taken by the program: 123091 milliseconds 
Total user CPU time taken by the program: 0 milliseconds 
Total system CPU time taken by the program: 3 milliseconds 
Number of times the process was preempted involuntarily 3
Number of times the process gave up CPU voluntarily 4
Number of page faults 0
Number of page faults that could be satisfied by unreclaimed pages 444

pwd
/home/ankit/Desktop/Project 1
-----------------------------------------------------------------------
Finished process number 17080
----------------------------> CPU INFORMATION <-------------------------------------

Total elapsed wall-clock time taken by the program: 2 milliseconds 
Total user CPU time taken by the program: 0 milliseconds 
Total system CPU time taken by the program: 1 milliseconds 
Number of times the process was preempted involuntarily 1
Number of times the process gave up CPU voluntarily 1
Number of page faults 0
Number of page faults that could be satisfied by unreclaimed pages 217









