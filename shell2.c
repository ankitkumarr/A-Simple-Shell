// Ankit Kumar		   akumar3@wpi.edu

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#define SIZE (90)
void executecommand(int argc, char** argv);  //executes the command for the process
char** getcommand(int argc, char **argv);  //finds the command from the input
void finishedprocess();		//searches for all the finished processes and completes them
long gettime();		//finds the time
void foregroundstuff(int pid);	//does what is required for the foreground process

long starttimef;
long stoptimef;

//structure to store the details of each process
typedef struct 
{
	int processid;
	int finished; //zero if running, 1 if still finished
	char** command;
	long starttime;
	long stoptime;
}processinfo;

//array of structures to store all the processes
processinfo backgroundChildren[SIZE];
int pos = 0; //position of the array

int main (int argc, char **argv) {

	int lc = 0; //making the finished to -1
	for(; lc < SIZE; lc++)
		backgroundChildren[lc].finished = -1;

	char *input = (char*)malloc(sizeof(char) * 528);
	char *word;
	while(1) {
		//taking the input
		fgets(input, 256, stdin);

		//Checking for the illlegal expression
		if(strlen(input)>128) {
			printf("The input contains more than 128 characters. Illlegal input!\n");
			continue;
		}

		if(*input=='\n'){
			continue;
		}
		//loop counter
		int i = 0;
		for(;i< strlen(input);i++) {
			//catching the return key input
			if(*(input+i)=='\n') {
				*(input+i) = '\0';
			}
		}

		//token to make the array of words
		const char token[1] = " ";
		word = strtok(input, token);

		argv = (char**)malloc(sizeof(char*) * 33);
		int count = 1;
		for(count = 1 ;word!= NULL;count++) {
			*(argv + count) = (char*)malloc(sizeof(char) * strlen(word));
			*(argv + count) = strdup(word);
			word = strtok(NULL, token); 
		}
		argc = count;
		if(count > 33) {
			printf("Number of arguments exceed the 32 argument limit. Illlegal expression!\n");
		}

		count--;  //This stores the string before the null to check for &
		//printf("the count is %i and the last argument is : %s\n", count, *(argv+count));
		int background = 0;  // 1 if process is background
		
		//if & is entered, identify it as a background process
		if(**(argv+count) == '&') {
			background = 1;
			*(argv + count) = NULL;
			argc--;
		}

		
		//when exit is encountered, check for the processes
		if((strncmp(*(argv+1),"exit",4) == 0)) {
			int i; int flag = 0;
			for(i = 0; i <= pos; i++) {
				if (backgroundChildren[i].finished==0) {
					printf("\n There are background processes running. Please wait until they are done\n");
					flag = 1; break;
				}
			}
			if(flag == 1) {
				continue;
			}

			exit(0);
		}

		//when cd is encountered, change the directory
		if ((strncmp(*(argv+1),"cd",2) == 0)) {
			printf("test = %s\n", *(argv+2));
			if((chdir (*(argv+2))) == -1) {
				printf("Invalid directory \n");}
			continue;
		}

		//when jobs is entered, diplay the jobs running
		if((strncmp(*(argv + 1), "jobs",4) == 0)) {
			printf("The current processes running are: \n%i\n", pos);
			int i;
			for(i = 0; i <= pos; i++) {

				if(backgroundChildren[i].finished==0) {
					char** temp = backgroundChildren[i].command;
					char* temp2 = *temp;
					printf("Process id= %d ; Command= %s\n",backgroundChildren[i].processid, temp2);
				}
			}
			continue;
		}
		
		
		int status = 0; int pid;


		//parent process
		if((pid=fork())!=0) {

			struct timeval start, stop;
			struct rusage usage;
			gettimeofday(&start, NULL);
			
			//If a background process is identified store it in the array, record the time and check if any process is finished
			if(background == 1) {
				backgroundChildren[pos].starttime = gettime();
				backgroundChildren[pos].processid = pid;
				backgroundChildren[pos].finished = 0;
				char **command = getcommand(argc, argv);
				backgroundChildren[pos].command = command;
				pos++;
				finishedprocess();

			}

			else 
				//if it's a foregroud process, wait for the process to get over and then proceed
				{
				starttimef = gettime();
				foregroundstuff(pid);
			}
		}

		//Child process
		else {
			//execute the command
			executecommand(argc, argv);
		}
	}
}

