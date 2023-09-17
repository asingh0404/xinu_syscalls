/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{

	int funcId = 13;

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

	short	*nxtdev;

	if (isbadpid(pid)){

	    if(trackFlag == 1 && startTrackFlag == 1)
    	{
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(OK);
}
