/* test.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

/*------------------------------------------------------------------------
*  main  --  user main program
*------------------------------------------------------------------------
*/
int prX;
void halt();

prch(c)
char c;
{
    int i;
    sleep(5);
}

int main()
{

    long res = zfunction(0xaabbccdd);
	printf("\nZfunction(0xaabbccdd) = 0x%08x\n", res);

	printprocstks(2);
    
	syscallsummary_start();
	resume(prX = create(prch,2000,20,"proc A",1,'A'));	
	sleep(10);
	syscallsummary_stop();
	printsyscallsummary();

    return 0;

}
