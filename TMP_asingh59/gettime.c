/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <lab0.h>
#include <proc.h>

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */

        int funcId = 4;

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

        if(trackFlag == 1 && startTrackFlag == 1)
        {
                unsigned long timeElapsed = ctr1000 - startTime;
                sysList[currpid][funcId].execTime += timeElapsed;
        }

    return OK;
}
