/* signaln.c - signaln */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  signaln -- signal a semaphore n times
 *------------------------------------------------------------------------
 */
SYSCALL signaln(int sem, int count)
{

	int funcId = 17;

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
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE || count<=0) {
		restore(ps);
	
	    if(trackFlag == 1 && startTrackFlag == 1)
    	{
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	sptr = &semaph[sem];
	for (; count > 0  ; count--)
		if ((sptr->semcnt++) < 0)
			ready(getfirst(sptr->sqhead), RESCHNO);
	resched();
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(OK);
}
