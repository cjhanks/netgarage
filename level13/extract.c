#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    pid_t pid;

    pid = fork();
    if(pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    }
    else {
        int status;
        struct user_regs_struct regs;

        // single stepping until it reached the real code segment
        while(1) {
            wait(&status);
            if(WIFEXITED(status))
                break;

            // get registers for the instruction pointer
            ptrace(PTRACE_GETREGS, pid, NULL, &regs);
	    //printf("eip = %lp\n", regs.rip);

            // strace ./bin
            // brk(0) = 0x804a000
            if(regs.rip==0x401106)
            {
                printf("in code section at EIP=%lx\n",regs.rip);
                unsigned int i;

                // Dump code
                for(i=0; i<0x1000; i+=4) {
                    long data = ptrace(PTRACE_PEEKTEXT, pid, regs.rip+i, 0);
                    printf("%lx",data);
                }
            }

            // single step in child process
            ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        }
    }
    return 0;
}