//To execute the command
void executecommand(int argc, char **argv) {
	char** command = getcommand(argc, argv);

	if (execvp(*command, command) < 0) {
		//if the command is incorrect, exit the process with error code
		printf("Error: Unknown or bad command\n");
		exit(1);
	}
}

//Function to get the command for the execute function
char** getcommand(int argc, char **argv) {
	char **command = (char**)malloc(argc * sizeof(char*));
	int i =1; //loop counter
	for(i = 1; i < argc; i++) {

		*(command+(i-1)) = strdup(*(argv+i)); 

	}
	*(command+i-1) = NULL;
	return command;
}

//Check if a process is finished, complete it by printing the statistics
void finishedprocess() {
	struct rusage usagedata;
	int pid = wait3(NULL, WNOHANG, &usagedata);
	while(pid!=0 && pid!=-1) {
		int i = 0;
		for(i = 0; i <= pos; i++) {
			if(backgroundChildren[i].processid == pid) {
				backgroundChildren[i].finished = 1;
				backgroundChildren[i].stoptime = gettime();
				printf("-----------------------------------------------------------------------\n");
				char** temp = backgroundChildren[i].command;
				char* temp2 = *temp;
				printf("The process number %i finished with command %s\n",backgroundChildren[i].processid, temp2);
				unsigned int millieucpu = (usagedata.ru_utime.tv_usec/1000) + (usagedata.ru_utime.tv_sec*1000);
				unsigned int milliescpu = (usagedata.ru_stime.tv_usec/1000) + (usagedata.ru_stime.tv_sec*1000);
				printf("----------------------------> CPU INFORMATION <-------------------------------------");
				printf("\n\nTotal elapsed wall-clock time taken by the program: %ld milliseconds \n", (backgroundChildren[i].stoptime - backgroundChildren[i].starttime));
				printf("Total user CPU time taken by the program: %1u milliseconds \n", millieucpu);
				printf("Total system CPU time taken by the program: %1u milliseconds \n", milliescpu);
				printf("Number of times the process was preempted involuntarily %ld\n", usagedata.ru_nivcsw);
				printf("Number of times the process gave up CPU voluntarily %ld\n", usagedata.ru_nvcsw);
				printf("Number of page faults %ld\n", usagedata.ru_majflt);
				printf("Number of page faults that could be satisfied by unreclaimed pages %ld\n\n", usagedata.ru_minflt);
			}
		}

		pid = wait3(NULL, WNOHANG, &usagedata); //wait for another process to exit
	}
}


//do this when a foreground process is identified
void foregroundstuff(int pid) {
	struct rusage usagedata;
	wait4(pid, NULL, 0, &usagedata);
	stoptimef = gettime();
	printf("-----------------------------------------------------------------------\n");
	printf("Finished process number %i\n", pid);
	unsigned int millieucpu = (usagedata.ru_utime.tv_usec/1000) + (usagedata.ru_utime.tv_sec*1000);
	unsigned int milliescpu = (usagedata.ru_stime.tv_usec/1000) + (usagedata.ru_stime.tv_sec*1000);
	printf("----------------------------> CPU INFORMATION <-------------------------------------");
	printf("\n\nTotal elapsed wall-clock time taken by the program: %ld milliseconds \n", (stoptimef - starttimef));
	printf("Total user CPU time taken by the program: %1u milliseconds \n", millieucpu);
	printf("Total system CPU time taken by the program: %1u milliseconds \n", milliescpu);
	printf("Number of times the process was preempted involuntarily %ld\n", usagedata.ru_nivcsw);
	printf("Number of times the process gave up CPU voluntarily %ld\n", usagedata.ru_nvcsw);
	printf("Number of page faults %ld\n", usagedata.ru_majflt);
	printf("Number of page faults that could be satisfied by unreclaimed pages %ld\n\n", usagedata.ru_minflt);
	finishedprocess();
}

//get the time in millieseconds
long gettime() {
	long time;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec*1000) + (tv.tv_usec/1000));
	return time;
}



