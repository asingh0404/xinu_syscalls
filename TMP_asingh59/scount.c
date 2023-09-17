/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{

    int funcId = 10;

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

extern	struct	sentry	semaph[];

	if (isbadsem(sem) || semaph[sem].sstate==SFREE){

        if(trackFlag == 1 && startTrackFlag == 1)
        {
            unsigned long timeElapsed = ctr1000 - startTime;
            sysList[currpid][funcId].execTime += timeElapsed;
        }

		return(SYSERR);
    }

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(semaph[sem].semcnt);
}
