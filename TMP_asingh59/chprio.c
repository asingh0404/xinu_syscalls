/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{

	int funcId = 1;

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
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);

    	if(trackFlag == 1 && startTrackFlag == 1)
    	{
        	unsigned long timeElapsed = ctr1000 - startTime;
        	sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(newprio);
}
