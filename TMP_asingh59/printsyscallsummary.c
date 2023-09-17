#include <stdio.h>
#include <lab0.h>
#include <conf.h>

// NPROC is the number of allowed processes in pentry table proctab in proc.h
struct sysCallInfo sysList[NPROC][27];

// Declaring track_flag.
int trackFlag = 0;

// Start tracing the system calls till syscallsummary_stop
void syscallsummary_start()
{
	// Start tracing the calls
	trackFlag = 1; 

	// Initialize the parameters for every system call in the process
	int i,j;
	for(i=0; i<NPROC; i++)
	{
		for(j=0; j<27; j++)
		{
			sysList[i][j].freq = 0;
			sysList[i][j].execTime = 0;
		}
	}
}

// Stop tracing the calls by inverting track_flag
void syscallsummary_stop()
{
	trackFlag = 0;
}

// Print all the details captured in proclist
void printsyscallsummary()
{
	int i, j;
	long int averageExecTime;
	int processFlag;

	printf("\n\nvoid printsyscallsummary()");

	for(i=0; i<NPROC; i++)
	{	
		processFlag = 1;

		for(j=0; j<27; j++)
		{	
			// Displaying details for called system calls only
			if(sysList[i][j].freq > 0)
			{	
				if(processFlag==1)
				{
					printf("\nProcess [pid: %d]", sysList[i][j].pid);
					processFlag=0;
				}
				averageExecTime = sysList[i][j].execTime / sysList[i][j].freq;
				 
				printf("\n\tSyscall: sys_%s, count: %d, average execution time: %lu (ms)", sysList[i][j].sysCallName, sysList[i][j].freq, averageExecTime);		
			}
		}
	}
}