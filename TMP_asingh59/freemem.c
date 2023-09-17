/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <lab0.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{

	int funcId = 0;
	
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
	struct	mblock	*p, *q;
	unsigned top;

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end)){
		if(trackFlag == 1 && startTrackFlag == 1)
    	{
        	unsigned long timeElapsed = ctr1000 - startTime;
        	sysList[currpid][funcId].execTime += timeElapsed;
    	}
		return(SYSERR);
		}
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);

	    if(trackFlag == 1 && startTrackFlag == 1)
    	{
        	unsigned long timeElapsed = ctr1000 - startTime;
        	sysList[currpid][funcId].execTime += timeElapsed;
    	}

		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);

    if(trackFlag == 1 && startTrackFlag == 1)
    {
        unsigned long timeElapsed = ctr1000 - startTime;
        sysList[currpid][funcId].execTime += timeElapsed;
    }

	return(OK);
}
