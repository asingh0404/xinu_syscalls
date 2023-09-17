/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>
/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	int funcId = 2;
	
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

	return(currpid);
}