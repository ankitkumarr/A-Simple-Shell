// Ankit Kumar		   akumar3@wpi.edu

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char **argv) {

	int status = 0;
	//status for the child process
	
	//parent process
	if(fork()!=0) {

		struct timeval start, stop;
		struct rusage usage;
		gettimeofday(&start, NULL);
		
		//waiting for the child process to complete
		wait(&status);
		//after child process is finished

		//if child process failed, exit the program
		if(status!=0) { exit(1);}

		gettimeofday(&stop, NULL);
		getrusage(RUSAGE_CHILDREN, &usage);
		
		//calculating the wall-clock time elapsed taken in milliseconds
		unsigned int millielapsedtook = ((stop.tv_usec/1000) - (start.tv_usec/1000)) + ((stop.tv_sec*1000) - (start.tv_sec*1000));

		//calculating the user CPU time taken by the program
		unsigned int millieucpu = (usage.ru_utime.tv_usec/1000) + (usage.ru_utime.tv_sec*1000);

		//calculating the system CPU time taken by the program
		unsigned int milliescpu = (usage.ru_stime.tv_usec/1000) + (usage.ru_stime.tv_sec*1000); 
		
		printf("----------------------------> CPU INFORMATION <-------------------------------------");
		printf("\n\nTotal elapsed wall-clock time taken by the program: %1u milliseconds \n", millielapsedtook);
	
		printf("Total user CPU time taken by the program: %1u milliseconds \n", millieucpu);
		printf("Total system CPU time taken by the program: %1u milliseconds \n", milliescpu);
		printf("Number of times the process was preempted involuntarily %ld\n", usage.ru_nivcsw);
		printf("Number of times the process gave up CPU voluntarily %ld\n", usage.ru_nvcsw);
		printf("Number of page faults %ld\n", usage.ru_majflt);
		printf("Number of page faults that could be satisfied by unreclaimed pages %ld\n\n", usage.ru_minflt);
		
	}	

	else {
		//array of strings to store the command with the parameters
		char **command = (char**)malloc(argc * sizeof(char*));
		int i =1; //loop counter
		for(i = 1; i < argc; i++) {
			
			//allocating each string by mallocing	
			*(command+(i-1)) = (char*)malloc(sizeof(*(argv+i)));

			//copying the arguments to the command variable
			strcpy(*(command+(i-1)), *(argv+i));
		}
			//mallocing for NULL string in the array and storing the NULL
			*(command+(i-1)) = (char*)malloc(sizeof(*(argv+i)));
			*(command+i-1) = NULL;

			printf("the command is %s\n", *command);
			printf("the command is %s\n", *(command+1));
			printf("the command is %s\n", *(command+2));
			
			if (execvp(*command, command) < 0) {
				//if the command is incorrect, exit the process with error code
				printf("Error: Unknown or bad command\n");
				exit(1);
			}
	}
}



