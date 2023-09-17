/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{

    int funcId = 9;

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
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);

		if(trackFlag == 1 && startTrackFlag == 1)
    	{
        	unsigned long timeElapsed = ctr1000 - startTime;
        	sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(prio);
}
