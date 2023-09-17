    .text
    .code32
    .globl zfunction

zfunction:

    pushl   %ebp
    movl    %esp,%ebp
    /* Push the value of EBP (EBP is the stack base pointer) onto the stack, 
    and then copy the value of ESP into EBP using the following instructions: */

    movl    8(%ebp),%eax   
    /* Move value of parameter 1 into EAX. */

    andl    $0xfffff00f,%eax 
    /* Clear the 20th to 27th bits by doing bitwise AND operation with 0xFFCFFFFF. */

    shl $8,%eax
    /* Shift left by 8 bits */

    orl $0x000000ff,%eax
    /* Fill the right-most 8 bits with 1s */

    /* Deallocate the local variable space*/
	movl    %ebp,%esp

    /* Restore the caller's base pointer value*/
	popl    %ebp

    /* Return the value of EAX register to the caller*/
	ret