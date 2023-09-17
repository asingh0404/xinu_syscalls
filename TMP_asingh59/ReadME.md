I have created a "lab0.h" file that declares the functions and data structures for all 3 parts

I ran the command: make depend && make && make run

For the main.c attached. I am getting the following output:

/*
Zfunction(0xaabbccdd) = 0xbbc00dff

void printprocstks(int priority)
Process [main]
        pid: 49
        priority: 20
        base: 0x00ffeff8
        limit: 0x00ffdffc
        len: 4096
        pointer: 0x00ffef90

void printsyscallsummary()
Process [pid: 48]
        Syscall: sys_freemem, count: 1, average execution time: 0 (ms)
        Syscall: sys_getpid, count: 1, average execution time: 0 (ms)
        Syscall: sys_kill, count: 1, average execution time: 0 (ms)
        Syscall: sys_send, count: 1, average execution time: 0 (ms)
        Syscall: sys_sleep, count: 1, average execution time: 5000 (ms)
        Syscall: sys_sleep10, count: 1, average execution time: 5000 (ms)
Process [pid: 49]
        Syscall: sys_resume, count: 1, average execution time: 0 (ms)
        Syscall: sys_sleep, count: 1, average execution time: 10000 (ms)
        Syscall: sys_sleep10, count: 1, average execution time: 10000 (ms)

*/