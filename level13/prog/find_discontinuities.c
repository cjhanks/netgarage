#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


unsigned 
get_gap_size() {
	const char* gap = getenv("GAP_SIZE");
	if (gap == NULL)
		return 1 << 28;
	else
		return atoi(gap);
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s command arg1 arg2 arg3...\n", argv[0]);
		return 1;
	}

	pid_t pid = fork();
	
	if (pid == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execv(argv[1], &argv[1]);
		printf("ERROR LAUNCHING PROGRAM\n");
		return -1;
	}

	// - Parent
	unsigned max_gap = get_gap_size();	
	int status;
	struct user_regs_struct last = {};
	struct user_regs_struct regs;

	while (1) {
		wait(&status);
		if (WIFEXITED(status))
			break;

		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		
		unsigned delta = abs(regs.rip - last.rip);
		if (delta >= max_gap) {
			printf("%10u: %p -> %p\n", delta, last.rip, regs.rip);
		}

		last = regs;
            	ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
	}

	return 0;
}
