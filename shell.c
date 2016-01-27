// Ankit Kumar		   akumar3@wpi.edu

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

//function to execute the command
void executecommand(int argc, char** argv);
int main (int argc, char **argv) {

	//user input
	char *input = (char*)malloc(sizeof(char) * 128);
	char *word;
	while(1) {
		fgets(input, 1024, stdin); //taking the user input

		//Checking for the illlegal expression
		if(strlen(input)>128) {
			printf("The input contains more than 128 characters. Illlegal input!\n");
			continue;
		}


		int i = 0;

		//Making sure enter key doesn't terminate the program
		for(;i< strlen(input);i++) {
			if(*(input+i)=='\n') {
				*(input+i) = '\0';
			}
		}
		

		const char token[1] = " ";
		word = strtok(input, token); //get the first token
		argv = (char**)malloc(sizeof(char*) * 32);
		int count = 1;
		for(count = 1 ;word!= NULL;count++) {
			*(argv + count) = strdup(word);
			word = strtok(NULL, token); 
		}
		argc = count;
		if(count > 33) {
			printf("Number of arguments exceed the 32 argument limit. Illlegal expression!\n");
		}

		//checking if the input is end of file.
		if(feof(stdin)) {
			exit(0);
		}
		if((strncmp(*(argv+1),"exit",4) == 0)) {
			exit(0);
		}
		if ((strncmp(*(argv+1),"cd",2) == 0)) {
			printf("test = %s\n", *(argv+2));
			if((chdir (*(argv+2))) == -1)
				printf("Invalid directory \n");
			continue;
		}
		int status = 0;
		//parent process
		if(fork()!=0) {

			struct timeval start, stop;
			struct rusage usage;
			struct rusage nusage;
			gettimeofday(&start, NULL);

			getrusage(RUSAGE_CHILDREN, &usage);
			//waiting for the child process to complete
			wait(&status);
			//after child process is finished

			//if child process failed, exit the program
			if(status!=0) { exit(1);}

			gettimeofday(&stop, NULL);
			getrusage(RUSAGE_CHILDREN, &nusage);

			//calculating the wall-clock time elapsed taken in milliseconds
			unsigned int millielapsedtook = ((stop.tv_usec/1000) - (start.tv_usec/1000)) + ((stop.tv_sec*1000) - (start.tv_sec*1000));

			//calculating the user CPU time taken by the program
			unsigned int millieucpu = ((nusage.ru_utime.tv_usec/1000) + (nusage.ru_utime.tv_sec*1000)) - ( (usage.ru_utime.tv_usec/1000) + (usage.ru_utime.tv_sec*1000));

			//calculating the system CPU time taken by the program
			unsigned int milliescpu = ((nusage.ru_stime.tv_usec/1000) + (nusage.ru_stime.tv_sec*1000)) - ( (usage.ru_stime.tv_usec/1000) + (usage.ru_stime.tv_sec*1000));
			//unsigned int milliescpu = (usage.ru_stime.tv_usec/1000) + (usage.ru_stime.tv_sec*1000); 
			
			  printf("----------------------------> CPU INFORMATION <-------------------------------------");
			  printf("\n\nTotal elapsed wall-clock time taken by the program: %1u milliseconds \n", millielapsedtook);

			  printf("Total user CPU time taken by the program: %1u milliseconds \n", millieucpu);
			  printf("Total system CPU time taken by the program: %1u milliseconds \n", milliescpu);
			  printf("Number of times the process was preempted involuntarily %ld\n", nusage.ru_nivcsw - usage.ru_nivcsw);
			  printf("Number of times the process gave up CPU voluntarily %ld\n", nusage.ru_nvcsw - usage.ru_nvcsw);
			  printf("Number of page faults %ld\n", nusage.ru_majflt - usage.ru_majflt);
			  printf("Number of page faults that could be satisfied by unreclaimed pages %ld\n\n", nusage.ru_minflt - usage.ru_minflt);
			
		}
			//child process; execute the command	

		else {
				
			executecommand(argc, argv);
		}
	}
	}
//executecommand to execute the passed command
	void executecommand(int argc, char **argv) {

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
		if (execvp(*command, command) < 0) {
			//if the command is incorrect, exit the process with error code
			printf("Error: Unknown or bad command\n");
			exit(1);
		}
	}

