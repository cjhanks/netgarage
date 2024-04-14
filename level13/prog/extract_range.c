#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


unsigned long
parse_address(const char* address) {
	return strtoul(address, NULL, 16);
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("%s start end command arg1 arg2 arg3...\n", argv[0]);
		return 1;
	}

	pid_t pid = fork();
	
	if (pid == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execv(argv[3], &argv[3]);
		printf("ERROR LAUNCHING PROGRAM\n");
		return -1;
	}

	// - These define the beginning and end range of relevance.
	unsigned long head = parse_address(argv[1]);
	unsigned long tail = parse_address(argv[2]);

	// - These store the data.
	unsigned char* stack_ptr = (unsigned char*)malloc(4096);

	unsigned long* index_ptr = (unsigned long*)malloc(1024 * sizeof(unsigned long));
	unsigned long* index_cur = index_ptr;

	bool trigger_enable = false;

	memset(stack_ptr, 0, 4096);
	memset(index_ptr, 0, 1024 * sizeof(unsigned long));

	int status;
	struct user_regs_struct regs = {};

	while (1) {
		wait(&status);
		if (WIFEXITED(status))
			break;

		ptrace(PTRACE_GETREGS, pid, NULL, &regs);

		if (regs.rip == head) { 
			trigger_enable = true;
			unsigned long i = 0;
			while (head + i < tail) {
				long elem = ptrace(
						PTRACE_PEEKTEXT, 
					        pid, 
					        regs.rip + i,
					        0);
				memcpy(stack_ptr + i, &elem, sizeof(elem));
				i += 4;
			}
		}
		
		if (regs.rip >= head && regs.rip <= tail && trigger_enable) {
			printf("%p %p\n", head, regs.rip);
			*(index_cur++) = regs.rip - head;
		}


            	ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
	}
	
	unsigned i = 0;
	while (index_ptr[i + 1] != 0) {
		unsigned this_head = index_ptr[i + 0];
		unsigned this_tail = index_ptr[i + 1];

		long delta = this_tail - this_head;
		if (delta > 32) {
			delta = 2;
		}
			

		for (unsigned j = 0; j < delta; ++j) {
			printf("%x", stack_ptr[this_head + j]);
		}
		printf("\n");

		i++;
	}

	return 0;
}
