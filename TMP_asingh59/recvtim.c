/* recvtim.c - recvtim */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  recvtim  -  wait to receive a message or timeout and return result
 *------------------------------------------------------------------------
 */
SYSCALL	recvtim(int maxwait)
{

    int funcId = 8;

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
	int	msg;

	if (maxwait<0 || clkruns == 0){
		
    	if(trackFlag == 1 && startTrackFlag == 1)
    	{
        	unsigned long timeElapsed = ctr1000 - startTime;
        	sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait		*/
	        insertd(currpid, clockq, maxwait*1000);
		slnempty = TRUE;
		sltop = (int *)&q[q[clockq].qnext].qkey;
	        pptr->pstate = PRTRECV;
		resched();
	}
	if ( pptr->phasmsg ) {
		msg = pptr->pmsg;	/* msg. arrived => retrieve it	*/
		pptr->phasmsg = FALSE;
	} else {			/* still no message => TIMEOUT	*/
		msg = TIMEOUT;
	}
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(msg);
}
