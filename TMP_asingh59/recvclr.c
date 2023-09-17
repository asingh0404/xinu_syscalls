/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{

    int funcId = 7;

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
	WORD	msg;

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(msg);
}
