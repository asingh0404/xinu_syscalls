#include <proc.h>

static unsigned long *esp; 
//a static pointer variable esp which will be used to store the stack pointer value.

void printprocstks(int priority)
{
	printf("\nvoid printprocstks(int priority)");

	int i;

	for(i = 0; i < NPROC; i++) 
	// The constant NPROC specifies the number of processes and the process identifiers range from 0 through NPROC - 1 
	
	{
		// Checking the priority for every process entry (pentry) in proctab array.	
        // For each process entry in proctab, the function checks if the process priority (proctab[i].pprio) is greater than the specified priority.
		
		if(proctab[i].pprio > priority)
		
		{
            printf("\nProcess [%s]", proctab[i].pname);        		// Process name
            printf("\n\tpid: %d", getpid());                     	// Process ID
			printf("\n\tpriority: %d", proctab[i].pprio);       	// Process priority
			printf("\n\tbase: 0x%08x", proctab[i].pbase);         	// Base address of the stack
			printf("\n\tlimit: 0x%08x", proctab[i].plimit);         // Stack limit
            printf("\n\tlen: %d", proctab[i].pstklen);         		// Size of the stack
		
			/* 
            If the process is currently running (proctab[i].pstate == PRCURR):
            it uses inline assembly to get the current stack pointer value and stores it in the esp variable.
            Since processes that are currently running will always have updated esp, 
            we must always display the updated esp for those processes instead of saved stack pointer pesp.
			*/

			if(proctab[i].pstate == PRCURR)
			
			{
				asm("movl %esp, esp");
				printf("\n\tpointer: 0x%08x", esp);
			}

			else
			
			{
				printf("\n\tpointer: 0x%08x", proctab[i].pesp);

                // Finally, it prints the stack pointer value 
                // (esp if the process is currently running, or proctab[i].pesp if it's not).
			}
			
		}

	}	

}