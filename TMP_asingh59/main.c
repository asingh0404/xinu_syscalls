/* test.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include "printprocstks.c"

/*------------------------------------------------------------------------
*  main  --  user main program
*------------------------------------------------------------------------
*/
int prX;

prch(c)
char c;
{
    int i;
    sleep(5);	
}

long zfunction(long param);

int main()
{

    long res = zfunction(0xaabbccdd);
	printf("\nZfunction(0xaabbccdd) = 0x%08x\n", res);
    
    resume(prX = create(prch,2000,40,"proc A",1,'A'));
    printprocstks(2);
    return 0;
}
