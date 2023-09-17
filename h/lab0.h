#ifndef _lab0_h_
#define _lab0_h_

/* part 1 */
long zfunction();

/* part 2 */
void printprocstks(int);
						
/* part 3 */
// Function declarations used for tracing system calls

void syscallsummary_start(void);
void syscallsummary_stop(void);
void printsyscallsummary(void);

// Data Structure for process monitor which stores details about each system call

struct sysCallInfo
{
	char* sysCallName;   // Name of System Call
	int pid;            // Process ID which last called the system call
	int freq; 	    // The number of times the system call was called
	unsigned long execTime;  // The execution time of the system call
};


// We must monitor 27 system calls for each of the process separately

extern struct sysCallInfo sysList[][27];

// Track flag declared to indicate whether tracking is to be started

extern int trackFlag;

// Time Counter to get Current Time

extern unsigned long ctr1000;

#endif