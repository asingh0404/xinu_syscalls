/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep10(int n)
{

	int funcId = 19;

	unsigned long startTime, endTime;

	int startTrackFlag = 0;

	if(trackFlag==1)
	{
			sysList[currpid][funcId].sysCallName = __func__;
			sysList[currpid][funcId].pid = currpid;
			sysList[currpid][funcId].freq += 1;
			startTime = ctr1000;
			startTrackFlag = 1;
	}

	STATWORD ps;    
	if (n < 0  || clkruns==0){

	    if(trackFlag == 1 && startTrackFlag == 1)
    	{
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    	}

	    return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	
    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }
	return(OK);
}
