/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{

	int funcId = 12;

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
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);

	    if(trackFlag == 1 && startTrackFlag == 1)
    	{
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(OK);
}
